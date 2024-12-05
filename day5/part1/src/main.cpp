#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
    std::fstream day5file("../resource/day5-input.txt");

    int middlePageNumbers = 0;

    std::map<int, std::unordered_set<int>> ruleMap;
    std::vector<int> updates;

    std::string line;
    bool instructions = true;
    while (std::getline(day5file, line)) {
        if (!line.empty()) {
            if (instructions) {
                std::istringstream split(line);

                std::string number;
                std::getline(split, number, '|');
                int firstNum = std::atoi(number.c_str());
                std::getline(split, number, '|');
                int secondNum = std::atoi(number.c_str());

                if (ruleMap.find(firstNum) == ruleMap.end()) {
                    ruleMap[firstNum] = std::unordered_set<int>();
                }
                ruleMap[firstNum].insert(secondNum);
            } else {
                updates.clear();

                std::string number;
                std::istringstream split(line);
                while(std::getline(split, number, ',')) {
                    updates.push_back(std::atoi(number.c_str()));
                }

                bool validUpdate = true;
                for (int i = 0; i < updates.size(); i++) {
                    auto rulesForI = ruleMap[updates[i]];
                    for (int j = i; j < updates.size(); j++) {
                        auto rulesForJ = ruleMap[updates[j]];
                        if (rulesForI.count(updates[j]) == 0 && rulesForJ.count(updates[i]) == 1) {
                            validUpdate = false;
                            break;
                        }
                    }

                    if (!validUpdate)break;
                }

                if (validUpdate) {
                    for (int i = 0; i < updates.size(); i++) {
                        std::cout << updates[i] << " ";
                    }
                    std::cout << std::endl;
                    middlePageNumbers += updates[((updates.size()-1)/2)];
                }
            }
        } else {
            instructions = false;
            std::cout << "Finished reading rules for " << ruleMap.size() << " numbers:" << std::endl;

            for (auto x = ruleMap.begin(); x != ruleMap.end(); ++x) {
                std::cout << (x->first);
                std::cout << ": ";

                for (auto y = x->second.begin(); y != x->second.end(); y++) {
                    std::cout << (*y);
                    std::cout << " ";
                }

                std::cout << std::endl;
            }
        }
    }


    std::cout << "Middle page numbers: " << middlePageNumbers << std::endl; 


    return 0;
}

