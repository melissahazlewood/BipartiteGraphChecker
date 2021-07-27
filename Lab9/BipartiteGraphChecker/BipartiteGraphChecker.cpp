//
//  BipartiteGraphChecker.cpp
//  Lab9
//
//  Created by Melissa Hazlewood on 12/16/19.
//  Copyright © 2019 Melissa Hazlewood. All rights reserved.
//

#include <iostream>
#include <queue>
#include <string>
#include "Graph.hpp"

using namespace std;

void explore(Graph &g);
bool isBipartite(Graph &g, Node &n);
bool BFS_color(Graph &g, Node &s);

int main() {
    srand((unsigned) time(NULL));
    int v = 5;
    int e = 3;
    
    cout << "1.)" << endl;
    cout << "Please enter the number of vertices you would like in your graph: ";
    cin >> v;
    cout << "\nPlease enter desired number of edges: ";
    cin >> e;

    cout << "\n2.)" << endl;
    cout << "Generating edges and making graph..." << endl;
    Graph g{v,e,false};
    cout << "Done." << endl;

    cout << "\n3.)" << endl;
    cout << "Adjacency lists for each vertex in the resulting graph:" << endl;
    g.printAdjLists();
    
//    string yesOrNo = isBipartite(g, *g.getNodeList()[0]) ? "yes" : "no";
//    cout << "Is G bipartite? " << yesOrNo << endl;
    explore(g);
    
    for (int i = 0; i < g.getNodeListSize(); i++)
    {
        cout << "v_" << g.getNodeList()[i]->getIndex() << ": " << g.getNodeList()[i]->color << endl;
    }
    
    return 0;
}


void explore(Graph &g)
{
    //initialize
    for (int i = 0; i < g.getNodeListSize(); i++)
    {
        g.getNodeList()[i]->color = 'g';
    }
    
    g.getNodeList()[0]->color = 'b';
    isBipartite(g, *g.getNodeList()[0]);
    for (int i = 0; i < g.getNodeListSize(); i++)
    //while()?
    {
        if (g.getNodeList()[i]->color == 'g')
        {
            g.getNodeList()[i]->color = 'b';
            isBipartite(g, *g.getNodeList()[i]);
        }
    }
}

bool isBipartite(Graph &g, Node &n)
{
    return BFS_color(g, n);
}


bool BFS_color(Graph &g, Node &s)
{
//    vector<Node*> visited = {};
    queue<Node*> q = {};
    q.push(&s);
    Node * sParent = new Node{};
    s.setParentPointer(*sParent);
//    cout << s.parent->index;
    
    while(!q.empty())
    {
        Node * curr(q.front());
        q.pop();
        for (int i = 0; i < curr->getAdjListSize(); i++)
        {
            if ((*curr->getAdjList()[i]).color == 'g')
            {
                if (curr->color == 'b')
                    (*curr->getAdjList()[i]).color = 'r';
                else
                    (*curr->getAdjList()[i]).color = 'b';
            }
            else if ((*curr->getAdjList()[i]).color == curr->color)
            {
                cout << "NOT BIPARTITE" << endl;
                return false;
            }
            if ((*curr->getAdjList()[i]).getParentPointer() == nullptr)
            {
                (*curr->getAdjList()[i]).setParentPointer(*curr);
                q.push(&(*curr->getAdjList()[i]));
//                visited.push_back(curr->getAdjList()[i]);
            }
        }
    }
//    return visited;
    return true;
}
