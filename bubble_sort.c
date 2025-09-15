#include<stdio.h>
#include<stdlib.h>

int count;

void bubbleSort(int *a, int n)
{
	count=0;                       
	
	int flag, temp;
	for(int i=0; i<n-1; i++)
	{
		flag=0;
		for(int j=0; j<n-i-1; j++)
		{
			count++;                      
			if(a[j]>a[j+1])
			{
				temp= a[j];
				a[j]= a[j+1];
				a[j+1]= temp;
				flag=1;          
			}
		}
		
		if(flag==0)
		    break;             
	}
}

void tester()
{
	int *a, n;
	printf("Enter the number of elements: ");
	scanf("%d", &n);
	a= (int *)malloc(n*sizeof(int));
	
	printf("Enter the elements of the array :");
	for(int i=0; i<n; i++)
	{
		scanf("%d", &a[i]);                      
	}
	bubbleSort(a, n);
	printf("After sorting: ");
	for(int i=0; i<n; i++)
	  printf("%d  ", *(a+i));                      
	
}


void plotter()
{
	int *arr, n;
	
	FILE *f1, *f2, *f3;
	
	f1=fopen("bubble_b.txt", "w");
	f2= fopen("bubble_a.txt", "w");
	f3= fopen("bubble_w.txt", "w");
	
	n=10;
	while(n<=30000)
	{
		arr= (int *)malloc(n*sizeof(int));
		
		//best case: sorted in ascending order
		for(int i=0; i<n; i++)
		   *(arr+i)= i+1;
		bubbleSort(arr, n);
		fprintf(f1, "%d\t%d\n", n, count);
		
		//avg case: random
		for(int i=0; i<n; i++)
		  *(arr+i)= rand()%n;
		bubbleSort(arr, n);
		fprintf(f2, "%d\t%d\n", n, count);
		
		//worst case: sorted in descending order
		
		for(int i=0; i<n; i++)
		  *(arr+i)= n-i;                  
		bubbleSort(arr, n);
		fprintf(f3, "%d\t%d\n", n, count);
		
		if(n<10000)
		  n=n*10;
		else
		  n= n+10000;
		
		free(arr);
	}
	fclose(f1);
	fclose(f2);
	fclose(f3);
}

void main()
{
	int ch;
	for(;;)
	{
		printf("Enter your choice: \n1.TEST\n2.PLOT\n");
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

