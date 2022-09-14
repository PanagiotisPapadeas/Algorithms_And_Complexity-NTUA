#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define nf 3115098112
#define mN 5001
#define mM 1501







std::vector <std::pair<int, unsigned long> > arr[4][4];
std::vector <unsigned long> chosen[4][4];
int N, M, A;
unsigned long P;
unsigned long int k_arr[mM+1][mN+1];







void knapsack(int ind, int item) {
    int G = arr[ind][item].size();
    int H = N;
    for(int j = 1; j <= H; j++)
        k_arr[0][j] = nf;   
    for(int i = 0; i <= G; i++)
        k_arr[i][0] = 0;
    for(int i = 1; i <= G; i++) {
        int howmuch = arr[ind][item][i-1].first;
        int pay    = arr[ind][item][i-1].second;
        for(int j = 1; j <= H; j++)
            k_arr[i][j] = std::min(k_arr[i-1][std::max(0,j-howmuch)] + pay, k_arr[i-1][j]);
    }
    for(int j = 0; j <= H; j++)
        chosen[ind][item].push_back(k_arr[G][j]);
}

int main(int argc, char **argv) {
    FILE *input;
    input = fopen(argv[1], "r");
    fscanf(input, "%d %d", &N, &M);
    for(int i = 0; i < M; i++) {
        int ind;
        fscanf(input, "%d", &ind);
        //char ch = getchar();
        char ch;
        fscanf(input, "%c", &ch);
        int item;
        /*switch(ch) {
            case 'A': item = 1; break;
            case 'B': item = 2; break;
            case 'C': item = 3; break;
        }*/
        if (ch == 'A') item = 1;
        else if (ch == 'B') item = 2;
        else if (ch == 'C') item = 3;
        fscanf(input, "%d %lu", &A, &P);
        arr[ind][item].push_back(std::make_pair(A,P));
    }
    for(int i = 1; i <= 3; i++)
        for(int j = 1; j <= 3; j++)
            knapsack(i,j);
    for(int i = 1; i <= 3; i++)
        for(int j = 0; j <= N; j++) 
            chosen[i][1][j] += chosen[i][2][j] + chosen[i][3][j];
    unsigned long exit = nf;
    for(int i = 0; i <= N; i++)
        for(int j = 0; j <= N; j++)
            if(N-i-j >= 0)
                exit = std::min(exit, chosen[1][1][i] + chosen[2][1][j] + chosen[3][1][N-i-j]);
            else
                exit = std::min(exit, chosen[1][1][i] + chosen[2][1][j]);
    if(exit == nf)
        printf("%d\n", -1);
    else
        printf("%lu\n", exit);
}