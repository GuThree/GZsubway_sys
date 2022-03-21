#include "test.h"
#include "algraph.h"
#include <iostream>
#include <QDebug>
using namespace std;
extern int VertexNum;                  //顶点的数目
extern int EdgeNum;                    //边的数目
extern QString Station[MaxSize];        //存储站点名称
extern float Weight[MaxSize];          //两个顶点之间的权值
extern QString CSortStation[MaxSize];

extern QString StartStation;         //起点位置
extern QString EndStation;

void Test::StartTest() {
    //创建邻接表对象
    ALGraph MG(Station,VertexNum,EdgeNum,Weight);
    //交互界面
    int start=0,end=0,i;

    for(i=0;i<VertexNum;i++)     //找出起点和终点对应的下标
    {
        if(StartStation==Station[i])
        {
            start=i;
        }
        if(EndStation==Station[i])
            end=i;
    }
    if(end!=start)
    {
        MG.Djikstra(start,EndStation);
        MG.BFTraverse(start,EndStation);
        MG.DeepBack(start,EndStation);
    }

}
