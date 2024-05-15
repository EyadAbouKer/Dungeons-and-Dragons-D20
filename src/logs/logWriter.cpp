//
// Created by Admin on 4/13/2024.
//

#include "logWriter.h"

 std::string LogWriter::getCurrentTime() {
    // Get the current time
    std::time_t currentTime = std::time(nullptr);

    // Convert the current time to local time
    std::tm* localTime = std::localtime(&currentTime);

    // Create a string stream to build the time string
    std::stringstream ss;

    // Format and append the local time components to the string stream
    ss << localTime->tm_hour << ":" // hour (0-23)
       << localTime->tm_min << ":"  // minute (0-59)
       << localTime->tm_sec << " "  // second (0-59)
       << localTime->tm_mday << "/" // day of the month (1-31)
       << (localTime->tm_mon + 1) << "/" // month (0-11, so add 1)
       << (localTime->tm_year + 1900); // year (since 1900)

    // Return the string representation of the current local time
    return ss.str();
}
