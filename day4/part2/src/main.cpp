#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <string>
#include <vector>

using namespace std;

int checkXMASForPosition(vector<vector<char>>&, int x, int y);

int main() {
    std::fstream day2file("../resource/day4-input.txt");
    const uint8_t matrixSize = 140;

    std::string line;
    vector<vector<char>> matrix(matrixSize, vector<char>(matrixSize));
    uint16_t lineIndex = 0;
    while (std::getline(day2file, line)) {
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
        }

        lineIndex++;
    }

    int matches = 0;
    for (int y = 0; y <matrix.size(); y++) {
        for (int x = 0; x <matrix[y].size(); x++) {
           if (matrix[y][x] == 'A') {
                matches += checkXMASForPosition(matrix, x, y);
           } 
        }
    }

    std::cout << "Matches found: " << matches << std::endl;
}


int checkXMASForPosition(vector<vector<char>> &matrix, int x, int y) {
    // 0xxx
    // yxxx
    // yxxx
    // yxx3

    vector<char> text = {'M', 'A', 'S'};
    int directions[] = {1, 1, 
        -1, 1, 
        -1, -1, 
        1, -1};
    
    int count = 0;
    for (int dir = 0; dir < 8; dir+=2) {
        if (0 <= x - 1 && x + 1 < matrix[y].size()
             && 0 <= y - 1 && y + 1 < matrix.size()) {

            //Abysmal
            bool valid = true; 
            int tmpX = x - directions[dir];
            int tmpY = y - directions[dir+1];

            for (int i = 0; i < text.size(); i++) {
                if (matrix[tmpY+(i*directions[dir+1])][tmpX+(i*directions[dir])] != text[i]) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                count++;
                std::cout << "Position " << x << ":" << y << "Direction " << directions[dir] << ":" << directions[dir+1] << " Count " << count << std::endl;
            }

        }
    } 
    
    if (count != 2) return 0;
    return 1;
}
