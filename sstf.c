#include<stdio.h>
#include<stdlib.h>
int front,rear;
void init()
{
	front=rear=-1;
}
void display(int *Q)
{
	int i;
	printf("\nFront %d\t",front);
	for(i=front;i<=rear;i++)
		printf("\t%d",Q[i]);
}
void enqueu(int *Q,int n,int var)
{
	if(rear==n)
		printf("\nQueue is Full");
	else
	{
		if(front==-1&&rear==-1)
		{
			front++;
			rear++;
		}
		else
			rear++;	
		Q[rear]=var;
	}
}
int SSTF(int *Q,int n,int initial)
{
    int min,diff,index,TotalHeadMoment=0,count=0,i;
    while(count!=n)
    {
        min=1000;
        for(i=0;i<n;i++)
        {
            diff=abs(Q[i]-initial);
            if(min>diff)
            {
                min=diff;
                index=i;
            }
        }
        printf("\nIndex=%d\n",index);
        printf("Disk head moves from %d to %d with seek %d\n",initial,Q[index],min);
        TotalHeadMoment=TotalHeadMoment+min;
        initial=Q[index];
     	Q[index]=1000;
        count++;
    }
    return TotalHeadMoment;
}
int main()
{
    int queue[100],i,n,TotalHeadMoment,initial,max,var;
    init();
    printf("\nEnter the max range of disk\n");
    scanf("%d",&max);
    printf("\nEnter the size of queue request\n");
    scanf("%d",&n);
    printf("\nEnter the queue of disk positions to be read\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&var);
        if(var<0||var>max)
            printf("\nError..!Given Position is invalid\n");
        else
        {
            enqueu(queue,n,var);
        }
    }
 }
