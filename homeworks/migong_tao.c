//
// Created by Calun on 2021/1/12.
//

#include "migong_tao.h"
#include <stdio.h>
#include <stdlib.h>
#define MIGONG_SIZE 70
#include <time.h>


/* �����Թ��������õϽ�˹�����㷨��������������·�� */
int maze[MIGONG_SIZE + 2][MIGONG_SIZE + 2];

//��1��10��10
//��10��1��10
//��1��1��1
//��10��10��10
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
    //����α����Թ�

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
                    printf("Ҽ");
                    fprintf(save_file, "Ҽ");
                }
                if(maze[i][j]==2)
                {
                    printf("ʰ");
                    fprintf(save_file, "ʰ");
                    maze[i][j]=10;
                }
                if(maze[i][j]==0)
                {
                    printf("��");
                    fprintf(save_file,"��");
                }
            }

        }
        printf("\n");
        fprintf(save_file, "\n");
    }

    //����list��ʾͼ ˳�� �������� ÿ��ռ4��λ�� 1,10��ʾ��· 0��ʾû��
    int mazelist[MIGONG_SIZE * MIGONG_SIZE][4];
    for(int i=0; i < MIGONG_SIZE * MIGONG_SIZE; i++)
    {
        //mazelist[i]=maze[1+i/20][1+i%20] ��i������Ӧ����maze�����е�λ��
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
            //printf("\n��%d���ڵ㣬%d,%d,%d,%d.",i,mazelist[i][0],mazelist[i][1],mazelist[i][2],mazelist[i][3]);
        }
    }

    //����visited list
    int visited[MIGONG_SIZE * MIGONG_SIZE][3];
    for (int i = 0; i < MIGONG_SIZE * MIGONG_SIZE; i++)
    {
        visited[i][0]=0;//0��δ�����ʣ�1��������
        visited[i][1]=-1;//��һ���ڵ����ĸ�
        visited[i][2]=999999;//Dist,�ӵ�һ���ڵ㵽�ýڵ�ľ���
        if(maze[1+ i / MIGONG_SIZE][i % MIGONG_SIZE] == 0)
            visited[i][1]=-2;
    }
    visited[0][0]=1;visited[0][2]=0;
    //������ʼ�㣬��ֹ��
    int start,end, px, py;
    printf("\n��������ʼλ�ã�");
    scanf("%d %d",&px, &py);
    start = point_to_index(px, py);
    fprintf(save_file, "%d %d\n", px, py);
    printf("\n��������ֹλ�ã�");
    scanf("%d %d",&px, &py);
    fprintf(save_file, "%d  %d", px, py);
    end = point_to_index(px, py);

    //���õϽ�˹����ÿ��ѭ�������
    int dijstart=start;
    int min=0;int d=0;int id=0;
    visited[dijstart][0]=1;
    visited[dijstart][2]=0;
    if(maze[1+ dijstart / MIGONG_SIZE][1 + dijstart % MIGONG_SIZE] == 0)
    {
        printf("\nû��ͨ·\n");
        fprintf(save_file, "\nû��ͨ·\n");
        system("pause");
        exit(0);
    }
    //�Ͻ�˹�����㷨
    int roundtime=0;
    while(visited[end][0]!=1)
    {
        roundtime+=1;
        if(roundtime>20000)
        {
            printf("\nû��ͨ·\n");
            fprintf(save_file, "\nû��ͨ·\n");
            system("pause");
            exit(0);
            break;
        }
        //visited �� ��i������
        //��ߣ�i-1���ұ�i+1.�����Ҷ˵㴦�����漰�����Ҷ˵Ĳ���
        //�ϱߣ�i%20+20*(i/20-1);�±ߣ�i%20+20*(i/20+1)
        if(maze[1+ dijstart / MIGONG_SIZE][dijstart % MIGONG_SIZE] > 0)//�жϷ�����ʼ����ߵĵ��Ƿ������
        {										//�����ߣ��ұȵ�ǰ��distС����
            d=visited[dijstart][2]+mazelist[dijstart][0];
            if(d<visited[dijstart-1][2])
            {
                visited[dijstart-1][1]=dijstart;	//��һ�ڵ�(pr)����Ϊdijstart
                visited[dijstart-1][2]=d; //DistΪdijstart��Dist+dijstart����ߵ�ľ���
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
    printf("\n���·�������ǣ�%d��·���ǣ�",visited[end][2]);
    fprintf(save_file, "\n���·�������ǣ�%d��·���ǣ�",visited[end][2]);
    //���·��
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
    //���ͼ
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
                    printf("Ҽ");
                    fprintf(save_file, "Ҽ");
                }
                if(maze[i][j]==10)
                {
                    printf("ʰ");
                    fprintf(save_file, "ʰ");
                }
                if(maze[i][j]==0)
                {
                    printf("��");
                    fprintf(save_file, "��");
                }
                if(maze[i][j]==5)
                {
                    printf("��");
                    fprintf(save_file, "��");
                }
            }

        }
        printf("\n");
        fprintf(save_file, "\n");
    }
    system("pause");
    return 0;
}
