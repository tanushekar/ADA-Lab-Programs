#include<stdio.h>
#include<stdlib.h>

int count;

void insertionSort(int *arr, int n)
{
	count=0;                            
	
	for(int i=1; i<n; i++)               
	{
		int key= arr[i];
		int j= i-1;
		                
		while(j>=0 && ++count && key<arr[j])   
		{
			arr[j+1]= arr[j];
			j--;
		}
		arr[j+1]= key;
	}
}

void plotter()
{
	int *arr, n;
	n=10;
	
	FILE *f1, *f2, *f3;
	f1= fopen("insert_b.txt", "w");
	f2= fopen("insert_a.txt", "w");
	f3= fopen("insert_w.txt", "w");
	
	while(n<=30000)
	{
		arr= (int *)malloc(n*sizeof(int));
		
		//best case: sorted array
		for(int i=0; i<n; i++)
		   *(arr+i)= i+1;
		insertionSort(arr, n);
		fprintf(f1, "%d\t%d\n", n, count);
		
		//avg case: random
		for(int i=0; i<n; i++)
		  *(arr+i)= rand()%n;
		insertionSort(arr, n);
		fprintf(f2, "%d\t%d\n", n, count);
		
		//worst case: descending array
		for(int i=0; i<n; i++)
		  *(arr+i)= n-i;
	    insertionSort(arr, n);
	    fprintf(f3, "%d\t%d\n", n, count);
	    
	    if(n<10000)
	      n= n*10;
	    else
	      n= n+10000;
	    
	    free(arr);                           
	}
	
	fclose(f1);
	fclose(f2);
	fclose(f3);
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
	
	insertionSort(arr, n);
	
	printf("Sorted array: ");
	for(int i=0; i<n; i++)
	{
		printf("%d  ", *(arr+i));
	}
	
}

void main()
{
	int ch;
	for(;;)
	{
		printf("Enter choice\n1.TEST\n2.PLOT\n");
		scanf("%d",&ch);
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
