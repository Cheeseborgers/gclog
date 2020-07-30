////////////////////////////////////////////////////////////////////////////////
//      Filename: Logger.hpp                                                  //
//                                                                            //
//      Gclog: A Minimal, Header only, Modern C++ Logger.                           //
//      https://github.com/Cheeseborgers/gclog                                //
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
#include <utility>
#include <fstream>
#include <mutex>

namespace gc {
    enum ConsoleColorCode : unsigned char {
        FG_DEFAULT [[maybe_unused]] = 39,
        FG_BLACK [[maybe_unused]] = 30,
        FG_RED [[maybe_unused]] = 31,
        FG_GREEN [[maybe_unused]] = 32,
        FG_YELLOW [[maybe_unused]] = 33,
        FG_BLUE [[maybe_unused]] = 34,
        FG_MAGENTA [[maybe_unused]] = 35,
        FG_CYAN [[maybe_unused]] = 36,
        FG_LIGHT_GRAY [[maybe_unused]] = 37,
        FG_DARK_GRAY [[maybe_unused]] = 90,
        FG_LIGHT_RED [[maybe_unused]] = 91,
        FG_LIGHT_GREEN [[maybe_unused]] = 92,
        FG_LIGHT_YELLOW [[maybe_unused]] = 93,
        FG_LIGHT_BLUE [[maybe_unused]] = 94,
        FG_LIGHT_MAGENTA [[maybe_unused]] = 95,
        FG_LIGHT_CYAN [[maybe_unused]] = 96,
        FG_WHITE [[maybe_unused]] = 97,
        FG_ORANGE [[maybe_unused]] = 166,
        BG_DEFAULT [[maybe_unused]] = 49,
        BG_RED [[maybe_unused]] = 41,
        BG_GREEN [[maybe_unused]] = 42,
        BG_YELLOW [[maybe_unused]] = 43,
        BG_BLUE [[maybe_unused]] = 44,
        BG_MAGENTA [[maybe_unused]] = 45,
        BG_CYAN [[maybe_unused]] = 46,
        BG_LIGHT_GRAY [[maybe_unused]] = 47,
        BG_DARK_GRAY [[maybe_unused]] = 90,
        BG_LIGHT_RED [[maybe_unused]] = 101,
        BG_LIGHT_GREEN [[maybe_unused]] = 102,
        BG_LIGHT_YELLOW [[maybe_unused]] = 103,
        BG_LIGHT_BLUE [[maybe_unused]] = 104,
        BG_LIGHT_MAGENTA [[maybe_unused]] = 105,
        BG_LIGHT_CYAN [[maybe_unused]] = 106,
        BG_WHITE [[maybe_unused]] = 107,
        BG_ORANGE [[maybe_unused]] = 214
    };

// -----------------------------------------------------------------------------
    class ConsoleColor {
    private:
        ConsoleColorCode code;
    public:
        [[maybe_unused]] explicit ConsoleColor(ConsoleColorCode pCode) : code(pCode) {}

        friend std::ostream &
        operator<<(std::ostream &os, const ConsoleColor &mod) {
        return os << "\033[" << mod.code << "m";
    }
};
// -----------------------------------------------------------------------------
class Time
{
public:
    inline static std::string getTime() {
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
    inline static std::string getDate() {
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
    enum class LogLevel : char {
        TRACE = 0, DEBUG = 1, INFO = 2, WARN = 3, ERROR = 4
    };
    enum class AppendDateTimeFormat : char {
        NONE = 0, TIME_ONLY, DATE_ONLY, DATE_TIME
    };

    Logger() = delete;
    explicit Logger(LogLevel logLevel)
            : m_logLevel(logLevel) {}

    Logger(LogLevel logLevel, AppendDateTimeFormat dateTimeFormat)
            : m_dateTimeFormat(dateTimeFormat), m_logLevel(logLevel) {}

    virtual ~Logger() = default;

    Logger(const Logger &) = delete;            // non construction-copyable
    Logger(Logger &&) = delete;                 // non movable
    Logger &operator=(const Logger &) = delete; // non copyable
    Logger &operator=(Logger &&) = delete;      // move assignment

protected:
    std::mutex lock;

private:
    AppendDateTimeFormat m_dateTimeFormat{AppendDateTimeFormat::DATE_TIME};
    LogLevel m_logLevel{LogLevel::INFO};

public:
    // Setters -----------------------------------------------------------------
    //
    [[maybe_unused]] void setLevel(LogLevel level) { m_logLevel = level; }

    // -------------------------------------------------------------------------
    void setAppendDateTime(AppendDateTimeFormat level)
    {
        m_dateTimeFormat = level;
    }

    // Getters -----------------------------------------------------------------
    [[nodiscard]] LogLevel getLogLevel() const { return m_logLevel; }

    // -------------------------------------------------------------------------
    inline std::string getDateTimeString() {
        std::string date_time;
        date_time.reserve(32);

        switch (m_dateTimeFormat) {
            case AppendDateTimeFormat::TIME_ONLY:
                date_time += Time::getTime();
                break;
            case AppendDateTimeFormat::DATE_ONLY:
                date_time += Time::getDate();
                break;
            case AppendDateTimeFormat::DATE_TIME:
                date_time += Time::getTime();
                date_time += Time::getDate();
                break;
            case AppendDateTimeFormat::NONE:
                break;
        }

        return date_time;
    }

    // Base Logger virtual methods, not pure virtual so you can use
    // as a null logger if you want.
    virtual void trace([[maybe_unused]] const std::string &message) {};

    virtual void debug([[maybe_unused]] const std::string &message) {};

    virtual void error([[maybe_unused]] const std::string &message) {};

    virtual void warn([[maybe_unused]] const std::string &message) {};

    virtual void info([[maybe_unused]] const std::string &message) {};
};
// -----------------------------------------------------------------------------
class ConsoleLogger final : public Logger
{
public:
    enum class ColorizeConsoleOutput : char {
        NO_COLOR = 0, LEVEL_ONLY, ALL
    };

    ConsoleLogger() = delete;

    [[maybe_unused]] explicit ConsoleLogger(LogLevel logLevel)
            : Logger(logLevel) {}

    [[maybe_unused]] ConsoleLogger(
            LogLevel logLevel, AppendDateTimeFormat dateTimeFormat)
            : Logger(logLevel, dateTimeFormat) {}

    [[maybe_unused]] ConsoleLogger(
            LogLevel logLevel,
            ConsoleColor errorColor,
            ConsoleColor warnColor,
            ConsoleColor infoColor)
            : Logger(logLevel),
              m_errorColor(errorColor),
              m_warnColor(warnColor),
              m_infoColor(infoColor) {}

    [[maybe_unused]] ConsoleLogger(
            LogLevel logLevel,
            AppendDateTimeFormat dateTimeFormat,
            ColorizeConsoleOutput colorizeOutput,
            ConsoleColor traceColor,
            ConsoleColor debugColor,
            ConsoleColor errorColor,
            ConsoleColor warnColor,
            ConsoleColor infoColor)
            : Logger(logLevel, dateTimeFormat),
              m_colorizeStyle(colorizeOutput),
              m_traceColor(traceColor),
              m_debugColor(debugColor),
              m_errorColor(errorColor),
              m_warnColor(warnColor),
              m_infoColor(infoColor) {}


    ConsoleLogger(const ConsoleLogger &) = delete;      // non construction-copyable
    ConsoleLogger(ConsoleLogger &&) = delete;                 // non movable
    ConsoleLogger &operator=(const ConsoleLogger &) = delete; // non copyable
    ConsoleLogger &operator=(ConsoleLogger &&) = delete;      // move assignment

private:
    ColorizeConsoleOutput m_colorizeStyle{
            ColorizeConsoleOutput::NO_COLOR};

    ConsoleColor m_defaultColor{FG_DEFAULT};
    ConsoleColor m_traceColor{FG_LIGHT_BLUE};
    ConsoleColor m_debugColor{FG_DEFAULT};
    ConsoleColor m_errorColor{FG_RED};
    ConsoleColor m_warnColor{FG_GREEN};
    ConsoleColor m_infoColor{FG_YELLOW};

public:
    // -------------------------------------------------------------------------
    void setConsoleColourStyle(ColorizeConsoleOutput style) {
        m_colorizeStyle = style;
    }

    // -------------------------------------------------------------------------
    void trace(const std::string &message) override {
        /**************************************************************
         * @brief
         *
         * @Note: cout is thread safe, to avoid multiple threads
         * interleaving on one line though, we make sure to only
         * call the << operator once on std::cout otherwise the
         * << operators from different threads could interleave
         * obviously we dont care if flushes interleave
         *************************************************************/

        if (getLogLevel() >= LogLevel::TRACE) {
            std::string date_time = getDateTimeString();

            switch (m_colorizeStyle) {
                case ColorizeConsoleOutput::NO_COLOR:
                    std::cout << m_defaultColor << "[TRACE]: "
                              << m_defaultColor << message << date_time << '\n';
                    break;
                case ColorizeConsoleOutput::LEVEL_ONLY:
                    std::cout << m_traceColor << "[TRACE]: "
                              << m_defaultColor << message << date_time << '\n';

                    break;
                case ColorizeConsoleOutput::ALL:
                    std::cout << m_traceColor << "[TRACE]: " << message
                              << date_time << m_defaultColor << '\n';
                    break;
            }

            std::cout.flush();
        }
    }

    // ---------------------------------------------------------------------
    void debug(const std::string &message) override {
        if (getLogLevel() >= LogLevel::DEBUG) {
            std::string date_time = getDateTimeString();

            switch (m_colorizeStyle) {
                case ColorizeConsoleOutput::NO_COLOR:
                    std::cout << m_defaultColor << "[DEBUG]]: "
                              << m_defaultColor << message << date_time << '\n';
                    break;
                case ColorizeConsoleOutput::LEVEL_ONLY:
                    std::cout << m_debugColor << "[DEBUG]: "
                              << m_defaultColor << message << date_time << '\n';
                    break;
                case ColorizeConsoleOutput::ALL:
                    std::cout << m_debugColor << "[DEBUG]: " << message
                              << date_time << m_defaultColor << '\n';
                    break;
            }

            std::cout.flush();
        }
    }

    // ---------------------------------------------------------------------
    void error(const std::string &message) override {
        if (getLogLevel() >= LogLevel::ERROR) {
            std::string date_time = getDateTimeString();

            switch (m_colorizeStyle) {
                case ColorizeConsoleOutput::NO_COLOR:
                    std::cout << m_defaultColor << "[ERROR]: "
                              << m_defaultColor << message << date_time << '\n';
                    break;
                case ColorizeConsoleOutput::LEVEL_ONLY:
                    std::cout << m_errorColor << "[ERROR]: "
                              << m_defaultColor << message << date_time << '\n';
                    break;
                case ColorizeConsoleOutput::ALL:
                    std::cout << m_errorColor << "[ERROR]: " << message
                              << date_time << m_defaultColor << '\n';
                    break;
            }

            std::cout.flush();
        }
    }
    // ---------------------------------------------------------------------
    void warn(const std::string& message) override
    {
        if (getLogLevel() >= LogLevel::WARN) {
            std::string date_time = getDateTimeString();

            switch (m_colorizeStyle) {
                case ColorizeConsoleOutput::NO_COLOR:
                    std::cout << m_defaultColor << "[WARN]: "
                              << m_defaultColor << message << date_time << '\n';
                    break;
                case ColorizeConsoleOutput::LEVEL_ONLY:
                    std::cout << m_warnColor << "[WARN]: "
                              << m_defaultColor << message << date_time << '\n';
                    break;
                case ColorizeConsoleOutput::ALL:
                    std::cout << m_warnColor << "[WARN]: " << message
                              << date_time << m_defaultColor << '\n';
                    break;
            }

            std::cout.flush();
        }
    }
    // ---------------------------------------------------------------------
    void info(const std::string& message) override
    {
        if (getLogLevel() >= LogLevel::INFO)
        {
            std::string date_time = getDateTimeString();

            switch (m_colorizeStyle)
            {
                case ColorizeConsoleOutput::NO_COLOR:
                    std::cout << m_defaultColor << "[INFO]: "
                              << m_defaultColor << message << date_time << '\n';
                    break;
                case ColorizeConsoleOutput::LEVEL_ONLY:
                    std::cout << m_infoColor << "[INFO]: "
                              << m_defaultColor << message << date_time << '\n';
                    break;
                case ColorizeConsoleOutput::ALL:
                    std::cout << m_infoColor << "[INFO]: " << message
                              << date_time << m_defaultColor << '\n';
                    break;
            }

            std::cout.flush();
        }
    }
};

    class FileLogger final : public Logger {
    public:
        FileLogger() = delete;

        [[maybe_unused]] FileLogger(LogLevel logLevel, std::string filename)
                : Logger(logLevel), m_filename(std::move(filename)) {}

    private:
        std::string m_filename;
        std::ofstream m_file;
    public:
        void trace(const std::string &message) override {
            std::cout << "[TRACE]: " << message << '\n';
        }

        // -------------------------------------------------------------------------
        void debug(const std::string &message) override {
            std::cout << "[DEBUG]: " << message << '\n';
        }

        // -------------------------------------------------------------------------
        void error(const std::string &message) override {
            std::cout << "[ERROR]: " << message << '\n';
        }

        // -------------------------------------------------------------------------
        void warn(const std::string &message) override {
            std::cout << "[WARN]: " << message << '\n';
        }

        // -------------------------------------------------------------------------
        void info(const std::string &message) override {
            std::cout << "[INFO]: " << message << '\n';
        }
    };

}//namespace gc



#endif //GCLOG_LOGGER_HPP
