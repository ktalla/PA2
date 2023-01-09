#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

void convert_binary(double number, long bits, char binary_number[]);
void convert_twos_complement(double number, long bits, char binary_number[], char ones_complement[]);

int main(int argc, char* argv[argc+1]) //check this
{


FILE *graph_file = fopen(argv[1], "r"); //open the file to read
double number;
long bits; 
double min_representation;
double max_representation;

while (fscanf(graph_file, "%le %ld\n", &number, &bits)!=EOF)
{
    
   char binary_number[bits];
   char ones_complement[bits];
    min_representation= -1*(pow(2, bits-1));
    //printf("%ld\n", min_representation);
    max_representation= (pow(2, bits-1)) -1;
    if(number>=0.0) //if the number is 0 or positive
    {
        //printf("hellopos");
        if(number>max_representation)
        {
           convert_twos_complement(max_representation, bits, binary_number, ones_complement);
        }
        else
        {
            convert_twos_complement(number, bits, binary_number, ones_complement);
        }
    }
    else if (number<0.0) //if the number is negative
    {
         //printf("helloneg");
        if(number<min_representation)
        {   //printf("hello");
            convert_twos_complement(min_representation, bits, binary_number, ones_complement);
        }
        else
        {    //printf("hello2");
            //printf("%le\n", number);
            convert_twos_complement(number, bits, binary_number, ones_complement);
        }

    }

    for(long i=0; i<bits; i++)
   {
       
    printf("%c", binary_number[i]);
    
   }
   printf("\n");
}

fclose(graph_file);
return EXIT_SUCCESS;
}

void convert_binary(double number, long bits, char binary_number[])
{
  for(long i=0; i<bits; i++)
   {
       
    binary_number[i]='0';
   }
 

   int index=0;
    for(int i=bits-1; i>=0; i--)
    {
        
        // while(number!=0) //infinite loop check this
        // {
         if(number>=0) 
         {  
            if(number>=(pow(2, i)))
            {
                number = number-(pow(2,i));
                binary_number[index] = '1';
                //printf("1 ");
                index++;
            }
            else
            {
                binary_number[index] = '0';
                //printf("0\n");
                index++;
            }
         }
         else
         {
           // printf("hello\n");
            
           number=abs(number);
           //printf("%le\n", number);
        
           if(number>=(pow(2, i)))
            {
                number = number-(pow(2,i));
                binary_number[index] = '1';
                //printf("1 ");
                index++;
            }
            else
            {
                binary_number[index] = '0';
                //printf("0\n");
                index++;
            }


         }
        //}

    }

 


}
void convert_twos_complement(double number, long bits, char binary_number[], char ones_complement[])
{
    if(number>=0)
    {
    convert_binary(number, bits, binary_number);
   //char* binary_number= convert_binary(long number, long bits);
    }
    else
    {
        convert_binary(number, bits, binary_number);
    //     printf("binary rep: ");
    //    for(int i=0; i<bits; i++)
    //    printf("%c", binary_number[i]);
    //    printf("\n");
   //char twos_complement[bits];
    for(long i=0; i<bits; i++)
    {
        if (binary_number[i] == '0')
        {
            binary_number[i]= '1';
        }
        else if(binary_number[i]=='1')
        {
            binary_number[i]='0';
        }
    }
    // printf("binary rep: ");
    //    for(int i=0; i<bits; i++)
    //    printf("%c", binary_number[i]);
    //    printf("\n");

    for(long i=bits-1; i>=0; i--)
    {

        if(binary_number[i]=='1')
        {
            binary_number[i]='0';
        }
        else{
            binary_number[i]='1';
            return;
        }
        // long num_of_1s;
        // if(strcmp(ones_complement[i]==1))
        // {
        //     num_of_1s++;
        // }
    }
    }
    //make 0 into 1
    //add 1


}


