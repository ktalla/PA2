#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>


//char* binary_whole;
char* convert_binary_decimal(double decimal, long bits, char binary_decimal[]);
char* convert_binary_whole(long whole_number, char binary_whole[], long bits_for_whole);
long get_binary_whole_length(long whole_number);
void get_canonical(char full_binary_decimal[], long whole_number, char* binary_number_final, long fraction_bits, char* cannonical_binary_decimal, long bits_for_whole);
char get_sign_field(double number);
long exponent;
void get_fraction_field(char* cannonical_binary_decimal, long fraction_bits, long exponent_bits, char IEEE_form[], long total_bits);
void get_exponent_field(long exponent_bits, char IEEE_form[], long whole_number);
double convert_binary_to_num(char fraction_field[]);
void get_full_binary_decimal(double decimal, char full_binary_decimal[]);


int main(int argc, char* argv[argc+1])
{

FILE *graph_file = fopen(argv[1], "r"); //open the file to read
double number; //4.5
long total_bits;
long exponent_bits;
long fraction_bits;
exponent=0;
    while(fscanf(graph_file, "%le %ld %ld %ld\n", &number, &total_bits, &exponent_bits, &fraction_bits)!=EOF)
    {
        char IEEE_form[total_bits+1];
        memset(IEEE_form,0,total_bits+1);
        long whole_number= floor(abs(number)); //4
        //printf("whole num: %ld\n", whole_number);
        double decimal;
        if(number<0)
        decimal = (-1*number)-whole_number; //.5
        else
        decimal = number-whole_number;

        //printf("decimal: %le\n", decimal);
        char binary_decimal[fraction_bits+2]; //array with size of bits

        memset(binary_decimal, 0, fraction_bits+2); //set all fraction bits to 0

        long bits_for_whole = get_binary_whole_length(whole_number);
        char binary_whole[bits_for_whole+3+fraction_bits+1]; //how to get bits for whole....
        memset(binary_whole, 0, bits_for_whole+3+fraction_bits+1);
        char cannonical_binary_decimal[256];
        memset(cannonical_binary_decimal, 0, 256);

        char full_binary_decimal[256];
        memset(full_binary_decimal, 0, 256);
        get_full_binary_decimal(decimal, full_binary_decimal);

        //char* binary_decimal_string = convert_binary_decimal(decimal, fraction_bits, binary_decimal);
        //printf("%s\n", binary_decimal_string);
        char* binary_number = strcat(convert_binary_whole(whole_number, binary_whole, bits_for_whole), ".");
        char* binary_number_final = strcat(binary_number, convert_binary_decimal(decimal, fraction_bits, binary_decimal));

       // printf("binary num: %s\n", binary_decimal);

        get_canonical(full_binary_decimal, whole_number, binary_number_final, fraction_bits, cannonical_binary_decimal, bits_for_whole); //must fix this method
        // printf("bin num in can: %s\n", binary_number_final);
         IEEE_form[0]=get_sign_field(number);
         //printf("%s\n", IEEE_form);
         get_exponent_field(exponent_bits, IEEE_form, whole_number);
        get_fraction_field(cannonical_binary_decimal, fraction_bits, exponent_bits, IEEE_form, total_bits); //in this method we must check if the binary_decimal size is larger than the given fractional bits, if it is, then we must round, if not fill the empty bits with zeros
       
      printf("%s\n", IEEE_form); 
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


void get_fraction_field(char cannonical_binary_decimal[], long fraction_bits, long exponent_bits, char IEEE_form[], long total_bits)
{
    //printf("hello\n");
    //printf("can bin dec: %s\n", cannonical_binary_decimal);
    
    //printf("fraction bits: %ld\n", fraction_bits);
    if(strlen(cannonical_binary_decimal)>fraction_bits) 
    {//we must round
   // printf("hello2\n");
    char* lowerbound = malloc(fraction_bits+1*sizeof(char));
    memset(lowerbound, 0, fraction_bits+1);
    for(int i=0; i<fraction_bits; i++)
    {
        lowerbound[i]=cannonical_binary_decimal[i];
        
    }
    
    
    char* upperbound = malloc(fraction_bits+1*sizeof(char));
    //memset(upperbound, 0, fraction_bits+1);
    for(long i=0; i<fraction_bits+1; i++)
    {
       upperbound[i]=lowerbound[i];
    }
    //printf("lowerbound: %s\n", lowerbound);
   // printf("upperbound: %s\n", upperbound); workes
    for(long i=fraction_bits-1; i>=0; i--)
    {
       if(lowerbound[i]=='1')
        {
            upperbound[i]='0';
        }
        else if(lowerbound[i]!='\0')
        {
            upperbound[i]='1';
            break;
        }
    }

    //  printf("lowerbound: %s\n", lowerbound);
    //   printf("upperbound: %s\n", upperbound); //doesnt work

     
     char midpoint[fraction_bits+2];
     memset(midpoint, 0, fraction_bits+2);
   
     for(int i=0; i<fraction_bits+1; i++)
     {
        midpoint[i]=lowerbound[i];
     }
     midpoint[fraction_bits]='1';

    //printf("mdpt: %s\n", midpoint);
       

    //  long midpoint_long = atol(midpoint); 
     long upperbound_long=atol(upperbound);
     //long lowerbound_long=atol(lowerbound);         

    //  long binary_decimal_long = atol(cannonical_binary_decimal);

    


    double midpoint_double = convert_binary_to_num(midpoint);
   // double upperbound_double = convert_binary_to_num(upperbound_double);
    //double lowerbound_double = convert_binary_to_num(lowerbound_double);
    double decimal_double = convert_binary_to_num(cannonical_binary_decimal);

   // printf("comparing: %le with %le\n", decimal_double, midpoint_double);


      if(decimal_double==midpoint_double) //if they same
      { 
        if(upperbound_long%10 == 0)
        {
            for(int i=0; i<fraction_bits; i++)
            { 
             
             IEEE_form[1+exponent_bits+i]=upperbound[i];
             //printf("fraction: %s\n", upperbound);
                
            }

            int count=0;
            for(int i=0; i<strlen(upperbound); i++)
            {
                
                if(upperbound[i]=='0')
                {count++;
                }
            }
            if(count==(strlen(upperbound)))
            {
                IEEE_form[exponent_bits]='1';
                //printf("IEEE: %s\n", IEEE_form);
            }
        }
        else
        {
            for(int i=0; i<fraction_bits; i++)
            {   
             IEEE_form[1+exponent_bits+i]=lowerbound[i];
              //printf("fraction: %s\n", lowerbound);  
            }
        } //ties to even
      }
      else if(decimal_double>midpoint_double) //greater
    {
          int count=0;
            for(int i=0; i<strlen(upperbound); i++)
            {
                
                if(upperbound[i]=='0')
                {count++;
                }
            }
            if(count==(strlen(upperbound)))
            {
                IEEE_form[exponent_bits]='1';
                //printf("IEEE: %s\n", IEEE_form);
            }



        for(int i=0; i<fraction_bits; i++)
            {   
             IEEE_form[1+exponent_bits+i]=upperbound[i];
             //printf("fraction: %s\n", upperbound);
                
            }
      }
      else
      {
        for(int i=0; i<fraction_bits; i++)
            {   
             IEEE_form[1+exponent_bits+i]=lowerbound[i];
            // printf("fraction: %s\n", lowerbound);
                
            }
      }

      free(lowerbound);
      free(upperbound);
    
    }
   
      else
      {  //printf("hello3\n");
            for(int i=0; i<fraction_bits; i++)
            {   
                IEEE_form[1+exponent_bits+i]=cannonical_binary_decimal[i];
                
            }
      }
    
    
}

double convert_binary_to_num(char fraction_field[])
{

double M_value=0.0;
    long power=1;
    for(int i=0; i<strlen(fraction_field); i++)
    {
        if(fraction_field[i]=='1')
        {
          M_value = M_value+pow(2, -1*power);
        }
        power++;
    }

    return M_value;



}

void get_exponent_field(long exponent_bits, char IEEE_form[], long whole_number)
{
    long exponent_field;
    long bias = pow(2, exponent_bits-1)-1;
    //printf("bias: %ld\n", bias);
    if(whole_number!=0)
    exponent_field = exponent+bias;
    else
     exponent_field=bias-exponent;
   //printf("exp fd: %ld\n", exponent_field);
    int index=1;
    for(int i=exponent_bits-1; i>=0; i--)
    {
      
        // while(number!=0) //infinite loop check this
        // {
         if(exponent_field>=0) 
         {  
            if(exponent_field>=(pow(2, i)))
            {
                exponent_field = exponent_field-(pow(2,i));
                IEEE_form[index] = '1';
                //printf("1\n");
                index++;
            }
            else
            {
                IEEE_form[index] = '0';
                //printf("0\n");
                index++;
            }
         }
    }

}
char get_sign_field(double number)
{
    if(number>0)
        return '0';
    else
       return '1';
}

void get_canonical(char full_binary_decimal[], long whole_number, char* binary_number_final, long fraction_bits, char* cannonical_binary_decimal, long bits_for_whole)
{

//printf("full bd: %s\n", full_binary_decimal);
  if(whole_number==0)
{
    //printf("bin num fin: %s\n", binary_number_final);
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
   
   // printf("expontent: -%ld\n", exponent);


   //printf("bin num fin: %s\n", binary_number_final);
    for(long i=0; i<fraction_bits; i++)
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
binary_number_final[1]='.';
binary_number_final[0]='1';
//binary_number_final[2+fraction_bits]='\0';
//printf("%s -%ld\n", binary_number_final, exponent);

}

else
{
    char temp = binary_number_final[1];
    exponent=0;
while(temp!='.')
{
    //printf("%c\n", temp);
    exponent++;
    temp=binary_number_final[1+exponent];
    
}
//printf("expontent: %ld\n", exponent);
for(int i=exponent; i>=1; i--)
{
    binary_number_final[i+1]=binary_number_final[i];
}

binary_number_final[1]='.';
//binary_number_final[2+fraction_bits]='\0';
//printf("%s %ld\n", binary_number_final, exponent);
}

 //printf("bin num fin: %s\n", binary_number_final);
for(int i=0; i<strlen(binary_number_final)-2; i++)
{
   
    cannonical_binary_decimal[i]=binary_number_final[2+i];
}


}
 
    
char* convert_binary_whole(long whole_number, char binary_whole[], long bits_for_whole)
{
    if(whole_number==0)
    {
        binary_whole[0]=0;
    }
    
   //printf("whole: %ld\n", whole_number);
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
    // if(whole_number==0)
    //     return
    int count=0;
    long number=0;
    while(number<whole_number)
    {
        number+=pow(2, count);
        count++;
    }
    return count;


}



