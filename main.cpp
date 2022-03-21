#include "mywidget.h"
#include <QApplication>
#include "process_Data.h"
using namespace std;

int main(int argc, char *argv[])
{
    //应用程序对象，有且只有一个
    QApplication a(argc, argv);
    //窗口对象
    myWidget w;
    w.show();

    Process_Data file;          //创建数据处理类
    file.OpenFile();            //调用数据处理方法


    return a.exec();
}
