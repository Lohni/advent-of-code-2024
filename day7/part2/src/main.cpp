#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string>
#include <vector>

bool calculate(std::vector<int> &numbers, int i, uint64_t currRes, uint64_t target);

int main() {
    std::fstream day7file("../resource/day7-input.txt");

    uint64_t totalRes = 0;
    std::string line;
    std::vector<int> numbers;

    std::string num;
    try {
        while (std::getline(day7file, line)) {
            numbers.clear();

            std::istringstream iss(line);
            std::getline(iss, num, ' ');
            uint64_t res = std::stoull(num.substr(0, num.length() -1));

            while (std::getline(iss, num, ' ')) {
                numbers.push_back(std::stoi(num)); 
            }

            if (calculate(numbers, 0, 0, res)) {
                totalRes += res;
            }
        }
    } catch (std::exception &e) {
        std::cout << num << "\n" << e.what() << std::endl;
    }

    std::cout << "Total calibration result: " << totalRes << std::endl;
}

bool calculate(std::vector<int> &numbers, int i, uint64_t curRes, uint64_t target) {
    if (i == numbers.size()) {
        return curRes == target;
    }

    int num = numbers[i];
    uint64_t mult = 1;
    while(num > 0) {
        num/=10;
        mult*=10;
    }
    
    return calculate(numbers, i+1, curRes+numbers[i], target) 
        || calculate(numbers, i+1, curRes*numbers[i], target)
        || calculate(numbers, i+1, curRes*mult+numbers[i], target);
}