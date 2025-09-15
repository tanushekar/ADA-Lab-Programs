#include <stdio.h>
#include <stdlib.h>

int n, count = 0, top = -1;

int dfs(int mat[n][n], int *vis, int source, int *track,  int *stack)         
{
    vis[source] = 1;
    track[source] = 1;        

    for (int i=0; i<n; i++)
    {
        count++;
        
        if (mat[source][i]  && vis[i] && track[i] )
        {
            return 1;
        }
        if (mat[source][i] && !vis[i] && dfs(mat, vis, i, track, stack))         
        {
            return 1;
        }
    }
    
    stack[++top] = source;
    track[source] = 0;            
    
    return 0; 
}


/*
if(mat[source][i])
		{
                    count++;         
                    if(vis[i] && track[i])
                        return 1;
                   if(!vis[i] && dfs(mat, vis, i, track, stack))
                       return 1;
        }
*/



int *checkConnectivity(int mat[n][n])            
{
    int vis[n], track[n];
    
    int *stack = (int*)malloc(n * sizeof(int));

    for (int i=0; i<n; i++)
    {
        vis[i] = 0;
        track[i]=0;
    }

    for (int i=0; i<n; i++)
    {
        if (!vis[i])
        {
            if (dfs(mat, vis, i, track, stack))                   
            {
                return NULL;       
            }
        }
    }

    return stack;
}

void tester()
{
    printf("Enter number of vertices :\n");
    scanf("%d", &n);
    int adjMat[n][n];

    printf("Enter the adjacency matrix :\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &adjMat[i][j]);
        }
    }

    count=0;
    top=-1;
    
    int *stack = checkConnectivity(adjMat);       
	           
    if (stack == NULL)
    {
        printf("Cycle exists..Cannot perform topological sorting!!!");
        exit(0);
    }
    else
    {
        printf("Topological sorting order : \n");

        while (top != -1)
        {
            printf("%c ", stack[top--]+65);
        }
    }
}

void plotter()
{
    FILE *f1 = fopen("DfsTopo_best.txt", "w");
    FILE *f2 = fopen("DfsTopo_worst.txt", "w");

    for (int k = 2; k <= 10; k++)
    {
        n = k;
        int adjMat[n][n];
        
        //best case-> linear chain
        for (int i = 0; i < n; i++)
              for (int j = 0; j < n; j++)
                  adjMat[i][j] = 0;                         

        for (int i = 0; i < n - 1; i++)
                   adjMat[i][i+1] = 1;                    

        count = 0, top = -1;                               
        checkConnectivity(adjMat);
        fprintf(f1, "%d\t%d\n", n, count);
        
        // worst case-> upper triangular
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                adjMat[i][j] = 0;                  

        for (int i=0; i<n-1; i++)            
        {
            for (int j=i+1; j<n; j++)         
            {
                adjMat[i][j] = 1;
            }
        }

        count = 0, top = -1;             
        checkConnectivity(adjMat);
        fprintf(f2, "%d\t%d\n", n, count);
    }

    fclose(f1);
    fclose(f2);
}

void main()
{
    int choice;
    printf("Enter\n1.Tester\n2.Plotter\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        tester();
        break;
    case 2:
        plotter();
        break;
    default:
        printf("Invalid choice");
    }
}