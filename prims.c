#include<stdio.h>
#include<stdlib.h>

#include<time.h>

// vis-> nodes included in MST
// key[]-> min. edge wt to connect each vertex to MST


int mat[100][100], vis[100], source, parent[100], key[100];             

int n, count=0;

void create(int n)
{
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{
			if(i==j)
			  mat[i][j]=0;
			else
			  mat[i][j]= rand()%100+1;            
		}
	}
}

void prims(int source)
{
	int u, v, min;
	
	for(int i=1; i<=n; i++)
	{
		key[i]=9999;
		vis[i]=0;
		parent[i]= -1;
	}
	
	key[source]=0;                   
	
	for(int iter=1; iter<=n; iter++)
	{
		min= 9999;
		u= -1;
		
		for(v=1; v<=n; v++)                          
		{                              
			if(vis[v]==0 && key[v]< min)
			{
				min= key[v];
				u=v;
			}
		}
		
		if(u== -1)
		  break;
		
		vis[u]=1;
		
		for(int v=1; v<=n; v++)
		{
			count++;
			
			if(mat[u][v]!=0 && vis[v]==0 && mat[u][v]<key[v])              
			{
				parent[v]= u;
				key[v]= mat[u][v];
			}
		}
	}
}

void tester()
{
	int total_cost=0;
	
	printf("Enter the total number of vertices: ");
	scanf("%d", &n);
	
	printf("\nEnter the cost adj matrix(999 for infinity and 0 for self loop): \n");
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{
			scanf("%d", &mat[i][j]);
			
			if(mat[i][j] == 999)
			  mat[i][j]=0;                
		}
	}
	
	printf("\nEnter the source: ");
	scanf("%d", &source);
	
	prims(source);
	
	for(int i=1; i<=n; i++)
	{
		if(parent[i] != -1)                                          
		  printf("%d--%d\t %d\n", parent[i], i, key[i]);
		
		total_cost= total_cost + key[i];                            
	}
	
	printf("Min cost= %d\n", total_cost);
}

void plotter()
{
	FILE *f= fopen("prims.txt", "w");
	
	srand(time(NULL));
	
	for(int i=2; i<=10; i++)             
	{
		n=i;
		
		count=0;
		create(n);
		prims(1);
		
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
			case 1: tester(); break;
			case 2: plotter(); break;
			default: exit(0);
		}
	}
}
