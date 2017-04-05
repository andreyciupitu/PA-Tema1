#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>

int assignIntervals(const std::vector<int> &points, const std::vector<std::pair<int, int> > &intervals);

int main()
{
    int n, m;
    std::vector<int> points;
    std::vector<std::pair<int, int> > intervals;

    std::ifstream fin("points.in");
    std::ofstream fout("points.out");

    fin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        int aux;
        fin >> aux;
        points.push_back(aux);
    }

    for (int i = 0; i < m; i++)
    {
        std::pair<int, int> next;
        fin >> next.first >> next.second;
        intervals.push_back(next);
    }

    std::sort(intervals.begin(), intervals.end());

    fout << assignIntervals(points, intervals);

    return 0;
}

int assignIntervals(const std::vector<int> &points, const std::vector<std::pair<int, int> > &intervals)
{
    int interval_count = 0;
    size_t i = 0;
    size_t j = 0;
    while (i < points.size() && j < intervals.size())
    {
        while (j < intervals.size() && intervals[j].second < points[i])
            j++;
        int max = -1;
        size_t maxj = j;
        while (j < intervals.size() && intervals[j].first <= points[i])
        {
            if (max <= (intervals[j].second - points[i]))
            {
                max = intervals[j].second - points[i];
                maxj = j;
            }
            j++;
        }
        interval_count++;
        while (i < points.size() && intervals[maxj].second >= points[i])
            i++;
    }
    return interval_count;
}
