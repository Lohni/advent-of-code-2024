#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>

int main() {
    std::fstream day1file("../../resource/day1-list.txt");

    int firstList[1000];
    int secondList[1000];

    size_t i = 0;
    std::string line;
    while (std::getline(day1file, line)) {
        std:std::istringstream iss(line);
        int a, b;
        if (!(iss >> a >> b)) {
            std::cout << "File parsing error" << std::endl;
            break; //error
        }

        firstList[i] = a;
        secondList[i] = b;
        i++;
    }

    if (i != 1000) {
        std::cout << "Parsed less the 1000 entries. Entries: " << i << std::endl;
        return 1;
    }

    std::sort(std::begin(firstList), std::end(firstList));
    std::sort(std::begin(secondList), std::end(secondList));

    int totalDistance = 0;
    for (i = 0; i < 1000; i++) {
        totalDistance += std::abs(firstList[i] - secondList[i]);
    }


    std::cout << "Total Distance: " << totalDistance <<  std::endl;

    return 0;
}
