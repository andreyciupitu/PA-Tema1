#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef struct
{
    int position;
    int power;
}Point;

int setDirections(const Point *points, int points_count, int max_length);

int main()
{
    int points_count, stadium_length;
    string name;
    ifstream fin("stropitori.in");
    ofstream fout("stropitori.out");

    /* Citeste numele si lungimea stadionului */
    getline(fin, name);
    fin >> points_count >> stadium_length;

    /* Citeste pozitiile si puterile stropitorilor */
    Point *points = new Point[points_count];
    for (int i = 0; i < points_count; i++)
        fin >> points[i].position;
    for (int i = 0; i < points_count; i++)
        fin >> points[i].power;

    fout << setDirections(points, points_count, stadium_length);

    fout.close();
    fin.close();
    delete [] points;
    return 0;
}

/**
 * Functie ce determina cea mai buna configuratie pentru stropitori, astfel
 * incat sa fie deschise un numar maxim de stropitori.
 *
 * @method setDirections
 *
 * @param  points         Vectorul de stropitori.
 * @param  points_count   Numarul de stropitori.
 * @param  max_length     Lungimea stadionului.
 *
 * @return Numarul de stropitori pornite.
 */
int setDirections(const Point *points, int points_count, int max_length)
{
    int i;
    int turned_on = 0;
    int current_position = 0;

    for (i = 0; i < points_count - 1; i++)
    {
        /* Verifica daca stropitoarea poate uda la stanga fara
            a se suprapune cu stropitoarea precedenta */
        if (points[i].position - points[i].power > current_position)
        {
            turned_on++;
            current_position = points[i].position;
        }
        else
        {
            /* Verifica daca poate uda la dreapta fara sa acopere
                o alta stropitoare */
            if (points[i + 1].position - points[i].position > points[i].power)
            {
                turned_on++;
                current_position = points[i].position + points[i].power;
            }
            else
                /* Daca nu poate uda nici la stanga, nici la dreapta,
                    blocheaza stropitoarea */
                current_position = points[i].position;
        }
    }

    /* Verifica daca ultima stropitoare paote uda la stanga sau dreapta */
    if (points[i].position - points[i].power > current_position)
        turned_on++;
    else
        if (max_length - points[i].position >= points[i].power)
            turned_on++;

    return turned_on;
}
