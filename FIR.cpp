//使用二维数组构建棋盘 1为玩家，-1为计算机，0为空
//使用imp数组判断比重实现简单机器下棋
#include <iostream>
#include<Windows.h>
#include<conio.h>
using namespace std;
const int width = 18;
const int height = 9;
struct Index
{
    int imp;
    int x;
    int y;
};
void PrintBoard(int board[height][width]) {//打印棋盘
    printf("18*9\n");
    for (int i = 0; i < height; i++) {
        printf("|");
        for (int j = 0; j < width; j++) {
            
            if (board[i][j] == 1) {
                printf("O|");
            }
            else if (board[i][j] == -1) {
                printf("X|");
            }
            else {
                printf(" |");
            }
        }
        printf("\n");
        for (int j = 0; j < width*2; j++) {
            printf("-");
        }
        printf("\n");
    }
}
int IsWin(int board[height][width]) {
    int sum_x = 0;//玩家win和为5，机器为-5
    int sum_y = 0;
    int sum_z = 0;
    for (int i = 0; i < height-4; i++) {//横向判断是否win
        for (int j = 0; j < width-4; j++) {
            for (int z = 0; z < 5; z++) {
                sum_x += board[i][j+z];//横向
                sum_y += board[i+z][j];//纵向
                sum_z += board[i + z][j + z];//斜向
            }
            if (sum_x == 5 || sum_y == 5 || sum_z == 5) {
                //玩家win
                return 1;
            }
            else if (sum_x == -5 || sum_y == -5 || sum_z == -5) {
                //机器win
                return -1;
            }
        }
    }
    return 0;
}
void GoImp(int sum_x,int sum_y,int sum_z,int y,int x,int imp[height][width],int board[height][width]) {
    //权重计算并赋值,将八个方向的数值相加

    for (int z = -5; z < 5; z++) {
        
        if (x + z >= 0) {
            sum_x += abs(board[y][x + z]);//横向
        }
        
        if (y + z >= 0) {
            sum_y += abs(board[y + z][x]);//纵向
        }
        if (x + z >= 0 && y + z >= 0) {
            sum_z += abs(board[y + z][x + z]);//斜向
        }
    }

    imp[y][x] = abs(sum_x) + abs(sum_y) + abs(sum_z);
}
void Computer(int board[height][width], int imp[height][width]) {
    Index index = {0,0,0};//用以标记权重最大的位置
    int sum_x = 0;//根据数值来进行imp赋值，越小或越大imp越大，优先越大出棋
    int sum_y = 0;
    int sum_z = 0;
    for (int i = 0; i < height-4; i++) {
        for (int j = 0; j < width-4; j++) {
            
                GoImp(sum_x, sum_y, sum_z, i, j, imp,board);
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            //遍历权重后选取最高的位置出棋
            if (imp[i][j] > index.imp && board[i][j]==0) {
                index.y = i;
                index.x = j;
                goto end;
            }
        }
    }
    end:
    board[index.y][index.x] = -1;
}
int main()
{
    int ret = -2;
    int y=0, x=0;
    int board[height][width] = { 0 };
    int imp[height][width] = { 0 };
    while (true)
    {
        PrintBoard(board);
        printf("出棋位置:");
        scanf_s("%d %d", &x, &y);
        x -= 1;
        y -= 1;
        if (x > 17 || y > 9 || x < 0 || y < 0||board[y][x]!=0) {
            printf("超出范围或已被占用");
            Sleep(500);
            system("cls");
            continue;
        }
        board[y][x] = 1;

        system("cls");
        //机器出棋
        Computer(board,imp);

        {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    printf("%d",imp[i][j]);
                }
                printf("\n");
            }
        }

        ret = IsWin(board);
        if (ret == 1) {
            printf("you win");
            return 0;
        }
        else if (ret == -1) {
            printf("you lose");
            return 0;
        }
    }
    
    
}

