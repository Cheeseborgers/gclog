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

namespace gc
{
    class Log {
    public:

        enum Level : char {ERROR = 0, WARNING, INFO};

    private:
        Level m_logLevel{INFO};

    public:
        // Methods
        void setLevel(Level level)
        {
            m_logLevel = level;
        }

        void error(const char *message)
        {
            if (m_logLevel >= ERROR) {
                std::cout << "[ERROR]: " << message << '\n';
            }
        }

        void warn(const char *message)
        {
            if (m_logLevel >= WARNING) {
                std::cout << "[WARNING]: " << message << '\n';
            }
        }

        void info(const char *message)
        {
            if (m_logLevel >= INFO) {
                std::cout << "[INFO]: " << message << '\n';
            }

        }
    };

}//namespace gcb



#endif //GCLOG_LOG_HPP
