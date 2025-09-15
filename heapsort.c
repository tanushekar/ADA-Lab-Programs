#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int count, count2=0;

void swap(int *a, int *b)
{
	int temp= *a;
	*a= *b;
	*b= temp;
}

int max(int a, int b)
{
	return (a>b)?a:b;
}

void heapify(int *heap, int n, int root)         
{
	int largest=root;
	int left= 2*root+1;
	int right= 2*root+2;
	
	if(left<n)
	{
		count++;
		if(heap[left]>heap[largest])
		  largest= left;
	}
	if(right<n)
	{
		count++;
		if(heap[right]>heap[largest])
		  largest= right;
	}
	if(largest!=root)
	{
		swap(&heap[root], &heap[largest]);     
		heapify(heap, n, largest);            
	}
}


void heapsort(int *heap, int n)
{
	for(int i=(n/2)-1; i>=0; i--)                   
	  heapify(heap, n, i);          
	
	count2= count;
	count=0;
	
	for(int i=n-1; i>=0; i--)
	{
		swap(&heap[0], &heap[i]);
		heapify(heap, i, 0);                  
	}                                        
}

void tester()
{
	int *arr, n;
	printf("Enter the no of ele: ");
	scanf("%d", &n);
	
	arr= (int *)malloc(n*sizeof(int));
	
	printf("Enter the ele of the array: ");
	for(int i=0; i<n; i++)
	  scanf("%d", &arr[i]);
	
	heapsort(arr, n);
	
	printf("The sorted array after heapsort: ");
	for(int i=0; i<n; i++)
	  printf("%d  ", arr[i]);
}

void plotter()
{
	srand(time(NULL));
	
	int *arr, n;
	
	FILE *f1= fopen("heapbest.txt", "w");
	FILE *f2= fopen("heapavg.txt", "w");
	FILE *f3= fopen("heapworst.txt", "w");
	
	n=100;
	while(n<=1000)
	{
		arr= (int *)malloc((n+1)*sizeof(int));                 
		
		//best case--> sorted in descending order
		for(int i=0; i<n; i++)
		  *(arr+i)= n-i+1;                               
		count=0;
		heapsort(arr, n);
		count=max(count, count2);
		fprintf(f1, "%d\t%d\n", n, count);
		
		//avg case--> random elements
		for(int i=0; i<n; i++)
		  *(arr+i)= rand()%n;
		count=0;
		heapsort(arr, n);
		count= max(count, count2);
		fprintf(f2, "%d\t%d\n", n, count);
		
		//worst case-->sorted in ascending array
		for(int i=0; i<n; i++)
		  *(arr+i)= i+1;
		count=0;
		heapsort(arr, n);
		count= max(count, count2);
		fprintf(f3, "%d\t%d\n", n, count);
		
		n= n+100;
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
		printf("Enter choice\n1.TEST\n2.PLOT\n");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1: tester();break;
			case 2: plotter();break;
			default: exit(0);
		}
	}
}