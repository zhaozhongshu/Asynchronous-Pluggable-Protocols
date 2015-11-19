#pragma once
#include <atldef.h>
#include <string>

class ATL_NO_VTABLE CCustomProtocolImpl:
	public IInternetProtocol,
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCustomProtocolImpl, &CLSID_CSkinLoaderImpl>
{
protected:
	std::string	m_Buffer;
public:
	CCustomProtocolImpl();
	~CCustomProtocolImpl();

	static BOOL Init();
	static HRESULT WINAPI UpdateRegistry(BOOL bRegister) throw();

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CCustomProtocolImpl)
		COM_INTERFACE_ENTRY(IInternetProtocol)
		COM_INTERFACE_ENTRY(IInternetProtocolRoot)
	END_COM_MAP()

	//IInternetProtocolRoot
	STDMETHOD(Start)(LPCWSTR szUrl,IInternetProtocolSink *,IInternetBindInfo *,DWORD ,HANDLE_PTR );
	STDMETHOD(Continue)(PROTOCOLDATA *pProtocolData);
	STDMETHOD(Abort)(HRESULT hrReason, DWORD dwOptions);
	STDMETHOD(Terminate)(DWORD dwOptions);
	STDMETHOD(Suspend)(void);
	STDMETHOD(Resume)(void);

	//IInternetProtocol
	STDMETHOD(Read)(void *pv, ULONG cb, ULONG *pcbRead);
	STDMETHOD(Seek)(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition);
	STDMETHOD(LockRequest)(DWORD dwOptions);
	STDMETHOD(UnlockRequest)(void);
};

