#if     _MSC_VER > 1000
	#pragma once
#endif

typedef struct {
	int	len;
   char  *string1;
}  MqlStr;
//typedef MqlStr _MqlStr;
extern "C" __declspec(dllexport) void  __stdcall __getSignal(MqlStr* array1, int index);
extern "C" __declspec(dllexport) int   __stdcall __getSignalCount();
extern "C" __declspec(dllexport) int  __stdcall __sendSignalIds(int* array1, const int arr_size);
extern "C" __declspec(dllexport) void  __stdcall __getSignals(MqlStr array1[]);
extern "C" __declspec(dllexport) void  __stdcall __getText(wchar_t *text,wchar_t *from,wchar_t *to);
