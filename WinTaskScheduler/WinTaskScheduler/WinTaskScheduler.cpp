/**********************************************************************
 This sample schedules a task to start notepad.exe when a user logs on.
**********************************************************************/

#define _WIN32_DCOM
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <comdef.h>
#include <conio.h>
//  Include the task header file.
#include <taskschd.h>

#pragma comment(lib, "taskschd.lib")
#pragma comment(lib, "comsupp.lib")

using namespace std;

// MSDN例子
int foo();

//创建用户登录启动软件的任务
// taskName 任务名字
// executablePath 可执行文件路径
// creater 创建者
int LogonStartScheduler(const wchar_t* taskName,
    const wchar_t* executablePath, const wchar_t* arguments, const wchar_t* delay = NULL,
    const wchar_t* creator = NULL);

// wstring strToStdWString(const string& str);

// ./program TaskName ExecutablePath Arguments [Delay]
// Delay: The format for this string is PnYnMnDTnHnMnS. 'T' is the date/time separator.
//   P1M4DT2H5M specifies one month, four days, two hours, and five minutes.
int __cdecl wmain(int argc, wchar_t** argv) {
    if (argc < 4) {
        fprintf(stderr, "Wrong number of parameters!\n");
        return 1;
    }

    setlocale(LC_ALL, "chs");

    wcout << L"TaskName: " << argv[1] << endl;
    wcout << L"ExecutablePath: " << argv[2] << endl;
    wcout << L"Arguments: " << argv[3] << endl;
    if (argc >= 5)wcout << L"Delay: " << argv[4] << endl;

    _getch();

    LogonStartScheduler(argv[1], argv[2], argv[3], (argc >= 5 ? argv[4] : NULL), L"abacker");

    _getch();

    return 0;
}

/* =============================================================================================================
 */

int foo() {
    /**********************************************************************
     This sample schedules a task to start notepad.exe when a user logs on.
    **********************************************************************/

    //  ------------------------------------------------------
    //  Initialize COM.
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        printf("\nCoInitializeEx failed: %x", hr);
        return 1;
    }

    //  Set general COM security levels.
    hr = CoInitializeSecurity(NULL, -1, NULL, NULL,
        RPC_C_AUTHN_LEVEL_PKT_PRIVACY,
        RPC_C_IMP_LEVEL_IMPERSONATE, NULL, 0, NULL);

    if (FAILED(hr)) {
        printf("\nCoInitializeSecurity failed: %x", hr);
        CoUninitialize();
        return 1;
    }

    //  ------------------------------------------------------
    //  Create a name for the task.
    LPCWSTR wszTaskName = L"Logon Trigger Test Task";

    //  Get the windows directory and set the path to notepad.exe.
    wstring wstrExecutablePath = _wgetenv(L"WINDIR");
    wstrExecutablePath += L"\\SYSTEM32\\NOTEPAD.EXE";

    //  ------------------------------------------------------
    //  Create an instance of the Task Service.
    ITaskService* pService = NULL;
    hr = CoCreateInstance(CLSID_TaskScheduler, NULL, CLSCTX_INPROC_SERVER,
        IID_ITaskService, (void**)&pService);
    if (FAILED(hr)) {
        printf("Failed to create an instance of ITaskService: %x", hr);
        CoUninitialize();
        return 1;
    }

    //  Connect to the task service.
    hr = pService->Connect(_variant_t(), _variant_t(), _variant_t(),
        _variant_t());
    if (FAILED(hr)) {
        printf("ITaskService::Connect failed: %x", hr);
        pService->Release();
        CoUninitialize();
        return 1;
    }

    //  ------------------------------------------------------
    //  Get the pointer to the root task folder.  This folder will hold the
    //  new task that is registered.
    ITaskFolder* pRootFolder = NULL;
    hr = pService->GetFolder(_bstr_t(L"\\"), &pRootFolder);
    if (FAILED(hr)) {
        printf("Cannot get Root Folder pointer: %x", hr);
        pService->Release();
        CoUninitialize();
        return 1;
    }

    //  If the same task exists, remove it.
    pRootFolder->DeleteTask(_bstr_t(wszTaskName), 0);

    //  Create the task builder object to create the task.
    ITaskDefinition* pTask = NULL;
    hr = pService->NewTask(0, &pTask);

    pService->Release();  // COM clean up.  Pointer is no longer used.
    if (FAILED(hr)) {
        printf("Failed to create a task definition: %x", hr);
        pRootFolder->Release();
        CoUninitialize();
        return 1;
    }

    //  ------------------------------------------------------
    //  Get the registration info for setting the identification.
    IRegistrationInfo* pRegInfo = NULL;
    hr = pTask->get_RegistrationInfo(&pRegInfo);
    if (FAILED(hr)) {
        printf("\nCannot get identification pointer: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    hr = pRegInfo->put_Author(_bstr_t(L"Author Name"));
    pRegInfo->Release();
    if (FAILED(hr)) {
        printf("\nCannot put identification info: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  ------------------------------------------------------
    //  Create the settings for the task
    ITaskSettings* pSettings = NULL;
    hr = pTask->get_Settings(&pSettings);
    if (FAILED(hr)) {
        printf("\nCannot get settings pointer: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  Set setting values for the task.
    hr = pSettings->put_StartWhenAvailable(VARIANT_TRUE);
    pSettings->Release();
    if (FAILED(hr)) {
        printf("\nCannot put setting info: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  ------------------------------------------------------
    //  Get the trigger collection to insert the logon trigger.
    ITriggerCollection* pTriggerCollection = NULL;
    hr = pTask->get_Triggers(&pTriggerCollection);
    if (FAILED(hr)) {
        printf("\nCannot get trigger collection: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  Add the logon trigger to the task.
    ITrigger* pTrigger = NULL;
    hr = pTriggerCollection->Create(TASK_TRIGGER_LOGON, &pTrigger);
    pTriggerCollection->Release();
    if (FAILED(hr)) {
        printf("\nCannot create the trigger: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    ILogonTrigger* pLogonTrigger = NULL;
    hr = pTrigger->QueryInterface(IID_ILogonTrigger, (void**)&pLogonTrigger);
    pTrigger->Release();
    if (FAILED(hr)) {
        printf("\nQueryInterface call failed for ILogonTrigger: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    hr = pLogonTrigger->put_Id(_bstr_t(L"Trigger1"));
    if (FAILED(hr)) printf("\nCannot put the trigger ID: %x", hr);

    //  Set the task to start at a certain time. The time
    //  format should be YYYY-MM-DDTHH:MM:SS(+-)(timezone).
    //  For example, the start boundary below
    //  is January 1st 2005 at 12:05
    hr = pLogonTrigger->put_StartBoundary(_bstr_t(L"2005-01-01T12:05:00"));
    if (FAILED(hr)) printf("\nCannot put the start boundary: %x", hr);

    hr = pLogonTrigger->put_EndBoundary(_bstr_t(L"2099-05-02T08:00:00"));
    if (FAILED(hr)) printf("\nCannot put the end boundary: %x", hr);

    //  Define the user.  The task will execute when the user logs on.
    //  The specified user must be a user on this computer.
    hr = pLogonTrigger->put_UserId(_bstr_t(L"DOMAIN\\1105908317@qq.com"));
    pLogonTrigger->Release();
    if (FAILED(hr)) {
        printf("\nCannot add user ID to logon trigger: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  ------------------------------------------------------
    //  Add an Action to the task. This task will execute notepad.exe.
    IActionCollection* pActionCollection = NULL;

    //  Get the task action collection pointer.
    hr = pTask->get_Actions(&pActionCollection);
    if (FAILED(hr)) {
        printf("\nCannot get Task collection pointer: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  Create the action, specifying that it is an executable action.
    IAction* pAction = NULL;
    hr = pActionCollection->Create(TASK_ACTION_EXEC, &pAction);
    pActionCollection->Release();
    if (FAILED(hr)) {
        printf("\nCannot create the action: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    IExecAction* pExecAction = NULL;
    //  QI for the executable task pointer.
    hr = pAction->QueryInterface(IID_IExecAction, (void**)&pExecAction);
    pAction->Release();
    if (FAILED(hr)) {
        printf("\nQueryInterface call failed for IExecAction: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  Set the path of the executable to notepad.exe.
    hr = pExecAction->put_Path(_bstr_t(wstrExecutablePath.c_str()));
    pExecAction->Release();
    if (FAILED(hr)) {
        printf("\nCannot set path of executable: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  ------------------------------------------------------
    //  Save the task in the root folder.
    IRegisteredTask* pRegisteredTask = NULL;

    hr = pRootFolder->RegisterTaskDefinition(
        _bstr_t(wszTaskName), pTask, TASK_CREATE_OR_UPDATE,
        _variant_t(L"DOMAIN\\1105908317@qq.com"), _variant_t(),
        TASK_LOGON_GROUP, _variant_t(L""), &pRegisteredTask);
    if (FAILED(hr)) {
        printf("\nError saving the Task : %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    printf("\nSuccess! Task successfully registered.");

    // Clean up
    pRootFolder->Release();
    pTask->Release();
    pRegisteredTask->Release();
    CoUninitialize();

    return 0;
}

//创建用户登录启动软件的任务
// taskName 任务名字
// executablePath 可执行文件路径
// creater 创建者
int LogonStartScheduler(const wchar_t* taskName,
    const wchar_t* executablePath, const wchar_t* arguments, const wchar_t* delay,
    const wchar_t* creator) {
    //  ------------------------------------------------------
    //  Initialize COM.
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        printf("\nCoInitializeEx failed: %x", hr);
        return 1;
    }

    //  Set general COM security levels.
    hr = CoInitializeSecurity(NULL, -1, NULL, NULL,
        RPC_C_AUTHN_LEVEL_PKT_PRIVACY,
        RPC_C_IMP_LEVEL_IMPERSONATE, NULL, 0, NULL);

    if (FAILED(hr)) {
        printf("\nCoInitializeSecurity failed: %x", hr);
        CoUninitialize();
        return 1;
    }

    //  ------------------------------------------------------
    //  Create a name for the task.
    LPCWSTR wszTaskName = taskName;

    //  Get the windows directory and set the path to notepad.exe.
    wstring wstrExecutablePath = executablePath;

    //  ------------------------------------------------------
    //  Create an instance of the Task Service.
    ITaskService* pService = NULL;
    hr = CoCreateInstance(CLSID_TaskScheduler, NULL, CLSCTX_INPROC_SERVER,
        IID_ITaskService, (void**)&pService);
    if (FAILED(hr)) {
        printf("Failed to create an instance of ITaskService: %x", hr);
        CoUninitialize();
        return 1;
    }

    //  Connect to the task service.
    hr = pService->Connect(_variant_t(), _variant_t(), _variant_t(),
        _variant_t());
    if (FAILED(hr)) {
        printf("ITaskService::Connect failed: %x", hr);
        pService->Release();
        CoUninitialize();
        return 1;
    }

    //  ------------------------------------------------------
    //  Get the pointer to the root task folder.  This folder will hold the
    //  new task that is registered.
    ITaskFolder* pRootFolder = NULL;
    hr = pService->GetFolder(_bstr_t(L"\\"), &pRootFolder);
    if (FAILED(hr)) {
        printf("Cannot get Root Folder pointer: %x", hr);
        pService->Release();
        CoUninitialize();
        return 1;
    }

    //  If the same task exists, remove it.
    pRootFolder->DeleteTask(_bstr_t(wszTaskName), 0);

    //  Create the task builder object to create the task.
    ITaskDefinition* pTask = NULL;
    hr = pService->NewTask(0, &pTask);

    pService->Release();  // COM clean up.  Pointer is no longer used.
    if (FAILED(hr)) {
        printf("Failed to create a task definition: %x", hr);
        pRootFolder->Release();
        CoUninitialize();
        return 1;
    }


    IPrincipal* principal = NULL;
    hr = pTask->get_Principal(&principal);
    if (FAILED(hr)) {
        printf("\nCannot get principal pointer: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    hr = principal->put_RunLevel(TASK_RUNLEVEL_HIGHEST);
    principal->Release();
    if (FAILED(hr)) {
        printf("\nCannot put RunLevel: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  ------------------------------------------------------
    //  Get the registration info for setting the identification.
    IRegistrationInfo* pRegInfo = NULL;
    hr = pTask->get_RegistrationInfo(&pRegInfo);
    if (FAILED(hr)) {
        printf("\nCannot get identification pointer: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }
    if (creator != NULL) {
        hr = pRegInfo->put_Author(_bstr_t(creator));
        pRegInfo->Release();
        if (FAILED(hr)) {
            pRegInfo->Release();
            printf("\nCannot put identification info: %x", hr);
            pRootFolder->Release();
            pTask->Release();
            CoUninitialize();
            return 1;
        }
    }

    //  ------------------------------------------------------
    //  Create the settings for the task
    ITaskSettings* pSettings = NULL;
    hr = pTask->get_Settings(&pSettings);
    if (FAILED(hr)) {
        printf("\nCannot get settings pointer: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  Set setting values for the task.
    hr = pSettings->put_StartWhenAvailable(VARIANT_TRUE);
    if (FAILED(hr)) {
        pSettings->Release();
        printf("\nCannot put setting info: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }
    hr = pSettings->put_DisallowStartIfOnBatteries(VARIANT_FALSE);
    pSettings->Release();
    if (FAILED(hr)) {
        printf("\nCannot put setting info: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  ------------------------------------------------------
    //  Get the trigger collection to insert the logon trigger.
    ITriggerCollection* pTriggerCollection = NULL;
    hr = pTask->get_Triggers(&pTriggerCollection);
    if (FAILED(hr)) {
        printf("\nCannot get trigger collection: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  Add the logon trigger to the task.
    ITrigger* pTrigger = NULL;
    hr = pTriggerCollection->Create(TASK_TRIGGER_LOGON, &pTrigger);
    pTriggerCollection->Release();
    if (FAILED(hr)) {
        printf("\nCannot create the trigger: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    ILogonTrigger* pLogonTrigger = NULL;
    hr = pTrigger->QueryInterface(IID_ILogonTrigger, (void**)&pLogonTrigger);
    pTrigger->Release();
    if (FAILED(hr)) {
        printf("\nQueryInterface call failed for ILogonTrigger: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    hr = pLogonTrigger->put_Id(_bstr_t(L"Trigger1"));
    if (FAILED(hr)) {
        printf("\nCannot put the trigger ID: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    if (delay) {
        hr = pLogonTrigger->put_Delay(_bstr_t(delay));
        if (FAILED(hr)) {
            printf("\nCannot put the trigger delay: %x", hr);
            pRootFolder->Release();
            pTask->Release();
            CoUninitialize();
            return 1;
        }
    }

    wchar_t computerName[256] = { 0 };
    wchar_t userName[256] = { 0 };
    DWORD dwSize = 256;
    if (!GetComputerNameW(computerName, &dwSize) ||
        !GetUserNameW(userName, &dwSize)) {
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return S_FALSE;
    }
    lstrcatW(computerName, (wchar_t*)L"\\");
    lstrcatW(computerName, userName);
    std::wcout << L"当前用户名：" << computerName << endl;

    //  Define the user.  The task will execute when the user logs on.
    //  The specified user must be a user on this computer.
    hr = pLogonTrigger->put_UserId(computerName);
    pLogonTrigger->Release();
    if (FAILED(hr)) {
        printf("\nCannot add user ID to logon trigger: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  ------------------------------------------------------
    //  Add an Action to the task. This task will execute notepad.exe.
    IActionCollection* pActionCollection = NULL;

    //  Get the task action collection pointer.
    hr = pTask->get_Actions(&pActionCollection);
    if (FAILED(hr)) {
        printf("\nCannot get Task collection pointer: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  Create the action, specifying that it is an executable action.
    IAction* pAction = NULL;
    hr = pActionCollection->Create(TASK_ACTION_EXEC, &pAction);
    pActionCollection->Release();
    if (FAILED(hr)) {
        printf("\nCannot create the action: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    IExecAction* pExecAction = NULL;
    //  QI for the executable task pointer.
    hr = pAction->QueryInterface(IID_IExecAction, (void**)&pExecAction);
    pAction->Release();
    if (FAILED(hr)) {
        printf("\nQueryInterface call failed for IExecAction: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  Set the path of the executable to notepad.exe.
    hr = pExecAction->put_Path(_bstr_t(wstrExecutablePath.c_str()));
    if (FAILED(hr)) {
        printf("\nCannot set path of executable: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }
    hr = pExecAction->put_Arguments(_bstr_t(arguments));
    pExecAction->Release();
    if (FAILED(hr)) {
        printf("\nCannot set arguments of executable: %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    //  ------------------------------------------------------
    //  Save the task in the root folder.
    IRegisteredTask* pRegisteredTask = NULL;

    hr = pRootFolder->RegisterTaskDefinition(
        _bstr_t(wszTaskName), pTask, TASK_CREATE_OR_UPDATE,
        _variant_t(computerName), _variant_t(), TASK_LOGON_INTERACTIVE_TOKEN,
        _variant_t(L""), &pRegisteredTask);
    if (FAILED(hr)) {
        printf("\nError saving the Task : %x", hr);
        pRootFolder->Release();
        pTask->Release();
        CoUninitialize();
        return 1;
    }

    printf("\nSuccess! Task successfully registered.");

    // Clean up
    pRootFolder->Release();
    pTask->Release();
    pRegisteredTask->Release();
    CoUninitialize();

    return 0;
}

// wstring strToStdWString(const string& str)
//{
//	wstring wStr;
//	int len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(),
//str.size(), NULL, 0); 	cout << str << endl; 	cout << len << endl; 	TCHAR* buffer
//= new TCHAR[len + 1]; 	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(),
//str.size(), buffer, len); 	buffer[len] = '\0'; 	wStr.append(buffer); 	delete[]
//buffer; 	return wStr;
//}
