#include "maplabel.h"
#include <QDialog>
#include <QProcess>
#include <QString>
#include <QDebug>
maplabel::maplabel(QWidget *parent) : QLabel(parent)
{

}

void maplabel::mousePressEvent(QMouseEvent *ev){
    QProcess* process = new QProcess();
    QString sPicPath = "C:\\Users\\Public\\Pictures\\subway_map.gif";
    //文件格式必须调整
    QString program = "cmd.exe";
    QStringList para;
//    para << "c:";
//    QString sPicPath = lastPicPath.toUtf8().replace("//", "\\");
    //命令间需要添加空格
    para << QString("rundll32.exe") + QString(" %Systemroot%\\System32\\shimgvw.dll,ImageView_Fullscreen ");

    qDebug() << para;
    process->start(program, para);
}

