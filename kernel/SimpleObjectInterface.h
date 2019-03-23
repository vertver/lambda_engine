/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* Lambda Engine - Open-source Source comp. engine
* MIT-License
**********************************************************
* Module Name: Lambda Kernel
*********************************************************/
#pragma once
#include "head.h"

/*****************************************************
*	IObject - simple object, need for interface impl.
*	Functions:
*
*	Release() - release interface
*
*	AddRef() - create new reference interface with
*	current params
******************************************************/
class IObject
{
public:
	virtual void Release() = 0;
	virtual void AddRef(void*& pReference) = 0;
};

