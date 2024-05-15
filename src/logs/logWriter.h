//
// Created by Admin on 4/13/2024.
//

#ifndef D20_LOGWRITER_H
#define D20_LOGWRITER_H
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>

class LogWriter {
    static std::string getCurrentTime();
public:
    template<typename T>
    static void writeLogsToFile(const T& content);
    template<typename T>
    static void writeLogsToFilee(const T &content);
};

template<typename T>
void LogWriter::writeLogsToFile(const T &contentt) {
    std::ofstream outtFile("../src/gameLogs.txt", std::ios::app);

    if (outtFile.is_open()) {
        outtFile << contentt << getCurrentTime() << " \n\n"; // Write the content to the file
        outtFile.close();
    }
}

template<typename T>
void LogWriter::writeLogsToFilee(const T &content) {
    std::ofstream outFile("../src/MAPOUT.txt", std::ios::trunc); // Open file in trunc mode

    if (outFile.is_open()) {
        outFile << content << getCurrentTime() << " \n\n"; // Write the content to the file
        outFile.close();
    }
}

#endif //D20_LOGWRITER_H
