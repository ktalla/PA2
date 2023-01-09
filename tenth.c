#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
void convert_binary_whole(unsigned int whole_number, char binary_whole[], long total_bits);
double get_fraction(char fraction_field[], long fraction_bits);
long get_exponent(char exponent_field[], long exponent_bits, long* E_value);
long get_sign(char sign_field);
long get_binary_whole_length(unsigned int whole_number);



int main(int argc, char* argv[argc+1])
{
long total_bits;
long exponent_bits;
long fraction_bits;
unsigned int hex;
int precision;
FILE *graph_file = fopen(argv[1], "r"); //open the file to read
while(fscanf(graph_file, "%ld %ld %ld %x %d\n", &total_bits, &exponent_bits, &fraction_bits, &hex, &precision)!=EOF)
    {
        //printf("test1:\n");
       long bits_for_whole = get_binary_whole_length(hex);
       //printf("")
      char* binary_whole;
       long offset = bits_for_whole-total_bits;
       if(offset>0)
       {
        binary_whole=malloc((bits_for_whole+1)*sizeof(char));
       memset(binary_whole, 0, bits_for_whole+1);
       convert_binary_whole(hex, binary_whole, bits_for_whole); //does thiis have to return
       //printf("%ld\n", offset);
       
       for(int i=0; i<total_bits; i++)
       {
        binary_whole[i]=binary_whole[offset+i];
       }
       binary_whole[total_bits]='\0';
       }
       else
       {
       binary_whole=malloc((total_bits+1)*sizeof(char));
       memset(binary_whole, 0, total_bits+1);
       convert_binary_whole(hex, binary_whole, total_bits); //does thiis have to return
       }



       //now we have our array of total bits
      //printf("%s\n", binary_whole);

       //split the converted hex

       char sign_field = binary_whole[0];
       //printf("%c\n", sign_field);

       char exponent_field[exponent_bits+1];
       memset(exponent_field, 0, exponent_bits+1);
       for(int i=0; i<exponent_bits; i++)
       {
        exponent_field[i]=binary_whole[1+i];
       }
    //printf("%s\n", exponent_field);
 
      long E_value=0;
       char fraction_field[fraction_bits+1];
       memset(fraction_field, 0, fraction_bits+1);
       for(int i=0; i<fraction_bits; i++)
       {
        fraction_field[i]=binary_whole[1+exponent_bits+i];
       }
       //printf("%s\n", fraction_field);

       long exponent = get_exponent(exponent_field, exponent_bits, &E_value);
      // printf("exp: %ld\n", exponent);
       double M_value = get_fraction(fraction_field, fraction_bits);
      // printf("M_value:%le\n", M_value);
       double number;
       long sign = get_sign(sign_field);

       //put it all together

       if(E_value==0)
       {
         number = 0.0+M_value;
       }
       else
       {
         number = 1.0+M_value;
       }
       double IEEE_number= pow(-1, sign)*number*pow(2,exponent);

       printf("%.*f\n", precision, IEEE_number);

       free(binary_whole);
       }

      fclose(graph_file);
     return EXIT_SUCCESS; 

    }





long get_sign(char sign_field)
{
    if(sign_field=='0')
    return 0;
    else 
    return 1;
}
long get_exponent(char exponent_field[], long exponent_bits, long* E_value)
{
    long bias = pow(2, exponent_bits-1)-1;
    long power=exponent_bits-1;
    for(int i=0; i<exponent_bits; i++)
    {
        if(exponent_field[i]=='1')
        {
          *E_value = *E_value+pow(2, power);
        }
        power--;
    }
    if(*E_value==0)
    {
        return 1-bias;
    }
    else
    return *E_value-bias;
}

double get_fraction(char fraction_field[], long fraction_bits)
{

    double M_value=0.0;
    long power=1;
    for(int i=0; i<fraction_bits; i++)
    {
        if(fraction_field[i]=='1')
        {
          M_value = M_value+pow(2, -1*power);
        }
        power++;
    }

    return M_value;


}

long get_binary_whole_length(unsigned int whole_number)
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

void convert_binary_whole(unsigned int whole_number, char binary_whole[], long total_bits)
{
    
   // printf("bits for whole: %ld\n", bits_for_whole);
    int index=0;
    for(int i=total_bits-1; i>=0; i--)
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
// //printf("%s\n", binary_whole);
//    return binary_whole;

}
