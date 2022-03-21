#ifndef ALGRAPH_H
#define ALGRAPH_H

#include <iostream>
#include <QString>
#define MaxSize 150
using namespace std;
struct EdgeNode                 //定义边表结点
{
    int adjvex;                 //可达顶点的序号
    float Weight;               //可达顶点之间的权值
    EdgeNode *next;
};
struct VertexNode               //定义顶点表结点
{
    int Line;
    QString vertex;
    EdgeNode *firstEdge= nullptr;
};
class ALGraph                                                   //创建邻接表类
{
private:
    VertexNode adjlist[MaxSize];                                //存储顶点数组
    int vertexNum;                                              //图的顶点数目
    int edgeNum;                                                //图的边数目
    void DeepBack(int Length, const VertexNode& bt,const QString &EndStation);//用于查找换乘最少
public:
    ALGraph(const QString *a,int n,int e,const float *Weight);   //构造函数
    ~ALGraph();                                                 //析构函数
    void BFTraverse(int v,const QString& EndStation);                       //广度优先遍历，站点最少情况
    void Djikstra(int start,const QString& EndStation);          //狄杰斯特拉算法，用于查找路程最短路径
    void DeepBack(int v,const QString &EndStation);              //查找换乘最少路径
};


#endif // ALGRAPH_H
