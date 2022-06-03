// Server.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include <iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;

int main()
{
    HANDLE write, read;
    int n;
    cout << "Enter array size \n";

    cin >> n;
    float* arr = new float[n];
    srand(time(NULL));
    cout << "\nEnter array elements \n";
    for (size_t i = 0; i < n; i++)
    {
        arr[i] = rand()%10+1;
        cout << arr[i] << " ";
    }
 
    HANDLE event = CreateEvent(NULL, FALSE, FALSE, "1");
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL; // ������ �� ���������
    sa.bInheritHandle = TRUE;
    CreatePipe(&read, &write, &sa, 0);
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    char a[80];
    wsprintf(a, "Mult.exe %d %d %d", int(write), int(read), n);

    if (!CreateProcess(NULL, a, NULL, NULL, TRUE,
        CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        GetLastError();
    }
   
    for (size_t i = 0; i < n; i++)
    {
        DWORD size;
        WriteFile(write, &arr[i], sizeof(arr[i]), &size, NULL);
    }
    SetEvent(event);
    HANDLE end = OpenEvent(SYNCHRONIZE, FALSE, "end");
    if (end == NULL) {
        GetLastError();
    }
    Sleep(500);
    WaitForSingleObject(end, INFINITE);
    DWORD size;
    float num = 0;
    ReadFile(read, &num, sizeof(num), &size, NULL);
    cout <<"\n"<< num;
    
}

// ������ ���������: CTRL+F5 ��� ���� "�������" > "������ ��� �������"
// ������� ���������: F5 ��� ���� "�������" > "��������� �������"

// ������ �� ������ ������ 
//   1. � ���� ������������ ������� ����� ��������� ����� � ��������� ���.
//   2. � ���� Team Explorer ����� ������������ � ������� ���������� ��������.
//   3. � ���� "�������� ������" ����� ������������� �������� ������ ������ � ������ ���������.
//   4. � ���� "������ ������" ����� ������������� ������.
//   5. ��������������� �������� ������ ���� "������" > "�������� ����� �������", ����� ������� ����� ����, ��� "������" > "�������� ������������ �������", ����� �������� � ������ ������������ ����� ����.
//   6. ����� ����� ������� ���� ������ �����, �������� ������ ���� "����" > "�������" > "������" � �������� SLN-����.
