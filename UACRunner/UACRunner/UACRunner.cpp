/****************************************************************
   A simple UAC runner for windows that prompts UAC for other
   program especially for batch scripts.

   Usage: UACRunner.exe ProgramPath Arg1 Arg2 Arg3 ...
 ****************************************************************/

#include <fstream>
#include <iostream>

#include <Windows.h>
#include <conio.h>

using namespace std;

void Usage(wchar_t* prog) {
    wcout << prog << L" ProgramPath Arg1 Arg2 Arg3 ..." << endl;
}

int __cdecl wmain(int argc, wchar_t** argv)
{
    if (argc == 1) {
        Usage(argv[0]);
        return 1;
    }

    wstring cmd;
    for (int i = 1; i < argc; ++i) {
        cmd.append(argv[i]);
        if (i < argc - 1) cmd.append(L" ");
    }
    wcout << cmd << endl;

    _wsystem(cmd.c_str());

    wofstream out(L"C:\\NINI\\ImDisk\\UACRunner.log");
    out << cmd;
    out.close();

    return 0;
}
