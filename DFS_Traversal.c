#include<stdio.h>
#include<stdlib.h>

int isCycle=0, components=0, isTester=0;
int n, count=0;

void dfs(int mat[n][n], int *visit, int source, int parent)        
{
	visit[source]=1;
	
	if(isTester)
	  printf("%c-> ", source+65);
	  
	for(int i=0; i<n; i++)
	{
		count++;                                    
		
		if(mat[source][i]==1 && visit[i]==1 && i!=parent)        
		  isCycle=1;
		  
		else if(mat[source][i]==1 && visit[i]==0)                        
		  dfs(mat, visit, i, source);
	}
}


/*
if(mat[source][i]==1)
		{
			count++;
			if( visit[i]==1 && i!=parent)        
		          isCycle=1;
		  
		    else if(visit[i]==0)                        
		          dfs(mat, visit, i, source);
			
		} 
*/


void checkConnectivity(int mat[n][n])
{
	int vis[n];
	int k=1;
	
	for(int i=0; i<n; i++)                          
	  vis[i]=0;
	
	for(int i=0; i<n; i++)
	{
		if(!vis[i])
		{
			components++;
			
			if(isTester)
			  printf("Component-%d: ", k++);
			
			dfs(mat, vis, i, -1);         
		}
	}
}

void tester()
{
	isTester=1;                     
	
	printf("Enter the number of vertices: ");
	scanf("%d", &n);
	
	int adjMat[n][n];
	
	printf("Enter adj matrix: ");
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			scanf("%d", &adjMat[i][j]);
		}
	}
	
	count=0;
	components=0;
	isCycle=0;
	
	checkConnectivity(adjMat);
	
	printf("\nThe number of components: %d\n", components);
	
	if(components==1)
	  printf("\nThe graph is connected\n");
	else
	  printf("\nThe graph is NOT connected\n");
	
	if(isCycle)
	  printf("Cycle exists\n");
	else
	  printf("Cycle doesn't exist\n");
}

void plotter()
{
	FILE *f1= fopen("dfs_best.txt", "w");
	FILE *f2= fopen("dfs_worst.txt", "w");
	
	isTester=0;                           
	
	for(int k=2; k<=10; k++)              
	{
		n=k;
		int adjMat[n][n];
		
		//best case--> linear chain
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				adjMat[i][j]=0;
			}
		}
		for(int i=0; i<n-1; i++)
		{
			adjMat[i][i+1]=1;
			adjMat[i+1][i]=1  ;                  
		}
		
		count=0;
		components=0;
		isCycle=0;
		checkConnectivity(adjMat);
		
		fprintf(f1, "%d\t%d\n",n, count);
		
		
		//worst case--> complete graph
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				if(i!=j)
				  adjMat[i][j]=1;       
				else
				  adjMat[i][j]=0;
				  
			}
		}
		
		count=0;                
		components=0;
		isCycle=0;      
		   
		checkConnectivity(adjMat);
		
		fprintf(f2, "%d\t%d\n", n, count);
	}
	
	fclose(f1);
	fclose(f2);
}

void main()
{
	int ch; 
	for(;;)                  
	{          
	
		printf("Enter choice: \n1.TEST\n2.PLOT\n");
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