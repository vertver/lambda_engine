/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* Lambda Engine - Open-source Source comp. engine
* MIT-License
**********************************************************
* Module Name: Lambda Kernel
*********************************************************/
#pragma once
#include "SimpleObjectInterface.h"
#include "System_API.h"
#include "Win32_Processes.h"
#include "Win32_Threads.h"
#include "Win32_Steam.h"
#include "Win32_FS.h"

class IRegValue : public IObject
{
	bool is_val(int KeyBranch, char* KeyPath, char* KeyName);
	bool valcmp(int KeyBranch, char* KeyPath, char* KeyName, void* KeyValue, size_t KeyValueSize);
	bool valset(int KeyBranch, char* KeyPath, char* KeyName, void* KeyValue, size_t KeyValueSize);
	bool valget(int KeyBranch, char* KeyPath, char* KeyName, void*& KeyValue, size_t& KeyValueSize);
};

class IWinSystem : public ISystemInterface
{
	IWinSystem()
	{
		pThread = new IWinThread();
		pProcess = new IWinProcess();
		lpArgs = nullptr;
	}

	IWinSystem(LPWSTR pArgs)
	{
		pThread = new IWinThread();
		pProcess = new IWinProcess();
		lpArgs = pArgs;
	}

	bool InitSystem(char* pCmd) override
	{

	}

	bool DestroySystem() override
	{

	}

	bool GetSystemName(STRING64& pString) override
	{

	}

	bool GetThisUserName(STRING128& pString) override
	{

	}

	bool GetLaunchPath(STRING512& pString) override
	{

	}

	bool GetCmd(char**& pString) override
	{

	}

	bool IsInstanceExist() override
	{

	}

	bool IsFeatureSupported(FeaturesEnum Feature) override
	{
		switch (Feature)
		{
		case COM_TECHNOLOGY:
			return true;
		case MULTI_MONITOR:

		default:
			break;
		}
	}

	void Release() override
	{
	}

	void AddRef(void*& pReference) override
	{

	}


	LPWSTR lpArgs;
};