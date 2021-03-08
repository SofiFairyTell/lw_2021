#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <locale.h>

#include "declaration_aes.h"
using namespace std;
int _tmain(int argc, LPCTSTR argv[])
{
	mode_aes enc, dec;
	_tsetlocale(LC_ALL, TEXT(""));
	if (2 == argc)
	{
		
		if (_tcsicmp(argv[1], TEXT("/start_encrypt")) == 0)
		{
			enc.encrypt_aes();
		}
		else
			if (_tcsicmp(argv[1], TEXT("/start_decrypt")) == 0)
			{
				dec.decrypt_aes();
			}
	}

}