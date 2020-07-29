#include "Log.hpp"

int main()
{
    gcb::Log log;

    log.setLevel(gcb::Log::Error);
    log.warn("hello");
    log.info("hello");
    log.error("hello");

    return 0;
}
