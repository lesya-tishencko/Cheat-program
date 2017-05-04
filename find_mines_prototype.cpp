#include <comdef.h>
#include <TlHelp32.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;


size_t find_minesweeper_pid()
{
	HANDLE processes = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	

	PROCESSENTRY32 cur_entry;
	cur_entry.dwSize = sizeof(cur_entry);
	size_t result_pid = 0;

	if (Process32First(processes, &cur_entry)) 
	{
		do
		{
			if (wcscmp(cur_entry.szExeFile, L"Minesweeper.exe") == 0) {
				result_pid = cur_entry.th32ProcessID;
			}
		} while (Process32Next(processes, &cur_entry));
	}

	CloseHandle(processes);

	return result_pid;
}


int main(void) {
	size_t pid = find_minesweeper_pid();

	HANDLE proc_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	if (proc_handle == 0) 
	{
		cout << "Opening process failed with error #" << GetLastError() << endl;
		return 0;
	}
	

	SYSTEM_INFO s_info;
	GetNativeSystemInfo(&s_info);
	
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
			pattern[16] = 0; 
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
					cout << dec << "Probably a mine in cell x=" << x << ", y=" << y << endl;
					cout << hex << idx + (uint64_t)(cur_mem_addr) << endl;
					unsigned char* buffer_write = new unsigned char[17]();
					memset(buffer_write, 0, 17 * sizeof(*buffer_write));
					buffer_write[0] = y;
					buffer_write[4] = x;
					buffer_write[8] = 1;
					buffer_write[15] = 1;
					if (!WriteProcessMemory(proc_handle, (void *)(idx + (uint64_t)cur_mem_addr), buffer_write, 17, NULL))
						printf("WriteProcess failed (%d).\n", GetLastError());
					delete[] buffer_write;
				}
			}

		loop_end:
			delete[] buffer;

			cur_mem_addr = (LPVOID)((char*)mem_info.BaseAddress +
				reg_size);
		}
	}

hell:
	CloseHandle(proc_handle);
	return 0;
}