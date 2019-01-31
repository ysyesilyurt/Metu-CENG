#ifndef ALGOHW3_GRAPH_HPP
#define ALGOHW3_GRAPH_HPP

#include <vector>
#include <climits>

// Edge comparator struct for comparing edges according to their weights in Priority Queue
struct edgeComparator
{
    bool operator()(std::pair<std::pair<int,int>,int> lhs, std::pair<std::pair<int,int>,int> rhs) const {
        return (lhs.first.second > rhs.first.second);
    }
};

// Adjacency list representation of the graph
class Graph {
    int verticeNum;
    std::vector<std::vector<std::pair<int,int>>> graph;
public:
    Graph(int);
    void addEdge(int src, int dest, int weight);
    void printGraph();
    std::vector<std::pair<int,int>> & operator[] (int);
};

Graph::Graph(int vNum) {
    verticeNum = vNum;
    graph = std::vector<std::vector<std::pair<int,int>>>(vNum);
}

std::vector<std::pair<int,int>> & Graph::operator[] (int index)
{
    return graph[index - 1];
}

// Method for adding edge to graph
void Graph::addEdge(int src, int dest, int weight) {
    graph[src - 1].emplace_back(std::make_pair(dest, weight));
}

void Graph::printGraph()
{
    for (int i = 0; i < verticeNum; ++i) {
        std::cout << i + 1;
        for (int j = 0; j < graph[i].size() ; ++j) {
             std::cout << " -> (" << graph[i][j].first << "," << graph[i][j].second << ")";
        }
        std::cout << "\n";
    }
}

#endif //ALGOHW3_GRAPH_HPP
