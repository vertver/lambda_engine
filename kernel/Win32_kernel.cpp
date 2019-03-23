/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* Lambda Engine - Open-source Source comp. engine
* MIT-License
**********************************************************
* Module Name: Lambda Kernel
*********************************************************/
#include "System_API.h"

HANDLE hHeap = nullptr;
WCHAR szArg[MAX_PATH] = {};
ISystemInterface* pSystem = nullptr;

HANDLE
WINAPI
GetKernelHeap()
{
	return hHeap;
}

VOID
WINAPI
StartApplication(LPCWSTR lpArgs)
{
	size_t HeapInfo = 2;

	// create heap with "enable execute code" flag
	if (!(hHeap = HeapCreate(0, 0x010000, 0))) { return; }

	// set low fragmentation heap for XP and Win2003 Server
	HeapSetInformation(hHeap, HeapCompatibilityInformation, &HeapInfo, sizeof(size_t));

	memcpy(szArg, lpArgs, wcslen(lpArgs) * 2);
}
  
