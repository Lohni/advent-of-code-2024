#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

int main() {
    std::fstream day1file("../resource/day1-list.txt");

    int firstList[1000];
    std::map<int, int> testMap;

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

        if (testMap.count(b) == 0) {
            testMap[b] = 1;
        } else {
            int t = testMap[b];
            testMap[b] = testMap[b] + 1;
        }

        i++;
    }

    if (i != 1000) {
        std::cout << "Parsed less the 1000 entries. Entries: " << i << std::endl;
        return 1;
    }

    int similarityScore = 0;
    for (i = 0; i < 1000; i++) {
        if (testMap.count(firstList[i]) > 0) {
            similarityScore += testMap[firstList[i]] * firstList[i];
        }
    }


    std::cout << "Similarity Score: " << similarityScore <<  std::endl;

    return 0;
}
