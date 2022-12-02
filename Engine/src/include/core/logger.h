#include <iostream>
#include <string>

namespace Nomu {
    class Logger{
    public:
        static void Error(std::string message){
            std::cerr << "Error: " << message << std::endl;
        }
        static void Info(std::string message){
            std::cout << "Info: " << message << std::endl;
        }
        static void Warning(std::string message){
            std::cout << "Warning: " << message << std::endl;
        }
    private:
        Logger() {}
        ~Logger() {}
    };
}