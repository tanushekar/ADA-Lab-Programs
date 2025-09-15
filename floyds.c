#include<stdio.h>
#include<stdlib.h>

#include<limits.h>
#include<time.h>

int n, count;
int dist[100][100];

int floyds(int adjMat[n][n], int n)
{
	count=0;
	
	for(int i=0; i<n; i++)
	  for(int j=0; j<n; j++)
	    if(adjMat[i][j]==-1)
	      dist[i][j]= INT_MAX;
	    else
	      dist[i][j]= adjMat[i][j];
	
	
	for(int k=0; k<n; k++)
	  for(int i=0; i<n; i++)
	  {
	  	int tempDist= dist[i][k];
	  	for(int j=0; j<n; j++)
	  	{
	  		if(dist[i][j]>tempDist)
	  		{
	  			count++;                   
	  			if(dist[k][j]!=INT_MAX && dist[i][j] > tempDist+dist[k][j])
	  			{
	  			   dist[i][j]= tempDist+ dist[k][j];
	  		    }
			}
		}
	 }
}

void tester()
{
	printf("Enter the number of nodes: ");
	scanf("%d", &n);
	
	int adjMat[n][n];
	
	printf("Enter the adj matrix: \n");
	printf("(Enter -1 for infinity)\n");
	
	for(int i=0; i<n; i++)
	  for(int j=0; j<n; j++)
	    scanf("%d", &adjMat[i][j]);
	
	floyds(adjMat, n);
	
	printf("Shortest distance between all pair of nodes: \n");
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		  printf("%d\t", dist[i][j]);                                
		printf("\n");
	}
}

void plotter()
{
	srand(time(NULL));
	
	FILE *f= fopen("floyds.txt", "w");
	
	for(int k=2; k<=12; k++)
	{
		n=k;
		int adjMat[n][n];
		for(int i=0; i<n; i++)
		  for(int j=0; j<n; j++)
		  {
		  	if(i!=j)
		  	  adjMat[i][j]=1;
		  	else
		  	  adjMat[i][j]=0;
		  }
		
		floyds(adjMat, n);
		fprintf(f, "%d\t%d\n", n, count);
	}
	fclose(f);
}

void main()
{
    int ch;
    printf("Enter\n1.Tester\n2.Plotter\n");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        tester();
        break;
    case 2:
        plotter();
        break;
    default:
        printf("Invalid choice!! ");
    }
}