#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Node
{
    char vertex[81];
    struct Node* next;
};

struct Node** adjlist;
struct Node* top; //keeps track of queue
//struct Node* isVistedListTop; //keeps track of other queue that checks if visited

void addEdge(char* vertex1, char* vertex2, long num_of_vertices);
long findVertex(char* vertex, long num_of_vertices);
void print_adjlist();
long vertexfound;
void bfs(char* edge, long num_of_vertices);
void enqueue(char* vertex);
 struct Node* pop();
 void push(char* vertex);
void make_visited(char* vertex);
 bool isVisited(char* vertex, long num_of_vertices);
 void empty_visited();

bool inQueue(char* vertex);

struct Node* vistedVertices;
struct Node* queueOfEdges;
// void get_adjacent_edges(char* vertex, long num_of_vertices);
// void get_degree(char* vertex, long num_of_vertices);

int main(int argc, char* argv[argc+1]) //check this
{


FILE *graph_file = fopen(argv[1], "r"); //open the file to read
FILE *query_file = fopen(argv[2], "r");

long num_of_vertices;
fscanf(graph_file, "%ld\n", &num_of_vertices);

//make graph

adjlist= malloc(num_of_vertices*sizeof(struct Node*));


// graph = malloc(sizeof(struct graph));
// graph->num_of_vertices=num_of_vertices; //graph made
// graph->adjlist = malloc(num_of_vertices*sizeof(struct Node)); //adj list (which is a pointer) stores an array of pointers

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

 char* v1=malloc(81*sizeof(char));
 char* v2 =malloc(81*sizeof(char));
while(fscanf(graph_file, "%s %s\n", v1, v2)!=EOF) //add edge both ways
{
    addEdge(v1, v2, num_of_vertices);
    addEdge(v2, v1, num_of_vertices);
}

// print_adjlist(num_of_vertices);
// printf("\n");
free(v1);
free(v2);
char* edge_for_bfs =malloc(81*sizeof(char));
while(fscanf(query_file, "%s\n", edge_for_bfs)!=EOF)
{   
    bfs(edge_for_bfs, num_of_vertices);
    printf("\n");
    empty_visited();
}
free(edge_for_bfs);



for(long i=0; i<num_of_vertices; i++) 
    {
        struct Node* temp = (adjlist[i]);

        while(temp!=NULL)
        { 
            struct Node* accessor = temp->next;
            free(temp);
            temp=accessor; 
        }
    }
    free(adjlist);

struct Node* cleanEdges = queueOfEdges;
{
    while(cleanEdges!=NULL)
    {
        struct Node* accessor = cleanEdges->next;
            free(cleanEdges);
            cleanEdges=accessor;
    }
}

fclose(graph_file);
fclose(query_file);
return EXIT_SUCCESS;
    

}


void addEdge(char* vertex1, char* vertex2, long num_of_vertices)
{
   struct Node* new = malloc(sizeof(struct Node)); //make a new node
   strcpy(new->vertex, vertex2); //set that node vertex
   long i = findVertex(vertex1, num_of_vertices);
   //printf("vertex1: %s vertex2: %s\n", vertex1, vertex2);
//    if( i== -1)
//    {
//      printf("error");
//      exit(EXIT_SUCCESS);
//    }

   //find where to add edge in adjlist
    struct Node* temp = (adjlist[i]);

   while(temp!=NULL)
   {
    //printf("hello\n");
     if(temp->next==NULL)
     {
        //printf("adding vertex %s after %s\n", vertex2, temp->vertex);
        temp->next = new; 
        new->next = NULL;//after
        //printf("%s\n", temp->vertex);
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

void print_adjlist(long num_of_vertices)
{
    for(long i=0; i<num_of_vertices; i++) //i<graph->adjlist;
    {
        struct Node* temp = (adjlist[i]);
        printf("\n");
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
void bfs(char* edge, long num_of_vertices)
{
    // // make_queue(char* edge);  
    // // make_visited(char*edge); //make the edge w dfs as visited AND POP IT FROM QUUEUE and shift top
    // // while(top!=NULL) //while queue is not empty
    // // {
    //     long i = findVertex(edge, num_of_vertices);
    //     struct Node* temp = (adjlist[i]); //make temp point to adjlist of edge
    //     if(!isVisited(temp->vertex, num_of_vertices))
    //     {
    //     make_visited(temp);
    //     printf("temp vertex that was just made visited: %s\n", temp->vertex);
    //     }
        
    //     while(temp->next!=NULL) //while there is an edge and it is not visited
    //     {  
    //         if(!isVisited(temp->vertex, num_of_vertices))
    //         {
    //         //printf("temp vertex: %s\n", temp->vertex);
    //         }
    //         temp=temp->next;
    //     }
    //     temp=adjlist[i];
    //     while(temp->next!=NULL)
    //     {
    //     if(!isVisited(temp->next->vertex, num_of_vertices))
        
    //     {   make_visited(temp->next);
    //         printf("temp vertex that was just made visited2: %s \n", temp->next->vertex);
    //         bfs(temp->next->vertex, num_of_vertices);
    //     }
    //     }
   if(!isVisited(edge, num_of_vertices)) 
     {
        printf("%s ", edge);
        make_visited(edge);
     
    long i = findVertex(edge, num_of_vertices);
    struct Node* adjacent_edges = (adjlist[i]->next);
    
    while((adjacent_edges!=NULL))
    { if(!isVisited(adjacent_edges->vertex, num_of_vertices))
    {
        //printf("enqueueing: %s \n", adjacent_edges->vertex );
        enqueue(adjacent_edges->vertex);
        adjacent_edges=adjacent_edges->next;
    }
    else
    {
        adjacent_edges=adjacent_edges->next;
    }
    }
     }
    while(queueOfEdges!=NULL)
    {
        struct Node* next_bfs = pop();
        bfs(next_bfs->vertex, num_of_vertices);
        free(next_bfs);
    }
  

    }
    


// void make_queue(char* edge) //dfs on b
// {
//     long i = findVertex[edge];
//     struct Node* temp = adjlist[i]->next;
//     while(temp!=NULL)
//     {
//         enqueue(temp->vertex);
//     }
// }

bool inQueue(char* vertex)
{
    struct Node* temp = queueOfEdges;
        
        while(temp!=NULL)
        { 
            //printf("checking if temp is equal to vertex: %s\n", temp->vertex);
            if(strcmp(temp->vertex, vertex)==0)
             {
                return true;
             }
             else
             {
             temp=temp->next; 
             }
        }
        return false;
}

    

void make_visited(char* vertex)
{
    if(vistedVertices!=NULL){
    struct Node* temp = vistedVertices; //points to the head
    while(temp->next!=NULL) //(*temp).next
    {
        temp = temp->next; 
    }
    struct Node* new_node = malloc(sizeof(struct Node));
    temp->next = new_node;
    new_node->next=NULL;
    strcpy(new_node->vertex, vertex);
    }
    else
    {
    struct Node* new_node = malloc(sizeof(struct Node));
    new_node->next = NULL;
    strcpy(new_node->vertex, vertex);
    vistedVertices = new_node;   
    }
// struct Node* temp2 = vistedVertices;
// printf("visited queue\n");
//     while(temp2!=NULL)
//     {
//         printf("%s\n", temp2->vertex);
//         temp2=temp2->next;
//     }
// printf("end of queue\n");
}

bool isVisited(char* vertex, long num_of_vertices)
{
    
    struct Node* temp = vistedVertices;
        
        while(temp!=NULL)
        { 
            //printf("checking if temp is equal to vertex: %s\n", temp->vertex);
            if(strcmp(temp->vertex, vertex)==0)
             {
                return true;
             }
             else
             {
             temp=temp->next; 
             }
        }
        return false;
}

void enqueue(char* vertex) 
{
    if(queueOfEdges!=NULL){
    struct Node* temp = queueOfEdges; //points to the head
    while(temp->next!=NULL) //(*temp).next
    {
        temp = temp->next; 
    }
    struct Node* new_node = malloc(sizeof(struct Node));
    temp->next = new_node;
    strcpy(new_node->vertex, vertex);
    new_node->next=NULL;
    }
    else
    {
    struct Node* new_node = malloc(sizeof(struct Node));
    queueOfEdges = new_node;
    strcpy(new_node->vertex, vertex);
    new_node->next=NULL;
    }
}

struct Node* pop()
{
    struct Node* temp;
    if(queueOfEdges!=NULL)
    {
  temp = queueOfEdges;
  queueOfEdges = queueOfEdges->next;

    }
    
     return temp;
  
}
void empty_visited()
{
    //struct Node* temp = vistedVertices;
    
    while(vistedVertices!=NULL)
    {
        struct Node* accessor = vistedVertices->next;
        free(vistedVertices);
        vistedVertices=accessor;
        
        
        
        
    }
}












