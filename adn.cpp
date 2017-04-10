#include <fstream>
#include <vector>

using namespace std;

bool testDna(string sequences[], int count, string dna);

int main()
{
    int tests_count;
    string sequences[4] = {"", "", "", ""};
    string dna;
    ifstream fin("adn.in");
    ofstream fout("adn.out");

    fin >> tests_count;

    for (int i = 0 ; i < tests_count; i++)
    {
        int sequence_count;
        fin >> sequence_count;

        for (int j = 0; j < sequence_count; j++)
            fin >> sequences[j];
        fin >> dna;

        fout << testDna(sequences, sequence_count, dna) << "\n";
    }

    fin.close();
    fout.close();

    return 0;
}

/**
 * Functia determina daca o secventa ADN este compusa din bucatile date.
 * Pentru testare, functia foloseste un tablou 4D pentru retinerea solutiilor
 * subproblemelor.
 *
 * @method testDna
 *
 * @param  sequences Bucatile de ADN.
 * @param  count     Numarul de bucati.
 * @param  dna       Secventa ce trebuie testata.
 *
 * @return TRUE daca secventa este valida, FALSE in caz contrar.
 */
bool testDna(string sequences[], int count, string dna)
{
    /* N == 1 */
    if (count == 1)
        return (sequences[0] == dna);

    /* Check if lengths match */
    int length = 0;
    for (int i = 0; i < count; i++)
        length += sequences[i].length();
    if (length != (int)dna.length())
        return false;

    int l1 = sequences[0].length();
    int l2 = sequences[1].length();
    int l3 = sequences[2].length();
    int l4 = sequences[3].length();

    /* Aloca memorie pentru PD */
    bool ****is_valid = new bool***[l1 + 1];
    for (int i = 0; i <= l1; i++)
    {
        is_valid[i] = new bool**[l2 + 1];
        for (int j = 0; j <= l2; j++)
        {
            is_valid[i][j] = new bool*[l3 + 1];
            for (int k = 0; k <= l3; k++)
                is_valid[i][j][k] = new bool[l4 + 1];
        }
    }
    /* Start PD */
    is_valid[0][0][0][0] = true;

    for (int i = 0; i <= l1; i++)
        for (int j = 0; j <= l2; j++)
            for (int k = 0; k <= l3; k++)
                for (int l = 0; l <= l4; l++)
                {
                    if (i != 0 || k != 0 || j != 0 || l != 0)
                        is_valid[i][j][k][l] = false;
                    if (i > 0 && sequences[0][i - 1] == dna[i + j + k + l - 1])
                        is_valid[i][j][k][l] |= is_valid[i - 1][j][k][l];
                    if (j > 0 && sequences[1][j - 1] == dna[i + j + k + l - 1])
                        is_valid[i][j][k][l] |= is_valid[i][j - 1][k][l];
                    if (k > 0 && sequences[2][k - 1] == dna[i + j + k + l - 1])
                        is_valid[i][j][k][l] |= is_valid[i][j][k - 1][l];
                    if (l > 0 && sequences[3][l - 1] == dna[i + j + k + l - 1])
                        is_valid[i][j][k][l] |= is_valid[i][j][k][l - 1];
                }

    bool result = is_valid[l1][l2][l3][l4];

    /* Elibereaza memoria */
    for (int i = 0; i <= l1; i++)
    {
        for (int j = 0; j <= l2; j++)
        {
            for (int k = 0; k <= l3; k++)
                delete[] is_valid[i][j][k];
            delete[] is_valid[i][j];
        }
        delete[] is_valid[i];
    }
    delete[] is_valid;

    return result;
}
