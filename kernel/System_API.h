/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* Lambda Engine - Open-source Source comp. engine
* MIT-License
**********************************************************
* Module Name: Lambda Kernel
*********************************************************/
#pragma once
#include "SimpleObjectInterface.h"
#include <wininet.h>
#include <vector>

#ifdef WIN32
#pragma comment(lib, "Wininet.lib")
#endif

enum FeaturesEnum
{
	COM_TECHNOLOGY = 0,
	MULTI_MONITOR
};

enum HandleType
{
	FILE_HANDLE = 0,
	INTERNET_HANDLE,
	PROCESSFIND_HANDLE,
	FIND_HANDLE,
	PROCESS_HANDLE,
	THREAD_HANDLE,
	REG_KEY,
	EVENT_HANDLE,
	WINDOW_HANDLE,
	UNKNOWN
};

typedef enum
{
	AAC_TYPE,
	AIFF_TYPE,
	ALAC_TYPE,
	MP3_TYPE,
	FLAC_TYPE,
	OGG_TYPE,
	OPUS_TYPE,
	WMA_TYPE,
	WAV_TYPE,
	RAW_TYPE,
	UNKNOWN_TYPE
} FILE_TYPE;

#define VIRTUAL_MEMORY_ALLOC	0xFF00FF00
#define HEAP_MEMORY_ALLOC		0x00FF00FF
#define MAPPED_MEMORY_ALLOC		0xF0F0F0F0

#ifndef WINAPI
#define WINAPI 
#endif

#include "LVectors.h"

void WINAPI StartApplication(LPCWSTR lpArgs);
HANDLE WINAPI GetKernelHeap();

template
<class T>
inline
T*
AllocateClass()
{
	return new T;
}

#ifdef WIN32
template
<typename T>
__forceinline
T*
AllocatePointer()
{
	return (T*)HeapAlloc(GetKernelHeap(), HEAP_ZERO_MEMORY, sizeof(T));
}

template
<typename T, SIZE_T Size>
__forceinline
T*
AllocatePointer()
{
	ASSERT2(Size, L"Can't alloc file with 0 size");
	return (T*)HeapAlloc(GetKernelHeap(), HEAP_ZERO_MEMORY, Size);
}

template
<typename T, SIZE_T Size>
__forceinline
T*
AllocateFile()
{
	ASSERT2(Size, L"Can't alloc file with 0 size");
	return (T*)VirtualAlloc(NULL, Size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

__forceinline
LPVOID
FastAlloc(
	SIZE_T uSize
)
{
	return HeapAlloc(GetKernelHeap(), HEAP_ZERO_MEMORY, uSize);
}

__forceinline
LPVOID
MapFile(
	SIZE_T PointerSize,
	LPCWSTR lpSharedMemoryName
)
{
	LPVOID lpSharedMemory = nullptr;

	// create file mapping at paging file
	HANDLE hSharedMemory = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, NULL, (DWORD)PointerSize, lpSharedMemoryName);
	lpSharedMemory = MapViewOfFile(hSharedMemory, FILE_MAP_ALL_ACCESS, NULL, NULL, PointerSize);

	return lpSharedMemory;
}

__forceinline
LPVOID
MapFile(
	SIZE_T PointerSize,
	LPCWSTR lpSharedMemoryName,
	HANDLE FileHandle
)
{
	LPVOID lpSharedMemory = nullptr;

	// create file mapping at paging file
	HANDLE hSharedMemory = CreateFileMappingW(FileHandle, NULL, PAGE_READONLY, NULL, (DWORD)PointerSize, lpSharedMemoryName);
	lpSharedMemory = MapViewOfFile(hSharedMemory, FILE_MAP_ALL_ACCESS, NULL, NULL, PointerSize);

	return lpSharedMemory;
}

/***********************************************************
* WINDOWS FUNCTION
* dwType reference:
* MAPPED_MEMORY_ALLOC - pointer from mapped pagefile memory
* HEAP_MEMORY_ALLOC - pointer from kernel heap
* VIRTUAL_MEMORY_ALLOC - pointer from mapped memory
* NULL - pointer from process heap
************************************************************/
__forceinline
LPVOID
AdvanceAlloc(
	SIZE_T PointerSize,
	DWORD dwType
)
{
	LPVOID pRet = nullptr;

	switch (dwType)
	{
	case MAPPED_MEMORY_ALLOC:
		pRet = MapFile(PointerSize, NULL);
		break;
	case VIRTUAL_MEMORY_ALLOC:
		pRet = VirtualAlloc(NULL, PointerSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		break;
	case HEAP_MEMORY_ALLOC:
		pRet = HeapAlloc(GetKernelHeap(), HEAP_ZERO_MEMORY, PointerSize);
		break;
	case NULL:
		pRet = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, PointerSize);
		break;
	}

	return pRet;
}

__forceinline
VOID
FreePointer(
	LPVOID pPointer,
	SIZE_T PointerSize,
	DWORD dwType
)
{
	switch (dwType)
	{
	case MAPPED_MEMORY_ALLOC:
		if (pPointer) { UnmapViewOfFile(pPointer); }
		pPointer = nullptr;
		break;
	case VIRTUAL_MEMORY_ALLOC:
		if (pPointer) { VirtualFree(pPointer, PointerSize, MEM_RELEASE | MEM_DECOMMIT); }
		pPointer = nullptr;
		break;
	case HEAP_MEMORY_ALLOC:
		if (pPointer) { HeapFree(GetKernelHeap(), NULL, pPointer); }
		pPointer = nullptr;
		break;
	case NULL:
		if (pPointer) { HeapFree(GetProcessHeap(), NULL, pPointer); }
		pPointer = nullptr;
		break;
	default:
		break;
	}
}

// DEPRECATED
__forceinline
VOID
UnloadFile(
	LPVOID pFile
)
{
	if (!HeapFree(GetKernelHeap(), NULL, pFile)) return;
	pFile = nullptr;
}

#else
template
<typename T>
inline
T*
AllocatePointer()
{
	return (T*)malloc(sizeof(T));
}

template
<typename T, size_t Size>
inline
T*
AllocatePointer()
{
	return (T*)malloc(Size);
}

template
<typename T, size_t Size>
inline
T*
AllocateFile()
{
	// map pointer by POSIX mapping
	void* pFile = mmap(NULL, Size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	// map fixed pointer 
	pFile = mmap(pFile, Size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);

	// protect mapped memory for R/W only
	mprotect(pFile, Size, PROT_READ | PROT_WRITE);
	return pFile;
}

inline
void*
FastAlloc(
	size_t uSize
)
{
	return malloc(uSize);
}

/***********************************************************
* POSIX FUNCTION
* dwType reference:
* HEAP_MEMORY_ALLOC & NULL - pointer from kernel heap
* VIRTUAL_MEMORY_ALLOC & MAPPED_MEMORY_ALLOC -
* pointer from mapped memory
*
* #NOTE: for free pointer in POSIX systems, we must know
* the size of it, because system doesn't know about it.
************************************************************/
inline
void*
AdvanceAlloc(
	size_t PointerSize,
	unsigned long  dwType
)
{
	void* pRet = nullptr;

	switch (dwType)
	{
	case VIRTUAL_MEMORY_ALLOC:
	case MAPPED_MEMORY_ALLOC:
		// map pointer by POSIX mapping
		pRet = mmap(NULL, PointerSize, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

		// map fixed pointer 
		pRet = mmap(pRet, PointerSize, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);

		// protect mapped memory for R/W only
		mprotect(pRet, PointerSize, PROT_READ | PROT_WRITE);
		break;
	case HEAP_MEMORY_ALLOC:
	case NULL:
		pRet = malloc(PointerSize);
		break;
	}

	return pRet;
}

inline
void*
MapFile(
	size_t PointerSize
)
{
	return AdvanceAlloc(PointerSize, MAPPED_MEMORY_ALLOC);
}

inline
void
FreePointer(
	void* pPointer,
	size_t PointerSize,
	unsigned long dwType
)
{
	switch (dwType)
	{
	case VIRTUAL_MEMORY_ALLOC:
	case MAPPED_MEMORY_ALLOC:
		// free paged memory by POSIX
		if (pPointer)
		{
			mprotect(pPointer, pointerSize, PROT_NONE);
			munmap(pPointer, pointerSize);
		}
		pPointer = nullptr;
		break;
	case HEAP_MEMORY_ALLOC:
	case NULL:
		if (pPointer)
		{
			free(pPointer);
		}
		pPointer = nullptr;
		break;
	default:
		break;
	}
}

inline
void
UnloadFile(
	void* pFile
)
{
	// #NOTE: it's must be allocated by malloc
	if (pFile)
	{
		free(pFile);
		pFile = nullptr;
	}
}
#endif

#define FREEPROCESSHEAP(Pointer)		if (Pointer) { FreePointer(Pointer, NULL, NULL);					Pointer = nullptr; }
#define FREEKERNELHEAP(Pointer)			if (Pointer) { FreePointer(Pointer, NULL, HEAP_MEMORY_ALLOC);		Pointer = nullptr; }
#define FREEVIRTUALMEM(Pointer, Size)	if (Pointer) { FreePointer(Pointer, Size, VIRTUAL_MEMORY_ALLOC);	Pointer = nullptr; }
#define FREEMAPPEDMEM(Pointer, Size)	if (Pointer) { FreePointer(Pointer, Size, MAPPED_MEMORY_ALLOC);		Pointer = nullptr; }		// in windows set Size to NULL

/*****************************************************
*	ExHandle - Extreme Handle class
*	Functions:
*
*	IsEmpty() - check for handle pointer
*	GetHandle() - get pointer to handle
*	SetHandle() - set handle pointer 
*	Duplicate() - duplicate current handle
*	Close() - close this shit now
******************************************************/
class ExHandle
{
public:
	ExHandle(void* pHandle, HandleType hTp)
	{
		SetHandle(pHandle, hTp);
	}

	ExHandle() : ThisHandle(nullptr), hType(UNKNOWN) {}

	bool IsEmpty()
	{
#ifdef WIN32
		return (!ThisHandle || ThisHandle == INVALID_HANDLE_VALUE);
#else
		return (!ThisHandle);
#endif
	}

	void* GetHandle() { return ThisHandle; }
	void SetHandle(void* pHandle, HandleType ht) { ThisHandle = pHandle; hType = ht; }
	void GetHandleType(HandleType& Type) { Type = hType; }

	void Duplicate(ExHandle& NewHandle)
	{
#ifdef WIN32
		if (!DuplicateHandle(GetCurrentProcess(), ThisHandle, GetCurrentProcess(), &NewHandle.ThisHandle, 0, TRUE, DUPLICATE_SAME_ACCESS))
#endif
			NewHandle.SetHandle(ThisHandle, hType);
	}

	void Close() 
	{ 
		if (!IsEmpty())
		{
#ifdef WIN32
			// if we can't close handle - do nothing
			__try
			{
				switch (hType)
				{
				case FIND_HANDLE:
					FindClose(ThisHandle);
					break;
				case INTERNET_HANDLE:
					InternetCloseHandle(ThisHandle);
					break;
				case REG_KEY:
					RegCloseKey((HKEY)ThisHandle);
					break;
				case WINDOW_HANDLE:
					DestroyWindow((HWND)ThisHandle);
				case PROCESS_HANDLE:
				case THREAD_HANDLE:
				case PROCESSFIND_HANDLE:
				case EVENT_HANDLE:
				default:
				case FILE_HANDLE:
					CloseHandle(ThisHandle);
					break;
				}
			}
			__except (EXCEPTION_CONTINUE_EXECUTION)
			{
				OutputDebugStringW(L"! Can't close handle. \n");
#ifdef DEBUG
				DebugBreak();
#endif
			}
#endif
		}
	}	

	~ExHandle() { Close(); }

private:
	HandleType hType;
	void* ThisHandle;
};

/*****************************************************
*	ExEvent - Extreme Event class
*	Functions:
*
*	Create() - create event
*	Raise() - set event
*	Reset() - reset event
*	Wait() - wait event signal 
*	IsTriggered() - check if event is triggered
******************************************************/
class ExEvent : public ExHandle
{
	bool Create()
	{
#ifdef WIN32
		SetHandle(CreateEventW(nullptr, TRUE, FALSE, nullptr), EVENT_HANDLE);
#endif
		return !!GetHandle();
	}

	bool Raise()
	{
#ifdef WIN32
		return !!SetEvent(GetHandle());
#endif
	}

	bool Reset()
	{
#ifdef WIN32
		return !!ResetEvent(GetHandle());
#endif
	}

	bool Wait(DWORD dwTime)
	{
#ifdef WIN32
		return !!WaitForSingleObject(GetHandle(), dwTime);
#endif
	}

	bool IsTriggered()
	{
#ifdef WIN32
		// WAIT_OBJECT_0 signaled
		return !WaitForSingleObject(GetHandle(), 0);
#endif
	}
};

class ExFile : public ExHandle
{
public:
#ifdef WIN32
	ExFile(LPCWSTR lpString)
	{
		if (!WideCharToMultiByte(CP_UTF8, 0, lpString, wcslen(lpString), PathFile, sizeof(PathFile), nullptr, nullptr))
		{
			return;
		}
	}
#endif

	ExFile()
	{
		memset(PathFile, 0, sizeof(PathFile));
	}

	void GetPath(char*& String)
	{
		String = PathFile;
	}

	void SetPath(char* String)
	{
		memset(PathFile, 0, sizeof(PathFile));
		memcpy(PathFile, String, strlen(String));
	}

	void Flush()
	{
#ifdef WIN32
		FlushFileBuffers(GetHandle());
#else
		flush(GetHandle());
#endif
	}

private:
	STRING512 PathFile;
};

struct THREAD_PROC
{
	void* pFunc;
	void* pArg;
	char ThreadName[64];
};

struct PROCESS_PROC
{
	char* pArgs;
	char* PathToFile;
	bool bPriv;
};

template
<typename T>
class ISysObject : public IObject
{
public:
	virtual ExHandle Create(T& Args) = 0;
	virtual ExHandle Open(DWORD dwId) = 0;
	virtual DWORD GetId(ExHandle Handle) = 0;
	virtual void Suspend(ExHandle Handle) = 0;
	virtual void Resume(ExHandle Handle) = 0;
	virtual void Terminate(ExHandle Handle) = 0;
};

class IThread : public ISysObject<THREAD_PROC>
{

};

class IProcess : public ISysObject<PROCESS_PROC>
{

};

/*****************************************************
*	LRect - Lambda rect class
*	Functions:
*
*	GetThisRect() - get rect from vector
*	SetThisRect() - set value to vector
*	GetWinRect() - (inline) get win rect from vector
*	SetWinRect() - (inline) set value to vector from RECT struct
*
*	Description:
*	
*	ThisVector[0] - left value
*	ThisVector[1] - top value
*	ThisVector[2] - right value
*	ThisVector[3] - bottom value
******************************************************/
class LRect : public LI64Vector4
{
	LRect& GetThisRect()
	{
		return *this;
	}

	void SetThisRect(i64 _left, i64 _top, i64 _right, i64 _bottom)
	{
		ThisVector[0] = _left;
		ThisVector[1] = _top;
		ThisVector[2] = _right;
		ThisVector[3] = _bottom;
	}

#ifdef WIN32	
	__forceinline RECT GetWinRect()
	{
		RECT rec	= {};
		rec.left	= ThisVector[0];
		rec.top		= ThisVector[1];
		rec.right	= ThisVector[2];
		rec.bottom	= ThisVector[3];

		return rec;
	}

	__forceinline void SetWinRect(RECT rec)
	{
		ThisVector[0] = rec.left;
		ThisVector[1] = rec.top;
		ThisVector[2] = rec.right;
		ThisVector[3] = rec.bottom;
	}
#endif
};

struct MONITOR_INFO
{
	LRect rect;
	STRING128 MonitorName;
	u32 MonitorNumber;
};

using MonitorVector = std::vector<MONITOR_INFO>;

class IWindow : public IObject
{
public:
	virtual void GetNumberOfMonitors(u32& Count) = 0;
	virtual void GetMonitors(MonitorVector& pMonitors, size_t& MonitorsCount) = 0;
	virtual void GetWindowHandle(ExHandle& Handle) = 0;
	virtual void GetAPICaps(STRING64& Name) = 0;
	virtual void GetDriverVersion(STRING128& OutString) = 0;
	virtual void GetGPUVendorName(STRING64& Vendor) = 0;
	virtual void SetWindowHandle(ExHandle Handle) = 0;
	virtual void SetToMonitor(u32 Number) = 0;
	virtual void SetWinPos(LRect rect) = 0;
	virtual void TerminateWindow() = 0;

	ExHandle WindowHandle;
};

class ISystemInterface : public IObject
{
public:
	virtual bool InitSystem(char* pCmd) = 0;
	virtual bool DestroySystem() = 0;
	virtual bool GetSystemName(STRING64& String) = 0;
	virtual bool GetThisUserName(STRING128& String) = 0;
	virtual bool GetLaunchPath(STRING512& String) = 0;
	virtual bool GetCmd(char**& pString) = 0;
	virtual bool IsInstanceExist() = 0;
	virtual bool IsFeatureSupported(FeaturesEnum Feature) = 0;

	IThread* pThread;
	IProcess* pProcess;
	IWindow* pProcessWindow;
};
  
class IFileSystem : public IObject
{
public:
	virtual bool OpenFile(char* PathToFile) = 0;
	virtual bool SyncRead(void*& pBuf, size_t& OutSize) = 0;
	virtual bool AsyncRead(void*& pBuf, size_t Size) = 0;
	virtual bool WriteNewFile(char* PathToFile, void* pBuf, size_t Size) = 0;
	virtual bool AsyncWrite(void* pBuf, size_t Size) = 0;
	virtual bool SyncWrite(void* pBuf, size_t Size) = 0;
	virtual bool IsFileExist(char* PathToFile) = 0;
	virtual bool GetFileType(FILE_TYPE& fileType) = 0;
	virtual bool CloseAll() = 0;

	ExFile CurrentHandle;
};

class ISteamInterface : public IObject
{
public:
};