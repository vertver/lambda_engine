/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* Lambda Engine - Open-source Source comp. engine
* MIT-License
**********************************************************
* Module Name: Lambda Kernel
*********************************************************/
#pragma once
#include "System_API.h"

class IWinThread : public IThread
{
	ExHandle Create(THREAD_PROC& Args) override
	{
		ExHandle ThreadHandle = {};
		DWORD dwThreadId = 0;
		
		ThreadHandle.SetHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Args.pFunc, Args.pArg, 0, &dwThreadId), THREAD_HANDLE);
		return ThreadHandle;
	}

	ExHandle Open(DWORD dwId) override
	{
		ExHandle ThreadHandle = {};

		ThreadHandle.SetHandle(OpenThread(THREAD_ALL_ACCESS, FALSE, dwId), THREAD_HANDLE);
		return ThreadHandle;
	}

	DWORD GetId(ExHandle Handle) override 
	{
		return GetThreadId(Handle.GetHandle());
	}

	void Suspend(ExHandle Handle) override
	{
		SuspendThread(Handle.GetHandle());
	}

	void Resume(ExHandle Handle) override
	{
		ResumeThread(Handle.GetHandle());
	}

	void Terminate(ExHandle Handle) override
	{
		TerminateThread(Handle.GetHandle(), 0x0);
	}

	void Release() override
	{
		delete this;
	}

	void AddRef(void*& pReference) override
	{

	}
};