// dllmain.cpp: определяет точку входа для приложения DLL.
#include "wchar.h" // _wtoi
//-------------------------------------------------------------------------------

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

//-------------------------------------------------------------------------------
LPWSTR pw1 = L"CESAR", // не более 63 символов
	  pw2 = L"delta",
	  pw3 = L"1d10m13y";

//-------------------------------------------------------------------------------

extern "C" __declspec(dllexport) int __stdcall GetOpt(LPWSTR po1, LPWSTR po2, LPWSTR po3)
{
	int len = lstrlen(pw1);
	memcpy(po1,pw1,len*sizeof(LPWSTR));
	//
	len = lstrlen(pw2);
	memcpy(po2,pw2,len*sizeof(LPWSTR));
	//
	len = lstrlen(pw3);
	memcpy(po3,pw3,len*sizeof(LPWSTR));
	//
	return 0;
}
//-------------------------------------------------------------------------------

extern "C" __declspec(dllexport) int __stdcall Enc(LPWSTR src, LPWSTR dst, LPWSTR pwd)
{
	int delta = _wtoi(pwd);
	int len = lstrlen(src);
	if ( src && dst && pwd )
	{
		for (int i=0; i<len; i++)
		{
			WCHAR wch = src[i];
			wch += delta;
			dst[i] = wch;
		}
	}
	return 0;
}
//-------------------------------------------------------------------------------

extern "C" __declspec(dllexport) int __stdcall Dec(LPWSTR src, LPWSTR dst, LPWSTR pwd)
{
	int delta = _wtoi(pwd);
	int len = lstrlen(src);
	if ( src && dst && pwd )
	{
		for (int i=0; i<len; i++)
		{
			WCHAR wch = src[i];
			wch -= delta;
			dst[i] = wch;
		}
	}
	return 0;
}
