/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* Lambda Engine - Open-source Source comp. engine
* MIT-License
**********************************************************
* Module Name: Lambda Kernel
*********************************************************/
#pragma once
#include "System_API.h"

typedef LONG(NTAPI *ProcFunc)(HANDLE);

class IWinProcess : public IProcess
{
	ExHandle Create(PROCESS_PROC& Args) override
	{
		DWORD dwThreadId = 0;
		ExHandle ThreadHandle = {};
		SHELLEXECUTEINFOW shellInfo = { };
		static WCHAR szPathToFile[MAX_PATH] = {};
		static WCHAR szArgs[MAX_PATH] = {};

		if (MultiByteToWideChar(CP_UTF8, 0, Args.PathToFile, strlen(Args.PathToFile), &szPathToFile[0], MAX_PATH * sizeof(WCHAR)) &&
			MultiByteToWideChar(CP_UTF8, 0, Args.pArgs, strlen(Args.pArgs), &szArgs[0], MAX_PATH * sizeof(WCHAR)))
		{
			shellInfo.cbSize = sizeof(SHELLEXECUTEINFOW);
			shellInfo.lpVerb = Args.bPriv ? L"runas" : nullptr;
			shellInfo.lpFile = szPathToFile;
			shellInfo.lpParameters = szArgs;
			shellInfo.nShow = SW_NORMAL;
			shellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;

			if (ShellExecuteExW(&shellInfo))
			{
				ThreadHandle.SetHandle(shellInfo.hProcess, PROCESS_HANDLE);
			}
		}

		return ThreadHandle;
	}

	ExHandle Open(DWORD dwId) override
	{
		ExHandle ThreadHandle = {};

		ThreadHandle.SetHandle(OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwId), PROCESS_HANDLE);
		return ThreadHandle;
	}

	DWORD GetId(ExHandle Handle) override
	{
		return GetProcessId(Handle.GetHandle());
	}

	void Suspend(ExHandle Handle) override
	{
		static ProcFunc pFunc = nullptr;

		if (!pFunc) 
		{ 
			pFunc = (ProcFunc)GetProcAddress(GetModuleHandleW(L"ntdll"), "NtSuspendProcess");
		}

		if (pFunc && !Handle.IsEmpty()) { pFunc(Handle.GetHandle()); }
	}

	void Resume(ExHandle Handle) override
	{
		static ProcFunc pFunc = nullptr;

		if (!pFunc)
		{
			pFunc = (ProcFunc)GetProcAddress(GetModuleHandleW(L"ntdll"), "NtResumeProcess");
		}

		if (pFunc && !Handle.IsEmpty()) { pFunc(Handle.GetHandle()); }
	}

	void Terminate(ExHandle Handle) override
	{
		TerminateProcess(Handle.GetHandle(), 0x0);
	}

	void Release() override
	{
		delete this;
	}

	void AddRef(void*& pReference) override
	{

	}
};