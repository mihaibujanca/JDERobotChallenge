#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;

char counter = '0';
typedef struct path
{
    int x, y;
    int length;
    static bool compare(path first, path second)
    {
        return first.length < second.length;
    }
} path;

const vector<int> dirX = {0,-1, 0, 1, 0};
const vector<int> dirY = {0, 0, -1, 0, 1};

bool outOfBounds(const vector<string>& map, const int i, const int j)
{
    return i < 0 || j < 0 || i >= map.size() || j >= map[0].length();
}

void DFS(const int x, const int y, vector<string> &map, vector<vector<bool> > &visited)
{
    for(int i = 0; i < dirX.size(); i++)
    {
        int tempX = x + dirX[i], tempY = y + dirY[i];
        if(outOfBounds(map,tempX,tempY))
            continue;

        if (map[tempX][tempY] == '.' && !visited[tempX][tempY])
        {
            visited[tempX][tempY] = true;
            map[tempX][tempY] = counter;
            counter++;
            DFS(tempX, tempY, map, visited);
        }

    }
}

void BFS(const vector<string>& map, vector<path>& paths)
{
    int rows = map.size(), cols = map[0].length();
    vector<vector<bool> > visited(map.size(), vector<bool> (cols, false));

    queue<pair<int,int> > queue;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(map[i][j] == '#' || visited[i][j])
                continue;
            queue.push(make_pair(i,j));
            visited[i][j] = true;
            int length = 0;

            while(!queue.empty())
            {
                pair<int,int> top = queue.front();
                queue.pop();
                length++;

                for(int k = 0; k < dirX.size(); k++)
                {
                    int tempX = top.first + dirX[k], tempY = top.second + dirY[k];
                    if(outOfBounds(map, tempX, tempY))
                        continue;
                    if(map[tempX][tempY] == '#' || visited[tempX][tempY])
                        continue;

                    visited[tempX][tempY] = true;
                    queue.push(make_pair(tempX,tempY));
                }
            }
            paths.push_back(path({i,j,length}));
        }
    }

}

path getLongestPath(const vector<string>& matrix)
{
    vector<path> paths;
    BFS(matrix, paths);
    sort(paths.begin(), paths.end(), path::compare);
    return paths.back();
}

int main(int argc, char *argv[])
{
    ifstream file(argv[1]);
    string line;
    vector<string> map;
    while(getline(file, line))
        map.push_back(line);

    vector<vector<bool> > visited(map.size(), vector<bool> (map[0].length(), false));
    path longestPath = getLongestPath(map);
    cout<<longestPath.length<<endl;

    DFS(longestPath.x, longestPath.y, map, visited);

    for(int i = 0; i < map.size(); i++)
    {
        for(int j = 0; j < map[0].length(); j++)
            cout<<map[i][j];
        cout<<endl;
    }
    return 0;
}
