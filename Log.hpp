////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//      Logger.hpp                                                                                                    //
//                                                                                                                    //
//      Created by Goodecheeseburgers on 28/07/2020.                                                                  //
//                                                                                                                    //
//      This program is free software: you can redistribute it and/or modify                                          //
//      it under the terms of the GNU General Public License as published by                                          //
//      the Free Software Foundation, either version 3 of the License, or                                             //
//      (at your option) any later version.                                                                           //
//                                                                                                                    //
//      This program is distributed in the hope that it will be useful,                                               //
//      but WITHOUT ANY WARRANTY; without even the implied warranty of                                                //
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                                                 //
//      GNU General Public License for more details.                                                                  //
//                                                                                                                    //
//      You should have received a copy of the GNU General Public License                                             //
//      along with this program.  If not, see <https://www.gnu.org/licenses/>.                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GCLOG_LOG_HPP
#define GCLOG_LOG_HPP

#include <iostream>
#include <sstream>
#include <ctime>

namespace gc {
    enum ColorCode {
        FG_DEFAULT = 39,
        FG_BLACK = 30,
        FG_RED = 31,
        FG_GREEN = 32,
        FG_YELLOW = 33,
        FG_BLUE = 34,
        FG_MAGENTA = 35,
        FG_CYAN = 36,
        FG_LIGHT_GRAY = 37,
        FG_DARK_GRAY = 90,
        FG_LIGHT_RED = 91,
        FG_LIGHT_GREEN = 92,
        FG_LIGHT_YELLOW = 93,
        FG_LIGHT_BLUE = 94,
        FG_LIGHT_MAGENTA = 95,
        FG_LIGHT_CYAN = 96,
        FG_WHITE = 97,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_BLUE = 44,
        BG_DEFAULT = 49
    };

    class ColorModifier {
        ColorCode code;
    public:
        ColorModifier(ColorCode pCode) : code(pCode) {}

        friend std::ostream &
        operator<<(std::ostream &os, const ColorModifier &mod) {
            return os << "\033[" << mod.code << "m";
        }
    };

    class Time {
    public:
        static const std::string getTime() {
            std::ostringstream oss;

            // Current date/time based on current system.
            time_t now = time(nullptr);

            // This returns a pointer to the time in the form of a tm structure.
            // The time is represented in Coordinated Universal Time (UTC),
            // which is essentially Greenwich Mean Time (GMT).
            tm *ltm = localtime(&now);

            // Fill oss stream with various time components of tm structure.
            oss << ' ' << ltm->tm_hour << ':'
                << ltm->tm_min << ':'
                << ltm->tm_sec;

            return oss.str();
        }

        static const std::string getDate() {
            std::ostringstream oss;

            // Current date/time based on current system.
            time_t now = time(nullptr);

            // This returns a pointer to the time in the form of a tm structure.
            // The time is represented in Coordinated Universal Time (UTC),
            // which is essentially Greenwich Mean Time (GMT).
            tm *ltm = localtime(&now);

            // Fill oss stream with various date components of tm structure.
            oss << ' ' << ltm->tm_mday << '/'
                << 1 + ltm->tm_mon << '/'
                << 1900 + ltm->tm_year;

            return oss.str();
        }
    };

    class Log {
    public:

        enum LogLevel : char {
            ERROR_LEVEL = 0, WARNING_LEVEL, INFO_LEVEL
        };
        enum ColorizeConsoleOutputStyle : char {
            NONE = 0, LEVEL_ONLY, ALL
        };
        enum AppendDateTime : char {
            TIME_ONLY = 0, DATE_ONLY, BOTH
        };

    private:
        LogLevel m_logLevel{INFO_LEVEL};
        ColorizeConsoleOutputStyle m_colorizeStyle{NONE};
        AppendDateTime m_dateTimeLevel{BOTH};

        ColorModifier m_defaultColor{FG_DEFAULT};
        ColorModifier m_errorColor{FG_RED};
        ColorModifier m_warnColor{FG_GREEN};
        ColorModifier m_infoColor{FG_YELLOW};

    public:
        // Methods
        void setLevel(LogLevel level) {
            m_logLevel = level;
        }

        void setAppendDateTimeLevel(LogLevel level) {
            m_logLevel = level;
        }

        void setConsoleColouringStyle(ColorizeConsoleOutputStyle style) {
            m_colorizeStyle = style;
        }

        void error(const char *message) {
            if (m_logLevel >= ERROR_LEVEL) {
                switch (m_colorizeStyle) {
                    case NONE:
                        std::cout << "[ERROR_LEVEL]: " << message << Time::getTime() << Time::getDate() << '\n';
                        break;
                    case LEVEL_ONLY:
                        std::cout << m_errorColor << "[ERROR_LEVEL]: " << m_defaultColor << message << '\n';
                        break;
                    case ALL:
                        std::cout << m_errorColor << "[ERROR_LEVEL]: " << message << '\n';
                        break;
                }
            }
        }

        void warn(const char *message) {
            if (m_logLevel >= WARNING_LEVEL) {
                switch (m_colorizeStyle) {
                    case NONE:
                        std::cout << "[WARNING_LEVEL]: " << message << '\n';
                        break;
                    case LEVEL_ONLY:
                        std::cout << m_warnColor << "[WARNING_LEVEL]: " << m_defaultColor << message << '\n';
                        break;
                    case ALL:
                        std::cout << m_warnColor << "[WARNING_LEVEL]: " <<  message << '\n';
                        break;
                }
            }
        }

        void info(const char *message) {
            if (m_logLevel >= INFO_LEVEL) {
                switch (m_colorizeStyle) {
                    case NONE:
                        std::cout << "[INFO_LEVEL]: " << message << '\n';
                        break;
                    case LEVEL_ONLY:
                        std::cout << m_infoColor << "[INFO_LEVEL]: " << m_defaultColor << message << '\n';
                        break;
                    case ALL:
                        std::cout << m_infoColor << "[INFO_LEVEL]: " <<  message << '\n';
                        break;
                }
            }
        }

    };

}//namespace gcb



#endif //GCLOG_LOG_HPP
