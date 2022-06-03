#include <iostream>
#include<Windows.h>
using namespace std;

HANDLE workEvent, mulEvent;
CRITICAL_SECTION cs;

struct arr {
    int* arr;
    int n;
};

DWORD WINAPI work(arr* a) {
    DWORD t;
    EnterCriticalSection(&cs);
    cout << "Input sleep time\n";
    cin >> t;
    int a1;
    int b;
    cout << "A = " << endl;
    cin >> a1;
    cout << "B = " << endl;
    cin >> b;
    int i = 0;
    if (b > a->n - 1)
        b = a->n - 1;
    if (a1 < 0)
        a1 = 0;
    for (; i < b - a1 + 1; i++)
    {
        a->arr[i] = a->arr[i + a1];
        Sleep(t);
    }
    while (i != a->n)
    {
        a->arr[i] = 0;
        i++;
    }
    LeaveCriticalSection(&cs);
    return 0;
}

int mul = 0;

DWORD WINAPI MulElement(arr* a) {
    EnterCriticalSection(&cs);
    mul = a->arr[0] * a->arr[1];
    for (int i = 2; i < a->n; i++) {
        if(a->arr[i]!=0)
        mul *= a->arr[i];
    }
    SetEvent(mulEvent);
    LeaveCriticalSection(&cs);
    return 0;
}

int main()
{
    arr a;
    cout << "Input array size\n";
    cin >> a.n;
    a.arr = new int[a.n];
    cout << "Input elements";
    for (size_t i = 0; i < a.n; i++)
    {
        cin >> a.arr[i];
    }
    cout << "Array size: " << a.n << "\n";
    cout << "Array:\n";
    for (size_t i = 0; i < a.n; i++)
    {
        cout << a.arr[i];
    }
    cout << "\n";
    HANDLE work_h, MulElement_h;
    DWORD work_id, MulElement_id;
    InitializeCriticalSection(&cs);
    workEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (workEvent == NULL) {
        GetLastError();
    }
    mulEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (mulEvent == NULL) {
        GetLastError();
    }
    work_h = (HANDLE)CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)work, &a, 0, &work_id);
    if (work_h == NULL) {
        GetLastError();
    }
    MulElement_h = (HANDLE)CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MulElement, &a, 0, &MulElement_id);
    if (MulElement_h == NULL) {
        GetLastError();
    }
    WaitForSingleObject(mulEvent, INFINITE);
    for (size_t i = 0; i < a.n; i++)
    {
        cout << a.arr[i];
    }
    cout << "\nMulElements:\n";
    cout << '\n' << mul;
    cout << "\n";
}