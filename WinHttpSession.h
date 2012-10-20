#pragma once

#include "WinHttpHandle.h"

const LPCWSTR s_userAgent = L"Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.4 (KHTML, like Gecko) Chrome/22.0.1229.79 Safari/537.4";

// Session
class WinHttpSession : public WinHttpHandle
{
public:
	HRESULT Initialize(const UINT flagAsync)
	{
		if (!Attach(::WinHttpOpen(s_userAgent,
			WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
			WINHTTP_NO_PROXY_NAME,
			WINHTTP_NO_PROXY_BYPASS,
			flagAsync))) /*WINHTTP_FLAG_ASYNC*/
		{
			return HRESULT_FROM_WIN32(::GetLastError());
		}
		return S_OK;
	}
};