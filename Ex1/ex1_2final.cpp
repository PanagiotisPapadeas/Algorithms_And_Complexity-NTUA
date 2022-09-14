#include <iostream>
using namespace std;

void makeArray(int N, int A[], int B[], int y, int K){
   //if (y+2>=N) return;
   //else {
       int sum = 0;
       for (int u=y+2; u<N; u++){
           sum = sum + A[u];
           if (sum >= K) break;
           if ((u-y-1)<B[sum] || B[sum]==0) B[sum] = u-y-1;}
    return;
   //}
}

/*int main(){
    int A[4] = {1,2,3,4};
    int B[8] = {0,0,0,0,0,0,0,0};
    makeArray(4, A, B, 2);
    for (int i=0; i<8; i++){
        cout << B[i] << " ";
    }
}*/
int main(){
    //clock_t tStart = clock();
    int x,y,sum,targ,final,steps,stepers,N,K;
    //FILE *input;
    //input = fopen(argv[1], "r");
    scanf("%d", &N);
    scanf("%d", &K);
    int *A = new int[N];
    int *B = new int[K]{0};
    for (int i=0; i<N; i++){
        scanf("%d", &A[i]);
    }
    /*for (int i=0; i<K; i++){
        B[i] = 0;
    }*/
    final = 20005;
    for (y=N-1; y>=0; y--){
         if (y+2<N) makeArray(N, A, B, y, K);
         sum = 0;
         for (x=y; x>=0; x--){
             sum = sum + A[x];
             steps = y-x+1;
             if (sum == K){ if (steps < final) final = steps;}
             else {targ = K - sum;
             if (targ>0 && B[targ]!=0){
                 stepers = steps + B[targ];
                 if (stepers < final) final = stepers; /*cout << final << " ";*/
             }
             }
         }
    }
    /*for (int i=0; i<9; i++){
        cout << B[i] << " ";
    }*/
    //cout << "\n";
    if (final == 20005) final = -1;
    cout << final << "\n";
    //printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}