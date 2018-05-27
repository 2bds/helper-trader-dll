// TrideHelper.cpp: определяет экспортированные функции для приложения DLL.
//
#include "stdafx.h"
#include "SimpleBrowser.h"
#include "ParserXml.h"
#include "utility.h"

#include "gtest/gtest.h"

#pragma comment(lib, "winhttp.lib")

//"E:\\NEW LIBS\\RUBY\\BODY\\logger.txt"
static PCWSTR signalUrl = L"http://tetraforex.anthill.by/management/components/signals/signal.xml";
static const std::wstring iDsUrl = L"http://tetraforex.anthill.by/management/components/signals/handler.php?action=deactivateSignals&id=";
static const std::string RESPONSE_FALSE = "false";

#define WINHTTP_FLAG_NOT_ASYNC              0x00000000  // this session is not asynchronous

BOOL parseXml() {
	WINHTTP_FLAG_ASYNC;
	SimpleBrowser simpleBrowser;
	simpleBrowser.Initialize(WINHTTP_FLAG_NOT_ASYNC);
	std::string response;
	BOOL result = simpleBrowser.getSignalsResponse(signalUrl, response);
	///TODO
	if(result != FALSE && response != RESPONSE_FALSE && !response.empty()){
		if(ParserXml::get_mutable_instance().createSignalCharStrings(response)){
			return TRUE;
		}
	}
	return FALSE;
}

int __stdcall __getSignalCount(){
	if(parseXml() == TRUE)
		return ParserXml::get_mutable_instance().getSignalCount();
	return -1;
}

void __stdcall __getSignal(MqlStr* array1, int index){
	std::string signalsLine = ParserXml::get_const_instance()[index];
	std::strcpy(array1[0].string1, signalsLine.c_str());
}

int __stdcall __sendSignalIds(int* array1, const int arr_size){
	if(array1 == NULL || arr_size < 1) 
		return -1;
	std::vector<std::wstring> urls;
	SimpleBrowser simpleBrowser;
	simpleBrowser.Initialize(0);

	for(int i = 0; i < arr_size; i++){
		wchar_t id[10];
		::_itow_s<10>(array1[i], id, 10);
		//::_itoa_s<10>(array1[i], id, 10);
		std::wstring tmp(id);
		urls.push_back(iDsUrl + tmp);
	}

	return simpleBrowser.SendSignalIds(urls);
}

void __stdcall __getSignals(MqlStr array1[]) {
	std::stringstream ss(readXmlFile1(xmlPath)); 
	const SignalsLineChar& signalsLine = ParserXml::get_mutable_instance().getSignals();

	//std::copy(files.begin(), files.end(),std::ostream_iterator<rds_t::value_type>(std::cout, "\n"));
	/*	
	for(SignalsLineChar::const_iterator b = signalsLine.begin(), e = signalsLine.end(); b != e; ++b)
	{
	strcpy(array1[i].string, (*b)->c_str());
	}
	*/
	for (int i = 0; i < signalsLine.size(); i++){
		::strcpy_s(array1[i].string1, strlen(array1[i].string1), signalsLine[i].c_str());
	}
}

void __stdcall __getText(wchar_t *text, wchar_t *from, wchar_t *to) {
	wchar_t *cp;
	//--- check parameters
	if(text==NULL || from==NULL || to==NULL) return;
	if(wcslen(from)!=wcslen(to))             return;
	//--- search substring
	if((cp=wcsstr(text,from))==NULL)         return;
	//--- replace
	memcpy(cp,to,wcslen(to)*sizeof(wchar_t));
}