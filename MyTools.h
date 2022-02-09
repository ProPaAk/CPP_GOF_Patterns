#pragma once

#include <stdint.h>
#include <string>

namespace MyTools {
    enum ConsoleColor
    {
        CC_Black = 0,
        CC_Blue,
        CC_Green,
        CC_Cyan,
        CC_Red,
        CC_Magenta,
        CC_Brown,
        CC_LightGray,
        CC_DarkGray,
        CC_LightBlue,
        CC_LightGreen,
        CC_LightCyan,
        CC_LightRed,
        CC_LightMagenta,
        CC_Yellow,
        CC_White
    };

	//=============================================================================================

	void ClrScr();
    void SetColor(ConsoleColor color);
	void __fastcall GotoXY(double x, double y);
	uint16_t GetMaxX();
	uint16_t GetMaxY();

	//=============================================================================================
	// void __fastcall OpenLogFile(const std::string& FN);
	// void CloseLogFile();
	// void __fastcall WriteToLog(const std::string& str);
	// void __fastcall WriteToLog(const std::string& str, int n);
	// void __fastcall WriteToLog(const std::string& str, double d);

    class FileLoggerSingletone{
    public:
        static FileLoggerSingletone& getInstance(){
            static FileLoggerSingletone theInstance;
            return theInstance;
        }
    private:
        FileLoggerSingletone(){}
        FileLoggerSingletone(const FileLoggerSingletone& root) = delete;
        FileLoggerSingletone& operator=(const FileLoggerSingletone&) = delete;
    public:
        void CloseLogFile();
        void __fastcall OpenLogFile(const std::string& FN);
        void __fastcall WriteToLog(const std::string& str);
        void __fastcall WriteToLog(const std::string& str, int n);
        void __fastcall WriteToLog(const std::string& str, double d);
    };
};