#include "../include/fileHandler.hpp"

long parseLine(std::string line);

void writeOnOverheadFile(std::string data, std::string filename){

    std::mutex mtx;

    std::lock_guard<std::mutex> lock(mtx);
    std::ofstream file(filename, std::ios_base::app);
    if(!file.is_open()){
        file.open(filename, std::ios_base::out);
    }
    file<<data;
    file.close();

}

void extractOverheadTime(std::string inFilename, std::string outFilename){

    std::ifstream inFile(inFilename, std::ios_base::in);

    if (inFile.is_open()){
        std::string line;
        std::ofstream outFile(outFilename, std::ios_base::app);
        if(!outFile.is_open()){
            outFile.open(outFilename, std::ios_base::out);
        }

        while(std::getline(inFile, line)){
            //Get each number as string separated with a ';' and sum them
            std::stringstream ss(line);
            std::string header;
            std::getline(ss, header, ';');
            std::string newLine = header + ";" + std::to_string(parseLine(line));
            outFile << newLine << std::endl;
        }
        outFile.close();
    }
    else{
        std::cout << "Error in opening " + inFilename;
    }
    
    inFile.close();
    
}

long parseLine(std::string line){

    std::stringstream ss(line);
    std::string elem;
    long sum = 0;
    std::getline(ss, elem, ';');
    while(std::getline(ss, elem, ';')){
        sum += std::stol(elem);
    }

    return sum;
}