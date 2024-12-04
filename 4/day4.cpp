#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <sstream>

const unsigned Padding = 3u;
const unsigned Size = 140u;
const unsigned Width = Size + Padding * 2;
const unsigned First_Elem = Padding;
const unsigned Last_Elem = Width - Padding;

unsigned Find_XMAS(const char Data[Width][Width]);
unsigned Find_X_MAS(const char Data[Width][Width]);

int main() {
    char Array[Width][Width]; // Input is 140 x 140 + Padding

    std::ifstream Input_File("input.txt");

    std::string Line;
    unsigned I = 0;
    while (std::getline(Input_File, Line)) {
        std::stringstream Str(Line);
        char C;
        
        unsigned J = 0;
        while (Str >> C) {
            Array[I][J] = C;
            ++J;
        }
        ++I;
    }

    Input_File.close();

    std::cout << "Part_1: " << Find_XMAS(Array) << std::endl;
    std::cout << "Part_2: " << Find_X_MAS(Array) << std::endl;

    char C;
    std::cin >> C;

    return 0;
}

unsigned Find_XMAS(const char Data[Width][Width]) {
    unsigned Count = 0;

    for (unsigned I = First_Elem; I < Last_Elem; ++I) {
        for (unsigned J = First_Elem; J < Last_Elem; ++J) {
            if (Data[I][J] != 'X') {
                continue;
            }

            if(Data[I][J] == 'X' && Data[I][J-1] == 'M' && Data[I][J-2] == 'A' && Data[I][J-3] == 'S') { // Left
                ++Count;
            }
            if(Data[I][J] == 'X' && Data[I][J+1] == 'M' && Data[I][J+2] == 'A' && Data[I][J+3] == 'S') { // Right
                ++Count;
            }
            if(Data[I][J] == 'X' && Data[I-1][J] == 'M' && Data[I-2][J] == 'A' && Data[I-3][J] == 'S') { // Up
                ++Count;
            }
            if(Data[I][J] == 'X' && Data[I+1][J] == 'M' && Data[I+2][J] == 'A' && Data[I+3][J] == 'S') { // Down
                ++Count;
            }
            if(Data[I][J] == 'X' && Data[I-1][J-1] == 'M' && Data[I-2][J-2] == 'A' && Data[I-3][J-3] == 'S') { // Up Left
                ++Count;
            }
            if(Data[I][J] == 'X' && Data[I-1][J+1] == 'M' && Data[I-2][J+2] == 'A' && Data[I-3][J+3] == 'S') { // Up Right
                ++Count;
            }
            if(Data[I][J] == 'X' && Data[I+1][J-1] == 'M' && Data[I+2][J-2] == 'A' && Data[I+3][J-3] == 'S') { // Down Left
                ++Count;
            }
            if(Data[I][J] == 'X' && Data[I+1][J+1] == 'M' && Data[I+2][J+2] == 'A' && Data[I+3][J+3] == 'S') { // Down Right
                ++Count;
            }
        }
    }

    return Count;
}

bool Left_Diagonal(const char Data[Width][Width], const unsigned X, const unsigned Y) {
    bool Found = false;

    if (Data[X-1][Y-1] == 'M' && Data[X+1][Y+1] == 'S') {
        Found = true;
    } else if (Data[X-1][Y-1] == 'S' && Data[X+1][Y+1] == 'M') {
        Found = true;
    }

    return Found;
}

bool Right_Diagonal(const char Data[Width][Width], const unsigned X, const unsigned Y) {
    bool Found = false;

    if (Data[X-1][Y+1] == 'M' && Data[X+1][Y-1] == 'S') {
        Found = true;
    } else if (Data[X-1][Y+1] == 'S' && Data[X+1][Y-1] == 'M') {
        Found = true;
    }

    return Found;
}

unsigned Find_X_MAS(const char Data[Width][Width]) {
    unsigned Count = 0;

    for (unsigned I = First_Elem; I < Last_Elem; ++I) {
        for (unsigned J = First_Elem; J < Last_Elem; ++J) {
            if (Data[I][J] != 'A') {
                continue;
            }

            if (Left_Diagonal(Data, I, J) && Right_Diagonal(Data, I, J)) {
                ++Count;
            }
        }
    }

    return Count;
}