#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   QString Text = "Hello,World!";//主串
    void match_result(QString search_method,int result);//匹配输出结果函数
    int bruteForce();//暴力匹配算法
    void buildNext_1(int *next,QString pattern);//kmp1.0算法构建next数组
    int kmp1_0();//kmp1.0匹配算法
    void buildNext_2(int *next);//kmp2.0算法构建next数组
    int kmp2_0();//kmp2.0匹配算法

private slots:

    void on_pushButton_clicked();//暴力匹配按钮

    void on_pushButton_2_clicked();//KMP1.0按钮

    void on_pushButton_3_clicked();//KMP2.0按钮

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
