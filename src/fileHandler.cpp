#include "../include/fileHandler.hpp"

/**
 * @brief Parse a line of the file csv of results and returns the average value
 * 
 * @param line to parse
 * @return long average of the values
 */
long parseLine(std::string line){

    std::stringstream ss(line);
    std::string elem;
    long sum = 0;
    int count = 0;
    std::getline(ss, elem, ';');
    while(std::getline(ss, elem, ';')){
        sum += std::stol(elem);
        count++;
    }

    return sum/count;
}

/**
 * @brief Write on a file the data passed
 * 
 * @param data to save
 * @param dirpath to the directory where to save the file
 * @param filename of the file to save
 */
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

/**
 * @brief Extract results from the csv file of results and aggregate them
 * 
 * @param dirpath to the directory where to read and save the file
 * @param inFilename of the file where to read
 * @param outFilename of the file where to write
 */
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