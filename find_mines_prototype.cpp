#include "stdafx.h"

#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;


int main(void) {
	LPWSTR path_to_exe = L"C:\\study\\devdays\\Minesweeper\\build-minesweeper-Desktop_Qt_5_6_2_MSVC2015_64bit-Release\\release\\Minesweeper.exe";

	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;
	if (!CreateProcess(path_to_exe, L"", NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
	{
		cout << "Failed to start process" << endl;
		return 1;
	}

	SYSTEM_INFO s_info;
	GetNativeSystemInfo(&s_info);

	cout << s_info.lpMaximumApplicationAddress << endl;

	HANDLE proc_handle = processInfo.hProcess;
	void* cur_mem_addr = 0;

	int field_width = 5;
	int field_height = 5;

	while (cur_mem_addr < s_info.lpMaximumApplicationAddress)
	{
		MEMORY_BASIC_INFORMATION mem_info;
		if (!VirtualQueryEx(proc_handle, cur_mem_addr, &mem_info, sizeof(mem_info)))
		{
			cout << "Failed to get info about memory " << GetLastError() << endl;
			goto hell;
		}
		cur_mem_addr = mem_info.BaseAddress;
		cout << "Current address: " << cur_mem_addr << endl;

		char* buffer = new char[mem_info.RegionSize];
		ReadProcessMemory(proc_handle, cur_mem_addr, buffer, mem_info.RegionSize, NULL);
		cout << "\tregion size: " << mem_info.RegionSize << endl;
		for (int idx = 0; idx < mem_info.RegionSize; idx++) {
			for (int y = 1; y <= field_height; y++) {
				for (int x = 1; x <= field_width; x++) {
					// Search for 
					// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 <-- just indicies, for convenience.
					// y 0 0 0 x 0 0 0 0 0 0  0  0  0  0  1  0
					// (17 characters in total).
					// If this is found, then a mine is *probably* set at (x, y).
					const int pat_length = 17;
					char pattern[pat_length];
					memset(pattern, 0, sizeof(pattern));
					pattern[0] = y;
					pattern[4] = x;
					pattern[15] = 1;
					pattern[16] = 1; // TODO: make it zero after debug.
					bool found_correctly = true;
					for (int shift = 0; found_correctly && shift < pat_length; shift++) {
						int mem_shifted_idx = idx + shift;
						if (mem_shifted_idx >= mem_info.RegionSize) {
							found_correctly = false;
							break;
						}
						found_correctly &= pattern[shift] == buffer[mem_shifted_idx];
					}

					if (found_correctly)
					{
						cout << "Probable mine in cell x=" << x << ", y=" << y << endl;
					}
				}
			}
		}

		delete[] buffer;

		cur_mem_addr = (LPVOID)((char*)mem_info.BaseAddress +
			mem_info.RegionSize);
	}

hell:
	WaitForSingleObject(processInfo.hProcess, INFINITE);
	//TerminateProcess(processInfo.hProcess, 0);
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
	return 0;
}