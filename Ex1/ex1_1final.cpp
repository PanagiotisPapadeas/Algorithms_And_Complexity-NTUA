#include <iostream>
using namespace std;

struct subset {
    int parent;
    int rank;
};

int find(struct subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent
            = find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}

void Union(struct subset subsets[], int xroot, int yroot)
{
    if (subsets[xroot].rank < subsets[yroot].rank)
        {subsets[xroot].parent = yroot;
        subsets[yroot].rank++;}
    else if (subsets[xroot].rank > subsets[yroot].rank)
        {subsets[yroot].parent = xroot;
        subsets[xroot].rank++;}
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
    //cout << yroot << "parent=" << subsets[yroot].parent << "\n";
    //cout << xroot << "parent=" << subsets[xroot].parent << "rank=" << subsets[xroot].rank << "\n";
}


int binary_search(struct subset subsets[], int arr[], int **B, int l, int r, int &x, int v, int e){
    //cout << "yo";
    if (r>=l){
        int mid = l + (r-l)/2;
        //cout << "nah";
        //int mid = 0;
        //struct subset* subsets = (struct subset*)malloc(v*sizeof(struct subset));
        //cout << "cool";
        for (int q=1; q<=e; q++){
            subsets[q].parent = q;
            subsets[q].rank = 0;
        }
        //cout << "wa";
        int d = B[mid][2];
        int o;
        int p;
        for (int i=mid; i<v; i++){
        //if (B[i][2] <= B[mid][2]) 
        o = find(subsets, B[i][0]);
        p = find(subsets, B[i][1]);
        //cout << o << "  " << p << "   ";
        if (o!=p){
        Union(subsets, o, p);
        //else {break;}
        //cout << "ya";
        }
        }
        //cout << d << "=mid,";
        int u=-2;
        int k=-3;
        for (int j=0; j<e; j++){
        if (arr[j]!=(j+1)) {
            //cout << arr[j] << "=arr[j],";
            u = find(subsets, arr[j]);
            //cout << u << "=u,";
                k = find(subsets, j+1);
                //cout << k << "=k\n";
        if (k!=u) {
            //cout << "troller";
            return binary_search(subsets, arr, B, l, mid - 1, x, v, e);}
            }
        }
        x = d;
        //free(subsets);
        return binary_search(subsets, arr, B, mid + 1, r, x, v, e);
    }
    //cout << "kido";
    return x;
}

void swapRows(int **matrix, int row1, int row2) 
{
    std::swap(matrix[row1], matrix[row2]);
}
  
int partition (int **arr, int low, int high) 
{ 
    int pivot = arr[high][2];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) 
    { 
        if (arr[j][2] < pivot) 
        { 
            i++;
            swapRows(arr, i, j); 
        } 
    } 
    swapRows(arr, i+1, high); 
    return (i + 1); 
} 

void quickSort(int **arr, int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(arr, low, high); 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 
  
/* Function to print an array */
void printArray(int arr[][3], int size) 
{ 
    int i; 
    for (i = 0; i < size; i++) {
        cout << arr[i][0] << arr[i][1] << arr[i][2] << " "; 
    cout << endl; 
    }
} 

//int A[10001];
//int B[10001][3];
int main(){
    //FILE *input;
    //input = fopen(argv[1], "r");
    //int e=8;
    //int v=12;
    int e,v;
    scanf("%d", &e);
    scanf("%d", &v);
    int *A = new int[e];
    int** B = new int*[v];
    for(int i = 0; i < v; ++i)
    B[i] = new int[3];
    for (int i=0; i<e; i++){
        scanf("%d", &A[i]);
    }
    for (int i=0; i<v; i++){
        scanf("%d", &B[i][0]);
        scanf("%d", &B[i][1]);
        scanf("%d", &B[i][2]);
    }
    int x;
    int final;
    struct subset* subsets = (struct subset*)malloc(e*sizeof(struct subset));
    //int A[8] = {8, 5, 3, 7, 4, 1, 6, 2};
    //int B[12][3] = {1, 2, 52, 3, 2, 75, 5, 6, 29, 4, 5, 39, 7, 6, 78, 3, 1, 23, 1, 8, 46, 1, 6, 54, 3, 6, 72, 1, 7, 48, 3, 7, 36, 3, 5, 33};
    quickSort(B, 0, v-1);
    //printArray(B, v);
    //cout << "\n";
    final = binary_search(subsets, A, B, 0, v-1, x, v, e);
    //cout << "\n";
    cout << final << "\n";
}