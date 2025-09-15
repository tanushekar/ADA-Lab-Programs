#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int t[15][15], wt[15], v[15];             

int n, m, count;

int max(int a, int b)
{
	return (a>b)?a:b;
}

int knapsack(int n, int m)
{
	if(t[n][m]!=-1)
	  return t[n][m];
	
	count++;
	
	if(wt[n]<=m)                            
	  return t[n][m]= max(knapsack(n-1, m), v[n]+knapsack(n-1, m-wt[n]) );
	else
	  return t[n][m]= knapsack(n-1, m);                     
}

void init(int n, int m)
{
	for(int i=0; i<=n; i++)
	{
		for(int j=0; j<=m; j++)
		{
			if(i==0||j==0)
			  t[i][j]=0;
			else
			  t[i][j]=-1;
		}
	}
}

void tester()
{
	printf("Enter the no of items: ");
	scanf("%d", &n);
	printf("\nEnter the CAPACITY of knapsack: ");
	scanf("%d", &m);
	
	printf("Enter the weights and values of the items: \n");
	printf("WT  VALUE\n");
	for(int i=1; i<=n; i++)                               
	{
		scanf("%d %d", &wt[i], &v[i]);                      
	}
	
	init(n, m);                                              
	
	printf("The max profit is %d\n", knapsack(n, m));
	
	printf("The table is as follows: \n");
	for(int i=0; i<=n; i++)
	{
		for(int j=0; j<=m; j++)
		{
			printf("%d  ", t[i][j]);
		}
		printf("\n");
	}
	
	printf("The composition of the sack is: \n");
	for(int i=n; i>0; i--)
	{
		if(t[i][m]!=t[i-1][m])
		{
			printf("Item-%d\t", i);
			m= m-wt[i];                                    
		}
	}
}

void plotter()
{
	FILE *f= fopen("mem_knap.txt", "w");
	
	for(int i=5; i<=10; i++)
	{
		n=i;
		m= 2*i;
		
		for(int j=1; j<=n; j++)
		{
			wt[j]= rand()%m+1;
			v[j]= rand()%50+1;
		}
		
		init(n, m);
		
		count=0;
		knapsack(n, m);
		fprintf(f, "%d\t%d\n", n, count);
	}
	fclose(f);
}

void main()
{
	int ch;
	for(;;)
	{
		printf("Enter choice\n1.TEST\n2.PLOT\n");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1: tester();
			break;
			case 2: plotter();
			break;
			default: exit(0);
		}
	}
}