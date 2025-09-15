//Program to find the gcd of two non-negative numbers m and n
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

//Euclid's Algo
int euclid(int m, int n)
{
	int r;
	int count=0;
	
	while(n!=0)
	{
		count++;              
		r= m%n;
		m=n;
		n=r;
	}
	
	printf("GCD(Euclid) is: %d\n", m);
	return count;
}

//Consecutive Integer Check algo

int consec(int m, int n)
{
	int count=0;
	
	int min= (m<n)?m:n;
	
	while(1)
	{
		count++;                
		if(m%min==0)
		{
			count++;           
			if(n%min==0)
			{
				printf("GCD (Consec) is %d\n", min);       
				return count;
			}
		}
		min--;
	}
}

//Repeated Sutraction Method

int modified(int m, int n)
{
	int count=0;
	
	while(n>0)
	{
		if(m<n)
		{
			int temp= m;
			m=n;
			n= temp;
		}
		
		m= m-n;
		count++;                       
	}
	
	printf("GCD (modified) is %d\n", m);
	return count;
}

void tester()
{
	int m, n;
	printf("Enter two numbers: ");
	scanf("%d %d", &m, &n);
	
	if(m<=0 || n<=0)
	{
		printf("GCD can't be found\n");
		return;
	}
	
	printf("Steps taken by each method: \n");
	printf("EUCLID'S: %d\n", euclid(m,n));
	printf("CONSECUTIVE: %d\n", consec(m, n));
	printf("MODIFIED: %d\n", modified(m, n));
	
}

void plotter()
{
	FILE *f1= fopen("e_best.txt", "w");
	FILE *f2= fopen("e_worst.txt", "w");
	FILE *f3= fopen("c_best.txt", "w");
	FILE *f4= fopen("c_worst.txt", "w");
	FILE *f5= fopen("m_best.txt", "w");
	FILE *f6= fopen("m_worst.txt", "w");
	
	int i, j, k;
	
	for(i=10; i<=100; i+=10)
	{
		int minE= INT_MAX, maxE= INT_MIN;
		int minC= INT_MAX, maxC= INT_MIN;
		int minM= INT_MAX, maxM= INT_MIN;
		
		for(j=2; j<=i; j++)
		{
			for(k=2; k<=i; k++)
			{
				int e= euclid(j, k);
				if(e<minE)
				   minE= e;
				if(e>maxE)
				   maxE= e;
				   
				int c= consec(j, k);
				if(c<minC)
				   minC= c;
				if(c>maxC)
				   maxC= c;
				   
			    int m= modified(j, k);
			    if(m<minM)
			       minM= m;
			    if(m>maxM)
			       maxM=m;
			}
		}
		fprintf(f1, "%d\t%d\n", i, minE);
		fprintf(f2, "%d\t%d\n", i, maxE);
		
		fprintf(f3, "%d\t%d\n", i, minC);
		fprintf(f4, "%d\t%d\n", i, maxC);
		
		fprintf(f5, "%d\t%d\n", i, minM);
		fprintf(f6, "%d\t%d\n", i, maxM);
	}
	
	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);
	fclose(f5);
	fclose(f6);
}

int main()
{
	int ch;
	printf("Enter choice:\n1.Tester\n2.Plotter\n");
	scanf("%d", &ch);
	
	switch(ch)
	{
		case 1: tester();
		        break;
		case 2: plotter();
		        break;
		default: printf("Invalid choice\n");
	}
	return 0;
}