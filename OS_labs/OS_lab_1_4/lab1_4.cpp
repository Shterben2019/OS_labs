#include <windows.h>
#include <iostream>
#include <process.h>

using namespace std;

struct mystruct {
    short* array;
    int size;
};



void worker(LPVOID object1) {
    mystruct* object = (mystruct*)object1;
    cout << "Odd elements:";
    for (int i = 0; i < object->size; i++) {
        if (object->array[i] % 2 == 1) {
            cout << endl;
            cout << object->array[i] ;
        }
    }
}

int main() {
    HANDLE hThread;
    DWORD IDThread;
    UINT IDThread1;

    srand(time(NULL));
    mystruct object;
    
    cout << "Enter array size:" << "\n";
    cin >> object.size;
    cout << "\n";

    short* array = new short[object.size];
    cout << "Array:" << "\n";

    for (int i = 0; i < object.size; i++) {
        array[i] = rand();
        cout << array[i] << "\n";
    }

    object.array = array;
    cout << "\n";

    int worker_suspend_time, worker_restart_time;
    cout << "Enter worker suspend time"; 
    cin >> worker_suspend_time;
    cout << "Enter worker resume time"; 
    cin >> worker_restart_time;

    hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)worker, &object, 0, &IDThread);

    if (hThread == NULL)
        return GetLastError();

    Sleep(worker_suspend_time);
    SuspendThread(hThread);
    Sleep(worker_restart_time);
    ResumeThread(hThread);
    WaitForSingleObject(hThread, INFINITE);
    TerminateThread(hThread, 0);
    CloseHandle(hThread);


    cout << "\n";
    cout << "_________________________________________________";
    cout << "\n";

    hThread = (HANDLE)
        _beginthreadex(NULL, 0, (_beginthreadex_proc_type)worker, &object, 0, &IDThread1);
    if (hThread == NULL)
        return GetLastError();
    WaitForSingleObject(hThread, INFINITE);
    TerminateThread(hThread, 0);
    CloseHandle(hThread);

    return 0;
}