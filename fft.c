#include"math.h"
#include "complex.h"
#include "stdlib.h"

#define pi 3.141592





int N=8;

double _Complex TEMP;
double _Complex W_N;
double _Complex W_n;

int cmplx_multiplication_counter=0;
int number_of_stages;
main()
{

static  double _Complex x[8]={1.0,4.0,3.0,2.0,2.0,3.0,4.0,1.0};

number_of_stages=log2(N);
//x[N]={1,2,3,4,4,3,2,1};
//x[N]={1,4,3,2,4,3,2,1};



//define the twiddle factor
W_N=cos(pi*2/N)-_Complex_I*sin(pi*2/N);
//1244321
//01234567
//04211537
//14322341
printf("The value of twiddle factor is %f + i%f : \n",creal(W_N),cimag(W_N));

fft(x,number_of_stages);
int i;
printf("The FFT of the sequence x[n] is : \n");
for(i=0;i<N;i++)
	{
	printf("%f + i%f \n",creal(x[i]),cimag(x[i]));
	}
printf("\n\n");
printf("The number of complex multiplications is: %d ",cmplx_multiplication_counter);

}


void fft(double _Complex *x,int number_of_stages)
{

int i,j,k,grouping_unit,number_of_butterflies_in_group;
int m,n,l;

/*************************************************/
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
		//X[k]=X[k]+X[k+grouping_unit/2]*W**(;	
		TEMP=x[k];	
		printf("\n The Upper input leg of Butterfly : : %f+ i%f ....",creal(TEMP),cimag(TEMP));
		printf("\n The Lower input leg of butterfly : : %f+ i%f ....",creal(x[k+grouping_unit/2]),cimag(x[k+grouping_unit/2]));

		x[k]=TEMP+x[k+grouping_unit/2]*W_n;
		x[k+grouping_unit/2]=TEMP-x[k+grouping_unit/2]*W_n;
		cmplx_multiplication_counter++;
		printf("\n The Upper output leg of Butterfly : : %f+ i%f ....",creal(x[k]),cimag(x[k]));
		printf("\n The Lower output leg of butterfly : : %f+ i%f ....",creal(x[k+grouping_unit/2]),cimag(x[k+grouping_unit/2]));

           }

	l=l+N/grouping_unit;
	
  	}
 

 }
/*************************************************/

}
