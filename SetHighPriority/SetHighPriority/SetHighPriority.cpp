//
//	Create on 4/16/2017 by ABacker
//

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <stdint.h>
#include <tlhelp32.h>
#include <vector>
#include <conio.h>

//ABOVE_NORMAL_PRIORITY_CLASS(0x00008000) 高于标准
//BELOW_NORMAL_PRIORITY_CLASS(0x00004000) 低于标准
//HIGH_PRIORITY_CLASS(0x00000080) 高
//IDLE_PRIORITY_CLASS(0x00000040) 低
//NORMAL_PRIORITY_CLASS(0x00000020) 标准
//REALTIME_PRIORITY_CLASS(0x00000100) 实时


#define HIDE 1	// 0 ---- 非隐藏运行,输出到标准设备
				// 1 ---- 隐藏运行,输出到Log.txt

#if(HIDE)
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//隐藏运行
#endif

HANDLE GetProcessHandleByID(int nID) {
	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, nID);
}

DWORD GetProcessIDByName(WCHAR* pName) {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot) {
		return NULL;
	}
	PROCESSENTRY32 pe = { sizeof(pe) };
	for (BOOL ret = Process32First(hSnapshot, &pe); ret; ret = Process32Next(hSnapshot, &pe)) {
		if (wcscmp(pe.szExeFile, pName) == 0) {
			CloseHandle(hSnapshot);
			return pe.th32ProcessID;
		}
	}
	CloseHandle(hSnapshot);
	return 0;
}

bool SetHighPriority(WCHAR* pName) {
	DWORD pid = GetProcessIDByName(pName);
	HANDLE handle = NULL;
	if (pid != 0) {
		handle = GetProcessHandleByID(pid);
		if (handle != NULL) {
			SetPriorityClass(handle, HIGH_PRIORITY_CLASS);
		}
	}
	return pid&&handle;
}

void _SetHighPriority(WCHAR* pName) {
	printf("SetHighPriority\t%ws\t\t", pName);
	if (SetHighPriority(pName)) {
		printf("Success!\n");
	} else {
		printf("Failed!\n");
	}
}

int main() {
#if(HIDE)
	freopen("Log.txt", "w", stdout);
#endif

	_SetHighPriority(L"NemuHeadless.exe");
	_SetHighPriority(L"NemuPlayer.exe");
	_SetHighPriority(L"NemuSVC.exe");

	//getch();

	return 0;
}