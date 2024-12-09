#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <map>
#include <sstream>
#include <bitset>
#include <limits>

const unsigned Width = 50;
const unsigned Height = 50;

struct Coordinate {
    Coordinate(char Frequency, bool Is_Antinode, unsigned X, unsigned Y) : Frequency{Frequency}, Is_Antinode{Is_Antinode}, X{X}, Y{Y} {}
    char Frequency;
    bool Is_Antinode;
    unsigned X;
    unsigned Y;
};

void Print_Map(Coordinate* Coords[Height][Width]) {
    for (unsigned I = 0; I < Height; ++I) {
        for (unsigned J = 0; J < Width; ++J) {
            if ((Coords[I][J])->Is_Antinode) {
                std::cout << '#';
            } else {
                std::cout << (Coords[I][J])->Frequency;
            }
        }
        std::cout << std::endl;
    }
}

unsigned Solve(Coordinate* Coords [Height][Width], std::map<char, std::vector<Coordinate*>> Tracker);
unsigned Solve_2(Coordinate* Coords [Height][Width], std::map<char, std::vector<Coordinate*>> Tracker);

int main() {
    Coordinate* Coords[Height][Width];
    std::map<char, std::vector<Coordinate*>> Tracker;
    std::ifstream Input_File("input.txt");
    std::string Line;
    unsigned I = 0;
    while (std::getline(Input_File, Line)) {
        int J = 0;
        std::stringstream Str(Line);
        long long Total;
        char C;
        while (Str >> C) {
            Coords[I][J] = new Coordinate(C, false, I, J);
            if (C != '.') {
                if (Tracker.find(C) == Tracker.end()) {
                    std::vector<Coordinate*> Cords;
                    Cords.push_back(Coords[I][J]);
                    Tracker[C] = Cords;
                } else {
                    Tracker[C].push_back(Coords[I][J]);
                }
            }
            ++J;
        }
        ++I;
    }
    Input_File.close();
    std::cout << "Input Done." << std::endl;

    Print_Map(Coords);

    std::cout << "Part_1: " << Solve(Coords, Tracker) << std::endl;

    std::cout << "Part_2: " << Solve_2(Coords, Tracker) << std::endl;

    for (unsigned I = 0; I < Height; ++I) {
        for (unsigned J = 0; J < Height; ++J) {
            delete Coords[I][J];
        }
    }

    return 0;
}

unsigned Count_Antinodes(Coordinate* Coords[Height][Width]) {
    unsigned Sum = 0;
     for (unsigned I = 0; I < Height; ++I) {
        for (unsigned J = 0; J < Width; ++J) {
            if (Coords[I][J]->Is_Antinode) {
                ++Sum;
            }
        }
    }
    return Sum;
}

bool Set_Antinodes(Coordinate* Coords[Height][Width], unsigned X, unsigned Y, int dX, int dY) {
    // Bounds Check
    if ((int(X) - dX >= 0 && int(X) - dX < Height) && (int(Y) - dY >= 0 && int(Y) - dY < Width)) {
        // std::cout << "Setting Antinode at (" << X - dX << ", " << Y - dY << ")" << std::endl;
        Coords[X - dX][Y - dY]->Is_Antinode = true;
        return true;
    }
    return false;
}

unsigned Solve(Coordinate* Coords [Height][Width], std::map<char, std::vector<Coordinate*>> Tracker) {
    for (auto Antenna_Type = Tracker.begin(); Antenna_Type != Tracker.end(); ++Antenna_Type) {
        for (auto It = Antenna_Type->second.begin(); It != Antenna_Type->second.end(); ++It) {
            for (auto It_2 = It + 1; It_2 != Antenna_Type->second.end(); ++It_2) {
                int dX = (*It_2)->X -(*It)->X;
                int dY = (*It_2)->Y -(*It)->Y;

                std::cout << "Delta X: " << dX << " Delta Y: " << dY << std::endl;

                Set_Antinodes(Coords, (*It)->X, (*It)->Y, dX, dY);
                Set_Antinodes(Coords, (*It_2)->X, (*It_2)->Y, -dX, -dY);
            }
        }
    }

    Print_Map(Coords);

    return Count_Antinodes(Coords);
}

unsigned Solve_2(Coordinate* Coords [Height][Width], std::map<char, std::vector<Coordinate*>> Tracker) {

    // Calculate all T antinodes
    for (auto Antenna_Type = Tracker.begin(); Antenna_Type != Tracker.end(); ++Antenna_Type) {
        for (auto It = Antenna_Type->second.begin(); It != Antenna_Type->second.end(); ++It) {
            Coords[(*It)->X][(*It)->Y]->Is_Antinode = true;
            for (auto It_2 = It + 1; It_2 != Antenna_Type->second.end(); ++It_2) {
                int dX = (*It_2)->X - (*It)->X;
                int dY = (*It_2)->Y - (*It)->Y;   

                int X = (*It)->X;
                int Y = (*It)->Y;
                int I = 1;
                while(Set_Antinodes(Coords, X, Y, dX * I, dY * I)) {
                    ++I;
                }
                I = 1;
                while(Set_Antinodes(Coords, X, Y, -dX * I, -dY * I)) {
                    ++I;
                }
                // Print_Map(Coords);
            }
        }
    }
    Print_Map(Coords);

    return Count_Antinodes(Coords);
}