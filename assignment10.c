/*
Problem Statement 10:
Implement the C program for Disk Scheduling Algorithms: SSTF, SCAN, and C-LOOK
considering the initial head position moving away from the spindle.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void SSTF() {
    int n, head, total=0;
    printf("Enter no. of requests: "); scanf("%d",&n);
    int rq[n], done[n];
    printf("Enter requests: ");
    for(int i=0;i<n;i++){ scanf("%d",&rq[i]); done[i]=0; }
    printf("Enter initial head: "); scanf("%d",&head);

    for(int k=0;k<n;k++){
        int min=9999, idx=-1;
        for(int i=0;i<n;i++){
            if(!done[i] && abs(rq[i]-head)<min){
                min=abs(rq[i]-head); idx=i;
            }
        }
        total+=min; head=rq[idx]; done[idx]=1;
        printf("%d ", head);
    }
    printf("\nTotal Head Movement = %d\n", total);
}

void SCAN() {
    int n, head, size, dir, total=0;
    printf("Enter no. of requests: "); scanf("%d",&n);
    int rq[n];
    printf("Enter requests: ");
    for(int i=0;i<n;i++) scanf("%d",&rq[i]);
    printf("Enter initial head: "); scanf("%d",&head);
    printf("Enter disk size: "); scanf("%d",&size);
    printf("Direction (1=right, 0=left): "); scanf("%d",&dir);

    qsort(rq,n,sizeof(int),compare);
    int i;
    for(i=0;i<n;i++) if(rq[i]>head) break;

    if(dir){
        for(int j=i;j<n;j++){ total+=abs(rq[j]-head); head=rq[j]; printf("%d ",head); }
        total+=abs((size-1)-head); head=size-1;
        for(int j=i-1;j>=0;j--){ total+=abs(rq[j]-head); head=rq[j]; printf("%d ",head); }
    } else {
        for(int j=i-1;j>=0;j--){ total+=abs(rq[j]-head); head=rq[j]; printf("%d ",head); }
        total+=abs(head-0); head=0;
        for(int j=i;j<n;j++){ total+=abs(rq[j]-head); head=rq[j]; printf("%d ",head); }
    }
    printf("\nTotal Head Movement = %d\n", total);
}

void CLOOK() {
    int n, head, dir, total=0;
    printf("Enter no. of requests: "); scanf("%d",&n);
    int rq[n];
    printf("Enter requests: ");
    for(int i=0;i<n;i++) scanf("%d",&rq[i]);
    printf("Enter initial head: "); scanf("%d",&head);
    printf("Direction (1=right, 0=left): "); scanf("%d",&dir);

    qsort(rq,n,sizeof(int),compare);
    int i; for(i=0;i<n;i++) if(rq[i]>head) break;

    if(dir){
        for(int j=i;j<n;j++){ total+=abs(rq[j]-head); head=rq[j]; printf("%d ",head); }
        for(int j=0;j<i;j++){ total+=abs(rq[j]-head); head=rq[j]; printf("%d ",head); }
    } else {
        for(int j=i-1;j>=0;j--){ total+=abs(rq[j]-head); head=rq[j]; printf("%d ",head); }
        for(int j=n-1;j>=i;j--){ total+=abs(rq[j]-head); head=rq[j]; printf("%d ",head); }
    }
    printf("\nTotal Head Movement = %d\n", total);
}

int main() {
    int ch;
    while(1){
        printf("\n1:SSTF  2:SCAN  3:C-LOOK  4:Exit\nEnter choice: ");
        scanf("%d",&ch);
        if(ch==1) SSTF();
        else if(ch==2) SCAN();
        else if(ch==3) CLOOK();
        else break;
    }
}
