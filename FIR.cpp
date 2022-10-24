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
    for (int i = 0; i < height; i++) {//横向判断是否win
        for (int j = 0; j < width; j++) {
            sum_x = 0;
            sum_y = 0;
            sum_z = 0;
            for (int z = 0; z < 5; z++) {
                if (j + z >= 0&&j+z<width) {
                    sum_x += board[i][j + z];//横向
                }

                if (i + z >= 0&&i+z<height) {
                    sum_y += board[i + z][j];//纵向
                }
                if (j + z >= 0 && i + z >= 0&&j+z<width&&i+z<height) {
                    sum_z += board[i + z][j + z];//斜向
                }
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
void GoImp(int y,int x,int imp[height][width],int board[height][width]) {
    //权重计算并赋值,将八个方向的数值相加
    int sum_x = 0;
    int sum_y = 0;
    int sum_z = 0;
    for (int z = -5; z < 5; z++) {
        
        if (x + z >= 0 && x + z < width ) {
            sum_x += abs(board[y][x + z]);//横向
        }
        
        if (y + z >= 0 && y + z < height) {
            sum_y += abs(board[y + z][x]);//纵向
        }
        if (x + z >= 0 && y + z >= 0 && x + z < width && y + z < height) {
            sum_z += abs(board[y + z][x + z]);//斜向
        }
    }

    imp[y][x] = abs(sum_x) + abs(sum_y) + abs(sum_z);
    for (int z = 0;y-z>=0; z++) {
        if (y-z > 0) {
            if (board[y-z - 1][x] != 0 || board[y+z + 1][x] != 0 || board[y+z + 1][x+z + 1] != 0) {
                imp[y][x]++;
            }
        }
        if (x-z > 0) {
            if (board[y][x - z - 1] != 0 || board[y][x+z + 1] != 0 || board[y+z + 1][x+z + 1] != 0) {
                imp[y][x]++;
            }
        }
        if (y-z > 0 && x-z > 0) {
            if (board[y-z - 1][x-z - 1] != 0) {
                imp[y][x]++;
            }
        }
    }
}
void Computer(int board[height][width], int imp[height][width]) {
    Index index = {0,0,0};//用以标记权重最大的位置
    //根据数值来进行imp赋值，越小或越大imp越大，优先越大出棋
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            
                GoImp( i, j, imp,board);
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

