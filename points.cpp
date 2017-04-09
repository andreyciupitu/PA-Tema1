#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int assignIntervals(vector<int> &points, vector<pair<int, int> > &intervals);

int main()
{
    int n, m;
    vector<int> points;
    vector<pair<int, int> > intervals;
    ifstream fin("points.in");
    ofstream fout("points.out");

    fin >> n >> m;

    /* Citeste punctele */
    for (int i = 0; i < n; i++)
    {
        int aux;
        fin >> aux;
        points.push_back(aux);
    }

    /* Citeste intervalele */
    for (int i = 0; i < m; i++)
    {
        std::pair<int, int> next;
        fin >> next.first >> next.second;
        intervals.push_back(next);
    }

    /* Sorteaza intervalele dupa coordonata x,
        iar in caz de egalitate dupa y */
    std::sort(intervals.begin(), intervals.end());

    fout << assignIntervals(points, intervals);

    fin.close();
    fout.close();
    return 0;
}

/**
 * Functia intoarce numarul minim de intervale necesare pentru a acoperi
 * toate punctele date. Intervalele sunt considerate sortate dupa coordonata x.
 *
 * @method assignIntervals
 *
 * @param  points          Vectorul ce contine punctele.
 * @param  intervals       Vectorul ce contine intervalele.
 *
 * @return Numarul de intervale.
 */
int assignIntervals(vector<int> &points, vector<pair<int, int> > &intervals)
{
    int interval_count = 0;
    size_t i = 0;
    size_t j = 0;

    do
    {
        /* Cauta primul interval care cuprinde punctul curent */
        while (j < intervals.size() && intervals[j].second < points[i])
            j++;

        /* Gaseste intervalul cel mai mare (la dreapta)
            care cuprinde punctul curent */
        int max = -1;
        size_t maxj = j;
        while (j < intervals.size() && intervals[j].first <= points[i])
        {
            if (max <= intervals[j].second)
            {
                max = intervals[j].second;
                maxj = j;
            }
            j++;
        }

        /* Creste numarul de intervale gasite si cauta
            urmatorul punct neacoperit*/
        interval_count++;
        while (i < points.size() && intervals[maxj].second >= points[i])
            i++;
    } while (i < points.size() && j < intervals.size());

    return interval_count;
}
