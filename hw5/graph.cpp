//TODO
#include <set>


/*
Greg Faaborg
graph.cpp
This program implements 3 graph algorithms depth first search, breadth first search, and topological sort
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <queue>
#include <sstream>
#include <limits>
#include <algorithm>
#include <stack>
using namespace std;

//used for topological sort
stack<int> topSort;

//used for discovery time 
stack<int> discov;

//used fot finish time
stack<int> fini;
//time
int start=1;

//depth first search that finds discover time and finsih time as well as topological sort
void first_dfs(vector<int> adj[],int node, int visited[], vector<int> &disco, vector<int> &fin)
{
    //node has been visited
    visited[node] = 1;

    //insert into discovery vector 
    disco.insert(disco.begin() + node,start++);

    //push discovery time onto discov stack
    discov.push(disco[node]);    

    int num;    

    //list size if the adjacent node is not visited recursively call dfs to 
    //mark as visited and find discovery and finish times
    for(int i = 0; i < adj[node].size(); i++)
    {
        if(visited[adj[node][i]] == 0)
            first_dfs(adj,adj[node][i],visited,disco,fin);
    }
    //push current node onto topological sort stack
    topSort.push(node);

    //find finish time for node
    fin.insert(fin.begin()+node,start++);

    //push finish time onto stack
    fini.push(fin[node]);
}

void second_dfs(vector<int> adj[],int size, vector<int> &disco, vector<int> &fin)
{
    //make visited array
    int visited[size];

    //initialize all nodes as unvisited
    for(int i = 1; i <= size;i++)
    {
        visited[i] = 0;
    }
     
    //do depth first search to find discovery time and finish time
    for(int i = 1; i <= size; i++)
    {
        if(visited[i] == 0)
        {
            first_dfs(adj,i,visited,disco,fin);
        }
    }
}

bool compare(const pair<int,int> &one, const pair<int,int> &two)
{
    return (one.second < two.second);
}

void bfs(vector<int> adj[], int size)
{
    //vector of pairs used for sorting 
    vector<pair<int,int> > sorted (size);
    pair<int,int> dist;
    //queue containg nodes
    queue<int> breadth;

    //distance between source and node array
    int distance[size];

    for(int i = 0; i <= size; i++)
    {
        //setting distance from source to infinity
        distance[i] = 999999;
    }
 
    //visited array
    int visited[size];

    //set all to unvisited
    for(int i = 1;i <= size;i++)
    {
        visited[i] = 0;
    }
    
    //node 1 is 0 away from 1 
    distance[1] = 0;
    //it is visited
    visited[1] = 1;

    //push into queue
    breadth.push(1);
    
    int node1;
    int node2;
    //while there are nodes in the queue
    while(!breadth.empty())
    {
        //get first node from queue
        node1 = breadth.front();
        breadth.pop();

        //for all of the current nodes adjacent nodes
        for(int i = 0; i < adj[node1].size(); i++)
        {
            //set node 2 to be the next in the list
            node2 = adj[node1][i];
            //if not visited
            if(visited[node2] == 0)
            {
                //mark as visited 
                visited[node2] = 1;
                //find distance of node2
                distance[node2] = distance[node1] + 1;
    
                //push node2 into queue
                breadth.push(node2);
            
            }
        }
    }

    cout << "Result of Breadth First Search Sorted based on distance:" << endl;
    cout << "COULD NOT GET TO WORK" << endl;


    //make pair for distance between node and source
    for(int i =1; i <= size;i++)
    {
        sorted.push_back(make_pair(distance[i],i));
    }
 
    //standard sort based on first element in pait
    sort(sorted.begin(),sorted.end());
  
    //print out vector of pairs
    for(int i = 1; i <=size; i++)
    {
        cout << sorted[i].second << " " << sorted[i].first << endl;
    }   
}
int main(int argc, char **argv)
{
    //checking for correct input
    if(argc < 2 || argc > 2)
    {
        cout << "Usage error:" << endl;
        cout << "Run " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    //file containing nodes
    ifstream infile(argv[1]);


    int count = 0;
    string line;
    //counting number of lines to determine number of nodes
    while(getline(infile,line))
    {
        ++count;
    }

    //rewind file
    infile.clear();
    infile.seekg(0);


    vector<int> adj[count+1];

    string data,line_num;
    int node1,node2;
    
    //read in from file
    while(!infile.eof())
    {
        getline(infile,data);
        stringstream stream;
        //make stream
        stream << data;

        //read in line
        stream >> line_num;

        
        stringstream(line_num) >> node1;
        //while there are still more elements in the stream
        while(!stream.eof())
        {
            //get next number
            stream >> line_num;
            if(stringstream(line_num) >> node2)
            {
                //add that node to the adjacecny list
                adj[node1].push_back(node2);
            }
        }
    }

    vector<int> discovered(count);
    vector<int> finished(count);
    
    //calling for depth first search
    second_dfs(adj,count,discovered,finished); 
    
    //calling for breadth first search
    bfs(adj,count);

    //clearing out vectors
    discovered.clear();
    finished.clear();

    //adding elements from stack to vectors
    while(!fini.empty())
    {
        finished.push_back(fini.top());
        fini.pop();    
    }
    while(!discov.empty())
    {
        discovered.push_back(discov.top());
        discov.pop();
    }   

    //making vecotor of pairs for sorting 
    vector<pair<int,int> > sorted;  
    cout << "\nThe following is breadth first search sorted by the discovery time:" << endl;
    cout << "COULD NOT GET TO WORK" << endl;

    //make pair
    for(int i = 1; i <= count; i++)
    {
        sorted.push_back(make_pair(discovered[i],i));
    }
    //sort 
    sort(sorted.begin(),sorted.end());
  
    //print results
    for(int i = 1;i < count; i++)
        cout << sorted[i].second << " " << sorted[i].first << " " << finished[i] << endl;

    cout << endl << "The following is the topological sorted order of the graph:" << endl;
    //pop from topological sort stack to get correct oreder
    while(!topSort.empty())
    {
        cout << topSort.top() << endl;
        topSort.pop();
    }
    return 0;

    
}
