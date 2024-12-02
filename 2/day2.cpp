#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <sstream>

unsigned Calc(const std::vector<std::vector<int>> Data, const bool Dampener_Avail);
std::vector<int>::iterator Is_Safe(const std::vector<int>::iterator Begin, const std::vector<int>::iterator End);

int main() {
    std::vector<std::vector<int>> Data;

    std::ifstream Input_File("input.txt");


    std::string Line;
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

    std::cout << "Part_1: " << Calc(Data, false) << std::endl;
    std::cout << "Part_2: " << Calc(Data, true) << std::endl;

    char C;
    std::cin >> C;

    return 0;
}

unsigned Calc(const std::vector<std::vector<int>> Data, const bool Dampener_Avail) {
    unsigned Count = 0;

    for(auto Row : Data) {
        
        auto It = Is_Safe(Row.begin(), Row.end());

        if (It == Row.end()) {
            ++Count;
        } else if (Dampener_Avail) {
            std::vector<int> Dampener;
            for (std::vector<int>::iterator I = Row.begin(); I != Row.end(); ++I) {
                Dampener.clear();
                for (std::vector<int>::iterator J = Row.begin(); J != Row.end(); ++J) {
                    if (I == J) {
                        continue;
                    }
                    Dampener.push_back(*J);
                }
                if (Is_Safe(Dampener.begin(), Dampener.end()) == Dampener.end()) {
                    ++Count;
                    break;
                } 
            }
        } 
    }

    return Count;
}

std::vector<int>::iterator Is_Safe(const std::vector<int>::iterator Begin, const std::vector<int>::iterator End) {
    bool Safe = true;
    auto Tail = Begin;
    auto Head = Tail + 1;
    auto Dampened = End;

    bool Ascending = (*Tail < *Head);

    while (Head != End) {
        int Diff = std::abs(*Tail - *Head);
        if (Diff == 0 || Diff > 3) {
            return Head;
            break;
        } else if ((Ascending && (*Tail > *Head) || (!Ascending && (*Tail < *Head)))) {
            return Head;
            break;
        }

        ++Tail;
        ++Head;
    }

    return End;
}