#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define INF 999             

int count=0;                   

void dijkstras(int n, int cost[15][15], int source)        
{
	int dist[15]= {0}    ;            
	int visited[15]={0};                      
	
	int i, j, u, min;
	
	for(i=1; i<=n; i++)                                   
	  dist[i]= cost[source][i];
	  
	dist[source]=0;
	
	for(int num=1; num<=n; num++)         
	{
		min= INF;                        
		u=-1;
		
		for(j=1; j<=n; j++)
		{
			if(visited[j]==0 && dist[j]<min)               
			{                                              
				min= dist[j];
				u=j;
			}
		}
		
		visited[u]=1;
		
		for(j=1; j<=n; j++)                   
		{
			count++;                                        
			if(visited[j]==0 && dist[j]> dist[u]+cost[u][j])
			{
				dist[j]= dist[u]+cost[u][j];
			}
		}
	}
	
	printf("Source\tDestination\tCost\n");
	for(int i=1; i<=n; i++)
	   printf("%c--%c\t%d\n", source+64, i+64, dist[i]);  
}


void tester()
{
	int n, cost[15][15], source;
	
	printf("Enter the number of vertices: ");
	scanf("%d", &n);
	
	printf("Enter the cost matrix(999 for no edge and 0 for self loop): \n");
	
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{
			scanf("%d", &cost[i][j]);
			
			if(i==j)
			  cost[i][j]=0;
			  
			if(cost[i][j]==0 && i!=j)
			  cost[i][j]=INF;                   
		}
	}
	
	printf("Enter the source vertex (1 to %d): ", n);
	scanf("%d", &source);
	
	dijkstras(n, cost, source);
}


void plotter()
{
	FILE *f= fopen("dijkstras.txt", "w");
	
	for(int v=2; v<=10; v++)
	{
		int n=v;
		int cost[15][15];
		
		for(int i=1; i<=n; i++)
		{
			for(int j=1; j<=n; j++)
			{
				if(i==j)
				  cost[i][j]=0;
				else
				  cost[i][j]= rand()%10+1;                 
			}
		}
		count=0;
		dijkstras(n, cost, 1);                    
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