#include<stdio.h>
#include<stdlib.h>

int main()
{
	int i,a[30],n,count;
	printf("How many Request Orders:\n");
	scanf("%d",&n);
	printf("Current head initial pointer")
	scanf("%d",&initial);
	printf("Enter Request Orders:\t");
	
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	while(count!=n)//change
	{
		int min=1000,diff,k;
		for(i=0;i<n;i++)
		{
			diff=abs(a[i]-initial)
			if(min > diff)
			{
				min=diff;
				k=i;
			}
		}
		sum=sum+min;
		initial=a[k];
		a[k]=1000;
		count++;	
	}
	printf("Total Head MOvements are:%d",sum);
}