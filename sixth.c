#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Node
{
    char vertex[81];
    struct NodeEdge* next;
};
struct NodeEdge
{
    char vertex[81];
    long weight;
    struct NodeEdge* next;
};

struct PriorityEdge
{
    char vertex[81];
    long distance;
};

struct Node** adjlist;
void addEdge(char* vertex1, char* vertex2, long weight, long num_of_vertices);
long findVertex(char* vertex, long num_of_vertices);
void print_adjlist(long num_of_vertices);
long vertexfound;
//void dfs(char* vertex, long num_of_vertices, char* visitedNodes[]);
long indexVisitedNodes;
void make_visited(char* vertex, char* visitedNodes[]);
bool isVisitedNode(char* vertex, long num_of_vertices, char* visitedNodes[]);
 long* distance;
void dijkstra_alg(long num_of_vertices, char* source, char* visitedNodes[]);
struct PriorityEdge* find_node_with_least_distance(struct PriorityEdge** vertex_priority_queue, long num_of_vertices, char* visitedNodes[]);
void empty_visited() ;
int main(int argc, char* argv[argc+1]) //check this
{
FILE *graph_file = fopen(argv[1], "r"); //open the file to read
FILE *query_file = fopen(argv[2], "r");

long num_of_vertices;
fscanf(graph_file, "%ld\n", &num_of_vertices);

//make graph

adjlist= malloc(num_of_vertices*sizeof(struct Node*));
distance = malloc(num_of_vertices*sizeof(long));

for(long i=0; i<num_of_vertices; i++) //fill array called adjlist
{ 

    adjlist[i] = NULL;
}

for(long i=0; i<num_of_vertices; i++) //fill array called adjlist
{ 
    char* vertex_name = malloc(81*sizeof(char));
    fscanf(graph_file, "%s\n", vertex_name);
    struct Node* vertexName = malloc(sizeof(struct Node));
    adjlist[i]=vertexName;
    strcpy(vertexName->vertex, vertex_name);
    vertexName->next = NULL;
    free(vertex_name);
}



char* temp= malloc(81*sizeof(char)); //sort adjlist alphabetically
for (long i = 0; i < num_of_vertices - 1; i++) 
{ 
    for (long j = i + 1; j < num_of_vertices; j++) 
    {
      if (strcmp(adjlist[i]->vertex, adjlist[j]->vertex)>0) 
      {
        strcpy(temp, adjlist[i]->vertex);
        strcpy(adjlist[i]->vertex, adjlist[j]->vertex);
        strcpy(adjlist[j]->vertex, temp);
      }
    }
  }
 free(temp);


 char* v1=malloc(81*sizeof(char));
 char* v2 =malloc(81*sizeof(char));
 long weight;
 
while(fscanf(graph_file, "%s %s %ld\n", v1, v2, &weight)!=EOF) 
{
     
    addEdge(v1, v2, weight, num_of_vertices); //v1 to v2
    
}

//print_adjlist(num_of_vertices);
free(v1);
free(v2);

char** visitedNodes= malloc(num_of_vertices* sizeof(char*));
indexVisitedNodes=0;
//dfs(adjlist[0]->vertex, num_of_vertices, visitedNodes);

// for(long i=0; i<num_of_vertices; i++)
// {
//     if(!isVisitedNode(adjlist[i]->vertex, num_of_vertices, visitedNodes))
//     {
//         dfs(adjlist[i]->vertex, num_of_vertices, visitedNodes);
//     }
// }

char source[81];
while(fscanf(query_file, "%s\n", source)!=EOF)
{
    dijkstra_alg(num_of_vertices, source, visitedNodes);
    empty_visited();
    printf("\n");
}



for(long i=0; i<num_of_vertices; i++) 
    {
        struct NodeEdge* temp = (adjlist[i]->next);

        while(temp!=NULL)
        { 
            struct NodeEdge* accessor = temp->next;
            free(temp);
            temp=accessor; 
        }
        free(adjlist[i]);
    }

   free(adjlist);


    free(visitedNodes);

fclose(graph_file);
return EXIT_SUCCESS;


}

void empty_visited() 
{
    indexVisitedNodes=0;
}

void addEdge(char* vertex1, char* vertex2, long weightOfPath, long num_of_vertices)
{
   
   struct NodeEdge* new = malloc(sizeof(struct NodeEdge)); //make a new node
   strcpy(new->vertex, vertex2); //set that node vertex
    
   new->weight = weightOfPath;
 
   long i = findVertex(vertex1, num_of_vertices);
  
  struct NodeEdge* temp = (adjlist[i]->next);
  //printf("hello\n");
  if(temp==NULL)
  {
        adjlist[i]->next = new; 
        new->next = NULL;//after
        //printf("%s\n", temp->vertex);
        return;
  }
  else
  {
   while(temp!=NULL)
   {
    //printf("hello\n");
     if(temp->next==NULL)
     {
        if(strcmp(temp->vertex, new->vertex)<0) //if temp is less than new
        {
       // printf("adding vertex %s after %s\n", vertex2, temp->vertex);
        temp->next = new; 
        new->next = NULL;//after
        //printf("%s\n", temp->vertex);
        return;
        }
        else
        {
            new->next = temp;
            adjlist[i]->next = new;
            return;
        }
    }
     else if (strcmp(adjlist[i]->next->vertex, new->vertex)>0)
     {
        new->next = adjlist[i]->next;
        adjlist[i]->next = new;
        return;        
     }
    else if(strcmp(temp->next->vertex, new->vertex)>0) //in between
    {
        //printf("%s %s\n", vertex2, temp->vertex);
        new->next = temp->next;
        temp->next = new;
        //printf("%s\n", temp->vertex);
        return;
    }

       temp=temp->next;
   }

    //temp=temp->next;
      
   }

   

}


long findVertex(char* vertex, long num_of_vertices)
{
    vertexfound= -1;
    for(long i=0; i<num_of_vertices; i++)
    {
        
        if( strcmp(adjlist[i]->vertex, vertex)==0)
        {
            vertexfound=i;
            return vertexfound;
        }
        
    }

    return vertexfound;
}


  void get_adjacent_edges(char* vertex, long num_of_vertices)
 {

      long i = findVertex(vertex, num_of_vertices);
        struct NodeEdge* temp = (adjlist[i]->next);
        //printf("\n");
        while(temp!=NULL)
        { 
            
            printf("%s ", temp->vertex);
             //printf("hello\n");
            temp=temp->next; 
        }
        //printf("hello2\n");
    
    printf("\n");

}


 void print_adjlist(long num_of_vertices)
{
    for(long i=0; i<num_of_vertices; i++) //i<graph->adjlist;
    {
        struct NodeEdge* temp = (adjlist[i]->next);
        printf("\n");
        printf("%s ", adjlist[i]->vertex);
        while(temp!=NULL)
        { 
            
             printf("%s ", temp->vertex);
             //printf("hello\n");
            temp=temp->next; 
        }
        //printf("hello2\n");
    }
    printf("\n");

}
// void dfs(char* vertex, long num_of_vertices, char* visitedNodes[])
// {   long index = findVertex(vertex, num_of_vertices);
//     struct Node* parent = adjlist[index];
//     printf("%s ", parent->vertex);
//     make_visited(parent->vertex, visitedNodes);
//     //printf("added parent: %s\n", parent->vertex);
//     struct NodeEdge* child = adjlist[index]->next;
//     //printf("hello4\n");
//     while(child!=NULL)
//     {
//         if(!isVisitedNode(child->vertex, num_of_vertices, visitedNodes))
//         {
//         //printf("dfs on: %s\n", child->vertex);
//         dfs(child->vertex, num_of_vertices, visitedNodes);
//         }
//         child=child->next;
//     }


// }

void dijkstra_alg(long num_of_vertices, char* source, char* visitedNodes[])
{
    struct PriorityEdge** vertex_priority_queue = malloc(num_of_vertices*sizeof(struct PriorityEdge*));
   
    for(long i=0; i<num_of_vertices; i++)
    { struct PriorityEdge* new_node = malloc(sizeof(struct PriorityEdge));
      vertex_priority_queue[i]=new_node;
      strcpy(new_node->vertex,adjlist[i]->vertex);
      new_node->distance=2147483647;      
    }
    
    long i = findVertex(source, num_of_vertices);
    vertex_priority_queue[i]->distance=0;

    //long i = findVertex(current_vertex, num_of_vertices);
   

 while(indexVisitedNodes<num_of_vertices)
 {
   struct NodeEdge* adj_edge= adjlist[i]->next;
    while(adj_edge!=NULL)
    {
        if(!isVisitedNode(adj_edge->vertex, num_of_vertices, visitedNodes) && vertex_priority_queue[findVertex(adj_edge->vertex, num_of_vertices)]->distance>adj_edge->weight+vertex_priority_queue[i]->distance)
       { 
        //printf("updating distance of %s\n", vertex_priority_queue[findVertex(adj_edge->vertex, num_of_vertices)]->vertex);
        vertex_priority_queue[findVertex(adj_edge->vertex, num_of_vertices)]->distance=adj_edge->weight+vertex_priority_queue[i]->distance;
        
        }

        adj_edge=adj_edge->next;
    }
    //printf("making %s visted\n", adjlist[i]->vertex);
    make_visited(adjlist[i]->vertex, visitedNodes);


    struct PriorityEdge* LDN= find_node_with_least_distance(vertex_priority_queue, num_of_vertices, visitedNodes);
    if(LDN==NULL)
    {
        break;
    }
    i = findVertex(LDN->vertex, num_of_vertices);

 }


    for(long i=0; i<num_of_vertices; i++)
    {
        if(vertex_priority_queue[i]->distance==2147483647)
        {
            printf("%s INF\n", vertex_priority_queue[i]->vertex);
        }
        else
        printf("%s %ld\n", vertex_priority_queue[i]->vertex, vertex_priority_queue[i]->distance);
    }

    for(long i=0; i<num_of_vertices; i++) 
    {
           struct PriorityEdge* temp = vertex_priority_queue[i];
            free(temp);
    
    }

   free(vertex_priority_queue);
    

}


struct PriorityEdge* find_node_with_least_distance(struct PriorityEdge** vertex_priority_queue, long num_of_vertices, char* visitedNodes[])
{
    
    struct PriorityEdge* LDN;
    long HighDistance = 2147483648;
    // if(LDN->distance==0)
    // {
    //  LDN=vertex_priority_queue[1];
    // }

    for(long i=0; i<num_of_vertices; i++)
    {
    if(!isVisitedNode(vertex_priority_queue[i]->vertex, num_of_vertices, visitedNodes))
    {
      if(HighDistance>vertex_priority_queue[i]->distance)
      {
        LDN = vertex_priority_queue[i];
        HighDistance=LDN->distance;
      }
    }

    }
return LDN;

}


     
bool isVisitedNode(char* vertex, long num_of_vertices, char* visitedNodes[])
{
    long index=0;
    char* temp; 
        
        while(index<indexVisitedNodes)
        { 
            temp =visitedNodes[index];
            //printf("checking if temp is equal to vertex: %s\n", temp->vertex);
            if(strcmp(temp, vertex)==0)
             {
                return true;
             }
             else
             {
             index++; 
             }
        }
        return false;
}


void make_visited(char* vertex, char* visitedNodes[])
{
    //printf("hello1\n");
    visitedNodes[indexVisitedNodes]= vertex;
    //printf("hello2\n");
    indexVisitedNodes++;
    //printf("hello3\n");

}






