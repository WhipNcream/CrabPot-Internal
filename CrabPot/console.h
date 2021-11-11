#include "includes.h"

static class Console
{
private:
	// get time in format hh:mm:ss
    static std::string GetTime()
	{
		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];

		std::time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		strftime(buffer, sizeof(buffer), "%X", &timeinfo);
		std::string str(buffer);
		str = "[" + str + "]";
		return str;
	}

public:
	static void Clear() {
        system("cls");
	}
	static void Log(std::string string) {
		std::cout << GetTime() + " " + string << std::endl;
	}
    static void Log(std::string string, std::string string2) {
        std::cout << GetTime() + " " + string + " " + string2 << std::endl;
    }
    static void Log(std::string string, int number) {
        std::cout << GetTime() + " " + string + " " + std::to_string(number) << std::endl;
    }
    static void Log(std::string string, float number) {
        std::cout << GetTime() + " " + string + " " + std::to_string(number) << std::endl;
    }
    static void Log(std::string string, double number) {
        std::cout << GetTime() + " " + string + " " + std::to_string(number) << std::endl;
    }
    static void Log(std::string string, bool boolean) {
        std::cout << GetTime() + " " + string + " " + std::to_string(boolean) << std::endl;
    }

   	static void Log(const char* string) {
		std::cout << GetTime() + " " + string << std::endl;
	}
    static void Log(const char* string, const char* string2) {
        std::cout << GetTime() + " " + string + " " + string2 << std::endl;
    }
    static void Log(const char* string , int number) {
        std::cout << GetTime() + " " + string + " " + std::to_string(number) << std::endl;
    }
    static void Log(const char* string , float number) {
        std::cout << GetTime() + " " + string + " " + std::to_string(number) << std::endl;
    }
    static void Log(const char* string , double number) {
        std::cout << GetTime() + " " + string + " " + std::to_string(number) << std::endl;
    }
    static void Log(const char* string , bool boolean) {
        std::cout << GetTime() + " " + string + " " + std::to_string(boolean) << std::endl;
    }

	static void Log(int number) {
        std::cout << GetTime() + " " + std::to_string(number) << std::endl;
    }
    static void Log(float number) {
        std::cout << GetTime() + " " + std::to_string(number) << std::endl;
    }
    static void Log(double number) {
        std::cout << GetTime() + " " + std::to_string(number) << std::endl;
    }
    static void Log(bool boolean) {
        std::cout << GetTime() + " " + std::to_string(boolean) << std::endl;
    }

    static void Log(int number, std::string string) {
        std::cout << GetTime() + " " + std::to_string(number) + " " + string << std::endl;
    }
    static void Log(float number, std::string string) {
        std::cout << GetTime() + " " + std::to_string(number) + " " + string << std::endl;
    }
    static void Log(double number, std::string string) {
        std::cout << GetTime() + " " + std::to_string(number) + " " + string << std::endl;
    }
    static void Log(bool boolean, std::string string) {
        std::cout << GetTime() + " " + std::to_string(boolean) + " " + string << std::endl;
    }
        

};