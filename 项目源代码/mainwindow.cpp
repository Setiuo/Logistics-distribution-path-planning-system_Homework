#include "mainwindow.h"
#include "./ui_mainwindow.h"

//#include <QKeyEvent>
#include <qpainter.h>

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMessageBox>

int computePath(int num, int _dot[110][2], int result[110]);

void MainWindow::initGraphics()
{
}

void MainWindow::drawGraphics(int n, int result[110])
{
    QRectF rect(-200, -100, 400, 200);
    Scene = new QGraphicsScene(rect);
    ui->graphicsView->setScene(Scene);


    QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
    pen.setColor(QColor(0, 160, 230));
    pen.setWidth(5);

    for(int i = 2; i <= n; i++){
        int _index1 = result[i-1];
        QString _name1 = "";
        int _x1 = 0, _y1 = 0;
        qDebug()<<_index1 <<" "<<n;
        if(_index1 == n){//判断是否是快递点
            _name1 = ui->CourierName->toPlainText();
            _x1 = ui->CourierX->toPlainText().toInt();
            _y1 = ui->CourierY->toPlainText().toInt();
        }else{
            _name1 = this->dataList[_index1 - 1].index;
            _x1 = this->dataList[_index1 - 1].x.toInt();
            _y1 = this->dataList[_index1 - 1].y.toInt();
        }


        int _index2 = result[i];
        qDebug()<<_index2 <<" "<<n;
        QString _name2 = "";
        int _x2, _y2;
        if(_index2 == n){
            _name2 = ui->CourierName->toPlainText();
            _x2 = ui->CourierX->toPlainText().toInt();
            _y2 = ui->CourierY->toPlainText().toInt();
        }else{
            _name2 = this->dataList[_index2 - 1].index;
            _x2 = this->dataList[_index2 - 1].x.toInt();
            _y2 = this->dataList[_index2 - 1].y.toInt();
        }


        //qDebug()<<result[i]<<" "<<_name2;

        QGraphicsLineItem *m_lineItem = new QGraphicsLineItem();    // 定义一个直线图元
        m_lineItem->setLine(QLineF(_x1, _y1, _x2, _y2));
        m_lineItem->setPen(pen);
        Scene->addItem(m_lineItem);      // 把直线图元添加到场景

        QGraphicsTextItem *textItem1 = new QGraphicsTextItem(_name1);
        textItem1->setFont(QFont("family", 13, 10));
        textItem1->setPos(_x1, _y1);
        Scene->addItem(textItem1);

        QGraphicsTextItem *textItem2 = new QGraphicsTextItem(_name2);
        textItem2->setFont(QFont("family", 13, 10));
        textItem2->setPos(_x2, _y2);
        Scene->addItem(textItem2);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->targetEditAdd, &QPushButton::clicked, [&]{
//        qDebug()<<"pushButton clicked";

        QString index = ui->targetEditName->toPlainText();

        int dataLength = this->dataList.length();
        for(int i = 0; i < dataLength; i++){
            if(this->dataList[i].index == index){
                QMessageBox::about(NULL,"提示","重复的地点名称！");
                return;
            }
        }

        QString _x = ui->targetEditX->toPlainText(), _y = ui->targetEditY->toPlainText();
        qDebug()<<_x<<" "<<_y;

        this->dataList.push_back({index, _x, _y});
        ui->comboBox->addItem(index);
    });

    connect(ui->targetEditDelete, &QPushButton::clicked, [&]{
        QString text=ui->comboBox->currentText();
        int _index = ui->comboBox->currentIndex();

        ui->comboBox->removeItem(_index);
        int dataLength = this->dataList.length();
        for(int i = 0; i < dataLength; i++){
            if(this->dataList[i].index == text){
                this->dataList.remove(i);
                break;
            }
        }
    });

    //计算路径
    connect(ui->computePath, &QPushButton::clicked, [&]{
        int n = this->dataList.length();
        int _dot[110][2];

        for(int i = 0; i < n; i++){
            _dot[i+1][0] = this->dataList[i].x.toInt();
            _dot[i+1][1] = this->dataList[i].y.toInt();
        }

        //加入快递点
        _dot[++n][0] = ui->CourierX->toPlainText().toInt();
        _dot[n][0] = ui->CourierY->toPlainText().toInt();

        int result[110];
        computePath(n, _dot, result);
        drawGraphics(n, result);

//        qDebug()<<"compute Path Result:";
//        for(int i = 1; i <= n; i++){
//            QString name = this->dataList[result[i] - 1].index;
//            QString x = this->dataList[result[i] - 1].x;
//            QString y = this->dataList[result[i] - 1].y;

//            qDebug()<<result[i]<<" "<<name;
//        }
    });

    connect(ui->comboBox, &QComboBox::currentIndexChanged, [&](int index){
        QString text=ui->comboBox->currentText();

        int dataLength = this->dataList.length();
        for(int i = 0; i < dataLength; i++){
            if(this->dataList[i].index == text){
                ui->targetEditName->setText(this->dataList[i].index);
                ui->targetEditX->setText(this->dataList[i].x);
                ui->targetEditY->setText(this->dataList[i].y);
                break;
            }
        }

//        qDebug()<<text;
//        qDebug()<<"comboBox clicked "<<index<< " " << text;
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mouseMovePoint(QPoint point)
{
}

void MainWindow::on_mouseClick(QPoint point)
{
}
