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

struct Node** adjlist;


void addEdge(char* vertex1, char* vertex2, long weight, long num_of_vertices);
long findVertex(char* vertex, long num_of_vertices);
void print_adjlist(long num_of_vertices);
void add_to_arr(char* vertex, long num_of_vertices);
long vertexfound;
//long index;
void dfs(char* vertex, long num_of_vertices, char* visitedNodes[]);
long indexVisitedNodes;
char** ordered;
void make_visited(char* vertex, char* visitedNodes[]);
bool isVisitedNode(char* vertex, long num_of_vertices, char* visitedNodes[]);
long topo_index;
bool is_in_array(char* vertex);
long* distance;
char* source;
void find_shortest_path(long num_of_vertices);
long get_weight(char* vertex, long num_of_vertices, long element);


int main(int argc, char* argv[argc+1]) //check this
{


FILE *graph_file = fopen(argv[1], "r"); //open the file to read
FILE *query_file = fopen(argv[2], "r");

long num_of_vertices;
fscanf(graph_file, "%ld\n", &num_of_vertices);

//make graph

adjlist= malloc(num_of_vertices*sizeof(struct Node*));
source = malloc(81*sizeof(char));


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

// for(long i=0; i<num_of_vertices; i++) //i<graph->adjlist;
//     {
//         //struct Node* temp = (adjlist[i]);
//         printf("%s\n", adjlist[i]->vertex);
//     }
 //correctly makes adjlist array

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
ordered=malloc(num_of_vertices* sizeof(char*));
indexVisitedNodes=0;
topo_index=0;

dfs(adjlist[0]->vertex, num_of_vertices, visitedNodes);

for(long i=num_of_vertices-1; i>=0; i--)
{
    
    if(!is_in_array(adjlist[i]->vertex))
    {
        //printf("adding vertex %s\n", adjlist[i]->vertex);
        add_to_arr(adjlist[i]->vertex, num_of_vertices);
    }
}

distance = malloc(num_of_vertices*sizeof(long));




while(fscanf(query_file, "%s\n", source)!=EOF)
{
    printf("\n");
    //printf("hello\n");
    find_shortest_path(num_of_vertices);
    
    
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


free(source);
fclose(graph_file);
fclose(query_file);
return EXIT_SUCCESS;

}


void addEdge(char* vertex1, char* vertex2, long weightOfPath, long num_of_vertices)
{
   
   struct NodeEdge* new = malloc(sizeof(struct NodeEdge)); //make a new node
   strcpy(new->vertex, vertex2); //set that node vertex
    
   new->weight = weightOfPath;
 
   long i = findVertex(vertex1, num_of_vertices);
   //printf("vertex1: %s vertex2: %s weight: %ld\n", vertex1, vertex2, weightOfPath);
//    if( i== -1)
//    {
//      printf("error");
//      exit(EXIT_SUCCESS);
//    }

   //find where to add edge in adjlist
   // printf("balls\n");
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
void dfs(char* vertex, long num_of_vertices, char* visitedNodes[])
{   long index = findVertex(vertex, num_of_vertices);
    struct Node* parent = adjlist[index];
    //printf("%s ", parent->vertex);
    make_visited(parent->vertex, visitedNodes);
    //printf("added parent: %s\n", parent->vertex);
    struct NodeEdge* child = adjlist[index]->next;
    //printf("hello4\n");
    while(child!=NULL)
    {
        if(!isVisitedNode(child->vertex, num_of_vertices, visitedNodes))
        {
        
        dfs(child->vertex, num_of_vertices, visitedNodes);
                
        }
        else if(!is_in_array(child->vertex))
        {
            printf("CYCLE\n");
            exit(EXIT_SUCCESS);
        }

        child=child->next;
    }
   
    add_to_arr(parent->vertex, num_of_vertices); //add node to array
       
}


bool is_in_array(char* vertex)
{
    long index=0;
    char* temp; 
        
        while(index<topo_index)
        { 
            temp =ordered[index];
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
    visitedNodes[indexVisitedNodes]= vertex;
    indexVisitedNodes++;

    }

// void topological_sort()
// {
//     dfs(adjlist[0]->vertex, num_of_vertices, visitedNodes); //run dfs (as it goes inside deeper and deeper)

// }
void add_to_arr(char* vertex, long num_of_vertices)
{
    
    if(topo_index<num_of_vertices)
    { 
        
        ordered[topo_index]=vertex;
        
        topo_index++;
        
    }
}
void find_shortest_path(long num_of_vertices)
{
    for(long i=0; i<num_of_vertices; i++)
    {
        distance[i] = 2147483647;
    }
    
    long source_index = findVertex(source, num_of_vertices);
    
    distance[source_index]=0;
     
    
    for(long i=topo_index-1; i>=0; i--)
    {
        long ele_in_ordered = findVertex(ordered[i], num_of_vertices);
        struct NodeEdge* temp = adjlist[ele_in_ordered]->next;
        while(temp!=NULL)
        {
            long j=findVertex(temp->vertex, num_of_vertices);
            if (distance[j] > distance[ele_in_ordered] + temp->weight)
            {
               //printf("%s distance greater than distance of %s: %ld+%ld\n", temp->vertex, adjlist[ele_in_ordered]->vertex, distance[ele_in_ordered], temp->weight);
                distance[j] = distance[ele_in_ordered]+ temp->weight;
                
            }
            //else
            //printf("%s distance %ld less than distance of %s: %ld+%ld\n", temp->vertex, distance[j], adjlist[ele_in_ordered]->vertex, distance[ele_in_ordered], temp->weight);
            temp=temp->next;
            
           
        }

    }
    for(long i=0; i<num_of_vertices; i++)
    {
        if(distance[i]==2147483647)
        {
            printf("%s INF\n", adjlist[i]->vertex);
        }
        else
         printf("%s %ld\n", adjlist[i]->vertex, distance[i]);
    }
}

long get_weight(char* vertex, long num_of_vertices, long element)
{
    long i = element;

    struct NodeEdge* temp = adjlist[i]->next;
    while(temp!=NULL)
    {
      if(strcmp(temp->vertex, vertex)==0)
      {
        return temp->weight;
      }
      else
      temp=temp->next;
    }
}