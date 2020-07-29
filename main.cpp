#include "Log.hpp"

int main()
{
    gc::Log log;

    log.setLevel(gc::Log::ERROR);
    log.warn("hello");
    log.info("hello");
    log.error("hello");

    return 0;
}
