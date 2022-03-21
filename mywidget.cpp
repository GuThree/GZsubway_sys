#include "mywidget.h"
#include "ui_mywidget.h"
#include "test.h"
#include <QDebug>
#include <QString>
using namespace std;

QString StartStation;         //起点位置
QString EndStation;

extern QString deepbackRes;
extern QString djikstraRes;
extern QString bftraverseRes;

myWidget::myWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myWidget)
{
    ui->setupUi(this);
    ui->mapL->setPixmap(QPixmap(":/img/smallmap.png"));

    QStringList Line;
     Line << "1号线" << "2号线" << "3号线" << "5号线" << "6号线";

    ui->S_L->addItems(Line);
    ui->E_L->addItems(Line);
    QStringList initPoint;
    initPoint << "西朗" << "坑口" << "花地湾" << "芳村" << "黄沙" << "长寿路" << "陈家祠" << "西门口" << "公园前"
          << "农讲所" << "烈士陵园" << "东山口" << "杨箕" << "体育西路" << "体育中心" << "广州东站";
    ui->S_P->addItems(initPoint);
    ui->E_P->addItems(initPoint);

    connect(ui->S_L, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), [=](){
        if (ui->S_L->currentIndex() == 0){
            QStringList Point;
            Point << "西朗" << "坑口" << "花地湾" << "芳村" << "黄沙" << "长寿路" << "陈家祠" << "西门口" << "公园前"
                  << "农讲所" << "烈士陵园" << "东山口" << "杨箕" << "体育西路" << "体育中心" << "广州东站";
            ui->S_P->clear();
            ui->S_P->addItems(Point);
        }else if (ui->S_L->currentIndex() == 1){
            QStringList Point;
            Point << "广州南站" << "石壁" << "会江" << "南浦" << "洛溪" << "南洲" << "东晓南" << "江泰路" << "昌岗"
                  << "江南西" << "市二宫" << "海珠广场" << "公园前" << "纪念堂" << "越秀公园" << "广州火车站" << "三元里" << "飞翔公园"
                  << "白云公园" << "白云文化广场" << "萧岗" << "江夏" << "黄边" << "嘉禾望岗";
            ui->S_P->clear();
            ui->S_P->addItems(Point);
        }else if (ui->S_L->currentIndex() == 2){
            QStringList Point;
            Point << "机场北" << "机场南" << "高增" << "人和" << "龙归" << "嘉禾望岗" << "白云大道北" << "永泰" << "同和"
                  << "京溪南方医院" << "梅花园" << "燕塘" << "广州东站" << "林和西" << "体育西路" << "珠江新城" << "广州塔" << "客村"
                  << "大塘" << "沥滘" << "厦滘" << "大石" << "汉溪长隆" << "市桥" << "番禺广场" << "石牌桥" << "岗顶" << "华师" << "五山" << "天河客运站";
            ui->S_P->clear();
            ui->S_P->addItems(Point);
        }else if (ui->S_L->currentIndex() == 3){
            QStringList Point;
            Point << "滘口" << "坦尾" << "中山八" << "西场" << "西村" << "广州火车站" << "小北" << "淘金" << "区庄"
                  << "动物园" << "杨箕" << "五羊邨" << "珠江新城" << "猎德" << "潭村" << "员村" << "科韵路" << "车陂南"
                  << "东圃" << "三溪" << "鱼珠" << "大沙地" << "大沙东" << "文冲";
            ui->S_P->clear();
            ui->S_P->addItems(Point);
        }else if (ui->S_L->currentIndex() == 4){
            QStringList Point;
            Point << "浔峰岗" << "横沙" << "沙贝" << "河沙" << "坦尾" << "如意坊" << "黄沙" << "文化公园" << "一德路"
                  << "海珠广场" << "北京路" << "团一大广场" << "东湖" << "东山口" << "区庄" << "黄花岗" << "沙河顶" << "沙河"
                  << "天平架" << "燕塘" << "天河客运站" << "长湴" << "植物园" << "龙洞" << "柯木塱" << "高塘石" << "黄陂"
                  << "金峰" << "暹岗" << "苏元" << "萝岗" << "香雪";
            ui->S_P->clear();
            ui->S_P->addItems(Point);
        }
    });

    connect(ui->E_L, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), [=](){
        if (ui->E_L->currentIndex() == 0){
            QStringList Point;
            Point << "西朗" << "坑口" << "花地湾" << "芳村" << "黄沙" << "长寿路" << "陈家祠" << "西门口" << "公园前"
                  << "农讲所" << "烈士陵园" << "东山口" << "杨箕" << "体育西路" << "体育中心" << "广州东站";
            ui->E_P->clear();
            ui->E_P->addItems(Point);
        }else if (ui->E_L->currentIndex() == 1){
            QStringList Point;
            Point << "广州南站" << "石壁" << "会江" << "南浦" << "洛溪" << "南洲" << "东晓南" << "江泰路" << "昌岗"
                  << "江南西" << "市二宫" << "海珠广场" << "公园前" << "纪念堂" << "越秀公园" << "广州火车站" << "三元里" << "飞翔公园"
                  << "白云公园" << "白云文化广场" << "萧岗" << "江夏" << "黄边" << "嘉禾望岗";
            ui->E_P->clear();
            ui->E_P->addItems(Point);
        }else if (ui->E_L->currentIndex() == 2){
            QStringList Point;
            Point << "机场北" << "机场南" << "高增" << "人和" << "龙归" << "嘉禾望岗" << "白云大道北" << "永泰" << "同和"
                  << "京溪南方医院" << "梅花园" << "燕塘" << "广州东站" << "林和西" << "体育西路" << "珠江新城" << "广州塔" << "客村"
                  << "大塘" << "沥滘" << "厦滘" << "大石" << "汉溪长隆" << "市桥" << "番禺广场" << "石牌桥" << "岗顶" << "华师" << "五山" << "天河客运站";
            ui->E_P->clear();
            ui->E_P->addItems(Point);
        }else if (ui->E_L->currentIndex() == 3){
            QStringList Point;
            Point << "滘口" << "坦尾" << "中山八" << "西场" << "西村" << "广州火车站" << "小北" << "淘金" << "区庄"
                  << "动物园" << "杨箕" << "五羊邨" << "珠江新城" << "猎德" << "潭村" << "员村" << "科韵路" << "车陂南"
                  << "东圃" << "三溪" << "鱼珠" << "大沙地" << "大沙东" << "文冲";
            ui->E_P->clear();
            ui->E_P->addItems(Point);
        }else if (ui->E_L->currentIndex() == 4){
            QStringList Point;
            Point << "浔峰岗" << "横沙" << "沙贝" << "河沙" << "坦尾" << "如意坊" << "黄沙" << "文化公园" << "一德路"
                  << "海珠广场" << "北京路" << "团一大广场" << "东湖" << "东山口" << "区庄" << "黄花岗" << "沙河顶" << "沙河"
                  << "天平架" << "燕塘" << "天河客运站" << "长湴" << "植物园" << "龙洞" << "柯木塱" << "高塘石" << "黄陂"
                  << "金峰" << "暹岗" << "苏元" << "萝岗" << "香雪";
            ui->E_P->clear();
            ui->E_P->addItems(Point);
        }
    });


    connect(ui->pushButton, &QPushButton::clicked, [=](){
       StartStation = ui->S_P->currentText();
       EndStation = ui->E_P->currentText();
       Test test;                  //创建测试类
       test.StartTest();           //调用测试方法
       ui->Res->setText(deepbackRes + "\n\n" + djikstraRes + "\n\n" + bftraverseRes);
    });


}

myWidget::~myWidget()
{
    delete ui;
}
