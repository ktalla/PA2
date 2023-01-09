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

void addEdge(char* vertex1, char* vertex2, long num_of_vertices);
long findVertex(char* vertex, long num_of_vertices);
void print_adjlist();
long vertexfound;
void get_adjacent_edges(char* vertex, long num_of_vertices);
void get_degree(char* vertex, long num_of_vertices);


int main(int argc, char* argv[argc+1]) //check this
{


FILE *graph_file = fopen(argv[1], "r"); //open the file to read
FILE *query_file = fopen(argv[2], "r");

long num_of_vertices;
fscanf(graph_file, "%ld\n", &num_of_vertices);

//make graph

adjlist= malloc(num_of_vertices*sizeof(struct Node*));



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
while(fscanf(graph_file, "%s %s\n", v1, v2)!=EOF) //add edge both ways
{
    addEdge(v1, v2, num_of_vertices);
    addEdge(v2, v1, num_of_vertices);
}

//print_adjlist(num_of_vertices);
free(v1);
free(v2);
char operation[2];
char vertex[81];
while(fscanf(query_file, "%s %s\n", operation, vertex)!=EOF)
{
if (strcmp(operation, "a") ==0)
{
    get_adjacent_edges(vertex, num_of_vertices);
}
else if (strcmp(operation, "d") ==0)
{
    get_degree(vertex, num_of_vertices);
}
else
{
    printf("error");
}
}


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

  void get_adjacent_edges(char* vertex, long num_of_vertices)
 {

     long i = findVertex(vertex, num_of_vertices);
        struct Node* temp = (adjlist[i]->next);
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

void get_degree(char* vertex, long num_of_vertices )
 {
    long degree=0;
    long i = findVertex(vertex, num_of_vertices);
    struct Node* temp = (adjlist[i]->next);
    //printf("\n");
    while(temp!=NULL)
    { 
        
        degree++;
        //printf("hello\n");
        temp=temp->next; 
    }

    printf("%ld\n", degree);

 }








