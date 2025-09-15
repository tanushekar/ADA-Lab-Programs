#include<stdio.h>
#include<stdlib.h>

int isCyclic=0, components=0, isTester=0;        
int n, count=0;

void bfs(int mat[n][n], int *visit, int source)                 
{
	int queue[n];                                              
	int parent[n];              
	int front=-1, rear=-1;
	
	queue[++rear]= source;
	parent[rear]= -1;                      
	visit[source]=1;
	
	while(rear!= front)
	{
		int cur= queue[++front];
		int par= parent[front];
		
		if(isTester)
		  printf("%c ", cur+65);
		  
		for(int i=0; i<n; i++)
		{
			count++;                 
			
			if(mat[cur][i] && visit[i] && i!=par)          
			   isCyclic=1;
			if(mat[cur][i] && visit[i]==0)                 
			{
				queue[++rear]=i;         
				parent[rear]= cur;    
				visit[i]=1;          
			}
		}	
	}
	
	
}


/*for(int i=0; i<n; i++)
		{
			//count++;                 
			if(mat[cur][i])
			{
				count++;
			
			    if(visit[i] && i!=par)          
			      isCyclic=1;
			      
			    if(visit[i]==0)                
			    {
				   queue[++rear]=i;
				   parent[rear]= cur;    
				   visit[i]=1;          
			   }
		   }
		}
		
*/


void connectivity(int mat[n][n])
{
	int visit[n];
	int k=1;
	
	for(int i=0; i<n; i++)
	   visit[i]=0;
	   
	for(int i=0; i<n; i++)
	{
		if(visit[i]==0)
		{
			components++;
			if(isTester)
			  printf("\nComponent-%d: ", k++);
			
			bfs(mat, visit, i);
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
	isCyclic=0;
	
	connectivity(adjMat);
	
	printf("\nThe number of components: %d\n", components);
	
	if(isCyclic)
	  printf("It has a cycle\n");
	else
	  printf("No cycle\n");
	
	if(components==1)                       
	  printf("It is connected\n");
	else
	  printf("Not connected\n");
}

void plotter()
{
	isTester=0;
	
	FILE *f1= fopen("bfs_best.txt", "w");
	FILE *f2= fopen("bfs_worst.txt", "w");
	
	for(int k=2; k<=10; k++)            
	{
		n=k;
		int mat[n][n];
		
		//best case->linear chain
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				mat[i][j]=0;
			}
		}
		
		for(int i=0; i<n-1; i++)              
		{
			mat[i][i+1]= 1;                  
			
			mat[i+1][1]=1;
		}
		
		count=0;
		isCyclic=0;
		components=0;
		
		connectivity(mat);
		fprintf(f1, "%d\t%d\n", n, count);
		
		
		//worst-> complete graph
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				if(i!=j)
				  mat[i][j]=1;
				else
				  mat[i][j]=0;
			}
		}
		
		count=0;
		isCyclic=0;
		components=0;
		
		connectivity(mat);
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