#pragma once
#include <iostream>
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
