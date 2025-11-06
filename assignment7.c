#include <stdio.h>

int main() {
    int n,m;
    printf("Enter processes and resources: ");
    scanf("%d %d",&n,&m);

    int alloc[n][m], max[n][m], need[n][m], avail[m];
    printf("Enter Allocation:\n");
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) scanf("%d",&alloc[i][j]);

    printf("Enter Max:\n");
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) scanf("%d",&max[i][j]);

    printf("Enter Available:\n");
    for(int j=0;j<m;j++) scanf("%d",&avail[j]);

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int done[n], safe[n], idx=0;
    for(int i=0;i<n;i++) done[i]=0;

    while(idx<n){
        int found=0;
        for(int i=0;i<n;i++){
            if(!done[i]){
                int ok=1;
                for(int j=0;j<m;j++)
                    if(need[i][j] > avail[j]) ok=0;
                if(ok){
                    for(int j=0;j<m;j++) avail[j]+=alloc[i][j];
                    safe[idx++] = i;
                    done[i]=1;
                    found=1;
                }
            }
        }
        if(!found){ printf("Unsafe\n"); return 0; }
    }

    printf("Safe Sequence: ");
    for(int i=0;i<n;i++) printf("P%d ",safe[i]);
}