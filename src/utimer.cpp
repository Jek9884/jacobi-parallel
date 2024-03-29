#include <iostream>
#include <chrono>
#include "constants.hpp"
#include "../include/fileHandler.hpp"

#define START(timename) auto timename = std::chrono::system_clock::now();
#define STOP(timename,elapsed)  auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - timename).count();

class utimer {
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point stop;
    std::string message;
    timerType type;
    using usecs = std::chrono::microseconds;
    using msecs = std::chrono::milliseconds;

private:
    long * us_elapsed;

public:

    utimer(const std::string m, const timerType type=performance) : message(m), type(type), us_elapsed((long *)NULL) {
        start = std::chrono::system_clock::now();
    }

    utimer(const std::string m, long * us) : message(m),us_elapsed(us) {
        start = std::chrono::system_clock::now();
    }

    ~utimer() {
        stop = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed = stop - start;
        auto musec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

        #if defined(OVERHEAD)
            if (type == overhead) {
                std::string line = std::to_string(musec) + ';';
                writeOnFile(line, RESULTS_FOLDER, OVERHEAD_IN_FILENAME);
            }
        #endif

        #if defined(PERFORMANCE)
            if (type == performance) {
                std::string line = std::to_string(musec) + ';';
                writeOnFile(line, RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
            }
        #endif

        //#if defined(PRINT)
            std::cout << message << " computed in " << musec << " usec " << std::endl;
        //#endif

        if(us_elapsed != NULL)
            (*us_elapsed) = musec;
    }
};