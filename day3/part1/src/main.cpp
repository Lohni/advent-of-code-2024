#include <exception>
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>


int main () {
    std::fstream day3file("../resource/day3-input.txt");
    std::string content;

    //Allocate memory upfront
    day3file.seekg(0, std::ios::end);
    content.reserve(day3file.tellg());
    day3file.seekg(0, std::ios::beg);

    content.assign(std::istreambuf_iterator<char>(day3file), std::istreambuf_iterator<char>());

    try {
        std::regex multMatcher("mul(\\(\\d*,\\d*\\))");
        std::sregex_iterator iter(content.begin(), content.end(), multMatcher);
        std::sregex_iterator end;

        int result = 0;
        while(iter != end) {
            std::smatch smatch = *iter;
            std::string match = smatch.str().substr(4, smatch.length()-5);

            std::cout << match << std::endl;

            std::istringstream split(match);
           
            std::string number;
            std::getline(split, number, ',');
            int firstNum = std::atoi(number.c_str());
            std::getline(split, number, ',');
            int secondNum = std::atoi(number.c_str());

            result = result + firstNum * secondNum;

            iter++;
        }

        std::cout << "Result: " << result << std::endl;

    } catch(std::exception& e) {
        std::cout << "Error! " << e.what() << std::endl;
    }
}