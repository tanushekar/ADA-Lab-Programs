#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int count;

void merge(int *arr, int beg, int mid, int end)
{
	int n1= (mid-beg)+1;                  
	int n2= (end-mid);
	
	int left[n1];
	int right[n2];
	
	int i, j, k;
	
	for(i=0; i<n1; i++)
	  left[i]= arr[beg+i];              
	for(j=0; j<n2; j++)
	  right[j]= arr[mid+1+j];
	  
	i=0;
	j=0;
	k=beg;               
	
	while(i<n1 && j<n2)
	{
		count++;              
		
		if(left[i]<=right[j])         
		  arr[k++]= left[i++];
		else
		  arr[k++]= right[j++];
	}
	
	while(i<n1)                       
	  arr[k++]= left[i++];
	while(j<n2)
	  arr[k++]= right[j++];
}

void mergesort(int *arr, int beg, int end)
{
	if(beg<end)                             
	{
	   int mid= (beg+end)/2;
	
	   mergesort(arr, beg, mid);          
	   mergesort(arr, mid+1, end);
	
	   merge(arr, beg, mid, end);
    }
}

void worst(int *arr, int beg, int end)
{
	if(beg<end)               
	{
		int mid=(beg+end)/2;
		int n1= (mid-beg)+1;
		int n2= end-mid;
		
		int i, j, k;
		
		int a[n1], b[n2];
		
		for(i=0; i<n1; i++)
		  a[i]= arr[(2*i)];
		  
		for(j=0; j<n2; j++)
		  b[j]= arr[(2*j)+1];
		
		worst(a, beg, mid);                  
		worst(b, mid+1, end);
		
		for(i=0; i<n1; i++)
		  arr[i]= a[i];
		for(j=1; j<n2; j++)                
		  arr[j+1]= b[j];
	}
}

void tester()
{
	int n, *arr;
	
	printf("Enter the number of elements: ");
	scanf("%d", &n);
	
	arr= (int *)malloc(n*sizeof(int));
	
	printf("Enter elements: ");
	for(int i=0; i<n; i++)
		scanf("%d", &arr[i]);
	
	mergesort(arr, 0, n-1);
	
	printf("Sorted array: ");
	for(int i=0; i<n; i++)
	  printf("%d  ", arr[i]);
	printf("\n");
}

void plotter()
{
	srand(time(NULL));
	int *arr, n;
	
	FILE *f1, *f2, *f3, *f4;
	
	f1= fopen("merge_best.txt", "w");
	f2= fopen("merge_avg.txt", "w");
	f3= fopen("merge_worst.txt", "w");
	f4= fopen("worstdata.txt", "w");
	
	n=2;
	while(n<=1024)
	{
		arr= (int *)malloc(n*sizeof(int));
		
		//best case: sorted arr
		for(int i=0; i<n; i++)
		  arr[i]= i+1;
		
		count=0;                   
		mergesort(arr, 0, n-1);
		fprintf(f1, "%d\t%d\n", n, count);
		
		//avg case: random elements
		for(int i=0; i<n; i++)
		  arr[i]= rand()%n;
		
		count=0;
		mergesort(arr, 0, n-1);
		fprintf(f2, "%d\t%d\n", n, count);
		
		//worst case
		worst(arr, 0, n-1);
		for(int i=0; i<n; i++)
		    fprintf(f4, "%d\n", arr[i]);
		count=0;
		mergesort(arr, 0, n-1);
		fprintf(f3, "%d\t%d\n", n, count);
		
		n= n*2;
		free(arr);
	}
	
	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);
	printf("Data entered into file\n");
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