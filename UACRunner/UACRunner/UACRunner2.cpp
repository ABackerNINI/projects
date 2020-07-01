#include <fstream>
#include <iostream>

#include <Windows.h>
#include <conio.h>

using namespace std;

//判断进程是否以管理员身份运行
bool isProcessRunAsAdmin()
{
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID AdministratorsGroup;

    BOOL b = AllocateAndInitializeSid(
        &NtAuthority,
        2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0,
        &AdministratorsGroup);
    if (b) {
        CheckTokenMembership(NULL, AdministratorsGroup, &b);
        FreeSid(AdministratorsGroup);
    }
    return b == TRUE;
}

//main函数
int __cdecl wmain(int argc, wchar_t** argv)
{
    std::wstring wstrParams;
    for (int i = 2; i < argc; ++i) {
        wstrParams.append(argv[i]);
        if (i < argc - 1) wstrParams.append(L" ");
    }
    wcout << argv[1] << L" " << wstrParams << endl;

    //任何对文件的操作在这里都不允许，不然会导致进程启动失败
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    //GetVersionExW(&osvi);
    //if (5 < osvi.dwMajorVersion) {
    //std::wstring wstrValue;

    //以下函数为查询注册表，读者可自行实现
    //int iReturn = CUtility::queryRegValue(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"EnableLUA", wstrValue);

    //if (Success == iReturn) {
    if (/*1 == *(int*)wstrValue.c_str() &&*/ false == isProcessRunAsAdmin()) {
        wchar_t szPath[MAX_PATH] = { 0 };
        GetModuleFileName(NULL, szPath, MAX_PATH);
        std::wcout << szPath << std::endl;
        wcout << L"Getting UAC" << endl;

        SHELLEXECUTEINFO sei = { 0 };
        sei.cbSize = sizeof(SHELLEXECUTEINFOW);
        sei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI;
        sei.lpFile = argv[1];
        sei.lpParameters = wstrParams.c_str();
        sei.nShow = SW_SHOW;
        sei.lpVerb = TEXT("runas");
        sei.lpDirectory = NULL;
        BOOL iRet = ShellExecuteEx(&sei);
        if (TRUE != iRet) {
            fprintf(stdout, "ShellExecuteEx Failure. Error Code is : %d", GetLastError());
        }
        //return 0;
    }
    //}
    //else {
    //    return 0;
    //}
//}

//接下来为程序正常处理逻辑

    //_wsystem(wstrParams.c_str());

    wofstream out(L"C:\\NINI\\ImDisk\\UACRunner.log");
    out << wstrParams;
    out.close();

    return 0;
}