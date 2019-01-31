#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "graph.hpp"

void choiceHandler(int, int, int, int, int, int, std::vector<int> &, std::vector<int> &, Graph &, std::vector<std::pair<int,int>> &);
std::vector<int> saveBunny(int, int, int, int &, int &, std::vector<int> &, std::vector<int> &, std::vector<int> &, Graph &);

int main() {

    // Open file
    std::ifstream inputFile("the3.inp");
    std::string line;
    char delimiter1(' ');
    char delimiter2('\n');

    // Read initial ammo amount
    std::getline(inputFile,line);
    int ammoAmount = stoi(line);

    // Read number of rooms
    std::getline(inputFile,line);
    int numRooms = stoi(line);

    // Read room of Bunny
    std::getline(inputFile,line);
    int bunLocation = stoi(line);

    // Read room of Skull Key
    std::getline(inputFile,line);
    int keyLocation = stoi(line);

    // Read room of scientist
    std::getline(inputFile,line);
    int sciLocation = stoi(line);

    // Read rooms that are locked in odd timesteps and store them as a vector
    std::getline(inputFile, line, delimiter2);
    int oddLockedLen = line[0] - '0';
    std::vector<int> oddLocked;
    std::vector<char> temp;
    std::string tempStr = "";
    if (oddLockedLen != 0)
    {
        for (int i = 2; i < line.size() ; ++i)
        {
            if (i == line.size() - 1)
            {
                temp.emplace_back(line[i]);
                for (int j = 0; j < temp.size(); ++j)
                    tempStr += temp[j];
                oddLocked.emplace_back(stoi(tempStr));
                temp = {};
                tempStr = "";
            }
            else if (line[i] != ' ')
                temp.emplace_back(line[i]);
            else
            {
                for (int j = 0; j < temp.size(); ++j)
                    tempStr += temp[j];
                oddLocked.emplace_back(stoi(tempStr));
                temp = {};
                tempStr = "";
            }
        }
    }

    // Read rooms that are locked in odd timesteps and store them as a vector
    std::getline(inputFile, line, delimiter2);
    int evenLockedLen = line[0] - '0';
    std::vector<int> evenLocked;
    if (evenLockedLen != 0)
    {
        for (int i = 2; i < line.size() ; ++i)
        {
            if (i == line.size() - 1)
            {
                temp.emplace_back(line[i]);
                for (int j = 0; j < temp.size(); ++j)
                    tempStr += temp[j];
                evenLocked.emplace_back(stoi(tempStr));
            }
            else if (line[i] != ' ')
                temp.emplace_back(line[i]);
            else
            {
                for (int j = 0; j < temp.size(); ++j)
                    tempStr += temp[j];
                evenLocked.emplace_back(stoi(tempStr));
                temp = {};
                tempStr = "";
            }
        }
    }

    // Create graph (In Adjacency List form)
    Graph graph(numRooms);

    // Construct graph from input file
    std::getline(inputFile,line);
    int numCorridors = stoi(line);
    for (int i = 0; i < numCorridors ; ++i)
    {
        std::getline(inputFile, line, delimiter1);
        int v1 = stoi(line);
        std::getline(inputFile, line, delimiter1);
        int v2 = stoi(line);
        std::getline(inputFile, line, delimiter2);
        graph.addEdge(v1,v2,stoi(line));
        graph.addEdge(v2,v1,stoi(line));
    }

    // Read nodes with ammo and store them as vector of pairs (vertexNumber, ammoAmount)
    std::getline(inputFile,line);
    int numRoomsWithAmmo = stoi(line);
    std::vector<std::pair<int,int>> roomsWithAmmo(numRoomsWithAmmo);
    for (int i = 0; i < numRoomsWithAmmo ; ++i)
    {
        std::getline(inputFile, line, delimiter1);
        int vertex = stoi(line);
        std::getline(inputFile, line, delimiter2);
        int ammoCount = stoi(line);
        roomsWithAmmo[i].first = vertex;
        roomsWithAmmo[i].second = ammoCount;
    }

    inputFile.close();

    // graph.printGraph();

    choiceHandler(ammoAmount,numRooms,bunLocation,keyLocation,sciLocation,numRoomsWithAmmo,oddLocked,evenLocked,graph,roomsWithAmmo);

    return 0;
}

// Function for calculation of Shortest Path from src to dst according to timesteps and Nodes with ammo
// Uses extended Dijsktra's Shortest Path algorithm, implementation is done with adjacency list and priority queue
std::vector<int> saveBunny(int src, int dst, int v_num, int & ammoAmount, int & time, std::vector<int> & oddLockedNodes,
                           std::vector<int> & evenLockedNodes, std::vector<int> & roomsToPass, Graph & graph) {

    // Priority queue to keep track of the nodes
    // vector of pair<pair<destnode, weight>, current_time> (current_time refers to time in which node is traversed)
    std::priority_queue<std::pair<std::pair<int, int>, int>, std::vector<std::pair<std::pair<int, int>, int>>, edgeComparator> pQueue;

    // Vector of pairs for keeping track of the weight and parent information
    // pair.first = shortest path, pair.second = its parent vertex
    // A node in distVector is implemented as "node = index - 1"
    // Initialize with INT_MAX
    std::vector<std::pair<int, int>> distVector(v_num, std::make_pair(INT_MAX, INT_MAX));

    // Initialize pQueue with src, its min costed path and current time
    pQueue.push(std::make_pair(std::make_pair(src, 0), time));

    // src's distance to itself is zero
    distVector[src - 1].first = 0;

    // Flag for keeping track of time updates for nodes
    bool finished = false;

    while (!pQueue.empty()) {

        // Access min costed vertex
        int destNode = pQueue.top().first.first;
        int timeStep = pQueue.top().second;

        // Break if reached to dst
        if (destNode == dst) {
            finished = true;
            time = timeStep;
            break;
        }

        // Pop vertex
        pQueue.pop();

        // Traverse all neighbours of the vertex
        std::vector<std::pair<int, int>>::iterator it;
        for (it = graph[destNode].begin(); it != graph[destNode].end(); ++it) {
            // Check if current room to visit is visitable
            if (std::find(roomsToPass.begin(), roomsToPass.end(), (*it).first) == roomsToPass.end()) {
                // Check if room is locked in next time step, if so continue
                if ((timeStep % 2 == 1) && std::find(evenLockedNodes.begin(), evenLockedNodes.end(), (*it).first) == evenLockedNodes.end() ||
                    (timeStep % 2 == 0) && std::find(oddLockedNodes.begin(), oddLockedNodes.end(), (*it).first) == oddLockedNodes.end())
                {
                    // Check if calculated cost is smaller than old calculated cost, if so Update the cost
                    if (distVector[(*it).first - 1].first > distVector[destNode - 1].first + (*it).second) {
                        distVector[(*it).first - 1].first = distVector[destNode - 1].first + (*it).second;
                        distVector[(*it).first - 1].second = destNode;
                        pQueue.push(std::make_pair(std::make_pair((*it).first, distVector[(*it).first - 1].first),timeStep+1));
                    }
                }
            }
        }
    }

    if (finished)
    {
        int dest = dst;
        // Construct shortest path from src to dst from distVector
        std::vector<int> path;
        path.emplace_back(dst);
        for (int i = 0; dst != src; ++i) {
            path.emplace_back(distVector[dst - 1].second);
            dst = distVector[dst - 1].second;
        }
        std::reverse(path.begin(), path.end());
        // Decrease ammo amount according to ammo used in path
        ammoAmount -= distVector[dest - 1].first;
        return path;
    }
    return std::vector<int> {-1};
}

// Function for calling saveBunny function with multiple ammo choices
void choiceHandler(int ammoAmount, int numRooms, int bunLocation, int keyLocation, int sciLocation, int numRoomsWithAmmo,
                   std::vector<int> & oddLocked, std::vector<int> & evenLocked, Graph & graph, std::vector<std::pair<int,int>> & roomsWithAmmo) {

    // t = 1 initially
    int time = 1;

    std::vector<int> roomsToPass;
    // holds (remainingAmmo of ith calculation, path of ith calculation)
    std::vector<std::pair<int,std::vector<int>>> resultVector (1,std::make_pair(-1,std::vector<int>{-1}));
    int initialAmmo = ammoAmount;
    std::vector<int> failVector {-1};
    std::vector<int> keyPath,sciPath,bunPath,ammo1Path,ammo2Path;

    if (numRoomsWithAmmo == 0)
    {
        // 1 KEY SCI BUN (0 0 0)
        // go to key
        keyPath = saveBunny(1,keyLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        if (keyPath != failVector)
        {
            // go to sci
            sciPath = saveBunny(keyLocation,sciLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
            if (sciPath != failVector)
            {
                // go to bun
                bunPath = saveBunny(sciLocation,bunLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                if (bunPath != failVector)
                {
                    // Concatenate paths
                    keyPath.insert(keyPath.end(), sciPath.begin() + 1, sciPath.end());
                    keyPath.insert(keyPath.end(), bunPath.begin() + 1, bunPath.end());
                    resultVector.emplace_back(initialAmmo, keyPath);
                }
            }
        }
        std::ofstream outputFile;
        outputFile.open ("the3.out");
        if (resultVector[0].second == failVector)
            outputFile << "Mission Failed, There is no such path to accomplish mission\n";
        outputFile << resultVector[0].first << std::endl;
        outputFile << resultVector[1].second.size() << std::endl;
        for (int i = 0; i < resultVector[1].second.size(); ++i)
            outputFile << resultVector[1].second[i] << " ";
        outputFile.close();
    }
        // if there is 1 room with ammo
    else if (numRoomsWithAmmo == 1)
    {
        // 1 KEY SCI BUN (0 0 0)
        // never go to ammo1
        roomsToPass = {roomsWithAmmo[0].first};
        // go to key
        keyPath = saveBunny(1,keyLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        if (keyPath != failVector)
        {
            // go to sci
            sciPath = saveBunny(keyLocation,sciLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
            if (sciPath != failVector)
            {
                // go to bun
                bunPath = saveBunny(sciLocation,bunLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                if (bunPath != failVector)
                {
                    // Concatenate paths
                    keyPath.insert(keyPath.end(), sciPath.begin() + 1, sciPath.end());
                    keyPath.insert(keyPath.end(), bunPath.begin() + 1, bunPath.end());
                    resultVector.emplace_back(initialAmmo, keyPath);
                }
            }
        }
        // 1 AMMO1 KEY SCI BUN (1 0 0)
        // go to ammo1 before going to key
        initialAmmo = ammoAmount;
        time = 1;
        // pass key room
        roomsToPass = {keyLocation};
        ammo1Path = saveBunny(1,roomsWithAmmo[0].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        initialAmmo += roomsWithAmmo[0].second;
        // you can go to key room now
        roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), keyLocation), roomsToPass.end());
        if (ammo1Path != failVector) {
            // go to key
            keyPath = saveBunny(roomsWithAmmo[0].first, keyLocation, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
            if (keyPath != failVector) {
                // go to sci
                sciPath = saveBunny(keyLocation, sciLocation, numRooms, initialAmmo, time, oddLocked, evenLocked,roomsToPass, graph);
                if (sciPath != failVector) {
                    // go to bun
                    bunPath = saveBunny(sciLocation, bunLocation, numRooms, initialAmmo, time, oddLocked,evenLocked, roomsToPass, graph);
                    if (bunPath != failVector) {
                        // Concatenate paths
                        ammo1Path.insert(ammo1Path.end(), keyPath.begin() + 1, keyPath.end());
                        ammo1Path.insert(ammo1Path.end(), sciPath.begin() + 1, sciPath.end());
                        ammo1Path.insert(ammo1Path.end(), bunPath.begin() + 1, bunPath.end());
                        resultVector.emplace_back(initialAmmo, ammo1Path);
                    }
                }
            }
        }
        // 1 KEY AMMO1 SCI BUN (0 1 0)
        // go to ammo1 before going to sci
        initialAmmo = ammoAmount;
        time = 1;
        // pass ammo1 room
        roomsToPass = {roomsWithAmmo[0].first};
        // go to key
        keyPath = saveBunny(1,keyLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        if (keyPath != failVector)
        {
            // go to ammo1 pass sci room
            roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[0].first), roomsToPass.end());
            roomsToPass.emplace_back(sciLocation);
            ammo1Path = saveBunny(keyLocation,roomsWithAmmo[0].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
            initialAmmo += roomsWithAmmo[0].second;
            // you can go to sci room now
            roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), sciLocation), roomsToPass.end());
            if (ammo1Path != failVector)
            {
                // go to sci
                sciPath = saveBunny(roomsWithAmmo[0].first,sciLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                if (sciPath != failVector)
                {
                    // go to bun
                    bunPath = saveBunny(sciLocation,bunLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                    if (bunPath != failVector)
                    {
                        // Concatenate paths
                        keyPath.insert(keyPath.end(), ammo1Path.begin() + 1, ammo1Path.end());
                        keyPath.insert(keyPath.end(), sciPath.begin() + 1, sciPath.end());
                        keyPath.insert(keyPath.end(), bunPath.begin() + 1, bunPath.end());
                        resultVector.emplace_back(initialAmmo,keyPath);
                    }
                }
            }
        }
        // 1 KEY SCI AMMO1 BUN (0 0 1)
        // go to ammo1 before going to bun
        initialAmmo = ammoAmount;
        time = 1;
        roomsToPass = {roomsWithAmmo[0].first};
        // go to key
        keyPath = saveBunny(1,keyLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        if (keyPath != failVector)
        {
            // go to sci
            sciPath = saveBunny(keyLocation,sciLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
            if (sciPath != failVector)
            {
                // go to ammo1 pass bun room
                roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[0].first), roomsToPass.end());
                roomsToPass.emplace_back(bunLocation);
                ammo1Path = saveBunny(sciLocation,roomsWithAmmo[0].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                initialAmmo += roomsWithAmmo[0].second;
                // you can go to key room now
                roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), bunLocation), roomsToPass.end());
                if (ammo1Path != failVector)
                {
                    bunPath = saveBunny(roomsWithAmmo[0].first,bunLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                    if (bunPath != failVector)
                    {
                        // Concatenate paths
                        keyPath.insert(keyPath.end(), sciPath.begin() + 1, sciPath.end());
                        keyPath.insert(keyPath.end(), ammo1Path.begin() + 1, ammo1Path.end());
                        keyPath.insert(keyPath.end(), bunPath.begin() + 1, bunPath.end());
                        resultVector.emplace_back(initialAmmo,keyPath);
                    }
                }
            }
        }

        const auto p = std::minmax_element(resultVector.begin(), resultVector.end());
        auto leftAmmo = p.second -> first;
        auto path = p.second -> second;

        std::ofstream outputFile;
        outputFile.open ("the3.out");
        if (path == failVector)
            outputFile << "Mission Failed, There is no such path to accomplish mission\n";
        outputFile << leftAmmo << std::endl;
        outputFile << path.size() << std::endl;
        for (int i = 0; i < path.size(); ++i)
            outputFile << path[i] << " ";
        outputFile.close();
    }
        // if there is 2 rooms with ammo
    else
    {
        // 1 KEY SCI BUN (0 0 0)
        // never go to ammo1
        roomsToPass = {roomsWithAmmo[0].first, roomsWithAmmo[1].first};
        // go to key
        keyPath = saveBunny(1,keyLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        if (keyPath != failVector)
        {
            // go to sci
            sciPath = saveBunny(keyLocation,sciLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
            if (sciPath != failVector)
            {
                // go to bun
                bunPath = saveBunny(sciLocation,bunLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                if (bunPath != failVector)
                {
                    // Concatenate paths
                    keyPath.insert(keyPath.end(), sciPath.begin() + 1, sciPath.end());
                    keyPath.insert(keyPath.end(), bunPath.begin() + 1, bunPath.end());
                    resultVector.emplace_back(initialAmmo, keyPath);
                }
            }
        }
        // 1 AMMO1 KEY SCI BUN (1 0 0)
        // go to ammo1 before going to key
        initialAmmo = ammoAmount;
        time = 1;
        // pass key room
        roomsToPass = {keyLocation, roomsWithAmmo[1].first};
        ammo1Path = saveBunny(1,roomsWithAmmo[0].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        initialAmmo += roomsWithAmmo[0].second;
        // you can go to key room now
        roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), keyLocation), roomsToPass.end());
        if (ammo1Path != failVector) {
            // go to key
            keyPath = saveBunny(roomsWithAmmo[0].first, keyLocation, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
            if (keyPath != failVector) {
                // go to sci
                sciPath = saveBunny(keyLocation, sciLocation, numRooms, initialAmmo, time, oddLocked, evenLocked,roomsToPass, graph);
                if (sciPath != failVector) {
                    // go to bun
                    bunPath = saveBunny(sciLocation, bunLocation, numRooms, initialAmmo, time, oddLocked,evenLocked, roomsToPass, graph);
                    if (bunPath != failVector) {
                        // Concatenate paths
                        ammo1Path.insert(ammo1Path.end(), keyPath.begin() + 1, keyPath.end());
                        ammo1Path.insert(ammo1Path.end(), sciPath.begin() + 1, sciPath.end());
                        ammo1Path.insert(ammo1Path.end(), bunPath.begin() + 1, bunPath.end());
                        resultVector.emplace_back(initialAmmo, ammo1Path);
                    }
                }
            }
        }
        // 1 KEY AMMO1 SCI BUN (0 1 0)
        // go to ammo1 before going to sci
        initialAmmo = ammoAmount;
        time = 1;
        // pass ammo1 room
        roomsToPass = {roomsWithAmmo[0].first, roomsWithAmmo[1].first};
        // go to key
        keyPath = saveBunny(1,keyLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        if (keyPath != failVector)
        {
            // go to ammo1 pass sci room
            roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[0].first), roomsToPass.end());
            roomsToPass.emplace_back(sciLocation);
            ammo1Path = saveBunny(keyLocation,roomsWithAmmo[0].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
            initialAmmo += roomsWithAmmo[0].second;
            // you can go to sci room now
            roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), sciLocation), roomsToPass.end());
            if (ammo1Path != failVector)
            {
                // go to sci
                sciPath = saveBunny(roomsWithAmmo[0].first,sciLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                if (sciPath != failVector)
                {
                    // go to bun
                    bunPath = saveBunny(sciLocation,bunLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                    if (bunPath != failVector)
                    {
                        // Concatenate paths
                        keyPath.insert(keyPath.end(), ammo1Path.begin() + 1, ammo1Path.end());
                        keyPath.insert(keyPath.end(), sciPath.begin() + 1, sciPath.end());
                        keyPath.insert(keyPath.end(), bunPath.begin() + 1, bunPath.end());
                        resultVector.emplace_back(initialAmmo,keyPath);
                    }
                }
            }
        }
        // 1 KEY SCI AMMO1 BUN (0 0 1)
        // go to ammo1 before going to bun
        initialAmmo = ammoAmount;
        time = 1;
        roomsToPass = {roomsWithAmmo[0].first, roomsWithAmmo[1].first};
        // go to key
        keyPath = saveBunny(1,keyLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        if (keyPath != failVector)
        {
            // go to sci
            sciPath = saveBunny(keyLocation,sciLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
            if (sciPath != failVector)
            {
                // go to ammo1 pass bun room
                roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[0].first), roomsToPass.end());
                roomsToPass.emplace_back(bunLocation);
                ammo1Path = saveBunny(sciLocation,roomsWithAmmo[0].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                initialAmmo += roomsWithAmmo[0].second;
                // you can go to key room now
                roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), bunLocation), roomsToPass.end());
                if (ammo1Path != failVector)
                {
                    bunPath = saveBunny(roomsWithAmmo[0].first,bunLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                    if (bunPath != failVector)
                    {
                        // Concatenate paths
                        keyPath.insert(keyPath.end(), sciPath.begin() + 1, sciPath.end());
                        keyPath.insert(keyPath.end(), ammo1Path.begin() + 1, ammo1Path.end());
                        keyPath.insert(keyPath.end(), bunPath.begin() + 1, bunPath.end());
                        resultVector.emplace_back(initialAmmo,keyPath);
                    }
                }
            }
        }
        // 1 AMMO2 KEY SCI BUN (2 0 0)
        // go to ammo2 before going to key
        initialAmmo = ammoAmount;
        time = 1;
        // pass key room
        roomsToPass = {keyLocation, roomsWithAmmo[0].first};
        ammo2Path = saveBunny(1,roomsWithAmmo[1].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        initialAmmo += roomsWithAmmo[1].second;
        // you can go to key room now
        roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), keyLocation), roomsToPass.end());
        if (ammo2Path != failVector) {
            // go to key
            keyPath = saveBunny(roomsWithAmmo[1].first, keyLocation, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
            if (keyPath != failVector) {
                // go to sci
                sciPath = saveBunny(keyLocation, sciLocation, numRooms, initialAmmo, time, oddLocked, evenLocked,roomsToPass, graph);
                if (sciPath != failVector) {
                    // go to bun
                    bunPath = saveBunny(sciLocation, bunLocation, numRooms, initialAmmo, time, oddLocked,evenLocked, roomsToPass, graph);
                    if (bunPath != failVector) {
                        // Concatenate paths
                        ammo2Path.insert(ammo2Path.end(), keyPath.begin() + 1, keyPath.end());
                        ammo2Path.insert(ammo2Path.end(), sciPath.begin() + 1, sciPath.end());
                        ammo2Path.insert(ammo2Path.end(), bunPath.begin() + 1, bunPath.end());
                        resultVector.emplace_back(initialAmmo, ammo2Path);
                    }
                }
            }
        }
        // 1 KEY AMMO2 SCI BUN (0 2 0)
        // go to ammo2 before going to sci
        initialAmmo = ammoAmount;
        time = 1;
        // pass ammo2 room
        roomsToPass = {roomsWithAmmo[1].first, roomsWithAmmo[0].first};
        // go to key
        keyPath = saveBunny(1,keyLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        if (keyPath != failVector)
        {
            // go to ammo2 pass sci room
            roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[1].first), roomsToPass.end());
            roomsToPass.emplace_back(sciLocation);
            ammo2Path = saveBunny(keyLocation,roomsWithAmmo[1].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
            initialAmmo += roomsWithAmmo[1].second;
            // you can go to sci room now
            roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), sciLocation), roomsToPass.end());
            if (ammo2Path != failVector)
            {
                // go to sci
                sciPath = saveBunny(roomsWithAmmo[1].first,sciLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                if (sciPath != failVector)
                {
                    // go to bun
                    bunPath = saveBunny(sciLocation,bunLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                    if (bunPath != failVector)
                    {
                        // Concatenate paths
                        keyPath.insert(keyPath.end(), ammo2Path.begin() + 1, ammo2Path.end());
                        keyPath.insert(keyPath.end(), sciPath.begin() + 1, sciPath.end());
                        keyPath.insert(keyPath.end(), bunPath.begin() + 1, bunPath.end());
                        resultVector.emplace_back(initialAmmo,keyPath);
                    }
                }
            }
        }
        // 1 KEY SCI AMMO2 BUN (0 0 2)
        // go to ammo2 before going to bun
        initialAmmo = ammoAmount;
        time = 1;
        roomsToPass = {roomsWithAmmo[1].first, roomsWithAmmo[0].first};
        // go to key
        keyPath = saveBunny(1,keyLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        if (keyPath != failVector) {
            // go to sci
            sciPath = saveBunny(keyLocation, sciLocation, numRooms, initialAmmo, time, oddLocked, evenLocked,roomsToPass, graph);
            if (sciPath != failVector) {
                // go to ammo2 pass bun room
                roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[1].first), roomsToPass.end());
                roomsToPass.emplace_back(bunLocation);
                ammo2Path = saveBunny(sciLocation, roomsWithAmmo[1].first, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
                initialAmmo += roomsWithAmmo[1].second;
                // you can go to key room now
                roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), bunLocation), roomsToPass.end());
                if (ammo2Path != failVector) {
                    bunPath = saveBunny(roomsWithAmmo[1].first, bunLocation, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
                    if (bunPath != failVector) {
                        // Concatenate paths
                        keyPath.insert(keyPath.end(), sciPath.begin() + 1, sciPath.end());
                        keyPath.insert(keyPath.end(), ammo2Path.begin() + 1, ammo2Path.end());
                        keyPath.insert(keyPath.end(), bunPath.begin() + 1, bunPath.end());
                        resultVector.emplace_back(initialAmmo, keyPath);
                    }
                }
            }
        }
        // 1 AMMO1 KEY AMMO2 SCI BUN (1 2 0)
        // go to ammo1 before going to key go to ammo2 before going to sci
        initialAmmo = ammoAmount;
        time = 1;
        // pass key and ammo2 room
        roomsToPass = {keyLocation, roomsWithAmmo[1].second};
        ammo1Path = saveBunny(1,roomsWithAmmo[0].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        initialAmmo += roomsWithAmmo[0].second;
        // you can go to key room now
        roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), keyLocation), roomsToPass.end());
        if (ammo1Path != failVector) {
            // go to key
            keyPath = saveBunny(roomsWithAmmo[0].first, keyLocation, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
            if (keyPath != failVector) {
                // pass sci room
                roomsToPass.emplace_back(sciLocation);
                // you can go to ammo2 now
                roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[1].first), roomsToPass.end());
                ammo2Path = saveBunny(keyLocation, roomsWithAmmo[1].first, numRooms, initialAmmo, time, oddLocked, evenLocked,roomsToPass, graph);
                initialAmmo += roomsWithAmmo[1].second;
                // you can go to key room now
                roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), sciLocation), roomsToPass.end());
                if (ammo2Path != failVector)
                {
                    // go to sci
                    sciPath = saveBunny(roomsWithAmmo[1].first, sciLocation, numRooms, initialAmmo, time, oddLocked, evenLocked,roomsToPass, graph);
                    if (sciPath != failVector) {
                        // go to bun
                        bunPath = saveBunny(sciLocation, bunLocation, numRooms, initialAmmo, time, oddLocked,evenLocked, roomsToPass, graph);
                        if (bunPath != failVector) {
                            // Concatenate paths
                            ammo1Path.insert(ammo1Path.end(), keyPath.begin() + 1, keyPath.end());
                            ammo1Path.insert(ammo1Path.end(), ammo2Path.begin() + 1, ammo2Path.end());
                            ammo1Path.insert(ammo1Path.end(), sciPath.begin() + 1, sciPath.end());
                            ammo1Path.insert(ammo1Path.end(), bunPath.begin() + 1, bunPath.end());
                            resultVector.emplace_back(initialAmmo, ammo1Path);
                        }
                    }
                }
            }
        }
        // 1 AMMO2 KEY AMMO1 SCI BUN (2 1 0)
        // go to ammo2 before going to key go to ammo1 before going to sci
        initialAmmo = ammoAmount;
        time = 1;
        // pass key and ammo1 room
        roomsToPass = {keyLocation, roomsWithAmmo[0].first};
        ammo2Path = saveBunny(1,roomsWithAmmo[1].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        initialAmmo += roomsWithAmmo[1].second;
        // you can go to key room now
        roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), keyLocation), roomsToPass.end());
        if (ammo2Path  != failVector) {
            // go to key
            keyPath = saveBunny(roomsWithAmmo[1].first, keyLocation, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
            if (keyPath != failVector) {
                // pass sci room
                roomsToPass.emplace_back(sciLocation);
                // you can go to ammo1 now
                roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[0].first), roomsToPass.end());
                ammo1Path = saveBunny(keyLocation, roomsWithAmmo[0].first, numRooms, initialAmmo, time, oddLocked, evenLocked,roomsToPass, graph);
                initialAmmo += roomsWithAmmo[0].second;
                // you can go to key room now
                roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), sciLocation), roomsToPass.end());
                if (ammo1Path != failVector)
                {
                    // go to sci
                    sciPath = saveBunny(roomsWithAmmo[0].first, sciLocation, numRooms, initialAmmo, time, oddLocked, evenLocked,roomsToPass, graph);
                    if (sciPath != failVector) {
                        // go to bun
                        bunPath = saveBunny(sciLocation, bunLocation, numRooms, initialAmmo, time, oddLocked,evenLocked, roomsToPass, graph);
                        if (bunPath != failVector) {
                            // Concatenate paths
                            ammo2Path.insert(ammo2Path.end(), keyPath.begin() + 1, keyPath.end());
                            ammo2Path.insert(ammo2Path.end(), ammo1Path.begin() + 1, ammo1Path.end());
                            ammo2Path.insert(ammo2Path.end(), sciPath.begin() + 1, sciPath.end());
                            ammo2Path.insert(ammo2Path.end(), bunPath.begin() + 1, bunPath.end());
                            resultVector.emplace_back(initialAmmo, ammo2Path);
                        }
                    }
                }
            }
        }
        // 1 KEY AMMO1 SCI AMMO2 BUN (0 1 2)
        // go to ammo1 before going to sci go to ammo2 before going to bun
        initialAmmo = ammoAmount;
        time = 1;
        roomsToPass = {roomsWithAmmo[0].first ,roomsWithAmmo[1].first};
        // go to key
        keyPath = saveBunny(1,keyLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        if (keyPath != failVector) {
            // go to ammo1 pass sci room
            roomsToPass.emplace_back(sciLocation);
            // you can go to ammo1 now
            roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[0].first), roomsToPass.end());
            ammo1Path = saveBunny(keyLocation, roomsWithAmmo[0].first, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
            initialAmmo += roomsWithAmmo[0].second;
            // you can go to sci room now
            roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), sciLocation), roomsToPass.end());
            if (ammo1Path != failVector)
            {
                // go to sci
                sciPath = saveBunny(roomsWithAmmo[0].first, sciLocation, numRooms, initialAmmo, time, oddLocked, evenLocked,roomsToPass, graph);
                if (sciPath != failVector) {
                    // go to ammo2 pass bun room
                    roomsToPass.emplace_back(bunLocation);
                    // you can go to ammo2 now
                    roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[1].first), roomsToPass.end());
                    ammo2Path = saveBunny(sciLocation, roomsWithAmmo[1].first, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
                    initialAmmo += roomsWithAmmo[1].second;
                    // you can go to key room now
                    roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), bunLocation), roomsToPass.end());
                    if (ammo2Path != failVector) {
                        bunPath = saveBunny(roomsWithAmmo[1].first, bunLocation, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
                        if (bunPath != failVector) {
                            // Concatenate paths
                            keyPath.insert(keyPath.end(), ammo1Path.begin() + 1, ammo1Path.end());
                            keyPath.insert(keyPath.end(), sciPath.begin() + 1, sciPath.end());
                            keyPath.insert(keyPath.end(), ammo2Path.begin() + 1, ammo2Path.end());
                            keyPath.insert(keyPath.end(), bunPath.begin() + 1, bunPath.end());
                            resultVector.emplace_back(initialAmmo, keyPath);
                        }
                    }
                }
            }
        }
        // 1 KEY AMMO2 SCI AMMO1 BUN (0 2 1)
        // go to ammo2 before going to sci go to ammo1 before going to bun
        initialAmmo = ammoAmount;
        time = 1;
        roomsToPass = {roomsWithAmmo[0].first ,roomsWithAmmo[1].first};
        // go to key
        keyPath = saveBunny(1,keyLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        if (keyPath != failVector) {
            // go to ammo2 pass sci room
            roomsToPass.emplace_back(sciLocation);
            // you can go to ammo2 now
            roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[1].first), roomsToPass.end());
            ammo2Path = saveBunny(keyLocation, roomsWithAmmo[1].first, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
            initialAmmo += roomsWithAmmo[1].second;
            // you can go to sci room now
            roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), sciLocation), roomsToPass.end());
            if (ammo2Path != failVector)
            {
                // go to sci
                sciPath = saveBunny(roomsWithAmmo[1].first, sciLocation, numRooms, initialAmmo, time, oddLocked, evenLocked,roomsToPass, graph);
                if (sciPath != failVector) {
                    // go to ammo1 pass bun room
                    roomsToPass.emplace_back(bunLocation);
                    // you can go to ammo1 now
                    roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[0].first), roomsToPass.end());
                    ammo1Path = saveBunny(sciLocation, roomsWithAmmo[0].first, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
                    initialAmmo += roomsWithAmmo[0].second;
                    // you can go to key room now
                    roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), bunLocation), roomsToPass.end());
                    if (ammo1Path != failVector) {
                        bunPath = saveBunny(roomsWithAmmo[0].first, bunLocation, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
                        if (bunPath != failVector) {
                            // Concatenate paths
                            keyPath.insert(keyPath.end(), ammo2Path.begin() + 1, ammo2Path.end());
                            keyPath.insert(keyPath.end(), sciPath.begin() + 1, sciPath.end());
                            keyPath.insert(keyPath.end(), ammo1Path.begin() + 1, ammo1Path.end());
                            keyPath.insert(keyPath.end(), bunPath.begin() + 1, bunPath.end());
                            resultVector.emplace_back(initialAmmo, keyPath);
                        }
                    }
                }
            }
        }
        // 1 AMMO1 KEY SCI AMMO2 BUN (1 0 2)
        // go to ammo1 before going to key go to ammo2 before going to bun
        initialAmmo = ammoAmount;
        time = 1;
        // pass key room and ammo2
        roomsToPass = {keyLocation, roomsWithAmmo[1].second};
        ammo1Path = saveBunny(1,roomsWithAmmo[0].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        initialAmmo += roomsWithAmmo[0].second;
        // you can go to key room now
        roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), keyLocation), roomsToPass.end());
        if (ammo1Path != failVector) {
            // go to key
            keyPath = saveBunny(roomsWithAmmo[0].first, keyLocation, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
            if (keyPath != failVector) {
                // go to sci
                sciPath = saveBunny(keyLocation, sciLocation, numRooms, initialAmmo, time, oddLocked, evenLocked,roomsToPass, graph);
                if (sciPath != failVector)
                {
                    // go to ammo2 pass bun room
                    roomsToPass.emplace_back(bunLocation);
                    // you can go to ammo2 now
                    roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[1].first), roomsToPass.end());
                    ammo2Path = saveBunny(sciLocation, roomsWithAmmo[1].first, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
                    initialAmmo += roomsWithAmmo[1].second;
                    // you can go to key room now
                    roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), bunLocation), roomsToPass.end());
                    if (ammo2Path != failVector) {
                        bunPath = saveBunny(roomsWithAmmo[1].first, bunLocation, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
                        if (bunPath != failVector) {
                            // Concatenate paths
                            ammo1Path.insert(ammo1Path.end(), keyPath.begin() + 1, keyPath.end());
                            ammo1Path.insert(ammo1Path.end(), sciPath.begin() + 1, sciPath.end());
                            ammo1Path.insert(ammo1Path.end(), ammo2Path.begin() + 1, ammo2Path.end());
                            ammo1Path.insert(ammo1Path.end(), bunPath.begin() + 1, bunPath.end());
                            resultVector.emplace_back(initialAmmo, ammo1Path);
                        }
                    }
                }
            }
        }
        // 1 AMMO2 KEY SCI AMMO1 BUN (2 0 1)
        // go to ammo2 before going to key go to ammo1 before going to bun
        initialAmmo = ammoAmount;
        time = 1;
        // pass key room and ammo1
        roomsToPass = {keyLocation, roomsWithAmmo[0].second};
        ammo2Path = saveBunny(1,roomsWithAmmo[1].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        initialAmmo += roomsWithAmmo[1].second;
        // you can go to key room now
        roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), keyLocation), roomsToPass.end());
        if (ammo2Path != failVector) {
            // go to key
            keyPath = saveBunny(roomsWithAmmo[1].first, keyLocation, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
            if (keyPath != failVector) {
                // go to sci
                sciPath = saveBunny(keyLocation, sciLocation, numRooms, initialAmmo, time, oddLocked, evenLocked,roomsToPass, graph);
                if (sciPath != failVector)
                {
                    // go to ammo1 pass bun room
                    roomsToPass.emplace_back(bunLocation);
                    // you can go to ammo1 now
                    roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[0].first), roomsToPass.end());
                    ammo1Path = saveBunny(sciLocation, roomsWithAmmo[0].first, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
                    initialAmmo += roomsWithAmmo[0].second;
                    // you can go to bun room now
                    roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), bunLocation), roomsToPass.end());
                    if (ammo1Path != failVector) {
                        bunPath = saveBunny(roomsWithAmmo[0].first, bunLocation, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
                        if (bunPath != failVector) {
                            // Concatenate paths
                            ammo2Path.insert(ammo2Path.end(), keyPath.begin() + 1, keyPath.end());
                            ammo2Path.insert(ammo2Path.end(), sciPath.begin() + 1, sciPath.end());
                            ammo2Path.insert(ammo2Path.end(), ammo1Path.begin() + 1, ammo1Path.end());
                            ammo2Path.insert(ammo2Path.end(), bunPath.begin() + 1, bunPath.end());
                            resultVector.emplace_back(initialAmmo, ammo2Path);
                        }
                    }
                }
            }
        }
        // 1 AMMO1 AMMO2 KEY SCI BUN (1/2 0 0)
        // first go to ammo1 then go to ammo2 before going to key
        initialAmmo = ammoAmount;
        time = 1;
        // pass key room and ammo2
        roomsToPass = {keyLocation, roomsWithAmmo[1].first};
        ammo1Path = saveBunny(1,roomsWithAmmo[0].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        initialAmmo += roomsWithAmmo[0].second;
        if (ammo1Path != failVector) {
            ammo2Path = saveBunny(roomsWithAmmo[0].first,roomsWithAmmo[1].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
            initialAmmo += roomsWithAmmo[1].second;
            // you can go to key room now
            roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), keyLocation), roomsToPass.end());
            if (ammo2Path != failVector) {
                // go to key
                keyPath = saveBunny(roomsWithAmmo[1].first, keyLocation, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
                if (keyPath != failVector) {
                    // go to sci
                    sciPath = saveBunny(keyLocation, sciLocation, numRooms, initialAmmo, time, oddLocked, evenLocked,roomsToPass, graph);
                    if (sciPath != failVector) {
                        // go to bun
                        bunPath = saveBunny(sciLocation, bunLocation, numRooms, initialAmmo, time, oddLocked,evenLocked, roomsToPass, graph);
                        if (bunPath != failVector) {
                            // Concatenate paths
                            ammo1Path.insert(ammo1Path.end(), ammo2Path.begin() + 1, ammo2Path.end());
                            ammo1Path.insert(ammo1Path.end(), keyPath.begin() + 1, keyPath.end());
                            ammo1Path.insert(ammo1Path.end(), sciPath.begin() + 1, sciPath.end());
                            ammo1Path.insert(ammo1Path.end(), bunPath.begin() + 1, bunPath.end());
                            resultVector.emplace_back(initialAmmo, ammo1Path);
                        }
                    }
                }
            }
        }
        // 1 AMMO2 AMMO1 KEY SCI BUN (2/1 0 0)
        // first go to ammo2 then go to ammo1 before going to key
        initialAmmo = ammoAmount;
        time = 1;
        // pass key room and ammo1
        roomsToPass = {keyLocation, roomsWithAmmo[0].first};
        ammo2Path = saveBunny(1,roomsWithAmmo[1].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        initialAmmo += roomsWithAmmo[1].second;
        if (ammo2Path != failVector) {
            roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[0].first), roomsToPass.end());
            ammo1Path = saveBunny(roomsWithAmmo[1].first,roomsWithAmmo[0].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
            initialAmmo += roomsWithAmmo[0].second;
            // you can go to key room now
            roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), keyLocation), roomsToPass.end());
            if (ammo1Path != failVector) {
                // go to key
                keyPath = saveBunny(roomsWithAmmo[0].first, keyLocation, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
                if (keyPath != failVector) {
                    // go to sci
                    sciPath = saveBunny(keyLocation, sciLocation, numRooms, initialAmmo, time, oddLocked, evenLocked,roomsToPass, graph);
                    if (sciPath != failVector) {
                        // go to bun
                        bunPath = saveBunny(sciLocation, bunLocation, numRooms, initialAmmo, time, oddLocked,evenLocked, roomsToPass, graph);
                        if (bunPath != failVector) {
                            // Concatenate paths
                            ammo2Path.insert(ammo2Path.end(), ammo1Path.begin() + 1, ammo1Path.end());
                            ammo2Path.insert(ammo2Path.end(), keyPath.begin() + 1, keyPath.end());
                            ammo2Path.insert(ammo2Path.end(), sciPath.begin() + 1, sciPath.end());
                            ammo2Path.insert(ammo2Path.end(), bunPath.begin() + 1, bunPath.end());
                            resultVector.emplace_back(initialAmmo, ammo2Path);
                        }
                    }
                }
            }
        }
        // 1 KEY AMMO1 AMMO2 SCI BUN (0 1/2 0)
        // first go to ammo1 then go to ammo2 before going to sci
        initialAmmo = ammoAmount;
        time = 1;
        // pass ammo1 and ammo2 room
        roomsToPass = {roomsWithAmmo[0].first, roomsWithAmmo[1].first};
        // go to key
        keyPath = saveBunny(1,keyLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        if (keyPath != failVector)
        {
            // go to ammo1 pass sci and ammo2 room
            roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[0].first), roomsToPass.end());
            roomsToPass.emplace_back(sciLocation);
            ammo1Path = saveBunny(keyLocation,roomsWithAmmo[0].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
            initialAmmo += roomsWithAmmo[0].second;
            if (ammo1Path != failVector)
            {
                // go to ammo2 pass sci room
                roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[1].first), roomsToPass.end());
                ammo2Path = saveBunny(roomsWithAmmo[0].first,roomsWithAmmo[1].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                initialAmmo += roomsWithAmmo[1].second;
                // you can go to sci room now
                roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), sciLocation), roomsToPass.end());
                if (ammo2Path != failVector)
                {
                    // go to sci
                    sciPath = saveBunny(roomsWithAmmo[1].first,sciLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                    if (sciPath != failVector)
                    {
                        // go to bun
                        bunPath = saveBunny(sciLocation,bunLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                        if (bunPath != failVector)
                        {
                            // Concatenate paths
                            keyPath.insert(keyPath.end(), ammo1Path.begin() + 1, ammo1Path.end());
                            keyPath.insert(keyPath.end(), ammo2Path.begin() + 1, ammo2Path.end());
                            keyPath.insert(keyPath.end(), sciPath.begin() + 1, sciPath.end());
                            keyPath.insert(keyPath.end(), bunPath.begin() + 1, bunPath.end());
                            resultVector.emplace_back(initialAmmo,keyPath);
                        }
                    }
                }
            }
        }
        // 1 KEY AMMO2 AMMO1 SCI BUN (0 2/1 0)
        // first go to ammo2 then go to ammo1 before going to sci
        initialAmmo = ammoAmount;
        time = 1;
        // pass ammo1 and ammo2 room
        roomsToPass = {roomsWithAmmo[0].first, roomsWithAmmo[1].first};
        // go to key
        keyPath = saveBunny(1,keyLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        if (keyPath != failVector)
        {
            // go to ammo2 pass sci and ammo1 room
            roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[1].first), roomsToPass.end());
            roomsToPass.emplace_back(sciLocation);
            ammo2Path = saveBunny(keyLocation,roomsWithAmmo[1].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
            initialAmmo += roomsWithAmmo[1].second;
            if (ammo2Path != failVector)
            {
                // go to ammo1 pass sci room
                roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[0].first), roomsToPass.end());
                ammo1Path = saveBunny(roomsWithAmmo[1].first,roomsWithAmmo[0].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                initialAmmo += roomsWithAmmo[0].second;
                // you can go to sci room now
                roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), sciLocation), roomsToPass.end());
                if (ammo1Path != failVector)
                {
                    // go to sci
                    sciPath = saveBunny(roomsWithAmmo[0].first,sciLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                    if (sciPath != failVector)
                    {
                        // go to bun
                        bunPath = saveBunny(sciLocation,bunLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                        if (bunPath != failVector)
                        {
                            // Concatenate paths
                            keyPath.insert(keyPath.end(), ammo2Path.begin() + 1, ammo2Path.end());
                            keyPath.insert(keyPath.end(), ammo1Path.begin() + 1, ammo1Path.end());
                            keyPath.insert(keyPath.end(), sciPath.begin() + 1, sciPath.end());
                            keyPath.insert(keyPath.end(), bunPath.begin() + 1, bunPath.end());
                            resultVector.emplace_back(initialAmmo,keyPath);
                        }
                    }
                }
            }
        }
        // 1 KEY SCI AMMO1 AMMO2 BUN (0 0 1/2)
        // first go to ammo1 then go to ammo2 before going to bun
        initialAmmo = ammoAmount;
        time = 1;
        roomsToPass = {roomsWithAmmo[0].first, roomsWithAmmo[1].first};
        // go to key
        keyPath = saveBunny(1,keyLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        if (keyPath != failVector)
        {
            // go to sci
            sciPath = saveBunny(keyLocation,sciLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
            if (sciPath != failVector)
            {
                // go to ammo1 pass bun room
                roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[0].first), roomsToPass.end());
                roomsToPass.emplace_back(bunLocation);
                ammo1Path = saveBunny(sciLocation,roomsWithAmmo[0].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                initialAmmo += roomsWithAmmo[0].second;
                if (ammo1Path != failVector)
                {
                    roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[1].first), roomsToPass.end());
                    ammo2Path = saveBunny(roomsWithAmmo[0].first, roomsWithAmmo[1].first, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
                    initialAmmo += roomsWithAmmo[1].second;
                    // you can go to bun room now
                    roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), bunLocation), roomsToPass.end());
                    if (ammo2Path != failVector) {
                        bunPath = saveBunny(roomsWithAmmo[1].first, bunLocation, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
                        if (bunPath != failVector) {
                            // Concatenate paths
                            keyPath.insert(keyPath.end(), sciPath.begin() + 1, sciPath.end());
                            keyPath.insert(keyPath.end(), ammo1Path.begin() + 1, ammo1Path.end());
                            keyPath.insert(keyPath.end(), ammo2Path.begin() + 1, ammo2Path.end());
                            keyPath.insert(keyPath.end(), bunPath.begin() + 1, bunPath.end());
                            resultVector.emplace_back(initialAmmo, keyPath);
                        }
                    }
                }
            }
        }
        // 1 KEY SCI AMMO2 AMMO1 BUN (0 0 2/1)
        // first go to ammo2 then go to ammo1 before going to bun
        initialAmmo = ammoAmount;
        time = 1;
        roomsToPass = {roomsWithAmmo[0].first, roomsWithAmmo[1].first};
        // go to key
        keyPath = saveBunny(1,keyLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
        if (keyPath != failVector)
        {
            // go to sci
            sciPath = saveBunny(keyLocation,sciLocation,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
            if (sciPath != failVector)
            {
                // go to ammo2 pass bun room
                roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[1].first), roomsToPass.end());
                roomsToPass.emplace_back(bunLocation);
                ammo2Path = saveBunny(sciLocation,roomsWithAmmo[1].first,numRooms,initialAmmo,time,oddLocked,evenLocked,roomsToPass,graph);
                initialAmmo += roomsWithAmmo[1].second;
                if (ammo2Path != failVector)
                {
                    roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), roomsWithAmmo[0].first), roomsToPass.end());
                    ammo1Path = saveBunny(roomsWithAmmo[1].first, roomsWithAmmo[0].first, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
                    initialAmmo += roomsWithAmmo[0].second;
                    // you can go to bun room now
                    roomsToPass.erase(std::remove(roomsToPass.begin(), roomsToPass.end(), bunLocation), roomsToPass.end());
                    if (ammo1Path != failVector) {
                        bunPath = saveBunny(roomsWithAmmo[0].first, bunLocation, numRooms, initialAmmo, time, oddLocked, evenLocked, roomsToPass, graph);
                        if (bunPath != failVector) {
                            // Concatenate paths
                            keyPath.insert(keyPath.end(), sciPath.begin() + 1, sciPath.end());
                            keyPath.insert(keyPath.end(), ammo2Path.begin() + 1, ammo2Path.end());
                            keyPath.insert(keyPath.end(), ammo1Path.begin() + 1, ammo1Path.end());
                            keyPath.insert(keyPath.end(), bunPath.begin() + 1, bunPath.end());
                            resultVector.emplace_back(initialAmmo, keyPath);
                        }
                    }
                }
            }
        }

        const auto p = std::minmax_element(resultVector.begin(), resultVector.end());
        auto leftAmmo = p.second -> first;
        auto path = p.second -> second;

        std::ofstream outputFile;
        outputFile.open ("the3.out");
        if (path == failVector)
            outputFile << "Mission Failed, There is no such path to accomplish mission\n";
        outputFile << leftAmmo << std::endl;
        outputFile << path.size() << std::endl;
        for (int i = 0; i < path.size(); ++i)
            outputFile << path[i] << " ";
        outputFile.close();
    }
}
