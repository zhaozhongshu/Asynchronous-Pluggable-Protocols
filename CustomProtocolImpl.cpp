#include "stdafx.h"
#include "CustomProtocolImpl.h"

CCustomProtocolImpl::CCustomProtocolImpl()
{
}

CCustomProtocolImpl::~CCustomProtocolImpl()
{
}

HRESULT WINAPI CCustomProtocolImpl::UpdateRegistry(BOOL bRegister) throw()
{
	HRESULT hr = S_OK;
	if (bRegister)
	{
		WCHAR wszModule[MAX_PATH] = { 0 };
		GetModuleFileName(g_hModule, wszModule, MAX_PATH);
		DWORD len = wcslen(wszModule) * 2 + 2;
		hr = SHSetValue(HKEY_CLASSES_ROOT, L"CLSID\\" MODULE_GUID L"\\InprocServer32", L"", REG_SZ, wszModule, len);
		
		LPCWSTR Model = L"Apartment";
		len = wcslen(Model) * 2 + 2;
		hr = SHSetValue(HKEY_CLASSES_ROOT, L"CLSID\\" MODULE_GUID L"\\InprocServer32", L"ThreadingModel", REG_SZ, Model, len);
		
		len = wcslen(MODULE_GUID) * 2 + 2;
		hr = SHSetValue(HKEY_CLASSES_ROOT, L"PROTOCOLS\\Handler\\" CUSTOM_PROTOCOL, L"CLSID", REG_SZ, MODULE_GUID, len);
	}
	else
	{
		hr = SHDeleteKey(HKEY_CLASSES_ROOT, L"CLSID\\" MODULE_GUID);
		hr = SHDeleteKey(HKEY_CLASSES_ROOT, L"PROTOCOLS\\Handler\\" CUSTOM_PROTOCOL);
	}
	return S_OK;
}


STDMETHODIMP CCustomProtocolImpl::Start(LPCWSTR szUrl, IInternetProtocolSink *pOIProtSink, IInternetBindInfo *pOIBindInfo, DWORD grfPI, HANDLE_PTR res)
{
	m_Buffer = "<p>hello world</p>";
	pOIProtSink->ReportData(BSCF_LASTDATANOTIFICATION | BSCF_DATAFULLYAVAILABLE, m_Buffer.size(), m_Buffer.size());
	pOIProtSink->ReportResult(S_OK, 0, 0);
	return S_OK;
	//return INET_E_USE_DEFAULT_PROTOCOLHANDLER;
}
STDMETHODIMP CCustomProtocolImpl::Continue(PROTOCOLDATA *pProtocolData)
{
	return S_OK;
}
STDMETHODIMP CCustomProtocolImpl::Abort(HRESULT hrReason, DWORD dwOptions)
{
	return E_NOTIMPL;
}
STDMETHODIMP CCustomProtocolImpl::Terminate(DWORD dwOptions)
{
	return  S_OK;
}
STDMETHODIMP CCustomProtocolImpl::Suspend()
{
	return E_NOTIMPL;
}

STDMETHODIMP CCustomProtocolImpl::Resume()
{
	return E_NOTIMPL;
}
STDMETHODIMP CCustomProtocolImpl::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *newpos)
{
	return E_NOTIMPL;
}

STDMETHODIMP CCustomProtocolImpl::LockRequest(DWORD dwOptions)
{
	return S_OK;
}

STDMETHODIMP CCustomProtocolImpl::UnlockRequest()
{
	return S_OK;
}
STDMETHODIMP CCustomProtocolImpl::Read(void *pv, ULONG cb, ULONG *pcbRead)
{
	_try
	{
		if (cb > m_Buffer.size() && pv && !m_Buffer.empty())
		{
			memcpy(pv, m_Buffer.c_str(), m_Buffer.size());
			*pcbRead = m_Buffer.size();
			m_Buffer.clear();
		}
		else
		{
			*pcbRead = 0;
		}
	}
	_except(EXCEPTION_EXECUTE_HANDLER)
	{
	}
	return S_FALSE;	//indicate all data downloaded
}