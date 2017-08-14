// *********************************************************************** //
//
// MODULE  : linux_ltlibraryloader.cpp
//
// PURPOSE : Linux implementation of LTLibraryLoader.
//
// CREATED : 05/21/04
//
// (c) 2004 Monolith Productions, Inc.  All Rights Reserved
//
// *********************************************************************** //

#include <iostream>
#include <dlfcn.h>
#include <linux/stddef.h>
#include "syslibraryloader.h"

HLTMODULE LTLibraryLoader::OpenLibrary(const char* pSoName)
{
	HLTMODULE handle = ::dlopen(pSoName, RTLD_NOW);
	
	if (handle == nullptr)
	{
		 std::cout << "Failed loading module '" << pSoName << "': " << ::dlerror() << '\n';
	}
	
	return handle;
}

void LTLibraryLoader::CloseLibrary(const HLTMODULE hModule)
{
	::dlclose((void*)hModule);
}

bool LTLibraryLoader::IsLibraryLoaded(const char* pFileName)
{
	void* hModule = ::dlopen(pFileName, RTLD_NOLOAD);

	return !!hModule;
}

HLTMODULE LTLibraryLoader::GetLibraryHandle(const char* pFileName)
{
	return ::dlopen(pFileName, RTLD_NOLOAD);
}

HLTMODULE LTLibraryLoader::GetMainHandle()
{
	return ::dlopen(NULL, 0);
}

HLTPROC LTLibraryLoader::GetProcAddress(HLTMODULE hModule, const char* pProcName)
{
	return ::dlsym(hModule, pProcName);
}
