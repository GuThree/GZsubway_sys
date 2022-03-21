#include <iostream>
#include <fstream>
#include <QDebug>
#include "algraph.h"
#include "process_Data.h"
using namespace std;
int Abscissa[MaxSize];          //横坐标
int Ordinate[MaxSize];          //纵坐标
float Weight[MaxSize];          //两个顶点之间的权值
int Weight2[MaxSize];            //
int VertexNum;                  //顶点的数目
int EdgeNum;                    //边的数目
QString Station[MaxSize];        //存储站点名称

void Process_Data::OpenFile() {
    //写入数据
    string pathname = "E:/Document/QT/subway_sys/Myfile.txt";
    ifstream file(pathname, ios::in);
    if (!file.is_open()) {
        qDebug() << "未成功打开文件..\n";
    }
    int Length1 = 0, Length2 = 0, Length3=0;       //存储站点

    int i = 0;
    file >> Length1;
    VertexNum = Length1;
    string temp;
    while (Length1 != 0) {
        file >> temp;
        Station[i].append(QString::fromStdString(temp));
        Length1--;
        i++;
    }
    file >> Length2;
    EdgeNum = Length2;
    i = 0;
    while (Length2 != 0) {
        file >> Abscissa[i] >> Ordinate[i] >> Weight[i];
        Length2--;
        i++;
    }

    file >> Length3;
    i = 0;
    while (Length3 != 0) {
        file >> Weight2[i];
        Length3--;
        i++;
    }
    file.close();
}

