#include<iostream>
int ans;
void findRoad(int (*house)[20], int row, int col, int size, int status);
int main () {
    int size, house[20][20];
    scanf("%d", &size);
    for(int i = 0; i < size; ++i)
    for(int j = 0; j < size; ++j)
        scanf("%d", &house[i][j]);
    
    findRoad(house, 0, 1, size, 1);

    printf("%d", ans);
    return 0;
}   //status:: 1 == '-', 2 == '\', 3 == '|'
void findRoad(int (*house)[20], int row, int col, int size, int status){
    if(row == size - 1 && col == size - 1){
        ++ans; return;
    }
    else if(row >= size || col >= size)
        return;
    if((status == 1 && house[row][col] == 1) ||
       (status == 2 && (house[row][col] == 1 || house[row - 1][col] == 1 || house[row][col - 1] == 1)) ||
       (status == 3 && house[row][col] == 1))
        return;
    if(status == 1){
        findRoad(house, row, col + 1, size, 1);
        findRoad(house, row + 1, col + 1, size, 2);
    }
    else if(status == 2){
        findRoad(house, row, col + 1, size, 1);
        findRoad(house, row + 1, col + 1, size, 2);
        findRoad(house, row + 1, col, size, 3);
    }
    else if(status == 3){
        findRoad(house, row + 1, col + 1, size, 2);
        findRoad(house, row + 1, col, size, 3);
    }
}
