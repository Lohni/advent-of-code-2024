#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <string>
#include <unordered_set>
#include <vector>

const uint8_t matrixSize = 50;

int main() {
    std::fstream day8file("../resource/day8-input.txt");

    std::string line;
    int lineIndex = 0;

    std::map<char, std::vector<std::string>> frequencyMap;
    while (std::getline(day8file, line)) {
        if (lineIndex >= matrixSize) {
            std::cout << "Too many lines! Max: " << matrixSize << std::endl;
            exit(1);
        }

        if (line.length() != matrixSize) {
            std::cout << "Unexpected line length: " << line.length() << std::endl;
            exit(1);
        }

        for (int i = 0; i < line.length(); i++) {
            if (line.at(i) != '.') {
                if (frequencyMap.count(line.at(i) == 0)) {
                    frequencyMap[line.at(i)] = std::vector<std::string>();
                }
                frequencyMap[line.at(i)].push_back(std::to_string(i)+","+std::to_string(lineIndex));
            }
        }

        lineIndex++;
    }

    std::unordered_set<std::string> positions;
    
    for (auto i = frequencyMap.begin(); i != frequencyMap.end(); i++) {
        std::vector<std::string> coords = i->second;

        for (int a = 0; a < coords.size()-1; a++) {
            int x1 = std::stoi(coords[a].substr(0, coords[a].find(',')));
            int y1 = std::stoi(coords[a].substr(coords[a].find(',')+1, coords[a].size()));
            for (int b = a+1; b < coords.size(); b++) {
                int x2 = std::stoi(coords[b].substr(0, coords[b].find(',')));
                int y2 = std::stoi(coords[b].substr(coords[b].find(',')+1, coords[b].size()));

                int dx = x2-x1; 
                int dy = y2-y1; 

                int inc = 0;
                while (true) {
                    int px = x2+(inc*dx);
                    int py = y2+(inc*dy);
                    
                    if (px >= 0 && px < matrixSize && py >= 0 && py < matrixSize) {
                        positions.insert(std::to_string(px) + "," + std::to_string(py));
                    } else {
                        break;
                    }

                    inc++;
                }

                inc = 0;
                while (true) {
                    int px = x1-(inc*dx);
                    int py = y1-(inc*dy);
                    
                    if (px >= 0 && px < matrixSize && py >= 0 && py < matrixSize) {
                        positions.insert(std::to_string(px) + "," + std::to_string(py));
                    } else {
                        break;
                    }

                    inc++;
                }
            } 
        } 
    }

    std::cout << "Different Positions: " << positions.size() << std::endl;
}
