#pragma once
typedef int (__stdcall *MYPROC)(LPWSTR,LPWSTR,LPWSTR);
MYPROC Proc1, Proc2, Proc3;
BOOL fRunTimeLinkSuccess;
WCHAR p1[64], p2[64], p3[64];

void Prg1::CesarTest()
{
	// Clear buffers
	memset(p1,0,sizeof(WCHAR)*64);
	memset(p2,0,sizeof(WCHAR)*64);
	memset(p3,0,sizeof(WCHAR)*64);

	// Get a handle to the DLL module
	hinstLib = LoadLibrary(L"cesar8.dll"); 

	// If the handle is valid, try to get the function address
	if (hinstLib != NULL)
	{
		Proc1 = (MYPROC) GetProcAddress(hinstLib, "_GetOpt@12");
		Proc2 = (MYPROC) GetProcAddress(hinstLib, "_Enc@12");
		Proc3 = (MYPROC) GetProcAddress(hinstLib, "_Dec@12");

        // Ensure function addresses is valid 
        if ( (NULL != Proc1) && (NULL != Proc2) && (NULL != Proc3) )
        {
			fRunTimeLinkSuccess = TRUE;
			// Get info about func DLL
            (Proc1) (p1,p2,p3);
        }
	}
	int iDebug = 0;
	//
}

void Prg1::Encrypt()
{
	// call the function
	if ( fRunTimeLinkSuccess )
	{
		(Proc2) (L"StringForCrypt",p2,L"5"); // Шифруем строку, смещение 5, результат в p2
		MessageBox(p2);
	}
}

void Prg1::Decrypt()
{
	// call the function
	if ( fRunTimeLinkSuccess )
	{
		(Proc3) (p2,p3,L"5"); // Дешифруем строку, смещение 5, результат в p3
		MessageBox(p3);
	}
}
