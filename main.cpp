#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <set>

using namespace std;

const int MAXN = 10000;
pair<int, int> points[MAXN];

int cross(pair<int, int> a, pair<int, int> b)
{
    return a.first * b.second - a.second * b.first;
}

bool cmp(pair<int, int> a, pair<int, int> b)
{
    int x = points[0].first;
    int y = points[0].second;
    int c = cross({a.first - x, a.second - y}, {b.first - x, b.second - y});
    if (c == 0)
    {
        return (a.first - x) * (a.first - x) + (a.second - y) * (a.second - y) < (b.first - x) * (b.first - x) + (b.second - y) * (b.second - y);
    }
    return c > 0;
}

bool rightTurn(vector<pair<int, int>>& st, pair<int, int>& cur)
{
    pair<int, int> prev = st[st.size() - 1];
    pair<int, int> prevprev = st[st.size() - 2];
    return cross({prev.first - prevprev.first, prev.second - prevprev.second}, {cur.first - prev.first, cur.second - prev.second}) <= 0;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (true)
    {
        cin >> n;
        if (n == 0)
            break;
        set<pair<int, int>> seen;
        int j = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> points[j].first >> points[j].second;
            if (seen.find(points[j]) == seen.end())
            {
                seen.insert(points[j]);
                j++;
            }
        }
        n = j;
        int pivIndex = 0;
        int minY = points[0].second;
        int minX = points[0].first;
        for (int i = 1; i < n; i++)
        {
            if (points[i].second < minY)
            {
                pivIndex = i;
                minY = points[i].second;
                minX = points[i].first;
            }
            else if (points[i].second == minY && points[i].first < minX)
            {
                pivIndex = i;
                minX = points[i].first;
            }
        }
        swap(points[0], points[pivIndex]);
        sort(points + 1, points + n, cmp);
        vector<pair<int, int>> st;
        for (int i = 0; i < n; i++)
        {
            pair<int, int> cur = points[i];
            while (st.size() >= 2 && rightTurn(st, cur))
            {
                st.pop_back();
            }
            st.push_back(cur);
        }
        while (st.size() >= 3 && rightTurn(st, points[0]))
            st.pop_back();
        stringstream ss;
        ss << st.size() << endl;
        for (pair<int, int> p : st)
            ss << p.first << " " << p.second << endl;
        cout << ss.str();
    }
    return 0;
}
