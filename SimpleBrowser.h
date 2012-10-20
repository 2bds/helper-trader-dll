#pragma once

#include "stdafx.h"
#include "UrlParser.h"
//#include "WinHttpConnection.h"
#include "WinHttpRequest.h"

const LPCWSTR host = L"tetraforex.anthill.by";
//const LPCWSTR host = L"groupmk.16mb.com";
const LPCWSTR path = L"/management/components/signals/signal.xml";
//const LPCWSTR path = L"/signals.xml";
static LPCWSTR userAgent = L"Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.4 (KHTML, like Gecko) Chrome/22.0.1229.79 Safari/537.4";

class SimpleBrowser// : public boost::serialization::singleton<Connector>
{
private:
	WinHttpSession session;

public:
	void Initialize(const UINT flagAsync)
	{
		session.Initialize(flagAsync);
	}

	int SendSignalIds(const std::vector<std::wstring>& urlIds)
	{
		// initialize connection
		URL_COMPONENTS urlComponents;
		if(FAILED(UrlParser::BuildUrlComponents(urlIds[0].c_str(), urlComponents)))
		{
			return FALSE;
		}
		WinHttpConnection connection;
		connection.Initialize(session, urlComponents);
		
		//for (int i = 100; i >= 0; i--)
		for (size_t i = 0; i < urlIds.size(); ++i)
		{
			if(FAILED(UrlParser::BuildUrlComponents(urlIds[i].c_str(), urlComponents)))
			{
				return FALSE;
			}
			WinHttpRequest request;
			request.Initialize(connection, urlComponents.lpszUrlPath);
			std::string response;
			if(FAILED(request.GetResponse(response)))
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	BOOL getSignalsResponse(PCWSTR pwszUrl, std::string& response)
	{
		URL_COMPONENTS urlComponents;
		
		if(FAILED(UrlParser::BuildUrlComponents(pwszUrl, urlComponents)))
		{
			return FALSE;
		}

		WinHttpConnection connection;
		if(FAILED(connection.Initialize(session, urlComponents)))
		{
			return FALSE;
		}

		WinHttpRequest request;
		if(FAILED(request.Initialize(connection, urlComponents.lpszUrlPath)))
		{
			return FALSE;
		}

		if(FAILED(request.GetResponse(response)))
		{
			return FALSE;
		}
		return TRUE;
	}
};