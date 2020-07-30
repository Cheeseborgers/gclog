////////////////////////////////////////////////////////////////////////////////
//      Logger.hpp                                                            //
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

#ifndef GCLOG_LOGGER_HPP
#define GCLOG_LOGGER_HPP

#include <iostream>
#include <sstream>
#include <ctime>

namespace gc {
enum ConsoleColorCode : char {
    FG_DEFAULT [[maybe_unused]] = 39,
    FG_BLACK [[maybe_unused]] = 30,
    FG_RED [[maybe_unused]] = 31,
    FG_GREEN [[maybe_unused]] = 32,
    FG_YELLOW [[maybe_unused]] = 33,
    FG_BLUE [[maybe_unused]] = 34,
    FG_MAGENTA [[maybe_unused]] = 35,
    FG_CYAN [[maybe_unused]]= 36,
    FG_LIGHT_GRAY [[maybe_unused]] = 37,
    FG_DARK_GRAY [[maybe_unused]] = 90,
    FG_LIGHT_RED [[maybe_unused]] = 91,
    FG_LIGHT_GREEN [[maybe_unused]] = 92,
    FG_LIGHT_YELLOW [[maybe_unused]] = 93,
    FG_LIGHT_BLUE [[maybe_unused]] = 94,
    FG_LIGHT_MAGENTA [[maybe_unused]] = 95,
    FG_LIGHT_CYAN [[maybe_unused]] = 96,
    FG_WHITE [[maybe_unused]] = 97,
    BG_RED [[maybe_unused]] = 41,
    BG_GREEN [[maybe_unused]] = 42,
    BG_BLUE [[maybe_unused]] = 44,
    BG_DEFAULT [[maybe_unused]] = 49
};
// -----------------------------------------------------------------------------
class ConsoleColor
{
private:
    ConsoleColorCode code;
public:
    [[maybe_unused]] ConsoleColor(ConsoleColorCode pCode) : code(pCode) {}

    friend std::ostream &
    operator<<(std::ostream &os, const ConsoleColor &mod) {
        return os << "\033[" << mod.code << "m";
    }
};
// -----------------------------------------------------------------------------
class Time
{
public:
    static const std::string getTime()
    {
        std::ostringstream oss;

        // Current date/time based on current system.
        time_t now = time(nullptr);

        // This returns a pointer to the time in the
        // form of a tm structure.
        // The time is represented in Coordinated Universal
        // Time (UTC), which is essentially
        // Greenwich Mean Time (GMT).
        tm *ltm = localtime(&now);

        // Fill oss stream with various time components
        // of tm structure.
        oss << ' ' << ltm->tm_hour << ':'
            << ltm->tm_min << ':'
            << ltm->tm_sec;

        return oss.str();
    }
// -----------------------------------------------------------------------------
    static const std::string getDate() {
        std::ostringstream oss;

        // Current date/time based on current system.
        time_t now = time(nullptr);

        // This returns a pointer to the time in the form
        // of a tm structure.
        // The time is represented in Coordinated Universal
        // Time (UTC), which is essentially
        // Greenwich Mean Time (GMT).
        tm *ltm = localtime(&now);

        // Fill oss stream with various date components
        // of tm structure.
        oss << ' ' << ltm->tm_mday << '/'
            << 1 + ltm->tm_mon << '/'
            << 1900 + ltm->tm_year;

        return oss.str();
    }
};
// -----------------------------------------------------------------------------
class Logger
{
public:
    enum LogLevel : char {
        ERROR_LEVEL = 0, WARNING_LEVEL, INFO_LEVEL
    };
    enum ColorizeConsoleOutputStyle : char {
        NO_COLOR = 0, LEVEL_ONLY, ALL
    };
    enum AppendDateTimeFormat : char {
        NONE = 0, TIME_ONLY, DATE_ONLY, DATE_TIME
    };

    Logger() {}
    Logger(LogLevel logLevel)
        :m_logLevel(logLevel) {}
    Logger(LogLevel logLevel, AppendDateTimeFormat dateTimeFormat)
        : m_logLevel(logLevel), m_dateTimeFormat(dateTimeFormat) {}

    virtual ~Logger() = default;
    Logger(const Logger&) = delete;            // non construction-copyable
    Logger(Logger&&) = delete;                 // non movable
    Logger& operator=(const Logger&) = delete; // non copyable
    Logger& operator=(Logger&&) = delete;      // move assignment

private:
    AppendDateTimeFormat m_dateTimeFormat{DATE_TIME};
    LogLevel m_logLevel{INFO_LEVEL};

public:
    // Setters -----------------------------------------------------------------
    void setLevel(LogLevel level){m_logLevel = level; }
    // -------------------------------------------------------------------------
    void setAppendDateTime(AppendDateTimeFormat level)
    {
        m_dateTimeFormat = level;
    }
    // Getters -----------------------------------------------------------------
    LogLevel getLogLevel() const {return m_logLevel;}
    // -------------------------------------------------------------------------
    const std::string getDateTimeString()
    {
        std::string date_time{""};

        switch (m_dateTimeFormat) {
            case TIME_ONLY:
                date_time += Time::getTime();
                break;
            case DATE_ONLY:
                date_time += Time::getDate();
                break;
            case DATE_TIME:
                date_time += Time::getTime();
                date_time += Time::getDate();
                break;
            case NONE:
                break;
        }

        return date_time;
    }

    // Pure virtual methods
    virtual void error(const std::string& message) = 0;
    // ---------------------------------------------------------------------
    virtual void warn(const std::string& message) = 0;
    // ---------------------------------------------------------------------
    virtual void info(const std::string& message) = 0;
    // ---------------------------------------------------------------------
};
// -----------------------------------------------------------------------------
class ConsoleLogger final : public Logger
{
public:
    ConsoleLogger() : Logger() {}
    ConsoleLogger(LogLevel logLevel) : Logger(logLevel) {}
    ConsoleLogger(LogLevel logLevel, AppendDateTimeFormat dateTimeFormat)
    : Logger(logLevel, dateTimeFormat) {}

    ConsoleLogger(LogLevel logLevel,
            ConsoleColor errorColor,
            ConsoleColor warnColor,
            ConsoleColor infoColor)
            : m_errorColor(errorColor),
             m_warnColor(warnColor),
             m_infoColor(infoColor),
             Logger(logLevel){}
    ConsoleLogger(LogLevel logLevel,
            AppendDateTimeFormat dateTimeFormat,
            ConsoleColor errorColor,
            ConsoleColor warnColor,
            ConsoleColor infoColor)
            : m_errorColor(errorColor),
              m_warnColor(warnColor),
              m_infoColor(infoColor),
              Logger(logLevel, dateTimeFormat) {}
    ConsoleLogger(LogLevel logLevel,
            AppendDateTimeFormat dateTimeFormat,
            ColorizeConsoleOutputStyle colorizeOutput,
            ConsoleColor errorColor,
            ConsoleColor warnColor,
            ConsoleColor infoColor)
            : m_errorColor(errorColor),
              m_warnColor(warnColor),
              m_infoColor(infoColor),
              m_colorizeStyle(colorizeOutput),
              Logger(logLevel, dateTimeFormat) {}

ConsoleLogger(const ConsoleLogger&) = delete;      // non construction-copyable
    ConsoleLogger(ConsoleLogger&&) = delete;                 // non movable
    ConsoleLogger& operator=(const ConsoleLogger&) = delete; // non copyable
    ConsoleLogger& operator=(ConsoleLogger&&) = delete;      // move assignment

private:
    ColorizeConsoleOutputStyle m_colorizeStyle{NO_COLOR};

    ConsoleColor m_defaultColor{FG_DEFAULT};
    ConsoleColor m_errorColor{FG_RED};
    ConsoleColor m_warnColor{FG_GREEN};
    ConsoleColor m_infoColor{FG_YELLOW};

public:
    // ---------------------------------------------------------------------
    void setConsoleColourStyle(ColorizeConsoleOutputStyle style)
    {
        m_colorizeStyle = style;
    }
    // ---------------------------------------------------------------------
    void error(const std::string& message)
    {
        if (getLogLevel() >= ERROR_LEVEL)
        {
            std::string date_time = getDateTimeString();

            switch (m_colorizeStyle)
            {
                case NO_COLOR:
                    std::cout << m_defaultColor << "[ERROR]: "
                              << m_defaultColor << message << date_time << '\n';
                    break;
                case LEVEL_ONLY:
                    std::cout << m_errorColor << "[ERROR]: "
                              << m_defaultColor << message << date_time << '\n';
                    break;
                case ALL:
                    std::cout << m_errorColor << "[ERROR]: " << message
                              <<  date_time << '\n';
                    break;
            }
        }
    }
    // ---------------------------------------------------------------------
    void warn(const std::string& message)
    {
        if (getLogLevel() >= WARNING_LEVEL)
        {
            std::string date_time = getDateTimeString();

            switch (m_colorizeStyle)
            {
                case NO_COLOR:
                    std::cout << m_defaultColor << "[WARNING]: "
                              << m_defaultColor << message << date_time << '\n';
                    break;
                case LEVEL_ONLY:
                    std::cout << m_warnColor << "[WARNING]: "
                              << m_defaultColor << message << date_time << '\n';
                    break;
                case ALL:
                    std::cout << m_warnColor << "[WARNING]: " << message
                              <<  date_time << '\n';
                    break;
            }
        }
    }
    // ---------------------------------------------------------------------
    void info(const std::string& message)
    {
        if (getLogLevel() >= INFO_LEVEL)
        {
            std::string date_time = getDateTimeString();

            switch (m_colorizeStyle)
            {
                case NO_COLOR:
                    std::cout << m_defaultColor << "[INFO]: "
                              << m_defaultColor << message << date_time << '\n';
                    break;
                case LEVEL_ONLY:
                    std::cout << m_infoColor << "[INFO]: "
                              << m_defaultColor << message << date_time << '\n';
                    break;
                case ALL:
                    std::cout << m_infoColor << "[INFO]: " << message
                              <<  date_time << '\n';
                    break;
            }
        }
    }
    // ---------------------------------------------------------------------

};

}//namespace gc



#endif //GCLOG_LOGGER_HPP
