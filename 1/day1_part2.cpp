#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <map>

int main() {
    std::vector<int> List_1 = {};
    std::vector<int> List_2 = {};

    std::ifstream inputFile("input.txt");

    int Num_1, Num_2;

    while (inputFile >> Num_1 >> Num_2) {
        List_1.push_back(Num_1);
        List_2.push_back(Num_2);
    }

    inputFile.close();

    std::sort(List_1.begin(), List_1.end());
    std::sort(List_2.begin(), List_2.end());

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

    std::cout << Sum;

    return 0;
}