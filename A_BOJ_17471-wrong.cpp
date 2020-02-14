// 게리멘더링
// time out

#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>

int wards[10][10], trace[10];

int eq(int* a, int* b, int N);
int isThatGroup(int* smallgroup, int sgN, int N);
int isItThere(int a, int* table, int N);

int main () {
    int N, inp, edges, sgNum, all = 0, tempAns, ans = 2147000000;
    int citizen[10], combTable[10], A[10], B[10], traceA[10], traceB[10];
    scanf("%d", &N);
    for(int i = 0; i < N; ++i){
        scanf("%d", &citizen[i]);
        all += citizen[i];
    }
    for(int i = 0; i < N; ++i){
        scanf("%d", &edges);
        for(int j = 0; j < edges; ++j){
            scanf("%d", &inp);
        ++wards[i][inp - 1];
        }
    }
    for(int i = 1; i <= N / 2; ++i){
        for(int j = 0; j < N; ++j)
            combTable[j] = j;
        for(int j = 0; j < 10; ++j){
            traceA[j] = -1;
            traceB[j] = -1;
        }
        do{
            for(int j = 0; j < i; ++j)
                A[j] = combTable[j];
            for(int j = 0; j < N - i; ++j)
                B[j] = combTable[N - j - 1];
            std::sort(A, A + i); std::sort(B, B + N - i);
            if(eq(A, traceA, i) && eq(B, traceB, N - i))
                continue;
            for(int j = 0; j < i; ++j)
                traceA[j] = A[j];
            for(int j = 0; j < N - i; ++j)
                traceB[j] = B[j];
            if(isThatGroup(A, i, N) && isThatGroup(B, N - i, N)){
                sgNum = 0;
                for(int j = 0; j < i; ++j)
                    sgNum += citizen[A[j]];
                tempAns = (2 * sgNum - all < 0) ? all - 2 * sgNum : 2 * sgNum - all;
                ans = (ans > tempAns) ? tempAns : ans;
            }            
        }while(std::next_permutation(combTable, combTable + N));
    }
    if(ans == 2147000000)
        printf("-1");
    else    
        printf("%d", ans);
}

int eq(int* a, int* b, int N){
    int ans = 0;
    for(int i = 0; i < N; ++i)
        ans += (a[i] == b[i]) ? 1 : 0;
    if(ans == N) return 1;
    else         return 0;
}
int isThatGroup(int* sg, int sgN, int N){
    std::queue<int> bfs;
    int size = 0, semiGroup[10];
    for(int i = 0; i < 10; ++i)
        trace[i] = 0;
    bfs.push(sg[0]);
    ++trace[sg[0]];
    while(!bfs.empty()){
        for(int i = 0; i < N; ++i){
            if(!trace[i] && isItThere(i, sg, sgN) && wards[bfs.front()][i] > 0){
                bfs.push(i);
                trace[i] = 1;
            }
        }
        semiGroup[size++] = bfs.front();
        bfs.pop();
    }
    std::sort(semiGroup, semiGroup + size);
    if(eq(semiGroup, sg, sgN)) return 1;
    else                   return 0;
}
int isItThere(int a, int* table, int N){
    for(int i = 0; i < N; ++i)
        if(a == table[i]) return 1;
    return 0;
}
