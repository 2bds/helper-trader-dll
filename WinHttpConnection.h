#pragma once

#include "WinHttpSession.h"

// Connection
class WinHttpConnection : public WinHttpHandle
{
public:
	HRESULT Initialize(const WinHttpSession& session, URL_COMPONENTS& urlComp)
	{
		WCHAR wCharSave = urlComp.lpszHostName[urlComp.dwHostNameLength];
		urlComp.lpszHostName[urlComp.dwHostNameLength] = L'\0';

		//Create connection
		if (!Attach(::WinHttpConnect(session.m_handle, urlComp.lpszHostName, urlComp.nPort, 0))) // reserved
		{
			return HRESULT_FROM_WIN32(::GetLastError());
		}
		urlComp.lpszHostName[urlComp.dwHostNameLength] = wCharSave;

		return S_OK;
	}
};