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
void PrintBoard(int board[height][width]);//��ӡ����
int IsWin(int board[height][width]);//�Ƿ���Ӯ
int MaxOf(int, int, int, int, int, int, int, int);//ȡ���˷�Ȩֵ�����ֵ
void GetImp(int y, int x, int imp[height][width], int board[height][width]);//����Ȩֵ
void Computer(int board[height][width], int imp[height][width]);//ai����
