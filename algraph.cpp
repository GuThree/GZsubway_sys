#include <iostream>
#include <cstring>
#include <QDebug>
#include "algraph.h"
//构造函数
extern int Abscissa[MaxSize];           //横坐标
extern int Ordinate[MaxSize];           //纵坐标
extern float Weight[MaxSize];           //两个顶点之间的权值
extern int Weight2[MaxSize];
int visited[MaxSize];                   //顶点是否被访问

int Min;
int Size=0;
int CurTen=0;
QString CurStation[MaxSize];
int Temp[MaxSize];
QString CSortStation[MaxSize];

QString deepbackRes;
QString djikstraRes;
QString bftraverseRes;

void ALGraph::DeepBack(int v,const QString &EndStation) {
    Min=10000;
    CurStation[0] = adjlist[v].vertex;
    CurTen = adjlist[v].Line;
    int i=0;
    if (CurTen == 0)    i=1;
    memset(visited, 0, sizeof(int) * MaxSize);
    visited[v] = 1;

    DeepBack(1, adjlist[v], EndStation);

    deepbackRes.clear();
    deepbackRes = deepbackRes + "换乘次数为:" + QString::number(Min-i) + " ";
    deepbackRes += CSortStation[0];
    for (i = 1; i < Size; i++) {
         deepbackRes = deepbackRes + "->" +  CSortStation[i];
    }
//    cout << "换乘次数为:" << Min << endl;
//    cout<<CSortStation[0];
//    for (i = 1; i < Size; i++) {
//        cout <<"->"<< CSortStation[i];
//    }
//    cout << endl;
}

void ALGraph::DeepBack(int Length, const VertexNode& bt, const QString &EndStation) {
    //回溯法
    int k, i;
    EdgeNode *p;
    if (bt.vertex == EndStation) {//剪枝条件
        int Count = 0;
        for (i = 0; i < Length; i++) {
            if (Temp[i] != 0) {
                if (Temp[i] != CurTen) {
                    CurTen = Temp[i];
                    Count++;
                }
            }
        }
        if (Count < Min) {
            Min = Count;
            Size = Length;
            for (i = 0; i < Length; i++)
                CSortStation[i] = CurStation[i];
        }
        return;
    } else {
        p = bt.firstEdge;
        while (p != nullptr) {
            k = p->adjvex;
            if (visited[k] == 0) {
                visited[k] = 1;
                CurStation[Length] = adjlist[k].vertex;
                Temp[Length++] = adjlist[k].Line;
                DeepBack(Length, adjlist[k], EndStation);
                Length--;
                visited[k] = 0;
            }
            p = p->next;
        }
    }
}

ALGraph::~ALGraph() {
    EdgeNode *p,*q;
    for(int i=0;i<vertexNum;i++)
    {
        p = adjlist[i].firstEdge;
        while(p!= nullptr)
        {
            q = p->next;
            delete p;
            p = q;
        }
    }

}
ALGraph::ALGraph(const QString *a,int n,int e,const float *weight) {
    memset(visited, 0, sizeof(int) * MaxSize);        //初始化visited数组
    vertexNum = n;
    edgeNum = e;
    int i, t, k;
    EdgeNode *p;

    for (i = 0; i < vertexNum; i++){                                //初始化顶点
        adjlist[i].vertex = a[i];                             //给顶点赋值
        adjlist[i].Line = Weight2[i];
        adjlist[i].firstEdge = nullptr;
    }

    t = 0;
    for (k = 0; k < edgeNum; k++){                                  //创建每个顶点的边表
        p = new EdgeNode;
        p->adjvex = Ordinate[t];
        p->Weight = weight[t];
        p->next = adjlist[Abscissa[t]].firstEdge;
        adjlist[Abscissa[t]].firstEdge = p;
        t++;
    }

    t = 0;
    for (k = 0; k < edgeNum; k++){                                  //由于是无向图，因此采用对称存储
        p = new EdgeNode;
        p->adjvex = Abscissa[t];
        p->Weight = weight[t];
        p->next = adjlist[Ordinate[t]].firstEdge;
        adjlist[Ordinate[t]].firstEdge = p;
        t++;
    }
}

int MIN(const float *dist,int vertexNum)                    //求最小值函数,用于最短路径算法
{
    float min = 255;
    int k = 0;
    for (int i = 0; i < vertexNum; i++)
        if (dist[i] != 0 && dist[i] < min) {
            min = dist[i];
            k = i;
        }
    return k;
}
//最短路径算法
void ALGraph::Djikstra(int start,const QString& EndStation)
{
    float dist[MaxSize];
    int k,i,min;
    EdgeNode *p;
    QString path[MaxSize];

    for(i=0;i<vertexNum;i++) {            //初始化dist数组为最大值，path数组为空
        dist[i] = 255;
        path[i] = "";
    }

    p=adjlist[start].firstEdge;        //搜索起点所有可达的顶点
    while(p!=nullptr) {
        k = p->adjvex;
        dist[k] = p->Weight;
        path[k] = adjlist[start].vertex + "->" + adjlist[k].vertex;
        p = p->next;
    }

    djikstraRes.clear();
    for(i=0;i<vertexNum;i++) {
        min = MIN(dist, vertexNum);                 //在dist数组中找最小值并放回其下标
        if (adjlist[min].vertex == EndStation) {    //如果找出终点，则输出结果，并且跳出循环
            djikstraRes += "最短路径为: ";
            djikstraRes += path[min];
            djikstraRes = djikstraRes + "  距离为:" + QString::number(dist[min]) + "km";
//            cout << "最短路径为:" << endl;
//            cout << path[min] << endl;
//            cout << "距离为:" << dist[min] << "km" <<endl;
            break;
        }
        p = adjlist[min].firstEdge;                 //找dist中最小值所指顶点，继续向前搜索
        while (p != nullptr) {
            k = p->adjvex;
            if (dist[k] > dist[min] + p->Weight) {
                dist[k] = dist[min] + p->Weight;
                path[k] = path[min] + "->" + adjlist[k].vertex;
            }
            p = p->next;
        }
        dist[min] = 0;                              //将顶点加入到已经找出最小路径的集合中
    }
}

void ALGraph::BFTraverse(int v,const QString& EndStation)//广度优先算法，寻找站点最少和换乘次数最少
{
    int getTop,k;
    int flag=0;                         //判断是否得出最终结果
    int stack[MaxSize];                 //队列的顺序存储
    QString path[MaxSize];               //存储搜索后的结果
    int rear=-1,front=-1;
    EdgeNode *p;
    visited[v]=1;                       //将起点设为已访问

    for(int i=0;i<vertexNum;i++) {      //初始化path数组
        path[i] = "";
    }

    bftraverseRes.clear();
    p=adjlist[v].firstEdge;             //访问起点所有可达的顶点
    while(p!=nullptr) {
        k = p->adjvex;
        path[k] = adjlist[v].vertex + "->" + adjlist[k].vertex;
        if (adjlist[k].vertex == EndStation) {
            bftraverseRes += "站数最少路径为: ";
            bftraverseRes += path[k];
//            cout << "站数最少路径为:" <<endl;
//            cout << path[k] << endl;
            rear = front;
            break;
        }
        stack[++rear] = k;
        p = p->next;
    }

    while(rear!=front) {                            //向前搜索
        getTop = stack[++front];
        p = adjlist[getTop].firstEdge;
        while (p != nullptr) {
            k = p->adjvex;
            if (visited[k] == 0)                   //如果没有被访问，则访问该顶点
            {
                stack[++rear] = k;
                path[k] = path[getTop] + "->" + adjlist[k].vertex;
                visited[k] = 1;
            }
            if (EndStation == adjlist[k].vertex)   //如果找到终点，输出结果，并将flag设为1，然后退出循环
            {
                bftraverseRes += "站数最少路径为: ";
                bftraverseRes += path[k];
//                cout << "站数最少路径为:" <<endl;
//                cout << path[k] << endl;
                flag = 1;
                break;
            }
            p = p->next;
        }
        if (flag)                                //退出外循环
            break;
    }
}

