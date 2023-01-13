#include "../include/fileHandler.hpp"

long parseLine(std::string line);

void writeOnFile(std::string data, std::string dirpath, std::string filename){

    //Check if the folder already exist otherwise create the folder
    struct stat info;
    if(stat(reinterpret_cast<char*>(dirpath.data()), &info) != 0){
        mkdir(reinterpret_cast<char*>(dirpath.data()), 0700);
    }

    std::string path = dirpath+"/"+filename;
    std::mutex mtx;

    std::lock_guard<std::mutex> lock(mtx);
    std::ofstream file(path, std::ios_base::app);
    if(!file.is_open()){
        file.open(path, std::ios_base::out);
    }
    file<<data;
    file.close();

}

void extractTime(std::string dirpath, std::string inFilename, std::string outFilename){

    std::string inpath = dirpath + "/" + inFilename;
    std::string outpath = dirpath + "/" + outFilename;
    std::ifstream inFile(inpath, std::ios_base::in);

    if (inFile.is_open()){
        std::string line;
        std::ofstream outFile(outpath, std::ios_base::out);

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