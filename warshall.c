#include<stdio.h>
#include<stdlib.h>

int n, count;

int paths[100][100];

int warshall(int adjMat[n][n], int n)
{
	count=0;
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
		  paths[i][j]= adjMat[i][j];
		  
	for(int k=0; k<n; k++)
	{
		for(int i=0; i<n; i++)
		{
			if(paths[i][k])
	        {
	    	   for(int j=0; j<n; j++)
	    	   {
	    		  count++;                 
	    		  paths[i][j]= paths[i][j] || paths[i][k]&&paths[k][j];
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
	
	printf("Enter the adj matrix: ");
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			scanf("%d", &adjMat[i][j]);
		}
	}
	
	warshall(adjMat, n);
	
	printf("Transitive closure matrix is: \n");
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			printf("%d", paths[i][j]);     
		}
		printf("\n");
	}
}

void plotter()
{
	FILE *f1= fopen("warshall_best.txt", "w");
	FILE *f2= fopen("warshall_worst.txt", "w");
	
	for(int k=1; k<=10; k++)
	{
		n=k;
		int adjMat[n][n];         
	
        //best case	
	    for(int i=0; i<n; i++)
	     for(int j=0; j<n; j++)
	       adjMat[i][j]=0;
	       
 	    for(int i=0; i<n-1; i++)
	       adjMat[i][i+1]=1;
	    adjMat[n-1][0]=1;                         
	
	    warshall(adjMat, n);
	    fprintf(f1, "%d\t%d\n", n, count);
	    
	    //worst case
	    for(int i=0; i<n; i++)
	      for(int j=0; j<n; j++)
	      {
	      	if(i!=j)
	      	  adjMat[i][j]= 1;
	      	else
	      	  adjMat[i][j]=0;
		  }
		  
		warshall(adjMat, n);
		fprintf(f2, "%d\t%d\n", n, count);
	}	
	fclose(f1);
	fclose(f2);
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

