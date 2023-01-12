#include <fstream>
#include <mutex>
#include <string>
#include <iostream>
#include <sstream>
#include <numeric>

void writeOnOverheadFile(std::string data, std::string filename);
void extractOverheadTime(std::string inFilename, std::string outFilename);