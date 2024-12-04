#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>

int main() {
    std::fstream day2file("../resource/day2-input.txt");

    int validLines = 0;
    std::string line;
    while (std::getline(day2file, line)) {
        std::istringstream iss(line);
        int prev = -1;
        int num = -1;
        bool isValid = true;
        int ascOrDesc = 0; //asc 1, desc -1
        while (iss >> num) {
            if (prev > -1) {
                if (ascOrDesc == 0) {
                    if (prev < num) {
                        ascOrDesc = 1;
                    } else if (prev > num) {
                        ascOrDesc = -1;
                    } else {
                        isValid = false;
                        break;
                    }
                } 

                if (ascOrDesc == 1 && num > prev && num <= (prev + 3)) {
                    //fine
                } else if (ascOrDesc == -1 && num < prev && num >= (prev - 3)) {
                    //fine
                } else {
                    isValid = false;
                    break;
                }
            }
            prev = num;
        } 

        if (isValid) {
            validLines++;
        }

    }
    std::cout << "Valid lines: " << validLines <<  std::endl;
    return 0;
}

