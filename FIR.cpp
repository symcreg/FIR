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
void PrintBoard(int board[height][width]);//打印棋盘
int IsWin(int board[height][width]);//是否输赢
int MaxOf(int, int, int, int, int, int, int, int);//取出八方权值的最大值
void GetImp(int y, int x, int imp[height][width], int board[height][width]);//计算权值
void Computer(int board[height][width], int imp[height][width]);//ai出棋
int main()
{
    int ret = -2;
    int y = 0, x = 0;
    int board[height][width] = { 0 };
    int imp[height][width] = { 0 };
    while (true)
    {
        PrintBoard(board);
        printf("出棋位置:");
        scanf_s("%d %d", &x, &y);
        x -= 1;
        y -= 1;
        if (x > 17 || y > 9 || x < 0 || y < 0 || board[y][x] != 0) {
            printf("超出范围或已被占用");
            Sleep(500);
            system("cls");
            continue;
        }
        board[y][x] = 1;

        system("cls");

        //机器出棋
        Computer(board, imp);

        {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    printf("%d", imp[i][j]);
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
int MaxOf(int sum_up ,int sum_down ,int sum_left ,int sum_right ,int sum_UpRight ,int sum_UpLeft ,int sum_DownRight ,int sum_DownLeft) {
    int nums = 8;
    int max = 0;
    int t[8] = { sum_up , sum_down , sum_left , sum_right , sum_UpRight , sum_UpLeft , sum_DownRight , sum_DownLeft };
    for (int i = 0; i < nums; i++) {
        if (max < t[i]) {
            max = t[i];
        }
    }
    return max;
}
void GetImp(int y,int x,int imp[height][width],int board[height][width]) {
    
    //权值计算,八方相加
    int color = -3;
    int sum_left = 0;
    int sum_right = 0;
    int sum_up = 0;
    int sum_down = 0;
    int sum_UpLeft = 0;
    int sum_UpRight = 0;
    int sum_DownLeft = 0;
    int sum_DownRight = 0;
    //计算左方的权值
    for (int i = 1;x-i>=0; i++) {
        if (board[y][x - i] == 0) {//相邻为空
            break;
        }
        else if (board[y][x-i]==color||color==-3) {//相邻相同颜色的棋子
            color = board[y][x - i];
            sum_left++;
        }
        else {//遇到颜色不同的棋子
            break;
        }
    }
    //计算右方的权值
    color = -3;
    for (int i = 1; x + i < width; i++) {
        if (board[y][x + i] == 0) {//相邻为空
            break;
        }
        else if (board[y][x + i] == color || color == -3) {//相邻相同颜色的棋子
            color = board[y][x + i];
            sum_right++;
        }
        else {//遇到颜色不同的棋子
            break;
        }
    }
    //计算上方的权值
    color = -3;
    for (int i = 1; y - i >= 0; i++) {
        if (board[y-i][x] == 0) {//相邻为空
            break;
        }
        else if (board[y-i][x] == color || color == -3) {//相邻相同颜色的棋子
            color = board[y-i][x];
            sum_up++;
        }
        else {//遇到颜色不同的棋子
            break;
        }
    }
    //计算下方的权值
    color = -3;
    for (int i = 1; y + i < height; i++) {
        if (board[y + i][x] == 0) {//相邻为空
            break;
        }
        else if (board[y + i][x] == color || color == -3) {//相邻相同颜色的棋子
            color = board[y + i][x];
            sum_down++;
        }
        else {//遇到颜色不同的棋子
            break;
        }
    }
    //计算左上方的权值
    color = -3;
    for (int i = 1; y - i >= 0&&x-i>=0; i++) {
        if (board[y - i][x-i] == 0) {//相邻为空
            break;
        }
        else if (board[y - i][x-i] == color || color == -3) {//相邻相同颜色的棋子
            color = board[y - i][x-i];
            sum_UpLeft++;
        }
        else {//遇到颜色不同的棋子
            break;
        }
    }
    //计算左下方的权值
    color = -3;
    for (int i = 1; y + i < height && x - i >= 0; i++) {
        if (board[y + i][x - i] == 0) {//相邻为空
            break;
        }
        else if (board[y + i][x - i] == color || color == -3) {//相邻相同颜色的棋子
            color = board[y + i][x-i];
            sum_DownLeft++;
        }
        else {//遇到颜色不同的棋子
            break;
        }
    }
    //计算右上方的权值
    color = -3;
    for (int i = 1; y - i >= 0 && x + i < width; i++) {
        if (board[y - i][x + i] == 0) {//相邻为空
            break;
        }
        else if (board[y - i][x + i] == color || color == -3) {//相邻相同颜色的棋子
            color = board[y - i][x+i];
            sum_UpRight++;
        }
        else {//遇到颜色不同的棋子
            break;
        }
    }
    //计算右下方的权值
    color = -3;
    for (int i = 1; y + i < height && x + i < width; i++) {
        if (board[y + i][x + i] == 0) {//相邻为空
            break;
        }
        else if (board[y + i][x + i] == color || color == -3) {//相邻相同颜色的棋子
            color = board[y + i][x + i];
            sum_DownRight++;
        }
        else {//遇到颜色不同的棋子
            break;
        }
    }
    imp[y][x] = MaxOf(sum_up, sum_down, sum_left, sum_right, sum_UpRight, sum_UpLeft, sum_DownRight, sum_DownLeft);
}
void Computer(int board[height][width], int imp[height][width]) {
    Index index = {0,0,0};//用以标记权值最大的位置
    //根据imp权值下棋
    //首先初始化imp数组
    memset(imp, 0, sizeof(imp));
    for (int i = 0; i < height; i++) {//遍历计算权值
        for (int j = 0; j < width; j++) {
            if (board[i][j] == 0) {//该位置为空，计算权值
                GetImp(i, j, imp, board);
            }
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            //遍历权值后选取权值最高的位置
            if (imp[i][j] > index.imp&&board[i][j]==0) {
                index.imp = imp[i][j];
                index.y = i;
                index.x = j;
            }
        }
    }
    cout << "y x" << index.y+1 << " " << index.x+1 << endl;
    board[index.y][index.x] = -1;//下棋
}

