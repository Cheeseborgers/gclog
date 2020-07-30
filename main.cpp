////////////////////////////////////////////////////////////////////////////////
//      main.cpp                                                            //
//                                                                            //
//      Created by Goodecheeseburgers on 28/07/2020.                          //
//                                                                            //
//      This program is free software: you can redistribute it and/or modify  //
//      it under the terms of the GNU General Public License as published by  //
//      the Free Software Foundation, either version 3 of the License, or     //
//      (at your option) any later version.                                   //
//                                                                            //
//      This program is distributed in the hope that it will be useful,       //
//      but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//      GNU General Public License for more details.                          //
//                                                                            //
//      You should have received a copy of the GNU General Public License     //
//      along with this program.  If not, see <https://www.gnu.org/licenses/>.//
////////////////////////////////////////////////////////////////////////////////


#include "Logger.hpp"

using namespace gc;

int main()
{
    ConsoleLogger log;
    FileLogger logt;

    log.setLevel(Logger::LogLevel::ERROR);
    log.setConsoleColourStyle(
            ConsoleLogger::ColorizeConsoleOutput::LEVEL_ONLY);
    log.setAppendDateTime(
            Logger::AppendDateTimeFormat::TIME_ONLY);
    log.warn("hello");

    log.setConsoleColourStyle(
            ConsoleLogger::ColorizeConsoleOutput::LEVEL_ONLY);
    log.setAppendDateTime(Logger::AppendDateTimeFormat::DATE_ONLY);
    log.info("hello");

    log.setConsoleColourStyle(ConsoleLogger::ColorizeConsoleOutput::ALL);
    log.trace("hello");
    log.debug("hello");

    log.setAppendDateTime(Logger::AppendDateTimeFormat::DATE_TIME);
    log.error("hello");

    logt.warn("hello");

    return 0;
}

