#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <sstream>
#include <map>
#include <set>

void Calc(const std::vector<std::vector<int>>& Data, const std::map<int, std::set<int>>& Rules);

int main() {
    std::vector<std::vector<int>> Data;
    std::map<int, std::set<int>> Rules;
    // Input split into two seperate files, | removed from first part and commas removed from second part
    std::ifstream Rule_File("rules.txt");
    std::ifstream Input_File("input.txt");
    std::string Line;

    while (std::getline(Rule_File, Line)) {
        std::stringstream Str(Line);
        int First;
        int Second;

        Str >> First >> Second;
        if (Rules.find(First) == Rules.end()) {
            std::set<int> Tmp = { Second };
            Rules[First] = Tmp;
        } else {
            Rules[First].insert(Second);
        }
    }

    Rule_File.close();
    
    while (std::getline(Input_File, Line)) {
        std::stringstream Str(Line);
        std::vector<int> Row;
        int Num;
        
        while (Str >> Num) {
            Row.push_back(Num);
        }
        Data.push_back(Row);
    }

    Input_File.close();

    Calc(Data, Rules);    

    char C;
    std::cin >> C;

    return 0;
}

bool Correct_Order(std::vector<int>& Data, const std::map<int, std::set<int>>& Rules) {
    bool Correct_Order = true;

    for (auto It = Data.begin(); It != Data.end(); ++It) {
        std::set<int> Specific_Rules = Rules.at(*It);
        for(auto J = Data.begin(); J != It; ++J) {
            if (Specific_Rules.find(*J) != Specific_Rules.end()) {
                Correct_Order = false;
                break;
            }
        }
        if (!Correct_Order) {
            break;
        }
    }
    return Correct_Order;
}

unsigned Incorrect_Order(std::vector<int>& Data, const std::map<int, std::set<int>>& Rules) {
    std::sort(Data.begin(), Data.end(), 
        [&Rules](int Lhs, int Rhs) {
            std::set<int> Tmp = Rules.at(Rhs);
            return Tmp.find(Lhs) != Tmp.end();
        });
    return static_cast<unsigned>(Data[Data.size() / 2]);
}

void Calc(const std::vector<std::vector<int>>& Data, const std::map<int, std::set<int>>& Rules) {
    unsigned Correct_Sum = 0;
    unsigned Incorrect_Sum = 0;

    for (auto Row : Data) {
        if (Correct_Order(Row, Rules)) {
            Correct_Sum += Row[Row.size() / 2];
        } else {
            Incorrect_Sum += Incorrect_Order(Row, Rules);
        }
    }

    std::cout << "Part_1: " << Correct_Sum << std::endl;
    std::cout << "Part_2: " << Incorrect_Sum << std::endl;
}
