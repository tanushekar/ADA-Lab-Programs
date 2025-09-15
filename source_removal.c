#include<stdio.h>
#include<stdlib.h>

int queue[20], front= -1, rear=-1, indegree[20];

int opcount=0, n;
int i, j, k;

int bfs(int mat[n][n])
{
	int count=0;                  
	front=-1;
	rear=-1;                        
	
	for(i=0; i<n; i++)
	{
		if(indegree[i]==0)
		{
			queue[++rear]=i;
		}
	}
	
	while(front != rear)
	{
		count++;
		
		int cur=queue[++front];
		
		for(i=0; i<n; i++)
		{
			opcount++;
			if(mat[cur][i]==1)
			{
				indegree[i]--;
				if(indegree[i]==0)
				   queue[++rear]=i;
			}
			
		}
	}
	 
	if(count!=n)                
	    return 1;
	else
	    return 0;               
}

void tester()
{
	printf("Enter the number of vertices: ");
	scanf("%d", &n);
	int mat[n][n];
	
	for(i=0; i<n; i++)
	{
		indegree[i]=0;
	}
	
	printf("Enter the adjacency matrix: ");
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			scanf("%d", &mat[i][j]);
			if(mat[i][j])
			   indegree[j]++;               
		}
	}
	
	printf("Input matrix is: \n");
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			printf("%d  ", mat[i][j]);
	    }
	    printf("\n");
    }
	if(bfs(mat))
	{
		printf("Cycle exists\n");
		exit(0);
	}
	else
	{
		printf("Topological Order: ");
		for(i=0; i<= rear ; i++)              
		  printf("%c-->", queue[i]+65);
	}
}

void plotter()
{
	FILE *f1= fopen("src_best.txt", "w");
	FILE *f2= fopen("src_worst.txt", "w");
	
	for(k=2; k<=10; k++)
	{
		n=k;
		int mat[n][n];
		
		for(i=0; i<n; i++)
		  indegree[i]=0;                
		
		//BEST CASE->LINEAR CHAIN
		for(int i=0; i<n-1; i++)
		{
			mat[i][i+1]=1;
			indegree[i+1]++;
		}
		opcount=0;
	    bfs(mat);
	    fprintf(f1, "%d\t%d\n", n, opcount);
	    
	    //WORST CASE-> UPPER TRIANGULAR
		for(i=0; i<n; i++)
		  indegree[i]=0;  
		  
		for(i=0; i<n; i++)
		  for(j=0; j<n; j++)
		    mat[i][j]= 0;
	    
	    for(i=0; i<n-1; i++)
	    {
		 for(j=i+1; j<n; j++)
	      {
	        mat[i][j]=1;
	        indegree[j]++;                                  
	      }
	    }
	
	    opcount=0;
	    bfs(mat);
	    fprintf(f2, "%d\t%d\n", n, opcount);
    }
    fclose(f1);
    fclose(f2);
}

void main()
{
	int ch;
	for(;;)
	{
		printf("\nEnter the choice\n1.TEST\n2.PLOT\n");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1: tester();
			        break;
			case 2: plotter(0);
			        plotter(1);
			        printf("best and worst case files generated\n");
			        break;
			default: exit(0);
		}
	}
}