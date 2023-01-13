#include <string>

//#define OVERHEAD
#define PERFORMANCE
enum timerType{performance, overhead};

const std::string OVERHEAD_IN_FILENAME = "OverheadTime.csv";
const std::string OVERHEAD_OUT_FILENAME = "ResultsOverhead.csv";
const std::string PERFORMANCE_IN_FILENAME = "Performances.csv";
const std::string PERFORMANCE_OUT_FILENAME = "ResultsPerformance.csv";
const std::string RESULTS_FOLDER = "../results";