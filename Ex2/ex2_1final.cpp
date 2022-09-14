#include <iostream>
#include <vector>
#include <stdio.h>

//longest increasing subsequence algorithm taken from geeks for geeks

// Binary search (note boundaries in the caller) 
int CeilIndex(std::vector<int>& v, int l, int r, int key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (v[m] >= key)
            r = m;
        else
            l = m;
    }
 
    return r;
}
int CeilIndex2(std::vector<int>& v, int l, int r, int key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (v[m] <= key)
            r = m;
        else
            l = m;
    }
 
    return r;
}
 
int LongestIncreasingSubsequenceLength(std::vector<int>& v, int B[], int **C)
{ 
    int u;
    if (v.size() == 0)
        return 0;
 
    std::vector<int> tail(v.size(), 0);
    int length = 1; // always points empty slot in tail
 
    tail[0] = v[0];
    B[0] = 1;
    C[0][0] = tail[length-1];
    C[0][1] = length;
    for (size_t i = 1; i<v.size(); i++) {
 
        // new smallest value
        if (v[i] < tail[0])
            {tail[0] = v[i];
            B[i] = 1;
            }
 
        // v[i] extends largest subsequence
        else if (v[i] > tail[length - 1])
            {tail[length++] = v[i];
            B[i] = length;}
 
        // v[i] will become end candidate of an existing
        // subsequence or Throw away larger elements in all
        // LIS, to make room for upcoming greater elements
        // than v[i] (and also, v[i] would have already
        // appeared in one of LIS, identify the location
        // and replace it)
        else
            {u = CeilIndex(tail, -1, length - 1, v[i]);
            tail[u] = v[i];
            B[i] = u+1;}
    C[i][0] = tail[length-1];
    C[i][1] = length;
    }
    return length;
}

int LongestDecreasingSubsequenceLength(std::vector<int>& v,int D[],int **E)
{
    int u;
    if (v.size() == 0)
        return 0;
 
    std::vector<int> tail(v.size(), 0);
    int length = 1; // always points empty slot in tail
 
    tail[0] = v[0];
    D[0] = 1;
    E[0][0] = tail[length-1];
    E[0][1] = length;
    for (size_t i = 1; i <v.size(); i++) {
 
        // new smallest value
        if (v[i] > tail[0])
           { tail[0] = v[i];
           D[i] = 1; }
 
        // v[i] extends largest subsequence
        else if (v[i] < tail[length - 1])
            { tail[length++] = v[i];
            D[i] = length; }
 
        // v[i] will become end candidate of an existing
        // subsequence or Throw away larger elements in all
        // LIS, to make room for upcoming greater elements
        // than v[i] (and also, v[i] would have already
        // appeared in one of LIS, identify the location
        // and replace it)
        else
           { u = CeilIndex2(tail, -1, length - 1, v[i]);
            tail[u] = v[i];
            D[i] = u+1;}
           E[i][0] = tail[length-1];
           E[i][1] = length;
    }
    return length;
}
 
int main(int argc, char **argv){
    //FILE *input;
    //input = fopen(argv[1], "r");
    int N, k, j;
    std::vector<int> v;
    scanf("%d", &N);
    scanf("%d", &k);
    //std::vector<int> v{ 1,2,5,8,10 };
    int* A = new int[N];
    for (int i=0; i<N; i++){
        scanf("%d", &A[i]);
    }
    for(int i = 0; i<N; i++) 
    v.push_back(A[i]);
    int* B = new int[N];
    int** C = new int*[N];
    for(int i = 0; i < N; ++i)
    C[i] = new int[2];
    int* D = new int[N];
    int** E = new int*[N];
    for(int i = 0; i < N; ++i)
    E[i] = new int[2];
    //for (int i=0; i<N; i++){
    //    B[i][0] = v[i];
    //}
    std::vector<int> x;
    for(int i = (N-1); i >= 0; i--) 
    x.push_back(v[i]+k);
    //for (int i=0; i<N; i++){
     //   D[i][0] = x[i];
    //}
    int y,z;
    /*std::cout << "Length of Longest Increasing Subsequence is "
              << LongestIncreasingSubsequenceLength(v,B,C) << '\n';
              std::cout << "Length of Longest Decreasing Subsequence is "
              << LongestDecreasingSubsequenceLength(x,D,E) << '\n';*/
              y = LongestIncreasingSubsequenceLength(v,B,C);
              z = LongestDecreasingSubsequenceLength(x,D,E);
     /*         for (int i=0; i<N; i++){
        std::cout << B[i] << "\n";
    }
    for (int i=0; i<N; i++){
        std::cout << v[i] << "\n";
    }
     for (int i=0; i<N; i++){
        std::cout << C[i][0] << " " << C[i][1] << "\n";
    }
            for (int i=0; i<N; i++){
        std::cout << D[i] << "\n";
    }
    for (int i=0; i<N; i++){
        std::cout << x[i] << "\n";
    }
    for (int i=0; i<N; i++){
      std::cout << E[i][0] << " " << E[i][1] << "\n";
    } */
    int exit = std::max(C[N-1][1], E[0][1]);
    for (int i=0; i<N-1; i++){
        if (E[N-2-i][0] > C[i][0])
        exit = std::max(C[i][1] + E[N-2-i][1], exit);
        if (v[i+1] + k > v[i])
        exit = std::max(B[i] + D[N-2-i], exit);
    }
    std::cout << exit << "\n";
    return 0;
}