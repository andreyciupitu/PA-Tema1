#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

int main()
{
    int n, k;
    ifstream fin("warriors.in");
    ofstream fout("warriors.out");

    fin >> n >> k;

    /* Verifica daca sunt suficiente vieti pentru a aplica
        cautarea binara */
    int bsearch_comps = log2(n) + 1;
    if (bsearch_comps <= k)
        fout << bsearch_comps << endl;
    else
    {
        /* Determina nivelul maxim care poate fi descoperit
            folosind cel mult i comparari */
        for (int i = k; i < n; i++)
        {
            double level = 0;
            double binomial = 1;

            /* Calculeaza suma de combinari, necesara pentru
                a determina nivelul care poate fi descoperit */
            for (int j = 1; j <= k; j++)
            {
                binomial *= (i - j + 1) / (double)j;
                level += binomial;

                if (level >= n)
                    break;
            }

            /* Daca pot acoperi tot intervalul folosing i comparari
                atunci acesta este minimul (pt ca e primul la rand) */
            if (level >= n)
            {
                fout << i << endl;
                break;
            }
        }
    }

    fin.close();
    fout.close();
    return 0;
}
