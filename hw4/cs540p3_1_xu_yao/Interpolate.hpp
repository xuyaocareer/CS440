
#ifndef Interpolate_interpolate_hpp
#define Interpolate_interpolate_hpp

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

namespace cs540 {
    
    class WrongNumberOfArgs : public std::runtime_error {
    public:
        WrongNumberOfArgs(const std::string &message) : runtime_error("Error: " + message) {
        }
    };
    
    std::string Interpolate(std::string ln) {
        std::string ret(ln);
        size_t pos = 0;
        
        while (true) {
            pos = ln.find("%", pos);
            if (pos == std::string::npos) {
                break; // no % in the string
            }
            else if (pos > 0 && ln.at(pos-1) == '\\') {
                ret.replace(pos-1, 2, std::string("%")); // replace \% with % ( \% sequence should output a percent sign)
            }
            else {
                throw WrongNumberOfArgs("Wrong Number Of Args"); // exist % in the string
            }
            pos++;
        }
        
        return ret;
    }
    
    template<typename First, typename ... Rest>
    std::string Interpolate(const std::string ln, First &&arg_first, Rest&&... arg_rest){
        std::string temp(ln);
        std::string ret("");
        size_t pos = 0;
        
        while (true) {
            pos = temp.find("%", pos);
            if (pos == std::string::npos) {
                throw WrongNumberOfArgs("Wrong Number Of Args"); // no % in the string
            }
            else if (pos > 0 && temp.at(pos-1) == '\\') {
                temp.replace(pos-1, 2, std::string("%")); // replace \% with % ( \% sequence should output a percent sign)
            }
            else {
                break; // find % in the string
            }
            pos++;
        }
        
        if (pos > 0)
            ret += temp.substr(0, pos);
        std::stringstream _stringstream;
        _stringstream << arg_first;
        ret += _stringstream.str();
        std::string str_rest = temp.substr(pos+1);
        ret += Interpolate(str_rest, std::forward<Rest>(arg_rest)...);
        return ret;
    }
    
}

#endif
