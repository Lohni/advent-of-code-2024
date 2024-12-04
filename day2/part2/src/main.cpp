#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

void getLineAsVector(std::vector<int>&, std::string);
short checkLineValidity(std::vector<int>&, short);

int main() {
    std::fstream day2file("../resource/day2-input.txt");

    int validLines = 0;

    std::string line;
    std::vector<int> lineNumbers;
    while (std::getline(day2file, line)) {
       getLineAsVector(lineNumbers, line); 

       if (lineNumbers.size() == 0) {
            std::cout << "Failed to get line numbers." << std::endl;
            break;
       }

       bool valid = true;

       short invalidPosition = checkLineValidity(lineNumbers, -1);
       if (invalidPosition >= 0) {
           std::cout << "XX";
           valid = (checkLineValidity(lineNumbers, invalidPosition) == -1) 
               || (checkLineValidity(lineNumbers, invalidPosition-1) == -1)
               || (checkLineValidity(lineNumbers, invalidPosition-2) == -1);
       }


       for (int i = 0; i < lineNumbers.size(); i++) {
           std::cout << lineNumbers[i] << " ";
       }

       if (valid) {
           validLines++;
           std::cout << "valid" << std::endl;
       } else {
           std::cout << "invalid" << std::endl;
       }


       lineNumbers.clear();
    }
    std::cout << "Valid lines: " << validLines <<  std::endl;
    return 0;
}

short checkLineValidity(std::vector<int> &lineNumbers, short ignorePosition) {
       short ascOrDesc = 0; //1 asc, -1 desc
       int prev = -1;
       //start at 0 - as every number can be ignored
       for (short i = 0; i < lineNumbers.size(); i++) {
           if (ignorePosition != i) {
               int curr = lineNumbers[i];
               if (prev >= 0) {

                   if (ascOrDesc == 0) {
                       if (curr < prev) ascOrDesc = -1;
                       if (curr > prev) ascOrDesc = 1;
                   }

                   if (ascOrDesc == 1 && curr > prev && curr <= (prev + 3)) {
                       //fine
                   } else if (ascOrDesc == -1 && curr < prev && curr >= (prev - 3)) {
                       //fine
                   } else {
                       return i;
                   }
               }

               prev = curr;
           }
       }

       return -1;
}

void getLineAsVector(std::vector<int> &numbers, std::string line) {
    std::istringstream iss(line);
    int num;
    while(iss >> num) {
        numbers.push_back(num);
    }
}

