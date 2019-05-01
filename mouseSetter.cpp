// mouseSetter.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <windows.h>
#include "wtsapi32.h"
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Wtsapi32.lib")

int main(int argc, char* argv[])
{
	int iSetLines = 5;
	if (argc > 1) {
		int iInput = atoi(argv[1]);
		if (iInput >= 0) iSetLines = iInput;
	}

	while (argc--) {
		printf( "%s\n", argv[argc] );
	}

	BOOL bNotFound = TRUE;
	while (bNotFound) {
		WTS_PROCESS_INFO* pWPIs = NULL;
		DWORD dwProcCount = 0;
		if (WTSEnumerateProcesses(WTS_CURRENT_SERVER_HANDLE, NULL, 1, &pWPIs, &dwProcCount))
		{
			//Go through all processes retrieved
			for (DWORD i = 0; i < dwProcCount; i++)
			{
				if (0 == wcscmp(pWPIs[i].pProcessName, L"TbwHelper.exe")) {
					bNotFound = FALSE;
				}
			}
		}
		if (bNotFound) std::cout << "TrackballWorks Process have NOT found yet.\n";
		else std::cout << "TrackballWorks Process have found!!\n";
		::Sleep(1000);
	}
	

	int iGetLines;
	BOOL bGet = SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &iGetLines, 0);
	if (bGet) std::cout << "Current Mouse Wheel Scroll is " << iGetLines << ".\n";
	else std::cout << "Fail to Get Mouse Wheel Information.\n";

	BOOL bSet = SystemParametersInfo(SPI_SETWHEELSCROLLLINES, iSetLines, NULL, 0);
	if (bSet) std::cout << "New Mouse Wheel Scroll is " << iSetLines << ".\n";
	else std::cout << "Fail to Set Mouse Wheel Information.\n";

	getchar();
}