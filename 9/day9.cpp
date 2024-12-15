#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <map>
#include <sstream>
#include <bitset>
#include <limits>
#include <list>

const unsigned EMPTY_BLOCK = -1;

struct Block {
    unsigned Id;
    unsigned Width;
    bool Moved = false;
};

unsigned long long Defrag(std::vector<Block>& Blocks);
unsigned long long Better_Defrag(std::list<Block>& Blocks);

void Print_Blocks(const std::vector<Block>& Blocks) {
    for (auto B : Blocks) {
        if (B.Id == EMPTY_BLOCK) {
            std::cout << ".";
        } else {
            std::cout << B.Id;
        }
    }
    std::cout << std::endl;
}

void Print_Blocks_List(const std::list<Block>& Blocks) {
    for (auto B : Blocks) {
        for (unsigned I = 0; I < B.Width; ++I) {
            if (B.Id == EMPTY_BLOCK) {
                std::cout << ".";
            } else {
                std::cout << B.Id;
            }
        }
    }
    std::cout << std::endl;
}

int main() {

    std::vector<Block> Blocks;
    std::list<Block> Blocks_2;
    std::ifstream Input_File("input.txt");

    std::string Line;
    std::getline(Input_File, Line);
    std::stringstream Str(Line);
    char C;
    
    unsigned Id = 0;
    bool Alt = false;
    bool First = true;
    while (Str >> C) {
        unsigned Count = C - '0';
        // For Part 1
        for (unsigned I = 0; I < Count; ++I) {
            Block B;
            if (Alt) {
                // std::cout << "Empty" << std::endl;
                B.Id = EMPTY_BLOCK;
            } else {
                // std::cout << Id << std::endl;
                B.Id = Id;
            }
            Blocks.push_back(B);
        }
        // For part 2
        if (Count > 0) {
            Block B;
            if (Alt) {
                B.Id = EMPTY_BLOCK;
                B.Width = Count;
            } else {
                B.Id = Id;
                B.Width = Count;
            }
            Blocks_2.push_back(B);
        }
        if (!Alt) {
            ++Id;
        }
        Alt = !Alt;
    }
    Input_File.close();

    std::cout << "Part_1: " << Defrag(Blocks) << std::endl;
    std::cout << "Part_2: " << Better_Defrag(Blocks_2);
    return 0;
}

unsigned long long Calc_Checksum(const std::vector<Block>& Blocks) {
    unsigned long long Sum = 0;
    unsigned long long I = 0;
    for (auto B : Blocks) {
        if (B.Id == EMPTY_BLOCK) {
            break;
        }
        Sum += (I * B.Id);
        ++I;
    }
    return Sum;
}

unsigned long long Calc_Checksum_By_Width(const std::list<Block>& Blocks) {
    unsigned long long Sum = 0;
    unsigned long long I = 0;
    for (auto B : Blocks) {
        for (unsigned J = 0; J < B.Width; ++J, ++I) {
            if (B.Id != EMPTY_BLOCK) {
                Sum += (I * B.Id);
            }
        }
    }
    return Sum;
}

// Feels like an innefficient solution, would be better to refactor and use a std::list instead...
unsigned long long Defrag(std::vector<Block>& Blocks) {
    for (auto Rit = Blocks.rbegin(); Rit != Blocks.rend(); ++Rit) {
        if ((*Rit).Id != EMPTY_BLOCK) {
            auto Fit = --Rit.base();
            for (auto It = Blocks.begin(); It != Fit; ++It) {
                if ((*It).Id == EMPTY_BLOCK) {
                    std::iter_swap(It, Fit);
                } 
            }
        }
    }

    return Calc_Checksum(Blocks);
}

std::list<Block>::iterator Get_Fitting_Space(unsigned Width, std::list<Block>& Blocks, const std::list<Block>::iterator End) {
    for (auto It = Blocks.begin(); It != End; ++It) {
        if ((*It).Id == EMPTY_BLOCK && (*It).Width >= Width) {
            return It;
        }
    }
    return Blocks.end(); // No space found
}

unsigned long long Better_Defrag(std::list<Block>& Blocks) {
    for (auto It = --Blocks.end(); ; --It) {
        if (It == Blocks.begin()) {
            break;
        }
        if ((*It).Id != EMPTY_BLOCK && (*It).Moved == false) {
            (*It).Moved = true;
            auto Space = Get_Fitting_Space((*It).Width, Blocks, It);
            if (Space == Blocks.end()) {
                continue;
            }

            if ((*Space).Width != (*It).Width) {
                Block B;
                B.Id = EMPTY_BLOCK;
                B.Width = (*Space).Width - (*It).Width;
                (*Space).Moved = true;
                (*Space).Width = (*It).Width;
                Blocks.insert(std::next(Space), B);
            }
            if (Space != Blocks.end()) {
                std::iter_swap(It, Space);
            }
        }
    }

    return Calc_Checksum_By_Width(Blocks);
}