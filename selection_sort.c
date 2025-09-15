#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int count;

void selectionSort(int *arr, int n)
{
	count=0;
	
	for(int i=0; i<n-1; i++)                
	{
		int min=i;
		
		for(int j=min+1; j<n; j++)          
		{
			count++;
			if(arr[j]<arr[min])
			  min=j;
		}
		if(min!= i)
		{
			int temp= arr[min];
			arr[min]= arr[i];
			arr[i]= temp;
		}
	}
}

void tester()
{
	int *arr, n;
	
	printf("Enter the number of elements: ");
	scanf("%d", &n);
	arr= (int *)malloc(n*sizeof(int));
	
	printf("Enter the elements: ");
	for(int i=0; i<n; i++)
	{
		scanf("%d", &arr[i]);
	}
	
	selectionSort(arr, n);
	
	printf("Sorted array: ");
	for(int i=0; i<n; i++)
	  printf("%d ", *(arr+i));
	
}
void plotter()
{
	FILE *f= fopen("selectsort.txt", "w");
	
	int n=10;
	while(n<=30000)
	{
		int *a= (int *)malloc(n*sizeof(int));
		
		for(int i=0; i<n; i++)
		  *(a+i)= i;
		count=0;                       
		selectionSort(a, n); 
		fprintf(f, "%d\t%d\n", n, count);
		
		if(n<10000)
		  n= n*10;
		else
		  n= n+10000;
		
		free(a);
	}
	fclose(f);
}

void main()
{
	int ch;
	for(;;)
	{
		printf("\nEnter choice\n1.TEST\n2.PLOT\n");
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