#include <fstream>
#include <iostream>
#include <vector>

typedef struct
{
    int position;
    int power;
}Point;

int setDirections(const Point* points, int points_count, int stadium_length);

int main()
{
    int points_count, stadium_length;
    std::string name;
    std::ifstream fin("stropitori.in");
    std::ofstream fout("stropitori.out");

    /* Citeste numele si lungimea stadionului */
    std::getline(fin, name);
    fin >> points_count >> stadium_length;

    /* Citeste pozitiile si puterile stropitorilor */
    Point* points = new Point[points_count];
    for (int i = 0; i < points_count; i++)
        fin >> points[i].position;
    for (int i = 0; i < points_count; i++)
        fin >> points[i].power;

    fout << setDirections(points, points_count, stadium_length);

    fout.close();
    fin.close();

    return 0;
}

int setDirections(const Point* points, int points_count, int stadium_length)
{
    int i;
    int turned_on = 0;
    int current_position = 0;
    for (i = 0; i < points_count - 1; i++)
    {
        int left_reach = points[i].position - points[i].power;
        if (left_reach > current_position)
        {
            turned_on++;
            current_position = points[i].position;
        }
        else
        {
            if (points[i + 1].position - points[i].position - points[i].power > 0)
            {
                turned_on++;
                current_position = points[i].position + points[i].power;
            }
            else
                current_position = points[i].position;
        }
    }

    int left_reach = points[i].position - points[i].power;
    if (left_reach > current_position)
        turned_on++;
    else
        if (stadium_length - points[i].position - points[i].power > 0)
            turned_on++;
    return turned_on;

}
