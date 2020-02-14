// 게리멘더링
// 비트마스크로 시간초과 해결

#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>

int wards[10][10], trace[10];

int eq(std::vector<int> a, std::vector<int> b);
int isThatGroup(std::vector<int> smallgroup, int N);
int isItThere(int a, std::vector<int> table);

int main () {
    int N, inp, edges, sgNum, tempAns, bitCal, bitmask = 1, all = 0, ans = 2147000000;
    int citizen[10];
    std::vector<int> A, B;
    scanf("%d", &N);
    for(int i = 0; i < N; ++i){
        scanf("%d", &citizen[i]);
        all += citizen[i];
    }
    for(int i = 0; i < N; ++i){
        scanf("%d", &edges);
        for(int j = 0; j < edges; ++j){
            scanf("%d", &inp);
        wards[i][inp - 1] = 1;
        wards[inp - 1][i] = 1;
        }
    }
    for(int i = 0; i < N; ++i)
        bitmask *= 2;
    for(int i = 1; i <= bitmask - 2; ++i){
        bitCal = i;
        for(int j = 0; j < N; ++j){
            if(bitCal & 1)
                A.push_back(j);
            else 
                B.push_back(j);
            bitCal >>= 1;
        }
        if(isThatGroup(A, N) && isThatGroup(B, N)){
            sgNum = 0;
            for(int j = 0; j < A.size(); ++j)
                sgNum += citizen[A[j]];
            tempAns = (2 * sgNum - all < 0) ? all - 2 * sgNum : 2 * sgNum - all;
            ans = (ans > tempAns) ? tempAns : ans;
        }
        A.clear(); B.clear();
    }
    if(ans == 2147000000)
        printf("-1");
    else    
        printf("%d", ans);
}

int eq(std::vector<int> a, std::vector<int> b){
    int ans = 0;
    if(a.size() != b.size()) return 0;
    for(int i = 0; i < a.size(); ++i)
        ans += (a[i] == b[i]) ? 1 : 0;
    if(ans == a.size()) return 1;
    else         return 0;
}
int isThatGroup(std::vector<int> sg, int N){
    std::queue<int> bfs;
    std::vector<int> semiGroup;
    for(int i = 0; i < 10; ++i)
        trace[i] = 0;
    bfs.push(sg[0]);
    trace[sg[0]] = 1;
    while(!bfs.empty()){
        for(int i = 0; i < N; ++i){
            if(!trace[i] && isItThere(i, sg) && wards[bfs.front()][i] > 0){
                bfs.push(i);
                trace[i] = 1;
            }
        }
        semiGroup.push_back(bfs.front());
        bfs.pop();
    }
    std::sort(semiGroup.begin(), semiGroup.end());
    if(eq(semiGroup, sg)) return 1;
    else                   return 0;
}
int isItThere(int a, std::vector<int> table){
    for(int i = 0; i < table.size(); ++i)
        if(a == table[i]) return 1;
    return 0;
}
