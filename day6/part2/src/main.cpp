#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <string>
#include <unordered_set>
#include <vector>

bool simulate(int startX, int startY, std::vector<std::vector<char>>&matrix);

const uint8_t matrixSize = 130;

int main() {
    std::fstream day6file("../resource/day6-input.txt");
    int currX = -1;
    int currY = -1;
    int direction = -1; //0 ^, 1 >, 2 v, 3 <

    std::string line;
    std::vector<std::vector<char>> matrix(matrixSize, std::vector<char>(matrixSize));
    uint16_t lineIndex = 0;
    while (std::getline(day6file, line)) {
        if (lineIndex >= matrixSize) {
            std::cout << "Too many lines! Max: " << matrixSize << std::endl;
            exit(1);
        }

        if (line.length() != matrixSize) {
            std::cout << "Unexpected line length: " << line.length() << std::endl;
            exit(1);
        }

        for (int i = 0; i < line.length(); i++) {
            matrix[lineIndex][i] = line.at(i);
            if (line.at(i) == '^'){
                direction = 0; 
                currX = i;
                currY = lineIndex;
            } else if (line.at(i) == '>'){
                direction = 1; 
                currX = i;
                currY = lineIndex;
            } else if (line.at(i) == 'v'){
                direction = 2; 
                currX = i;
                currY = lineIndex;
            } else if (line.at(i) == '<'){
                direction = 3; 
                currX = i;
                currY = lineIndex;
            }
        }

        lineIndex++;
    }

    std::unordered_set<std::string> positions;
    positions.insert(std::to_string(currX) + "," + std::to_string(currY));

    int startX = currX;
    int startY = currY;
    while (true) {
        int nextFieldX = currX;
        int nextFieldY = currY;

       if (direction == 0) nextFieldY-- ;
       else if (direction == 1) nextFieldX++;
       else if (direction == 2) nextFieldY++;
       else if (direction == 3) nextFieldX--;

       if (nextFieldX < 0 || nextFieldX == matrixSize || nextFieldY < 0 || nextFieldY == matrixSize) {
           break;
       }

       if (matrix[nextFieldY][nextFieldX] == '#') {
           direction++;
           if (direction == 4) {
               direction = 0;
           }
       } else {
           currX = nextFieldX;
           currY = nextFieldY;

           positions.insert(std::to_string(currX) + "," + std::to_string(currY));
       }
    }


    int loops = 0;
    for (auto i = positions.begin(); i != positions.end(); i++) {
        std::string entry = (*i);
        int firstNum = std::stoi(entry.substr(0, entry.find(',')));
        int secondNum = std::stoi(entry.substr(entry.find(',')+1, entry.size()));

        matrix[secondNum][firstNum] = '#';
        // I tried not to, i swear!!
        bool loop = simulate(startX, startY, matrix);
        if (loop) {
            loops++;
        }

        matrix[secondNum][firstNum] = '.';
    }

    std::cout << "Loops: " << loops << std::endl;
}

bool simulate(int startX, int startY, std::vector<std::vector<char>>&matrix) {
    int currX = startX;
    int currY = startY;
    int direction = 0;
    std::unordered_set<std::string> visited;
    while (true) {
        int nextFieldX = currX;
        int nextFieldY = currY;

       if (direction == 0) {
           nextFieldY-- ;
       } else if (direction == 1) {
           nextFieldX++;
       } else if (direction == 2) {
           nextFieldY++;
       } else if (direction == 3) {
           nextFieldX--;
       }

       if (nextFieldX < 0 || nextFieldX == matrixSize || nextFieldY < 0 || nextFieldY == matrixSize) {
           break;
       }

       if (matrix[nextFieldY][nextFieldX] == '#') {
           direction++;
           if (direction == 4) {
               direction = 0;
           }
       } else {
           currX = nextFieldX;
           currY = nextFieldY;

           std::string visit = std::to_string(currX) + "," + std::to_string(currY) + "," + std::to_string(direction);
           if (visited.count(visit) == 1) {
               return true;
           }
           visited.insert(visit);
       }
    }

    return false;
}
