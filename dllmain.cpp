#include "stdafx.h"
#include "CustomProtocolImpl.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_CSkinLoaderImpl, CCustomProtocolImpl)
END_OBJECT_MAP()

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

		g_hModule = hModule;
		DisableThreadLibraryCalls(hModule);

		CLSIDFromString(MODULE_GUID, &CLSID_CSkinLoaderImpl);
		_Module.Init(ObjectMap, hModule);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		_Module.Term();
		break;
	}
	return TRUE;
}

STDAPI DllCanUnloadNow(void)
{
	return (_Module.GetLockCount() == 0) ? S_OK : S_FALSE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

STDAPI DllRegisterServer(void)
{
	return _Module.RegisterServer(FALSE, &CLSID_CSkinLoaderImpl);
}
STDAPI DllUnregisterServer(void)
{
	return _Module.UnregisterServer(FALSE, &CLSID_CSkinLoaderImpl);
}