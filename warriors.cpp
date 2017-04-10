#include <fstream>
#include <vector>

using namespace std;

int main()
{
    int n, k;
    ifstream fin("warriors.in");
    ofstream fout("warriors.out");

    fin >> n >> k;

    fin.close();
    fout.close();
    return 0;
}
