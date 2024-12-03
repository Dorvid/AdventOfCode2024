#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <map>
#include <regex>

const std::regex Pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
const std::regex Do_Pattern(R"(do\(\))");
const std::regex Dont_Pattern(R"(don't\(\))");
const std::regex Pattern2(R"(do\(\)|don't\(\)|(mul\((\d{1,3}),(\d{1,3})\)))");

unsigned Part_1(const std::vector<std::string> List);
unsigned Part_2(const std::vector<std::string> List);

int main() {
    std::vector<std::string> List = {};

    std::ifstream Input_File("input.txt");

    std::string Line;

    while (Input_File >> Line) {
        List.push_back(Line);
    }

    Input_File.close();

    std::cout << "Part_1: " << Part_1(List) << std::endl;
    std::cout << "Part_2: " << Part_2(List) << std::endl;

    char C;
    std::cin >> C;

    return 0;
}

unsigned Part_1(std::vector<std::string> List) {
    unsigned Sum = 0;

    for(auto Str : List) {
        auto Begin = std::sregex_iterator(Str.begin(), Str.end(), Pattern);
        auto End = std::sregex_iterator();

        for (std::sregex_iterator I = Begin; I != End; ++I) {
            std::smatch Match = *I;
            Sum += (std::stoi(Match[1].str()) * std::stoi(Match[2].str()));
        }
    }

    return Sum;
}

unsigned Part_2(std::vector<std::string> List) {
    unsigned Sum = 0;
    bool Do = true;

    for(auto Str : List) {
        auto Begin = std::sregex_iterator(Str.begin(), Str.end(), Pattern2);
        auto End = std::sregex_iterator();

        for (std::sregex_iterator I = Begin; I != End; ++I) {
            std::smatch Match = *I;
            if (std::regex_match(Match[0].str(), Do_Pattern)) {
                Do = true;
            } else if (std::regex_match(Match[0].str(), Dont_Pattern)) {
                Do = false;
            } else if (std::regex_match(Match[0].str(), Pattern) && Do) {
                Sum += (std::stoi(Match[2].str()) * std::stoi(Match[3].str()));
            }
        }
    }

    return Sum;
}