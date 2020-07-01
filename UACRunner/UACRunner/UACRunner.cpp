#include <fstream>
#include <iostream>

#include <Windows.h>
#include <conio.h>

using namespace std;

int __cdecl wmain(int argc, wchar_t** argv)
{
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
