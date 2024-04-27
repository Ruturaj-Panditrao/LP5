#include <omp.h>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

// Time difference in sequential and parallel operations is noticeable only on huge graphs
// use double start/end = omp_get_wtime() for (end-start) time
// or use auto start/end = chrono::high_synchronization_clock::now() and (end-start).count() 

void sequentialDFShelper(int vertex, vector<bool>&visited, vector<vector<int>>&adj)
{
    visited[vertex] = true;
    cout<<vertex<<" ";

    for(int i=0; i<adj[vertex].size();i++)
    {
        int current = adj[vertex][i];
        if(visited[current]==false) sequentialDFShelper(current,visited,adj);
    }
}

void sequentialDFS(vector<vector<int>>&adj, int n)
{
    vector<bool>visited(n,false);

    int start;
    cout<<"Enter Starting Vertex : "; cin>>start;
    sequentialDFShelper(start,visited,adj);
}


void parallelDFShelper(int vertex, vector<bool>&visited, vector<vector<int>>&adj)
{
    visited[vertex] = true;
    cout<<vertex<<" ";

    #pragma op parallel for 
    for(int i=0; i<adj[vertex].size();i++)
    {
        int current = adj[vertex][i];
        if(visited[current]==false) parallelDFShelper(current,visited,adj);
    }
}

void parallelDFS(vector<vector<int>>&adj, int n)
{
    vector<bool>visited(n,false);

    int start;
    cout<<"Enter Starting Vertex : "; cin>>start;
    parallelDFShelper(start,visited,adj);
}

void sequentialBFS(vector<vector<int>>&adj, int n)
{
    int start;
    cout<<"Enter Starting Vertex : "; cin>>start;
    vector<bool>visited(n,false);
    queue<int>q;
    visited[start]=true;
    q.push(start);

    while(!q.empty())
    {
        int current = q.front();
        q.pop();
        cout<<current<<" ";
        for(auto it : adj[current])
        {
            if(visited[it]==false)
            {
                visited[it]=true;
                q.push(it);
            }
        }
    }
}

void parallelBFS(vector<vector<int>>&adj, int n)
{
    int start;
    cout<<"Enter Starting Vertex : "; cin>>start;
    vector<bool>visited(n,false);
    queue<int>q;
    visited[start]=true;
    q.push(start);

    while(!q.empty())
    {
        int current = q.front();
        q.pop();
        cout<<current<<" ";
        #pragma omp parallel for
        for(auto it : adj[current])
        {
            if(visited[it]==false)
            {
                visited[it]=true;
                q.push(it);
            }
        }
    }
}

void printGraph(vector<vector<int>>&adj, int n)
{
    for(int i=0; i<n; i++)
    {
        for(auto it : adj[i])
        {
            cout<<i<<"->"<<it<<endl;
        }
    }
}

int main()
{
    int n;
    cout<<"Enter the Number of Vertices : "; cin>>n;

    int m;
    cout<<"Enter the Number of Edges : "; cin>>m;

    vector<vector<int>>adj(n);

    for(int i=0; i<m; i++)
    {
        int u,v;
        cout<<"Enter u : "; cin>>u;
        cout<<"Enter v : "; cin>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        cout<<"Edge Inserted!"<<endl;
    }

    printGraph(adj,n);
    cout<<"Sequential DFS : "<<endl; 
    sequentialDFS(adj,n);
    // For disconnected Graphs, run the function inside a for loop so that all vertices are covered.
    cout<<"\nParallel DFS : "<<endl; 
    parallelDFS(adj,n);
    cout<<"\nSequential BFS : "<<endl;
    sequentialBFS(adj,n);
    cout<<"\nParalled BFS : "<<endl;
    parallelBFS(adj,n);
}