#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QLabel>
#include <QRectF>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QGraphicsScene>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct _data{
    QString index;
    QString x;
    QString y;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QList<_data> dataList;

    QLabel* labViewCord;
    QLabel* labSceneCord;
    QLabel* labItemCord;
    QGraphicsScene* Scene;

    void initGraphics();
    void drawGraphics(int n, int result[110]);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //void paintEvent(QPaintEvent *event);
    //bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void on_mouseMovePoint(QPoint point);
    void on_mouseClick(QPoint point);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
