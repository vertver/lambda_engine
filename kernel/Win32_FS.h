/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* Lambda Engine - Open-source Source comp. engine
* MIT-License
**********************************************************
* Module Name: Lambda Kernel
*********************************************************/
#pragma once
#include "System_API.h"

class IWinFileSystem : public IFileSystem
{
public:
	IWinFileSystem() {};
	IWinFileSystem(ExHandle NewHandle)
	{
		NewHandle.Duplicate(CurrentHandle);
	}

	bool OpenFile(char* PathToFile) override
	{
		WCHAR szPath[MAX_PATH] = {};
		DWORD OutSizeword = 0;
		LARGE_INTEGER largeCount = {};
		size_t uSize = 0;

		if (!CurrentHandle.IsEmpty())
		{
			CurrentHandle.Close();
		}

		if (MultiByteToWideChar(CP_UTF8, 0, PathToFile, strlen(PathToFile), szPath, sizeof(szPath)))
		{
			// open handle and read audio file to buffer
			CurrentHandle.SetHandle(CreateFileW(szPath, GENERIC_READ, NULL, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr), FILE_HANDLE);
			CurrentHandle.SetPath(PathToFile);
		}

		return !CurrentHandle.IsEmpty();
	}

	bool SyncRead(void*& pBuf, size_t& OutSize) override
	{
		DWORD size = 0;
		void* handle = nullptr;
		bool ret = false;
		LARGE_INTEGER largeInt = {};

		if (CurrentHandle.IsEmpty()) { return false; }
		handle = CurrentHandle.GetHandle();
		GetFileSizeEx(handle, &largeInt);
		pBuf = FastAlloc(largeInt.QuadPart);

		ret = !!ReadFile(handle, pBuf, largeInt.QuadPart, &size, nullptr);
		OutSize = size;

		return ret;
	}

	bool AsyncRead(void*& pBuf, size_t Size) override
	{
		DWORD size = 0;
		if (CurrentHandle.IsEmpty()) { return false; }

		pBuf = FastAlloc(Size);

		return !!ReadFile(CurrentHandle.GetHandle(), pBuf, Size, &size, nullptr);
	}

	bool WriteNewFile(char* PathToFile, void* pBuf, size_t Size) override
	{
		WCHAR szPath[MAX_PATH * 2] = {};
		bool ret = false;
		DWORD size = 0;

		if (!CurrentHandle.IsEmpty())
		{
			CurrentHandle.Close();
		}

		if (MultiByteToWideChar(CP_UTF8, 0, PathToFile, strlen(PathToFile), szPath, sizeof(szPath)))
		{
			CurrentHandle.SetHandle(CreateFileW(szPath, GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL), FIND_HANDLE);
			CurrentHandle.SetPath(PathToFile);
		}

		if (!(ret = WriteFile(CurrentHandle.GetHandle(), pBuf, Size, &size, nullptr)) && !CurrentHandle.IsEmpty())
		{
			CurrentHandle.Close();
		}

		return ret;
	}

	bool AsyncWrite(void* pBuf, size_t Size) override
	{
		DWORD size = 0;
		if (!CurrentHandle.IsEmpty()) { return false; }

		return !!WriteFile(CurrentHandle.GetHandle(), pBuf, Size, &size, nullptr);
	}

	bool SyncWrite(void* pBuf, size_t Size) override
	{
		return AsyncWrite(pBuf, Size);
	}

	bool IsFileExist(char* PathToFile) override
	{
		// check for existing file
		bool bDir = false;
		WCHAR szPath[MAX_PATH * 2] = {};
		WIN32_FIND_DATAW findData = { 0 };
		HANDLE hFind = nullptr;
		DWORD DataFile = 0;

		if (MultiByteToWideChar(CP_UTF8, 0, PathToFile, strlen(PathToFile), szPath, sizeof(szPath)))
		{
			hFind = FindFirstFileW(szPath, &findData);

			// if file doesn't exist
			if (!hFind || hFind == INVALID_HANDLE_VALUE)
			{
				SetLastError(0);		// no error. That's OK
			}
			else
			{
				// check for dir
				bDir = ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0);

				FindClose(hFind);
				return !bDir;
			}
		}

		return false;
	}

	bool GetFileType(FILE_TYPE& fileType) override
	{
		int TypeSize = 0;
		char* StringUTF8 = {};
		WCHAR szPath[MAX_PATH * 2] = {};
		LPCWSTR szTypes[] = {
		L"mp3", L"MP3", L"wav", L"WAV", L"flac", L"FLAC", L"aiff", L"AIFF", L"ogg", L"OGG", L"opus", L"OPUS", L"alac", L"ALAC", L"aac", L"AAC", L"m4a", L"M4A", L"raw", L"RAW", L"dll", L"DLL" };

		CurrentHandle.GetPath(StringUTF8);

		if (MultiByteToWideChar(CP_UTF8, 0, StringUTF8, strlen(StringUTF8), szPath, sizeof(szPath)))
		{
			for (size_t i = wcslen(szPath); i > 0; i--)
			{
				WCHAR cbSymbol = szPath[i];

				if (cbSymbol == L'.') { break; }

				TypeSize++;
			}

			if (TypeSize)
			{
				for (size_t i = 0; i < 22; i++)
				{
					LPCWSTR CurrentType = szTypes[i];
					LPCWSTR FileType = (szPath + wcslen(szPath) - (TypeSize - 1));
					if (!wcscmp(CurrentType, FileType))
					{
						switch (i)
						{
						case 0:
						case 1:
							return MP3_TYPE;
						case 2:
						case 3:
							return WAV_TYPE;
						case 4:
						case 5:
							return FLAC_TYPE;
						case 6:
						case 7:
							return AIFF_TYPE;
						case 8:
						case 9:
							return AIFF_TYPE;
						case 10:
						case 11:
							return OGG_TYPE;
						case 12:
						case 13:
							return OPUS_TYPE;
						case 14:
						case 15:
							return ALAC_TYPE;
						case 16:
						case 17:
							return AAC_TYPE;
						case 18:
						case 19:
							return AAC_TYPE;
						case 20:
						case 21:
							return RAW_TYPE;
						break;
						default:
							return UNKNOWN_TYPE;
							break;
						}
					}
				}
			}
		}
	}

	bool CloseAll() override
	{
		CurrentHandle.Close();
	}

	void AddRef(void*& pReference) override
	{
		pReference = new IWinFileSystem(CurrentHandle);
	}

	void Release() override
	{
		CloseAll();
		delete this;
	}
};
