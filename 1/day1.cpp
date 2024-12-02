#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <map>

unsigned Part_1(const std::vector<int> List_1, const std::vector<int> List_2);
unsigned Part_2(const std::vector<int> List_1, const std::vector<int> List_2);

int main() {
    std::vector<int> List_1 = {};
    std::vector<int> List_2 = {};

    std::ifstream Input_File("input.txt");

    int Num_1, Num_2;

    while (Input_File >> Num_1 >> Num_2) {
        List_1.push_back(Num_1);
        List_2.push_back(Num_2);
    }

    Input_File.close();

    std::sort(List_1.begin(), List_1.end());
    std::sort(List_2.begin(), List_2.end());

    unsigned Sum = 0;
    for(unsigned I = 0; I < List_1.size(); ++I) {
        Sum += std::abs(List_1[I] - List_2[I]);
    }

    std::cout << "Part_1: " << Part_1(List_1, List_2);
    std::cout << "Part_2: " << Part_2(List_1, List_2);
    return 0;
}

unsigned Part_1(const std::vector<int> List_1, const std::vector<int> List_2) {
    unsigned Sum = 0;
    for(unsigned I = 0; I < List_1.size(); ++I) {
        Sum += std::abs(List_1[I] - List_2[I]);
    }
    return Sum;
}

unsigned Part_2(const std::vector<int> List_1, const std::vector<int> List_2) {
    unsigned Sum = 0;
    std::map<int, int> Map;
    for(unsigned I = 0; I < List_1.size(); ++I) {
        unsigned Score = 0;
        int Num = List_1[I];
        if (Map.find(Num) == Map.end()) {
            Score = Num * std::count(List_2.begin(), List_2.end(), Num);
            Map[Num] = Score;
        } else {
            Score = Map[Num];
        }
        Sum += Score;
    }
    return Sum;
}