/*
Name: Process Counter
Author: Lee In Hyeok
Y-M-D : 2021-04-09

Func:
1초 단위로 동작중인 프로세스의 개수를 계산하여 출력
*/

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <psapi.h>
#include <tchar.h>
#include <Tlhelp32.h>

int main()
{
    int cnt_Processes; // 현재 프로세스 개수

    while (1)
    {
        cnt_Processes = 0;                                                 // 초기화
        HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // 시스템 정보를 가진 함수 호출.
        // TH32CS_SNAPPROCESS : 그 중에서 시스템의 모든 프로세스 나타냄

        if (hProcess)
        {
            {
                BOOL process_Count;
                PROCESSENTRY32 process_info; // 프로세스 정보를 담기위한 공간( 프로세스 ID 등..)
                process_info.dwSize = sizeof(PROCESSENTRY32);
                process_Count = Process32First(hProcess, &process_info); // Process32First : hProcess(=snapshot)의 프로세스 수를 세기위한 함수
                // 첫 번째 프로세스 리스트 들이 버퍼에 복사되면 TRUE 반환
                while (process_Count)
                {
                    process_Count = Process32Next(hProcess, &process_info); // 다음 프로세스 리스트가 버퍼에 복사되면 true 반환 없으면 false
                    cnt_Processes++;                                        // 프로세스 카운터
                }

                CloseHandle(hProcess);
            }
            // 시간 설정 부분
            time_t t = time(NULL);
            struct tm ti = *localtime(&t);

            // 프린트(년도.월.일 시:분:초 : 프로세스 개수)
            printf("%d.%02d.%02d %02d:%02d:%02d : %03d\n", ti.tm_year + 1900, ti.tm_mon + 1, ti.tm_mday, ti.tm_hour, ti.tm_min, ti.tm_sec, cnt_Processes);
            Sleep(1000);
        }
    }
    return 0;
}