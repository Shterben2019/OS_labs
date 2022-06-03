#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<conio.h>
#include <iostream>
#include <string>
using namespace std;

int main()
{
   // char lpszAppName[] = "C:\\Users\\Admin\\source\\repos\\lab2\\x64\\Debug\\Child.exe";
    char lpszAppName[] = "Child.exe";
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USEPOSITION;
    si.dwY = 1000;
    string str = "";
    int t;
    string tmp = "";
    int n;
    cout << "n = " << endl;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        str += tmp;
        str += " ";
    }
    cout << str;
    str.length();
    char* h = new char[str.length()];
    for (int i = 0; i < str.length() - 1; i++) {
        h[i] = str[i];
    }

    if (!CreateProcess(lpszAppName, h,NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi)) {
        _cputs("Invalid process");
        // _getch();
        return 0;
    }

    _cputs("Process created");
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
 
}