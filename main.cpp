#include "Logger.hpp"

using namespace gc;

int main()
{
    ConsoleLogger log;

    log.setLevel(Logger::INFO_LEVEL);
    log.setConsoleColourStyle(Logger::ColorizeConsoleOutputStyle::LEVEL_ONLY);
    log.setAppendDateTime(Logger::AppendDateTimeFormat::TIME_ONLY);
    log.warn("hello");

    log.setConsoleColourStyle(Logger::ColorizeConsoleOutputStyle::LEVEL_ONLY);
    log.setAppendDateTime(Logger::AppendDateTimeFormat::DATE_ONLY);
    log.info("hello");

    log.setConsoleColourStyle(Logger::ColorizeConsoleOutputStyle::ALL);
    log.setAppendDateTime(Logger::AppendDateTimeFormat::DATE_TIME);
    log.error("hello");

    return 0;
}

