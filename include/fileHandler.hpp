#include <fstream>
#include <mutex>
#include <string>
#include <iostream>
#include <sstream>
#include <numeric>

#include <sys/stat.h>
#include <sys/types.h>

void writeOnFile(std::string data, std::string path, std::string filename);
void extractTime(std::string dirpath, std::string inFilename, std::string outFilename);