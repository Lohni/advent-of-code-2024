#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
    std::fstream day6file("../resource/day6-input.txt");
    const uint8_t matrixSize = 130;
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

    std::cout << "Different Positions: " << positions.size() << std::endl;
}
