/*
Problem Statement 10:
Implement the C program for Disk Scheduling Algorithms: SSTF, SCAN, and C-LOOK
considering the initial head position moving away from the spindle.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cmp(const void *a,const void *b){ return (*(int*)a - *(int*)b); }

void SSTF(){
    int n,h; printf("n: "); scanf("%d",&n);
    int r[n],v[n],t=0; for(int i=0;i<n;i++){scanf("%d",&r[i]);v[i]=0;}
    printf("head: "); scanf("%d",&h);
    for(int k=0;k<n;k++){
        int min=9999,idx=-1;
        for(int i=0;i<n;i++)
            if(!v[i] && abs(r[i]-h)<min){ min=abs(r[i]-h); idx=i; }
        t+=min; h=r[idx]; v[idx]=1; printf("%d ",h);
    }
    printf("\nMove=%d\n",t);
}

void SCAN(){
    int n,h,s,d,t=0; printf("n: "); scanf("%d",&n);
    int r[n]; for(int i=0;i<n;i++) scanf("%d",&r[i]);
    printf("head: "); scanf("%d",&h);
    printf("size: "); scanf("%d",&s);
    printf("dir(1→): "); scanf("%d",&d);
    qsort(r,n,sizeof(int),cmp);
    int i=0; while(i<n && r[i]<h) i++;
    if(d){
        for(int j=i;j<n;j++){ t+=abs(r[j]-h); h=r[j]; printf("%d ",h); }
        t+=abs(s-1-h); h=s-1;
        for(int j=i-1;j>=0;j--){ t+=abs(r[j]-h); h=r[j]; printf("%d ",h); }
    }else{
        for(int j=i-1;j>=0;j--){ t+=abs(r[j]-h); h=r[j]; printf("%d ",h); }
        t+=abs(h-0); h=0;
        for(int j=i;j<n;j++){ t+=abs(r[j]-h); h=r[j]; printf("%d ",h); }
    }
    printf("\nMove=%d\n",t);
}

void CLOOK(){
    int n,h,d,t=0; printf("n: "); scanf("%d",&n);
    int r[n]; for(int i=0;i<n;i++) scanf("%d",&r[i]);
    printf("head: "); scanf("%d",&h);
    printf("dir(1→): "); scanf("%d",&d);
    qsort(r,n,sizeof(int),cmp);
    int i=0; while(i<n && r[i]<h) i++;
    if(d){
        for(int j=i;j<n;j++){ t+=abs(r[j]-h); h=r[j]; printf("%d ",h); }
        for(int j=0;j<i;j++){ t+=abs(r[j]-h); h=r[j]; printf("%d ",h); }
    }else{
        for(int j=i-1;j>=0;j--){ t+=abs(r[j]-h); h=r[j]; printf("%d ",h); }
        for(int j=n-1;j>=i;j--){ t+=abs(r[j]-h); h=r[j]; printf("%d ",h); }
    }
    printf("\nMove=%d\n",t);
}

int main(){
    int ch;
    while(1){
        printf("\n1:SSTF 2:SCAN 3:CLOOK 4:Exit\n");
        scanf("%d",&ch);
        if(ch==1) SSTF();
        else if(ch==2) SCAN();
        else if(ch==3) CLOOK();
        else break;
    }
}
