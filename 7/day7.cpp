#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <map>
#include <sstream>
#include <bitset>
#include <limits>

unsigned long long Solve(std::map<long long, std::vector<long long>>& Data);
unsigned long long Solve_Concatenate(std::map<long long, std::vector<long long>>& Data);

int main() {
    
    std::map<long long, std::vector<long long>> Data;
    std::ifstream Input_File("input.txt");

    std::string Line;
    while (std::getline(Input_File, Line)) {
        std::stringstream Str(Line);
        std::vector<long long> Numbers;
        long long Total;
        char C;
        Str >> Total >> C;
        long long  Num;
        while (Str >> Num) {
            Numbers.push_back(Num);
        }
        Data[Total] = Numbers;
    }
    Input_File.close();

    std::cout << "Part_1: " << Solve(Data) << std::endl;
    std::cout << "Part_2: " << Solve_Concatenate(Data) << std::endl;
    return 0;
}

unsigned long long Solve(std::map<long long, std::vector<long long>>& Data) {
    unsigned long long Sum = 0;

    for (auto It = Data.begin(); It != Data.end(); ++It) {
        std::bitset<64> Op;

        unsigned Combinations = 1ULL << (It->second.size() - 1);
        // std::cout << "Solving for " << It->first << std::endl;
 
        for(unsigned Mask = 0; Mask < Combinations; ++Mask) {
            Op = Mask;
            auto LHS = It->second.begin();
            auto RHS = LHS + 1;

            long long Total = *LHS;
            for (unsigned I = 0; I < It->second.size() - 1; ++I, ++RHS) {
                if (Op[I]) {
                    Total += *RHS;
                } else {
                    Total *= *RHS;
                }
                // std::cout << "Total: " << Total << std::endl;
                if (Total > It->first) {
                    break;
                }
            }
            if (Total == It->first) {
                // std::cout << "Added to Total" << std::endl;
                Sum += Total;
                break;
            }
        }
    }

    return Sum;
}

bool Increment_Ternary(std::vector<int>& Op) {
    for(unsigned I = 0; I < Op.size(); ++I) {
        Op[I]++;
        if (Op[I] == 3) {
            Op[I] = 0;
        } else {
            return false;
        }
    }
    return true;
}

// Could probably be improved
bool Concatenate(long long& LHS, const int& RHS) {
    std::string L = std::to_string(LHS);
    std::string R = std::to_string(RHS);
    L += R;
    try {
        LHS = std::stoll(L);
    } catch (const std::out_of_range& oor) {
        return false;
    }
    return true;
}

unsigned long long Solve_Concatenate(std::map<long long, std::vector<long long>>& Data) {
    unsigned long long Sum = 0;

    for (auto It = Data.begin(); It != Data.end(); ++It) {
        std::vector<int> Op(It->second.size() - 1, 0);
        // std::cout << "Solving for " << It->first << std::endl;
 
        do {
            auto LHS = It->second.begin();
            auto RHS = LHS + 1;

            long long Total = *LHS;

            for (unsigned I = 0; I < It->second.size() - 1; ++I, ++RHS) {
                if (Op[I] == 0) {
                    Total += *RHS;
                } else if (Op[I] == 1) {
                    Total *= *RHS;
                } else {
                    if(!Concatenate(Total, *RHS)) {
                        Total = std::numeric_limits<long long>::max();
                        break;
                    }
                }
                // std::cout << "Total: " << Total << std::endl;
                if (Total > It->first) {
                    break;
                }
            }
            if (Total == It->first) {
                // std::cout << "Added to Total" << std::endl;
                Sum += Total;
                break;
            }
        } while (!Increment_Ternary(Op));
    }

    return Sum;
}