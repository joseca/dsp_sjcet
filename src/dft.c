

//use this to compile =>  gcc dft.c -o dft.o -lm
// and to run         =>  ./dft.o

//plot data using GNU plot
//plot "plotData.dat" using 1:2 title "data A"


#include<stdio.h>
#include "complex.h"
#include "math.h"
#include "stdlib.h"

#define pi 3.14
int cmplx_multiplication_counter=0;
main()
{


FILE *fp;
fp=fopen("plotData.dat", "w");
//fprintf(fp, "Testing...\n");


printf("\n\n\n");

printf("Program to calculate N point DFT of a sequence\n");
printf("**********************************************\n\n");

int N;
printf("Enter the No. of points (2,4,8,16)  : ");
scanf("%d",&N);

int i,j;
double _Complex X[N],Y[N],Z[N];
double temp;
printf("\n\n");

for(i=0;i<N;i++)
	{
	printf("Enter Real Part of x[%d] :",i);
	scanf("%lf",&temp);  				//lf is reqd for double in scanf..
	__real__ X[i]=temp;
	printf("Enter Imaginary Part of x[%d]:",i);
	scanf("%lf",&temp);
	__imag__ X[i]=temp;
	printf("\n");
	}

double _Complex a=2.0f+3.0f*_Complex_I;

printf("The entered sequence x[n] is : \n");
for(i=0;i<N;i++)
	{
	printf("%f + i%f \n",creal(X[i]),cimag(X[i]));
	}
printf("\n\n");

		for(i=0;i<N;i++)
		{ Y[i]=0;
		 for(j=0;j<N;j++)
		  {
		    Y[i]=Y[i]+X[j]*(cos(2*pi*i*j/N)-_Complex_I*(sin(2*pi*i*j/N)));
			printf("%f + i%f \n",creal(Y[i]),cimag(Y[i]));
cmplx_multiplication_counter++;
		    	
		  }

                }


printf("The DFT of the sequence x[n] is : \n");
for(i=0;i<N;i++)
	{
	printf("%f + i%f \n",creal(Y[i]),cimag(Y[i]));
	}
printf("\n\n");

printf("The number of complex multiplications is: %d ",cmplx_multiplication_counter);

printf("The DFT absoulute magnitude of the sequence x[n] is : \n");
for(i=0;i<N;i++)
	{
	printf("%f\n",cabs(Y[i]));
	}
printf("\n\n");



for(i=0;i<N;i++)
	{
	fprintf(fp,"%d   %f \n",i,cabs(Y[i]));
	}
printf("\n\n");



fclose(fp);

}
