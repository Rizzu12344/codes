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
	for(i=front;i<=rear;i++)
		printf("\t%d",Q[i]);
}
void enqueu(int *Q,int n,int var)
{
	if(rear==n)
		printf("\nQueue is Full");
	else
	{
		if(front==-1)
			front++;
		rear++;
		Q[rear]=var;
	}
}
int FCFS(int *Q, int n)
{
    int j,seek=0,diff;
    for(j=0;j<n;j++)
    {
        diff=abs(Q[j+1]-Q[j]);
        seek+=diff;
    printf("Disk head moves from %d to %d with seek %d\n",Q[j],Q[j+1],diff);
    }
    return seek;
}
int main()
{
    int queue[20],n,var,head,i,j,k,seek,max;
    float avg;
    init();
    printf("\nFront=%d\nRear=%d",front,rear);
    printf("\nEnter the max range of disk\n");
    scanf("%d",&max);
    printf("Enter the size of queue request\n");
    scanf("%d",&n);
    printf("Enter the initial head position\n");
    scanf("%d",&head);
    printf("Enter the queue of disk positions to be read\n");
    enqueu(queue,n,head);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&var);
        if(var<0||var>max)
            printf("\nError..!Given Position is invalid\n");
        else
        {
            enqueu(queue,n,var);
        }
    }
    printf("\nGiven Queue is\n");
    display(queue);
    printf("\n\nFCFS Algorithm\n");
    seek=FCFS(queue,n);
    printf("Total seek time is %d\n",seek);
    avg=seek/(float)n;
    printf("Average seek time is %f\n",avg);
    return 0;
}
