//
// Created by Calun on 2021/1/12.
//

#include "migong.h"
#include <stdio.h>
#include <stdlib.h>
#define MIGONG_SIZE 70
#include <time.h>


/* 生成迷宫，并利用迪杰斯特拉算法求给定两点间的最短路径 */
int maze[MIGONG_SIZE + 2][MIGONG_SIZE + 2];

//从1到10：10
//从10到1：10
//从1到1：1
//从10到10：10
int distance(int a,int b)
{
    if(a==0)
    {
        return 0;
    }
    if(b==10&&a==10)
    {
        return 1;
    }
    if(a==1&&b==1)
    {
        return 1;
    }
    if(a==10&&b==1)
    {
        return 10;
    }
    if(a==1&&b==10)
    {
        return 10;
    }
}


int point_to_index(int x, int y)
{
    return y * MIGONG_SIZE + x;
}


int migong_main()
{
    FILE* save_file = fopen("migong.txt", "w+");
    //生成伪随机迷宫

    //srand(time(NULL));
    for(int i=0; i < MIGONG_SIZE + 2; i++)
    {
        for(int j=0; j < MIGONG_SIZE + 2; j++)
        {
            if(i==0 ||j==0 || i == MIGONG_SIZE + 1 || j == MIGONG_SIZE + 1)
            {
                maze[i][j]=0;
                printf("  ");
                fprintf(save_file,"  ");
            }
            else
            {
                maze[i][j]=rand()%3;
                if(maze[i][j]==1)
                {
                    printf("壹");
                    fprintf(save_file, "壹");
                }
                if(maze[i][j]==2)
                {
                    printf("拾");
                    fprintf(save_file, "拾");
                    maze[i][j]=10;
                }
                if(maze[i][j]==0)
                {
                    printf("〇");
                    fprintf(save_file,"〇");
                }
            }

        }
        printf("\n");
        fprintf(save_file, "\n");
    }

    //生成list表示图 顺序 左右上下 每个占4个位置 1,10表示有路 0表示没有
    int mazelist[MIGONG_SIZE * MIGONG_SIZE][4];
    for(int i=0; i < MIGONG_SIZE * MIGONG_SIZE; i++)
    {
        //mazelist[i]=maze[1+i/20][1+i%20] 第i个数对应的在maze矩阵中的位置
        if(maze[1+ i / MIGONG_SIZE][1 + i % MIGONG_SIZE] == 0)
        {
            mazelist[i][0]=0;mazelist[i][1]=0;mazelist[i][2]=0;mazelist[i][3]=0;
        }
        else{
            int b=maze[1+ i / MIGONG_SIZE][1 + i % MIGONG_SIZE];
            mazelist[i][0]=distance(maze[1+ i / MIGONG_SIZE][i % MIGONG_SIZE], b);
            mazelist[i][1]=distance(maze[1+ i / MIGONG_SIZE][2 + i % MIGONG_SIZE], b);
            mazelist[i][2]=distance(maze[i / MIGONG_SIZE][1 + i % MIGONG_SIZE], b);
            mazelist[i][3]=distance(maze[2+ i / MIGONG_SIZE][1 + i % MIGONG_SIZE], b);
            //printf("\n第%d个节点，%d,%d,%d,%d.",i,mazelist[i][0],mazelist[i][1],mazelist[i][2],mazelist[i][3]);
        }
    }

    //生成visited list
    int visited[MIGONG_SIZE * MIGONG_SIZE][3];
    for (int i = 0; i < MIGONG_SIZE * MIGONG_SIZE; i++)
    {
        visited[i][0]=0;//0：未被访问；1：被访问
        visited[i][1]=-1;//上一个节点是哪个
        visited[i][2]=999999;//Dist,从第一个节点到该节点的距离
        if(maze[1+ i / MIGONG_SIZE][i % MIGONG_SIZE] == 0)
            visited[i][1]=-2;
    }
    visited[0][0]=1;visited[0][2]=0;
    //设置起始点，终止点
    int start,end, px, py;
    printf("\n请输入起始位置：");
    scanf("%d %d",&px, &py);
    start = point_to_index(px, py);
    fprintf(save_file, "%d %d\n", px, py);
    printf("\n请输入终止位置：");
    scanf("%d %d",&px, &py);
    fprintf(save_file, "%d  %d", px, py);
    end = point_to_index(px, py);

    //设置迪杰斯特拉每次循环的起点
    int dijstart=start;
    int min=0;int d=0;int id=0;
    visited[dijstart][0]=1;
    visited[dijstart][2]=0;
    if(maze[1+ dijstart / MIGONG_SIZE][1 + dijstart % MIGONG_SIZE] == 0)
    {
        printf("\n没有通路\n");
        fprintf(save_file, "\n没有通路\n");
        system("pause");
        exit(0);
    }
    //迪杰斯特拉算法
    int roundtime=0;
    while(visited[end][0]!=1)
    {
        roundtime+=1;
        if(roundtime>20000)
        {
            printf("\n没有通路\n");
            fprintf(save_file, "\n没有通路\n");
            system("pause");
            exit(0);
            break;
        }
        //visited 中 第i个数的
        //左边：i-1；右边i+1.在左右端点处不会涉及其左、右端的操作
        //上边：i%20+20*(i/20-1);下边：i%20+20*(i/20+1)
        if(maze[1+ dijstart / MIGONG_SIZE][dijstart % MIGONG_SIZE] > 0)//判断访问起始点左边的点是否可以走
        {										//可以走，且比当前的dist小，则
            d=visited[dijstart][2]+mazelist[dijstart][0];
            if(d<visited[dijstart-1][2])
            {
                visited[dijstart-1][1]=dijstart;	//上一节点(pr)设置为dijstart
                visited[dijstart-1][2]=d; //Dist为dijstart的Dist+dijstart到左边点的距离
            }
        }
        if(maze[1+ dijstart / MIGONG_SIZE][2 + dijstart % MIGONG_SIZE] > 0)
        {
            d=visited[dijstart][2]+mazelist[dijstart][1];
            if(d<visited[dijstart+1][2])
            {
                visited[dijstart+1][1]=dijstart;
                visited[dijstart+1][2]=d;
            }
        }
        if(maze[dijstart / MIGONG_SIZE][1 + dijstart % MIGONG_SIZE] > 0)
        {
            id= dijstart % MIGONG_SIZE + MIGONG_SIZE * (dijstart / MIGONG_SIZE - 1);
            d=visited[dijstart][2]+mazelist[dijstart][2];
            if(d<visited[id][2])
            {
                visited[id][1]=dijstart;
                visited[id][2]=d;
            }
        }
        if(maze[2+ dijstart / MIGONG_SIZE][1 + dijstart % MIGONG_SIZE] > 0)
        {
            id= dijstart % MIGONG_SIZE + MIGONG_SIZE * (dijstart / MIGONG_SIZE + 1);
            d=visited[dijstart][2]+mazelist[dijstart][3];
            if(d<visited[id][2])
            {
                visited[id][1]=dijstart;
                visited[id][2]=d;
            }
        }
        min=99999;
        for(int i = 0; i < MIGONG_SIZE * MIGONG_SIZE; i++)
        {

            if((mazelist[i]!=0)&&(visited[i][0]==0))
            {
                if(visited[i][2]<min){min=visited[i][2];dijstart=i;}
            }
        }
        visited[dijstart][0]=1;
    }
    printf("\n最短路径长度是：%d，路径是：",visited[end][2]);
    fprintf(save_file, "\n最短路径长度是：%d，路径是：",visited[end][2]);
    //输出路径
    int temp=visited[end][1];
    while(temp!=start)
    {
        maze[1+ temp / MIGONG_SIZE][1 + temp % MIGONG_SIZE]=5;
        printf("%d,", temp);
        fprintf(save_file, "%d,", temp);
        temp=visited[temp][1];
    }
    printf("\n");
    fprintf(save_file, "\n");
    //输出图
    for(int i=0; i < MIGONG_SIZE + 2; i++)
    {
        for(int j=0; j < MIGONG_SIZE + 2; j++)
        {
            if(i==0 ||j==0 || i == MIGONG_SIZE + 1 || j == MIGONG_SIZE + 1)
            {
                printf("  ");
                fprintf(save_file, "  ");
            }
            else
            {
                if(maze[i][j]==1)
                {
                    printf("壹");
                    fprintf(save_file, "壹");
                }
                if(maze[i][j]==10)
                {
                    printf("拾");
                    fprintf(save_file, "拾");
                }
                if(maze[i][j]==0)
                {
                    printf("〇");
                    fprintf(save_file, "〇");
                }
                if(maze[i][j]==5)
                {
                    printf("▲");
                    fprintf(save_file, "▲");
                }
            }

        }
        printf("\n");
        fprintf(save_file, "\n");
    }
    system("pause");
    return 0;
}
