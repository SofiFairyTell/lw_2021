#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <locale.h>

#include "declaration_aes.h"
using namespace std;
int main(int argc, LPCTSTR argv[])
{
	mode_aes enc, dec;
	setlocale(LC_ALL, "");
	if (2 == argc)
	{
		
		if (_tcsicmp(argv[1], TEXT("/start_encrypt")) == 0)
		{
			enc.encrypt_aes();
		}
		else
			if (_tcsicmp(argv[1], TEXT("/start_encrypt")) == 0)
			{
				dec.decrypt_aes();
			}
	}

}