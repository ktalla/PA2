# Programming Assignment 2

## first.c: Undirected Graph Representation
![Screenshot 2023-11-25 163950](https://github.com/ktalla/PA2/assets/70788915/59ddc62a-25da-4bff-9c68-9fa04ffa8e5d)

Represent an undirected graph with an adjacency list. Then, the program will answer simple graph queries.

### Input-Output:
our program will take two file names as its command-line input. The first file includes the undirected graph. Your program reads the contents of this file and constructs the graph data structure. The first line in this file provides the number of vertices in the graph. Next, each line contains the name of each vertex in the graph. Afterwards, each following line includes information about an edge in the graph. Each edge is described by the name of its pair of vertices, separated by a space. The second file includes queries on the constructed graph. Each line contains a separate query that starts with the query type and a vertex, separated by a space. There are two query types. Degree queries start with the letter ’d’, followed by a space and the vertex’s name, which is a string. Upon processing a degree query, your program must print out the queried vertex’s degree, followed by a newline character. Adjacency queries start with the letter ’a’, followed by a space and the vertex’s
name. Upon processing an adjacency query, your program must print out the vertices adjacent to the queried vertex, each vertex separated by a space and finally, a newline character. When you print the results of the adjacency query, the results have to be sorted lexicographically.

Example Execution:
Let’s assume we have the following graph and query file: <br>
graph.txt<br>
5<br>
A<br>
B<br>
C<br>
D<br>
E<br>
A B<br>
A C<br>
A D<br>
B D<br>
C D<br>
C E<br>
D E<br>
query.txt:<br>
d E<br>
a C<br>
d A<br>
a A<br>
Then the result will be:<br>
$./first graph.txt query.txt<br>
2<br>
A D E<br>
3<br>
B C D<br>

## Second.c: Weighted Directed Graph Representation
![Screenshot 2023-11-25 164449](https://github.com/ktalla/PA2/assets/70788915/d69e4181-1ed8-4768-9e18-b9030789f25d)

Represent a directed graph with an adjacency list. Then, the program will answer simple graph queries.

### Input-Output format: 
Your program will take two file names as its command-line input. The first file includes the weighted directed graph. Your program reads the contents of this file and constructs the graph data structure. The first line in this file provides the number of vertices in the graph. Next, each line contains the name of each vertex in the graph. Afterwards, each following line includes information about a weighted directed edge in the graph. Each weighted edge is described by the name of its pair of vertices, followed by the edge weight, separated by a space. For example, B A 10 defines a directed edge from vertex B to vertex A with an edge weight of 10. The second file includes queries on the constructed graph. Each line contains a separate query that starts with the query type and a vertex, separated by a space. There are three query types. Out-degree queries start with the letter ’o’, followed by a space and the vertex’s name. Upon processing an out-degree query, your program must print out the queried vertex’s out-degree 1, followed by a newline character. In degree queries start with the letter ’i’, followed by a space and the vertex’s name. Upon processing an in degree query, your program must print out the queried vertex’s in
degree 2, followed by a newline character. Adjacency queries start with the letter ’a’, followed by a space and the vertex’s name. Upon processing an adjacency query, your program must print out the vertices adjacent to the queried vertex, each vertex separated by a space and finally, a newline character. When you print the results of the adjacency query, the results have to be sorted lexicographically.

Example Execution: <br>
Let’s assume we have the following graph and query file: <br>
graph.txt <br>
5 <br>
A <br>
B <br>
C <br>
D <br>
E <br>
B A 10 <br>
A C 8 <br>
A D 12 <br>
B D 5 <br>
C E 5 <br>
D C 9<br>
E C 7<br>
E D 3<br>
query.txt:<br>
o E<br>
a C<br>
i E<br>
a A<br>
a E<br>
Then the result will be:<br>
$./second graph.txt query.txt<br>
2<br>
E<br>
1<br>
C D<br>
C D<br>

#third.c: Breadth-first Search
Implement the bread-first search (BFS) graph traversal algorithm. For a given input graph G=(V,E) and a source vertex s, BFS starts exploring the edges of G until it discovers all vertices reachable from the source vertex. During a BFS search, we 
start by visiting the adjacent vertices to the source vertex, processing them, and subsequently exploring vertices in order of edge distance (i.e., the smallest number of edges) from it. Figure 3 shows an example graph and its BFS traversal starting from source vertex B. Note that the vertices are processed in order of their distance from the source. You will write a program that will read an undirected graph from a file using your implementation from part 1 and perform BFS starting from different source vertices. 
![Screenshot 2023-11-25 165550](https://github.com/ktalla/PA2/assets/70788915/f309f682-e146-4108-85a8-22c6d7db9578)

### Input-Output format: 
our program will take two file names as its command-line input. The first file includes the undirected graph. This file is similar to the graph file from part 1. Your program reads the contents of this file and constructs the graph data structure. The first line in this file provides the number of vertices in the graph. Next, each line contains the name of each vertex in the graph. Afterwards, each following line includes information about an edge in the graph. Each edge is described by the name of its pair of vertices, separated by a space. The second file includes BFS queries on the constructed graph. Each line contains a different BFS
query specifying a source vertex for the BFS. Your program must read the source vertex, perform a BFS traversal on the constructed graph using the chosen source vertex, and print out the graph vertices in order of BFS processing. Each vertex is separated by a space and finally, a newline character.

Let’s assume we have the following graph and query file: <br>
graph.txt<br>
6<br>
A<br>
B<br>
C<br>
D<br>
E<br>
F<br>
A B<br>
A C<br>
A D<br>
B D<br>
C D<br>
C E<br>
D E<br>
E F<br>
query.txt:<br>
B<br>
E<br>
$./third graph.txt query.txt<br>
B A D C E F<br>
E C D F A B<br>

# fourth.c: Depth-first Search

Implement the depth-first search (DFS) graph traversal algorithm. For a given input graph G=(V,E), DFS visits an unvisited vertex v. At each step in DFS, we choose an unvisited vertex adjacent to the most recently discovered vertex. We continue this process until all vertices reachable from v are discovered. If any undiscovered vertices remain, we choose one of them and repeat the above process until all vertices are discovered. For example, Figure 4 illustrates a DFS traversal of the example graph in Figure 2(a) 4. In this part, you write a program that will read a directed graph from a file using your implementation from part 2 and perform a DFS traversal, printing out the graph vertices in order of DFS vertex visit. When you are choosing a vertex to visit next among the adjacent children, you have to pick the vertex that is not visited yet and occurs first in the lexicographic order. 

### Input-Output format: 
Your program will take a file name as its command-line input. This file includes a directed graph, and it follows the same format from part 2. Your program reads the contents of this file and constructs the graph data structure. The first line in this file provides the number of vertices in the graph. Each following line includes information about a weighted directed edge in the graph. Each weighted edge is described by the name of its pair of vertices, followed by the edge weight, separated by a space. Your program must read and construct this graph, perform a DFS traversal, and print out the graph vertices in order of DFS visitation. Each vertex is separated by a space and, finally, a newline character.

Example Execution:<br>
Let’s assume we have the following graph input file:<br>
graph.txt<br>
5<br>
A<br>
B<br>
C<br>
D<br>
E<br>
B A 10<br>
A C 8<br>
A D 12<br>
B D 5<br>
C E 5<br>
D C 9<br>
E C 7<br>
E D 3<br>
Then the result will be:<br>
$./fourth graph.txt<br>
A C E D B<br>

## fifth.c: Single-source Shortest Path in a Directed Acyclic Graph
Given a weighted directed graph G=(V,E) and the source vertex s, the single-source shortest path problem’s goal is to identify to shortest path from the source vertex to all vertices in the graph. The single-source shortest problem in DAGs can be solved by visiting the DAG’s vertices in a topologically sorted order and updating the shortest path of the visited vertex’s adjacent vertices. You must use the DFS traversal from part 4 to topologically sort the DAG. Algorithm 1 shows the steps to compute the single source path for the graph G and source vertex src. The algorithm maintains a distance array that is initially set to infinity for all vertices except
the source vertex. distance[u] contains the shortest path from the source vertex to vertex u at the end of the algorithm or infinity if no path between src and u exists. A topological sorting of the a DAG G(V,E) is an ordering of its vertices, T such that for every directed (u,v), vertex u appears before vertex v in its topological ordering. For example, Figure 5(a) shows an example DAG and its topological sort. Figure 5(b-f) illustrates the steps taken by the DFS inspired algorithm7 to compute the topological ordering of the DAG by using a stack. Lastly, Figure 5(g) shows updates to the distance array by using Algorithm 1 on the DAG from
Figure 5(a).

## Input-Output: 
Your program will take two file names as its command-line input. This first file includes a DAG, and it follows the same format from parts 2 and 4. Your program reads the contents of this file and constructs the graph data structure. The first line in this file provides the number of vertices in the DAG. Each following line includes information about a weighted directed edge in the DAG. Each weighted edge is described by the name of its pair of vertices, followed by the edge weight, separated by a space. Your program must read and construct this DAG, The second file includes single source shortest path queries on the constructed DAG. Each line
contains a different single-source shortest path query by specifying a source vertex. Your program must read the source vertex, perform the single source shortest path algorithm using the provided source vertex, and print out each of vertex in the DAG in lexicographic ordering, followed by the length of the shortest path to that vertex, and a newline character. Note that an additional newline
character follows the last vertex in DAG. Further, your program must detect if the input graph is not a DAG. In such cases, your program simply prints out CYCLE, followed by a newline character.
![Screenshot 2023-11-25 170605](https://github.com/ktalla/PA2/assets/70788915/a6900e8b-e4af-412f-a8c7-5d4a713506e0)
![Screenshot 2023-11-25 170631](https://github.com/ktalla/PA2/assets/70788915/83bb86de-251f-463b-9b57-957fcddec9ee)

Let’s assume we have the following graph input file:<br>
graph.txt<br>
7<br>
A<br>
B<br>
C<br>
D<br>
E<br>
F<br>
G<br>
A D 10<br>
A C 5<br>
B D 7<br>
C D 3<br>
D E 5<br>
E F 1<br>
C F 10<br>
E G 10<br>
F G 5<br>
query.txt<br>
A<br>
G<br>
Then the result will be:<br>
$./fifth graph.txt query.txt<br>
A 0<br>
B INF<br>
C 5<br>
D 8<br>
E 13<br>
F 14<br>
G 19<br>
A INF<br>
B INF<br>
C INF<br>
D INF<br>
E INF<br>
F INF<br>
G 0<br>
For the scenario when the input graph is not a DAG:<br>
not_dag.txt<br>
2<br>
CA<br>
NJ<br>
NJ CA 3000<br>
CA NJ 3100<br>
query.txt<br>
CA<br>
Then the result will be:<br>
$./fifth not_dag.txt query.txt<br>
CYCLE<br>
