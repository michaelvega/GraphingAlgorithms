#include <bits/stdc++.h>
#include <stack>
#include <queue>
#include <utility>
#include <string>
using namespace std;

void printCharStack(stack<char> s) {
    cout << "-------" << endl;
    while (!s.empty()) {
        cout << ' ' << s.top();
        s.pop();
    }
    cout << endl << "-------" << endl;
}

void printStringVector(vector<string> s) {
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        cout << ' ' << *it;
    }
}

void depthFristPrint(unordered_map<char, string> graph, char source) {
    stack<char> stack;
    stack.push(source);

    while(!stack.empty())
    {
        char current = stack.top();
        stack.pop();
        cout << current << endl;

        for(int i = 0; i < graph[current].size(); i++)
        {
            stack.push(graph[current][i]);
        }
        //printCharStack(stack);
    }
}

// void depthFristPrintRecursive(unordered_map<char, string> graph, char source) {
//     cout << source << endl;
//     for(int i = 0; i < graph[source].size(); i++)
//     {
//         depthFristPrintRecursive(graph,graph[source][i]);
//     }
// }

void breadthFirstPrint(unordered_map<char, string> graph, char source) {
    queue<char> queue;
    queue.push(source);

    while(!queue.empty())
    {
        char current = queue.front();
        queue.pop();
        cout << current << endl;

        for(int i = 0; i < graph[current].size(); i++)
        {
            queue.push(graph[current][i]);
        }
        //printCharStack(stack);
    }
}

bool hasPath (unordered_map<char, string> graph, char src, char dst) {
    if(src == dst) return true;

    for (int i = 0; i < graph[src].size(); i++)
    {
        if (hasPath(graph, graph[src][i], dst) == true) return true;
    }
    return false;
}

bool hasPathBreadth (unordered_map<char, string> graph, char src, char dst) {
    queue<char> queue;
    queue.push(src);

    while(!queue.empty())
    {
        char current = queue.front();
        queue.pop();

        if(current == dst) return true;

        for(int i = 0; i < graph[current].size(); i++)
        {
            queue.push(graph[current][i]);
        }
    }
    return false;
}


/// @brief Prints unordered map in key, value pairs enclosed by {brackets}
/// @param K: is a temprate param
/// @param V: is a temprate param
/// @param m: an unordered_map of any types
/// @return void – prints argument unordered_map
template<typename K, typename V>
void print_map(std::unordered_map<K, V> const &m)
{
    for (auto const &pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

unordered_map<char, string> buildGraph(unordered_set<string> edges) {
    unordered_map<char, string> graph;

    unordered_set<string>::iterator itr;
    for (itr = edges.begin(); itr != edges.end(); itr++) 
    {
        string edge = *itr;
        char a = edge[0];
        char b = edge[1];
        if(!(graph.count(a))) graph[a] = {};
        if(!(graph.count(b))) graph[b] = {};
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    return graph;
}

bool hasPathUndirected (unordered_map<char, string> graph, char src, char dst, unordered_set<char> visited) {
    if(src == dst) return true;

    if(visited.count(src)) return false;
    visited.insert(src);

    for (int i = 0; i < graph[src].size(); i++)
    {
        if (hasPathUndirected(graph, graph[src][i], dst, visited) == true) return true;
    }
    return false;
}

bool undirectedPath (unordered_set<string> edges, char nodeA, char nodeB) {
    unordered_map<char, string> graph = buildGraph(edges); 
    unordered_set<char> set;
    return hasPathUndirected(graph, nodeA, nodeB, set);
}

int shortestPath(unordered_set<string> edges, char nodeA, char nodeB) {
    unordered_map<char, string> graph = buildGraph(edges); 

    unordered_set<char> visted = {nodeA};

    queue<pair<char, int>> queue;
    pair<char, int> src = {nodeA, 0};
    queue.push(src);

    while(!queue.empty())
    {
        pair<char, int> current = queue.front();
        char node =  current.first;
        int distance = current.second;
        queue.pop();

        if(node == nodeB) return distance;

        for(int i = 0; i < graph[node].size(); i++)
        {
            char neighbor = graph[node][i];
            if(!visted.count(neighbor))
            {
                visted.insert(neighbor);
                queue.push({neighbor, distance + 1});
            }
            
        }
    }
    return -1;
}

bool explore(vector<string> grid, int r, int c, unordered_set<string> &visited) {
    bool rowInbounds = false;
    bool colInbounds = false;
    if (0 <= r && r < grid.size()) rowInbounds = true;
    if (0 <= c && c < grid.begin()->size()) colInbounds = true;
    if(!rowInbounds || !colInbounds) return false;
    
    if(grid[r][c] == 'W') return false;

    char l = r+'0';
    char w = c+'0';
    string pos = {l, ',' , w};
    if(visited.count(pos) == true) return false;
    visited.insert(pos);

    explore(grid, r - 1, c, visited);
    explore(grid, r + 1, c, visited);
    explore(grid, r, c - 1, visited);
    explore(grid, r, c + 1, visited);

    // for(auto itr = visited.begin(); itr!=visited.end(); ++itr)
    // {
    //     cout << *itr << endl;
    // }
    //cout << "ISLAND FOUND!: " << r << ',' << c << endl; 
    return true;
}

int islandCount(vector<string> grid) {
    int length = grid.size();
    int width = grid.begin()->size();

    unordered_set<string> visited;

    int count = 0;
    for(int r = 0; r < length; r++)
    {
        for(int c = 0; c < width; c++)
        {
            if(explore(grid, r, c, visited) == true) 
            {
                count += 1;
                //cout << "COUNT ADDED" << endl;
            }
            
        }
    }
    return count;
}

int main() {
    unordered_map<char, string> g;
    g['f'] = {'g', 'i'};
    g['g'] = {'h'};
    g['h'] = {};
    g['i'] = {'g', 'k'};
    g['j'] = {'i'};
    g['k'] = {};

    unordered_map<char, string> g2;
    g2['a'] = {'b', 'c'};
    g2['b'] = {'d'};
    g2['c'] = {'e'};
    g2['d'] = {'f'};
    g2['e'] = {};
    g2['f'] = {};

    unordered_set<string> ge;
    ge.insert({'i', 'j'});
    ge.insert({'k', 'i'});
    ge.insert({'m', 'k'});
    ge.insert({'k', 'l'});
    ge.insert({'o', 'n'});

    unordered_set<string> ge2;
    ge2.insert({'w', 'x'});
    ge2.insert({'x', 'y'});
    ge2.insert({'z', 'y'});
    ge2.insert({'z', 'v'});
    ge2.insert({'w', 'v'});
    ge2.insert({'o', 'p'});

    vector<string> island;
    island.push_back({'W', 'L', 'W', 'W', 'W'});
    island.push_back({'W', 'L', 'W', 'W', 'W'});
    island.push_back({'W', 'W', 'W', 'L', 'W'});
    island.push_back({'W', 'W', 'L', 'L', 'W'});
    island.push_back({'L', 'W', 'W', 'L', 'L'});
    island.push_back({'L', 'L', 'W', 'W', 'W'});

    //printStringVector(island);
    cout << islandCount(island) << endl;
}

