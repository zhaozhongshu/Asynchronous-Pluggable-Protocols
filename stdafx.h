
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             
#include <windows.h>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      
#include <atlbase.h>
#include <atlstr.h>
#include <atlcom.h>
#include <shlobj.h>

__declspec(selectany) GUID		CLSID_CSkinLoaderImpl;
__declspec(selectany) HMODULE	g_hModule;

#define MODULE_GUID		L"{AC36EB56-1524-4F42-AF72-C1EF6646B6E0}"
#define CUSTOM_PROTOCOL	L"custom"

