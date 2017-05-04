#include "stdafx.h"

#include <comdef.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;



int main(void) {
	//freopen("output.txt", "w", stdout);
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

	HANDLE proc_handle = processInfo.hProcess;
	void* cur_mem_addr = (void*)0;

	int field_width = 50;
	int field_height = 50;

	while (true)
	{
		Sleep(1000);
		cur_mem_addr = 0;

		while (cur_mem_addr < s_info.lpMaximumApplicationAddress)
		{
			MEMORY_BASIC_INFORMATION mem_info;
			if (!VirtualQueryEx(proc_handle, cur_mem_addr, &mem_info, sizeof(mem_info)))
			{
				cout << "Failed to get info about memory " << GetLastError() << endl;
				goto hell;
			}
			cur_mem_addr = mem_info.BaseAddress;
			//cout << "Current address: " << cur_mem_addr << endl;
			//cout << "\tregion size: " << mem_info.RegionSize << endl;
			uint64_t reg_size = mem_info.RegionSize;
			uint64_t max_mem = static_cast<uint64_t>(1e8);
			if (reg_size > max_mem) {
				reg_size = max_mem;
			}

			unsigned char* buffer = new unsigned char[reg_size];

			if (!ReadProcessMemory(proc_handle, cur_mem_addr, buffer, reg_size, NULL))
			{
				reg_size = mem_info.RegionSize;
				goto loop_end;
			}

			const int pat_length = 17;
			char pattern[pat_length + 3];
			memset(pattern, 0, sizeof(pattern));
			pattern[15] = 1;
			pattern[16] = 0; // TODO: make it zero after debug.
			// Search for 
			// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 <-- just indices, for convenience.
			// y 0 0 0 x 0 0 0 0 0 0  0  0  0  0  1  0
			// (17 characters in total).
			// If this is found, then a mine is *probably* set at (x, y).
			for (size_t idx = 0; idx < reg_size; idx++) {
				if (idx + pat_length >= reg_size)
					break;

				unsigned y = buffer[idx];
				unsigned x = buffer[idx + 4];

				bool found_correctly = (1 <= x && x <= field_width) && (1 <= y && y <= field_height);

				for (size_t shift = 0; found_correctly && shift < pat_length; shift++) {
					size_t mem_shifted_idx = idx + shift;
					if (shift == 0 || shift == 4) // indices of `y` and `x`.
						continue;
					found_correctly &= pattern[shift] == buffer[mem_shifted_idx];
				}

				if (found_correctly)
				{
					// TODO: we want to find actual mines, not "no mines".
					cout << dec << "Probably a mine in cell x=" << x << ", y=" << y << endl;
					cout << hex << idx + (uint64_t)(cur_mem_addr) << endl;
				}
			}

		loop_end:
			delete[] buffer;

			cur_mem_addr = (LPVOID)((char*)mem_info.BaseAddress +
				reg_size);
		}
	}

hell:
	WaitForSingleObject(processInfo.hProcess, INFINITE);
	//TerminateProcess(processInfo.hProcess, 0);
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
	return 0;
}