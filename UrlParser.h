#pragma once

#include <winhttp.h>

struct UrlParser
{
	static HRESULT BuildUrlComponents(const PCWSTR pwszUrl, URL_COMPONENTS& UrlComponents)
	{
		SIZE_T cchUrl = ::wcslen(pwszUrl) + 1;
		WCHAR* m_pwszUrl = new WCHAR[cchUrl];
		::wcscpy_s(m_pwszUrl, cchUrl, pwszUrl);
		ZeroMemory(&UrlComponents, sizeof(UrlComponents));
		UrlComponents.dwStructSize = sizeof(UrlComponents);
		UrlComponents.dwSchemeLength    = (DWORD)-1;
		UrlComponents.dwHostNameLength  = (DWORD)-1;
		UrlComponents.dwUrlPathLength   = (DWORD)-1;
		if (::WinHttpCrackUrl(m_pwszUrl, (DWORD)::wcslen(m_pwszUrl), 0, &UrlComponents) == FALSE)
		{
			fprintf(stderr, "Requester #%d failed to open; ::WinHttpCrackUrl() failed; error = %d.\n", ::GetLastError());
			return HRESULT_FROM_WIN32(::GetLastError());
		}

		return S_OK;
	}
};