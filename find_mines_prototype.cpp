#include <comdef.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;


int main(void) {
	LPWSTR path_to_exe = L"C:\\Users\\lesya\\Downloads\\Minesweeper-master\\Minesweeper-master\\build-minesweeper-Desktop_Qt_5_8_0_MSVC2015_64bit-Debug\\debug\\Minesweeper.exe";

	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;
	if (!CreateProcess(path_to_exe, L"", NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
	{
		cout << "Failed to start process" << endl;
		return 1;
	}

	/*
	HMODULE module_handle = GetModuleHandle(path_to_exe);
	if (!module_handle) 
	{
		cout << "Failed to get module handle" << endl;
		cout << GetLastError() << endl;
		_com_error err(GetLastError());
		LPCTSTR errorText = err.ErrorMessage();
		cout << "err: " << errorText << endl;
		goto hell;
	}
	cout << module_handle << endl;
	
	goto hell;
	*/
	

	SYSTEM_INFO s_info;
	GetNativeSystemInfo(&s_info);

	cout << s_info.lpMaximumApplicationAddress << endl;

	HANDLE proc_handle = processInfo.hProcess;
	void* cur_mem_addr = (void*)0x140000000;

	int field_width = 9;
	int field_height = 9;

	uint64_t val;
	cin >> hex >> val;
	cur_mem_addr = (void*)val;
	cout << cur_mem_addr << endl;

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
		cout << "\tregion size: " << mem_info.RegionSize << endl;
		uint64_t reg_size = mem_info.RegionSize;
		uint64_t max_mem = static_cast<uint64_t>(1e8);
		if (reg_size > max_mem) {
			reg_size = max_mem;
		}

		char* buffer = new char[reg_size];
		
		if (!ReadProcessMemory(proc_handle, cur_mem_addr, buffer, reg_size, NULL))
		{
			cout << "Failed to read process memory" << endl;
			cout << GetLastError() << endl;
			goto hell;
		}

		for (int idx = 0; idx < reg_size; idx++) {
			const int pat_length = 17;
			char pattern[pat_length + 3];
			memset(pattern, 0, sizeof(pattern));

			for (int y = 1; y <= field_height; y++) {
				for (int x = 1; x <= field_width; x++) {
					// Search for 
					// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 <-- just indicies, for convenience.
					// y 0 0 0 x 0 0 0 0 0 0  0  0  0  0  1  0
					// (17 characters in total).
					// If this is found, then a mine is *probably* set at (x, y).
					pattern[0] = y;
					pattern[4] = x;
					pattern[15] = 1;
					pattern[16] = 0; // TODO: make it zero after debug.
					bool found_correctly = true;
					for (int shift = 0; found_correctly && shift < pat_length; shift++) {
						int mem_shifted_idx = idx + shift;
						if (mem_shifted_idx >= reg_size) {
							found_correctly = false;
							break;
						}
						found_correctly &= pattern[shift] == buffer[mem_shifted_idx];
					}

					if (found_correctly)
					{
						// TODO: we want to find actual mines, not "no mines".
						cout << dec << "Probably mine in cell x=" << x << ", y=" << y << endl;
						cout << hex << idx + (uint64_t)(cur_mem_addr) << endl;
					}
				}
			}
		}

		delete[] buffer;

		cur_mem_addr = (LPVOID)((char*)mem_info.BaseAddress +
			reg_size);
	}

hell:
	WaitForSingleObject(processInfo.hProcess, INFINITE);
	//TerminateProcess(processInfo.hProcess, 0);
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
	return 0;
}