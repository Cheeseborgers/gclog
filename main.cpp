#include "Log.hpp"

int main()
{
    gc::Log log;

    log.setLevel(gc::Log::INFO_LEVEL);
    log.setConsoleColouringStyle(gc::Log::ColorizeConsoleOutputStyle::ALL);
    log.warn("hello");
    log.info("hello");
    log.error("hello");

    return 0;
}
