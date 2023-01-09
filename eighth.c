#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


//char* binary_whole;
char* convert_binary_decimal(double decimal, long bits, char binary_decimal[]);
char* convert_binary_whole(long bits, long whole_number, char binary_whole[], long bits_for_whole);
long get_binary_whole_length(long whole_number);
void get_full_binary_decimal(double decimal, char full_binary_decimal[]);
int main(int argc, char* argv[argc+1])
{

FILE *graph_file = fopen(argv[1], "r"); //open the file to read
double number; //4.5
long bits;
long exponent;
 

while(fscanf(graph_file, "%le %ld\n", &number, &bits)!=EOF)
{
  long whole_number= floor(number); //4
  double decimal = number-whole_number; //.5
  char binary_decimal[bits+10]; //array with size of bits
  memset(binary_decimal, 0, bits+10);
  
  char full_binary_decimal[256]; //array with size of bits
  memset(full_binary_decimal, 0, 256);
  
  get_full_binary_decimal(decimal, full_binary_decimal);

  long bits_for_whole = get_binary_whole_length(whole_number);
  char binary_whole[bits_for_whole+3+bits+5];
memset(binary_whole, 0, bits_for_whole+3+bits+5);
// char totalBinaryArray[bits_for_whole+1+bits+10];
// strcat(totalBinaryArray, convert_binary_whole(whole_number, bits, whole_number, binary_whole, bits_for_whole));
// printf("%s\n", totalBinaryArray);

 char* binary_number = strcat(convert_binary_whole(bits, whole_number, binary_whole, bits_for_whole), ".");
 char* binary_number_final = strcat(binary_number, convert_binary_decimal(decimal, bits, binary_decimal));

//printf("%s\n", binary_number_final);

if(whole_number==0)
{
   
   if(decimal==0)
   {
    exponent=0;
   }
   else
   {

char temp = full_binary_decimal[0]; 
    exponent=0;
    if(temp!='1')
    {
    while(temp!='1')
    { 
        exponent++;
        //printf("%ld\n", exponent);
        temp=full_binary_decimal[exponent];
        
    }
    exponent=exponent+1;
    }
    else 
      exponent=1;
   
   //printf("expontent: %ld\n", exponent);
   }

   //printf("bin num fin: %s\n", binary_number_final);
    for(long i=0; i<bits; i++)
    { 
        binary_number_final[2+i]=full_binary_decimal[exponent+i];
        // if(binary_number_final[i+1]!='\0' && exponent!=1)
        //     binary_number_final[i]=full_binary_decimal[i+1];
        // else if(binary_number_final[i+1]=='\0' && binary_number_final[i]!='1')
        //     binary_number_final[i]='0';
        // else if (binary_number_final[i+1]=='\0' && binary_number_final[i]=='1' && i==exponent)
        //     binary_number_final[i]='0';
    }

//printf("binary nu, final: %s\n", binary_number_final);
// if(loop_start==3)
// {
// binary_number_final[2]=binary_number_final[1];
// }
if(decimal==0)
{
binary_number_final[1]='.';
binary_number_final[0]='0';
binary_number_final[2+bits]='\0';
printf("%s %ld\n", binary_number_final, exponent);
}
else
{
binary_number_final[1]='.';
binary_number_final[0]='1';
binary_number_final[2+bits]='\0';
printf("%s -%ld\n", binary_number_final, exponent);
}

}

else
{
    
char temp = binary_number_final[1];
 exponent=0;

while(temp!='.')
{
    exponent++;
    temp=binary_number_final[1+exponent];
    
}
//printf("expontent: %ld\n", exponent);
for(int i=exponent; i>=1; i--)
{
    binary_number_final[i+1]=binary_number_final[i];
}
   }

binary_number_final[1]='.';
binary_number_final[2+bits]='\0';
printf("%s %ld\n", binary_number_final, exponent);
}


fclose(graph_file);
return EXIT_SUCCESS;
}

void get_full_binary_decimal(double decimal, char full_binary_decimal[])
{

    int index=0;
    for(int long i =1; i<=255; i++)
    {
            if(decimal>=(pow(2, -1*i)))
            {
                decimal = decimal-(pow(2,-1*i));
                full_binary_decimal[index] = '1';
                //printf("1 ");
                index++;
            }
            else
            {
                full_binary_decimal[index] = '0';
                //printf("0\n");
                index++;
            }
      
   }
    
}

char* convert_binary_whole(long bits, long whole_number, char binary_whole[], long bits_for_whole)
{
    
   // printf("bits for whole: %ld\n", bits_for_whole);
    int index=0;
    for(int i=bits_for_whole-1; i>=0; i--)
    {
    
        
        // while(number!=0) //infinite loop check this
        // {
         if(whole_number>=0) 
         {  
            if(whole_number>=(pow(2, i)))
            {
                whole_number = whole_number-(pow(2,i));
                binary_whole[index] = '1';
                //printf("1 ");
                index++;
            }
            else
            {
                binary_whole[index] = '0';
                //printf("0\n");
                index++;
            }
         }
    }
//printf("%s\n", binary_whole);
   return binary_whole;


}

char* convert_binary_decimal(double decimal, long bits, char binary_decimal[])
{
   // printf("%le\n", decimal);
   
    int index=0;
    for(int long i =1; i<=bits; i++)
    {
            if(decimal>=(pow(2, -1*i)))
            {
                decimal = decimal-(pow(2,-1*i));
                binary_decimal[index] = '1';
                //printf("1 ");
                index++;
            }
            else
            {
                binary_decimal[index] = '0';
                //printf("0\n");
                index++;
            }
      
   }
  

   return binary_decimal;


}

long get_binary_whole_length(long whole_number)
{
    //printf("whole num: %ld\n", whole_number);
    int count=0;
    long number=0;
    while(number<whole_number)
    {
        number+=pow(2, count);
        count++;
    }
    return count;


}



