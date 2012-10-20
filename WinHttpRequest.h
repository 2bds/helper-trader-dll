#pragma once

#include <string>
#include "WinHttpConnection.h"

class WinHttpRequest : public WinHttpHandle
{

public:
	HRESULT Initialize(const WinHttpConnection& connection, const LPWSTR lpszUrlPath)
	{
		//char* wcscat_s(char* dest, const char* source)
		//char* wcsncat(char* dest, const char* source, size_t size)
		if (!Attach(::WinHttpOpenRequest(connection.m_handle,
			L"GET", 
			lpszUrlPath,
			NULL, 
			WINHTTP_NO_REFERER, 
			WINHTTP_DEFAULT_ACCEPT_TYPES, 
			/*WINHTTP_FLAG_SECURE*/ NULL )))
		{
			return HRESULT_FROM_WIN32(::GetLastError());
		}
		return S_OK;
	}

	HRESULT GetResponse(std::string& response)
	{
		//std::string response;
		DWORD dwSize = 0;
		DWORD dwDownloaded = 0;
		LPSTR pszOutBuffer;
		BOOL  bResults = FALSE;
		// Send a request.
		if(::WinHttpSendRequest(m_handle, WINHTTP_NO_ADDITIONAL_HEADERS, 0/*-1L*/,	WINHTTP_NO_REQUEST_DATA, 0, 0, 0))
		{
			bResults = ::WinHttpReceiveResponse(m_handle, NULL);
		}
		// Keep checking for data until there is nothing left.
		if( bResults ) 
		{
			do 
			{
				// Check for available data.
				dwSize = 0;
				if(!::WinHttpQueryDataAvailable(m_handle, &dwSize))
					printf("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());
				// Allocate space for the buffer.
				pszOutBuffer = new char[dwSize + 1];
				if( !pszOutBuffer ) {
					printf( "Out of memory\n" );
					dwSize=0;
				}
				else
				{
					// Read the data.
					::ZeroMemory(pszOutBuffer, dwSize + 1);

					if(!::WinHttpReadData(m_handle, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded))
					{
						printf( "Error %u in WinHttpReadData.\n", GetLastError( ) );
					} 
					else 
					{
						///TODO
						std::string temp(pszOutBuffer, strlen(pszOutBuffer));
						response += temp;
						//printf( "%s", pszOutBuffer );
					}
					// Free the memory allocated to the buffer.
					delete[] pszOutBuffer;
				}
			} while( dwSize > 0 );
		}

		// Report any errors.
		if( !bResults )
		{
			return HRESULT_FROM_WIN32(::GetLastError());
		}
		return S_OK;
	}
};