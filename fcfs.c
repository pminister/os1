#include<stdio.h>
void main()
{
	printf("How many Requests:");
	scanf("%d",&n);
	printf("Current head pointer initial");
	scanf("%d",&initial);
	printf("Enter Request Order");
	for(int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	sum=sum+abs(initial-a[0]);
	for(int i=1;i<n;i++)
	{
		sum=sum+abs(a[i]-a[i+1]);
	}
	printf("Total Head MOvements are:%d",sum);
}




