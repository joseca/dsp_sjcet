#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"

#define pi 3.1415926535897932384

void write_Complex_output_to_file(double _Complex *input);
double _Complex * read_Complex_input_from_file();
double _Complex * calculate_DFT(double _Complex *input);
double _Complex * calculate_FFT(double _Complex *input);
unsigned int reverseIntNBits(unsigned num,int bits) ;


int N=0;


int main()
{




char input_file_name[]="input.txt";
char output_file_name[]="output.txt";
int i;
double _Complex *input=read_Complex_input_from_file();
   for(i=0;i<N;i++)
    {
         printf("\n%f + %fj",creal(input[i]),cimag(input[i]));

    }

double _Complex *output_of_DFT=calculate_DFT(input);
double _Complex *output_of_FFT=calculate_FFT(input);



write_Complex_output_to_file(output_of_DFT);
return 0;
}


void write_Complex_output_to_file(double _Complex *input)
{

int i=0;

FILE* outFileFp = fopen("output.txt", "w");
    for(i=0;i<N;i++)
    {
        fprintf(outFileFp,"%f,%f\n",creal(input[i]),cimag(input[i]));

    }


}

double _Complex* calculate_DFT(double _Complex *input)
{


double _Complex X[N];
double _Complex *Y=malloc(sizeof(double)*N*2);  //each complex double has double*2 mem requirement!


int i,j,cmplx_multiplication_counter=0;
printf("starting DFT...\n\n");

for(i=0;i<N;i++)
{
X[i]=input[i];
printf("%f + i%f \n",creal(X[i]),cimag(X[i]));

}
for(i=0;i<N;i++)
		{ Y[i]=0;
		 for(j=0;j<N;j++)
		  {
		    Y[i]=Y[i]+X[j]*(cos(2*pi*i*j/N)-_Complex_I*(sin(2*pi*i*j/N)));
			

cmplx_multiplication_counter++;
		    	
		  }

                }

printf("\nThe number of complex multiplications for this %d point DFT is %d",N,cmplx_multiplication_counter);


return Y;

}



double _Complex * calculate_FFT(double _Complex *input)
{


double _Complex X[N];
double _Complex *Y=malloc(sizeof(double)*N*2);  //each complex double has double*2 mem requirement!

int i,j,cmplx_multiplication_counter=0;
printf("starting FFT...\n\n");
printf("Bit Reversal starting...\n");

for(i=0;i<N;i++)
{
X[i]=input[i];
printf("%f + i%f \n",creal(X[i]),cimag(X[i]));

}

   for(i=0;i<N;i++){
        printf("\n%d<=>%d",i,reverseIntNBits(i,log2(N) ));
    }
 

double _Complex bit_reversed_X[N];
for(i=0;i<N;i++){
       
        bit_reversed_X[i]=X[reverseIntNBits(i,log2(N))];
        
    }
    	
printf("After Bit Reversal...\n");

for(i=0;i<N;i++)
{

printf("%f + i%f \n",creal(bit_reversed_X[i]),cimag(bit_reversed_X[i]));

}
//*******************************************
int number_of_stages;
double _Complex TEMP;
double _Complex W_N;
double _Complex W_n;
W_N=cos(pi*2/N)-_Complex_I*sin(pi*2/N);
printf("The value of twiddle factor is %f + i%f : \n",creal(W_N),cimag(W_N));
number_of_stages=log2(N);


int k,grouping_unit,number_of_butterflies_in_group;
int m,n,l;


//Loop through each stage
for(i=1;i<=number_of_stages;i++)
 {
 
 printf("\n Stage %d starting....\n*******************",i);
 // 2  4  8 16
 grouping_unit=1<<i;
 printf("\n grouping by %d ....",grouping_unit);
 

 // 1  2  4  8
 number_of_butterflies_in_group=grouping_unit/2;
 printf("\n No of parameters in this group: %d ....",number_of_butterflies_in_group);
 l=0;	
    for(j=0;j<number_of_butterflies_in_group;j++)
	{
	
 
	
	//set parameter
	W_n=cpow(W_N,l);
	printf("\n The twiddle factor k: : %d ....",l);
	printf("\n The twiddle factor value: : %f +i%f ....",creal(W_n),cimag(W_n));
	
	
	for(k=j;k<N;k=k+grouping_unit) //same parameter
	   {
			
		TEMP=bit_reversed_X[k];	
		printf("\n The Upper input leg of Butterfly : : %f+ i%f ....",creal(TEMP),cimag(TEMP));
		printf("\n The Lower input leg of butterfly : : %f+ i%f ....",creal(bit_reversed_X[k+grouping_unit/2]),cimag(bit_reversed_X[k+grouping_unit/2]));

		bit_reversed_X[k]=TEMP+bit_reversed_X[k+grouping_unit/2]*W_n;
		bit_reversed_X[k+grouping_unit/2]=TEMP-bit_reversed_X[k+grouping_unit/2]*W_n;
		cmplx_multiplication_counter++;
		printf("\n The Upper output leg of Butterfly : : %f+ i%f ....",creal(bit_reversed_X[k]),cimag(bit_reversed_X[k]));
		printf("\n The Lower output leg of butterfly : : %f+ i%f ....",creal(bit_reversed_X[k+grouping_unit/2]),cimag(bit_reversed_X[k+grouping_unit/2]));

           }

	l=l+N/grouping_unit;
	
  	}
 

 }



//*******************************************



printf("\nThe number of complex multiplications for this %d point FFT is %d",N,cmplx_multiplication_counter);



for(i=0;i<N;i++)
{
Y[i]=bit_reversed_X[i];
}
return Y;


}




double _Complex * read_Complex_input_from_file()
{
	
	
	double _Complex *input;
	
	//initialize the file pointers..
	FILE* inFileFp = fopen("input.txt", "r");
	
	if(!inFileFp)
	 {
	  printf("Input file missing!!..");
	  exit(0);
	 }
    	
	char line[512];
	char real[100],img[100];
	char * pstr;
	double *realArr,*imgArr;

	//double realArr[10],imgArr[10];
	int count=0,i=0;

	printf("\nReading input file......");
	//get the number of lines in the input file
	while (fgets(line, sizeof(line), inFileFp)) 
	 {
	  count++;
	 }
	
	N=count;
	printf("\nThe number of inputs is %d",count);
	
		
	//allocate memory for getting in the input data into real and imaginary parts..
	realArr=malloc(sizeof(double)*count);
	imgArr=malloc(sizeof(double)*count);
	input=malloc(sizeof(double)*count*2);  //each complex double has double*2 mem requirement!


 	//reset file pointer to beginning again..
	fseek(inFileFp,0,SEEK_SET);

    while (fgets(line, sizeof(line), inFileFp)) 
	{

        	//printf("\n %s", line);
		pstr = strtok(line,",");
		while (pstr != NULL)
		 {
			//printf ("%s\n",real);
			//printf ("%s\n",pstr);
			strcpy(real,pstr);
			pstr = strtok (NULL, ",");
			//printf ("%s\n",pstr);
			strcpy(img,pstr);
			break;
		 }

		printf("\n%s+j%s",real,img);
		realArr[i]=atof(real);
		imgArr[i++]=atof(img);
	}

    for(i=0;i<count;i++)
    {

 	__real__ input[i]=realArr[i];
	__imag__ input[i]=imgArr[i];


    }

	



    return input;
}












unsigned int reverseIntNBits(unsigned num,int bits) 
{
    unsigned int NO_OF_BITS = bits;
    unsigned int reverse_num = 0, i, temp;

    for (i = 0; i < NO_OF_BITS; i++)
    {
        temp = (num & (1 << i));
        if(temp)
            reverse_num |= (1 << ((NO_OF_BITS - 1) - i));
    }
    return reverse_num;
}






