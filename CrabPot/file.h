#include "includes.h"

static class File {
private:


public:



	static std::string GetThisFileNameAndPath() {

		char buffer[MAX_PATH];
		GetModuleFileNameA(NULL, buffer, MAX_PATH);


		return std::string(buffer);
	}
	static std::string GetThisFilePath() {

		char buffer[MAX_PATH];
		GetModuleFileNameA(NULL, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");


		return std::string(buffer).substr(pos + 1);
	}
	static std::string Read(std::string path) {

		std::string result;
		std::ifstream file(path);
		if (!file.is_open()) {

		}
		std::string line;
		while (std::getline(file, line)) {
			result += line + "\n";
		}
		file.close();
		return result;
	}

	static void Write(std::string path, std::string content) {

		std::ofstream file(path);
		if (!file.is_open()) {

		}
		file << content;
		file.close();

	}

	static void Append(std::string path, std::string content) {

		std::ofstream file(path, std::ios::app);
		if (!file.is_open()) {

		}
		file << content;
		file.close();

	}

	static void Delete(std::string path) {

		if (!DeleteFileA(path.c_str())) {
		}
	}

	// create new file if not exists
	static void Create(std::string path) {

		std::ofstream file(path);
		if (!file.is_open()) {
			
		}
		file.close();


	}



	static void DeleteFolder(std::string path) {

		if (!RemoveDirectoryA(path.c_str())) {
		}
	}
	// does file exist 
	static bool Exists(std::string path) {

		return (GetFileAttributesA(path.c_str()) != INVALID_FILE_ATTRIBUTES);
	}
	static bool FolderExists(std::string path) {

		DWORD ftyp = GetFileAttributesA(path.c_str());
		if (ftyp == INVALID_FILE_ATTRIBUTES)
			return false;

		if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
			return true;

		return false;
	}
	static void CreateFolder(std::string path) {

		if (!CreateDirectoryA(path.c_str(), NULL)) {
			if (FolderExists(path)) {
			}
			else {
			}
		}


	}
};
