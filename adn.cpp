#include <fstream>
#include <iostream>
#include <vector>
#include <utility>

int main()
{
    int tests_count;
    std::string sequences[4];
    std::string dna;
    std::vector<std::vector<std::pair<int, int> > > variables;
    std::ifstream fin("adn.in");
    std::ofstream fout("adn.out");

    fin >> tests_count;

    for (int i = 0 ; i < tests_count; i++)
    {
        int sequence_count;
        fin >> sequence_count;
        for (int j = 0; j < sequence_count; j++)
            fin >> sequences[j];
        fin >> dna;
    }
}
