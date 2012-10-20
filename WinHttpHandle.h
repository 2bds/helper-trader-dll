#pragma once

#include <windows.h>
#include <winhttp.h>

#ifdef _DEBUG
	#define ASSERT(X) _ASSERT(X)
	#define VERIFY(X) _ASSERT(X)
	#define ASSUME(X) _ASSERT(X)
#else
	#define ASSERT(X)
	#define VERIFY(X) (X)
	#define ASSUME(X) __assume(X)
#endif

class WinHttpHandle
{
public:
	WinHttpHandle() : m_handle(0){}

	~WinHttpHandle()
	{
		Close();
	}

	bool Attach(HINTERNET handle)
	{
		ASSERT(0 == m_handle);
		m_handle = handle;
		return 0 != m_handle;
	}

	HINTERNET Detach()
	{
		HANDLE handle = m_handle;
		m_handle = 0;
		return handle;
	}

	void Close()
	{
		if (0 != m_handle)
		{   
			VERIFY(::WinHttpCloseHandle(m_handle));
			m_handle = 0;
		}
	}

	HRESULT SetOption(DWORD option, const void* value, DWORD length)
	{
		if (!::WinHttpSetOption(m_handle, option, const_cast<void*>(value), length))
		{
			return HRESULT_FROM_WIN32(::GetLastError());
		}
		return S_OK;
	}

	HRESULT QueryOption(DWORD option, void* value, DWORD& length) const
	{
		if (!::WinHttpQueryOption(m_handle, option, value, &length))
		{
			return HRESULT_FROM_WIN32(::GetLastError());
		}
		return S_OK;
	}

	HINTERNET m_handle;
};