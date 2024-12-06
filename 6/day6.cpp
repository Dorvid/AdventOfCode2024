#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <sstream>
#include <set>
#include <map>
#include <chrono>

const char Wall = '#';
const char Up = '^';
const char Down = 'v';
const char Left = '<';
const char Right = '>';
const char Out_Of_Bounds = '*'; // Added as a border around input

typedef std::vector<std::vector<char>> Map_Type;

struct Pos {
    int X;
    int Y;
    char Direction;

    bool operator<(const Pos& Other) const {
        if (X != Other.X) {
            return X < Other.X;
        }
        if (Y != Other.Y) {
            return Y < Other.Y;
        }
        return Direction < Other.Direction;
    }
};

void Solve(Map_Type Map, Pos Guard_Pos);

int main() {
    Map_Type Map;
    std::ifstream Input_File("input.txt");

    std::string Line;
    Pos Guard_Pos;
    int X = 0;
    int Y = 0;
    while (std::getline(Input_File, Line)) {
        std::stringstream Str(Line);
        char C;
        std::vector<char> Row;
        Y = 0;
        while (Str >> C) {
            if (C == Up) {
                Guard_Pos = {X, Y, Up};
            }
            Row.push_back(C);
            ++Y;
        }
        ++X;
        Map.push_back(Row);
    }

    Input_File.close();

    Solve(Map, Guard_Pos);


    char C;
    std::cin >> C;

    return 0;
}

Pos Step_Direction(const char& Direction) {
    if (Direction == Up) {
        return { -1, 0, Up };
    } else if (Direction == Down) {
        return { 1, 0, Down };
    } else if (Direction == Left) {
        return { 0, -1, Left };
    } else {
        return { 0, 1, Right };
    }
}

// Always rotates 90 Degrees to the right
void Rotate_Guard(Map_Type& Map, Pos& Guard_Pos) {
    switch (Guard_Pos.Direction) {
    case Up:
        Map[Guard_Pos.X][Guard_Pos.Y] = Right;
        Guard_Pos.Direction = Right;
        break;
    case Right:
        Map[Guard_Pos.X][Guard_Pos.Y] = Down;
        Guard_Pos.Direction = Down;
        break;
    case Down:
        Map[Guard_Pos.X][Guard_Pos.Y] = Left;
        Guard_Pos.Direction = Left;
        break;
    case Left:
        Map[Guard_Pos.X][Guard_Pos.Y] = Up;
        Guard_Pos.Direction = Up;
        break;
    default:
       //  std::cout << "dir:" << Guard_Pos.Direction << ", ERROR NOT ON GUARD";¨
       break;
    };
}

// Returns True when Out of bounds
bool Step(Map_Type& Map, Pos& Guard_Pos, std::set<Pos>& Rotate_Positions) {
    // std::cout << "First: " << Guard_Pos.X << " Y: " << Guard_Pos.Y << std::endl;
    Pos Dir = Step_Direction(Guard_Pos.Direction);
    Pos Next_Pos = { Guard_Pos.X + Dir.X, Guard_Pos.Y + Dir.Y, Guard_Pos.Direction };
    if (Map[Next_Pos.X][Next_Pos.Y] == Wall) {
        // std::cout << "ROTATING\n";
        Rotate_Guard(Map, Guard_Pos);
        Rotate_Positions.insert(Guard_Pos);
        return false;
    } else if (Map[Next_Pos.X][Next_Pos.Y] == Out_Of_Bounds) {
        // std::cout << "OoB!";
        Map[Guard_Pos.X][Guard_Pos.Y] = 'X';
        return true;
    } else {
        // std::cout << "STEPING FORWARD\n";
        Map[Next_Pos.X][Next_Pos.Y] = Map[Guard_Pos.X][Guard_Pos.Y];
        Map[Guard_Pos.X][Guard_Pos.Y] = 'X';
        Guard_Pos = Next_Pos;
        return false;
    }
}

void Print(Map_Type& Map) {
    std::cout << "=========================================================================================================================================================" << std::endl;
    for (auto Row : Map) {
        for (auto C : Row) {
            std::cout << C;
        }
        std::cout << std::endl;
    }
    std::cout << "=========================================================================================================================================================" << std::endl;    
}

unsigned Count(Map_Type& Map) {
    unsigned Sum = 0;
    
    for (auto Row : Map) {
        for (auto C : Row) {
            if (C == 'X') {
                ++Sum;
            }
        }
    }

    return Sum;
}

std::map<Pos, bool> Setup_Visited(std::set<Pos> Positions) {
    std::map<Pos, bool> Spots;

    for(auto P : Positions) {
        Spots[P] = false;
    }

    return Spots;
}

void Solve(Map_Type Map, Pos Guard_Pos) {
    Pos Original_Pos = Guard_Pos;
    Map_Type Original_Map = Map;

    std::set<Pos> Rotate_Positions;
    // Step Till out of bounds
    while(!Step(Map, Guard_Pos, Rotate_Positions)) {
        // Print(Map);
    }
    // Calc total X
    std::cout << "Part_1: " << Count(Map) << std::endl;

    unsigned Sum = 0;

    int X = 0;
    int Y = 0;
    for (auto Row : Map) {
        Y = 0;
        for (auto C : Row) {
            if (C == 'X') {
                Map_Type Test_Map = Original_Map;
                Guard_Pos = Original_Pos;
                std::map<Pos, bool> Spots = Setup_Visited(Rotate_Positions);
                std::set<Pos> New_Rotate_Positions;
                Test_Map[X][Y] = '#';
                while (true) {
                    
                    if (Step(Test_Map, Guard_Pos, New_Rotate_Positions)) {
                        break; // Out of bounds, not in a loop
                    }

                    for (auto Rot : New_Rotate_Positions) {
                        if (Spots.find(Rot) == Spots.end()) {
                            // NEW ROTATION SPOT
                            Spots[Rot] = false;
                        }
                        New_Rotate_Positions.clear();
                    }

                    if (Spots.find(Guard_Pos) != Spots.end()) {
                        if (Spots[Guard_Pos]) {
                            ++Sum;
                            // std::cout << "Loop Found!\n";
                            break;
                        } else {
                            Spots[Guard_Pos] = true;
                        }
                    }
                }
            }
            ++Y;
        }
        ++X;
    }

    std::cout << "Part_2: " << Sum << std::endl;
}