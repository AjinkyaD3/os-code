#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cmp(const void *a,const void *b){ return *(int*)a - *(int*)b; }

void SSTF(){
    int n,head;
    scanf("%d",&n);
    int req[n], done[n], total=0;
    for(int i=0;i<n;i++){ scanf("%d",&req[i]); done[i]=0; }
    scanf("%d",&head);

    for(int k=0;k<n;k++){
        int best=-1, dist=1e9;
        for(int i=0;i<n;i++)
            if(!done[i] && abs(req[i]-head)<dist)
                dist=abs(req[i]-head), best=i;
        total+=dist; head=req[best]; done[best]=1;
        printf("%d ", head);
    }
    printf("\nMove=%d\n", total);
}

void SCAN(){
    int n,head,size,dir, total=0;
    scanf("%d",&n);
    int req[n];
    for(int i=0;i<n;i++) scanf("%d",&req[i]);
    scanf("%d%d%d",&head,&size,&dir);

    qsort(req,n,sizeof(int),cmp);
    int pos=0; while(pos<n && req[pos]<head) pos++;

    if(dir==1){
        for(int i=pos;i<n;i++) total+=abs(req[i]-head), head=req[i], printf("%d ",head);
        total+=abs((size-1)-head); head=size-1;
        for(int i=pos-1;i>=0;i--) total+=abs(req[i]-head), head=req[i], printf("%d ",head);
    }
    else{
        for(int i=pos-1;i>=0;i--) total+=abs(req[i]-head), head=req[i], printf("%d ",head);
        total+=abs(head-0); head=0;
        for(int i=pos;i<n;i++) total+=abs(req[i]-head), head=req[i], printf("%d ",head);
    }
    printf("\nMove=%d\n", total);
}

void CLOOK(){
    int n,head,dir,total=0;
    scanf("%d",&n);
    int req[n];
    for(int i=0;i<n;i++) scanf("%d",&req[i]);
    scanf("%d%d",&head,&dir);

    qsort(req,n,sizeof(int),cmp);
    int pos=0; while(pos<n && req[pos]<head) pos++;

    if(dir==1){
        for(int i=pos;i<n;i++) total+=abs(req[i]-head), head=req[i], printf("%d ",head);
        for(int i=0;i<pos;i++) total+=abs(req[i]-head), head=req[i], printf("%d ",head);
    }
    else{
        for(int i=pos-1;i>=0;i--) total+=abs(req[i]-head), head=req[i], printf("%d ",head);
        for(int i=n-1;i>=pos;i--) total+=abs(req[i]-head), head=req[i], printf("%d ",head);
    }
    printf("\nMove=%d\n", total);
}

int main(){
    int ch;
    while(1){
        printf("\n1:SSTF 2:SCAN 3:CLOOK 4:Exit\n");
        scanf("%d",&ch);
        if(ch==1) SSTF();
        else if(ch==2) SCAN();
        else if(ch==3) CLOOK();
        else return 0;
    }
}
