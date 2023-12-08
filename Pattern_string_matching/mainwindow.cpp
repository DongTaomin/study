#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QLineEdit>
#include<QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::match_result(QString search_method,int result)
{
    if(result == 0)//判断输入文本框是否为空
    {
        QMessageBox::warning(this,search_method,"请输入！");
    }
    else if(result == -1)//没有找到，给出提示信息
    {
        QMessageBox::information(this,search_method,"抱歉，没有找到！");

    }
    else//找到并输出位置信息
    {
        QString Result = QString::number(result,10);//整型数据转为字符型
        Result = "找到，在第" + Result +"位";
        QMessageBox::about(this,search_method,Result);
    }

}
int MainWindow::bruteForce()
{
    QString pattern = ui->lineEdit->text();
    int n = Text.length();    // 获取文本的长度
    int m = pattern.length(); // 获取模式串的长度
    if (m == 0)
    {
        return 0;
    }
    else
    {
        // 从文本的第一个字符开始逐个比较
        for (int i = 0; i <= n - m; i++)
        { // i 表示文本中当前比较的起始位置
            int j;
            for (j = 0; j < m; j++)
            {                                  // j 表示模式中当前比较的字符位置
                if (Text[i + j] != pattern[j]) // 如果当前字符不匹配，则退出内层循环
                    break;
            }

            if (j == m)   // 如果内层循环正常结束，且 j 等于 m，说明找到了匹配的子串
                return i+1; // 返回匹配的起始位置
        }
        return -1; // 没有找到匹配的子串返回-1
    }
}
void MainWindow::on_pushButton_clicked()
{
    int result_1 = bruteForce();//BF匹配结果
    match_result("BF查找",result_1);//输出

}

void MainWindow::buildNext_1(int *next,QString pattern)
{
    // 构建一个字符串的最长前缀后缀数组
    int m = pattern.length();// 获取字符串的长度
    int len = 0;  // 当前匹配的前缀长度

    next[0] = -1;//next数组的第一个元素设为-1

    for (int i = 1; i < m; ) // 从1开始遍历字符串的每个字符
    {
        // 如果当前字符和前缀的下一个字符匹配，则前缀长度加1，next数组的当前位置设为前缀长度，然后i自增1
        if (pattern[i] == pattern[len])
        {
            len++;
            next[i] = len;
            i++;
        }
        else// 如果当前字符和前缀的下一个字符不匹配，则判断前缀长度是否为0，如果不为0，则将前缀长度设为前一个位置的next值，否则将next数组的当前位置设为0，然后i自增1
        {
            if (len != 0) {
                len = next[len - 1];
            } else {
                next[i] = 0;
                i++;
            }
        }
    }

}
int MainWindow::kmp1_0()
{
    QString pattern = ui->lineEdit->text();
    int n = Text.length();
    int m = pattern.length();
    if (m == 0)
    {
        return 0;
    }

    int *next2 = new int[m];
    buildNext_1(next2,pattern);//获取next数组

    // 初始化匹配起始位置和当前位置
    int i = 0; // 主串中当前比较的位置
    int j = 0; // 模式串中当前比较的位置

    // 遍历文本字符串
    while (i < n && j< m)
    {
        // 主串子串匹配均未结束
        if (j == -1 || Text[i] == pattern[j])
        {
            i++;
            j++;
        }

        // 当前字符匹配失败,j滑动到next[j]位置，继续匹配
        else
        {
            j = next2[j];
        }
    }
    delete[] next2;
    if(j == m)
    {
        return i - m + 1;// 匹配成功，返回匹配的起始位置
    }
    // 模式字符串没有匹配到
    else
    {
        return -1;
    }


}

void MainWindow::on_pushButton_2_clicked()
{
    int result_2 = kmp1_0();
    match_result("kmp1.0",result_2);
}


void MainWindow::buildNext_2(int *next)
{
    QString pattern = ui->lineEdit->text();
    int m = pattern.length();
    next[0] = -1;      // 初始化next[0]为-1
    int i = 0, j = -1; // i表示当前字符的位置，j表示当前字符之前的最长可匹配前缀的下一个字符的位置

    while (i < m - 1)
    {
        if (j == -1 || pattern[i] == pattern[j])
        {
            ++i;
            ++j;
            if (pattern[i] != pattern[j])
            {
                next[i] = j; // 当前字符与前缀不匹配时，next[i]的值为j
            }
            else
            {
                next[i] = next[j]; // 当前字符与前缀匹配时，next[i]的值与next[j]相同
            }
        }
        else
        {
            j = next[j]; // 当前字符与前缀不匹配时，j回退到next[j]的位置
        }
    }
}
int MainWindow::kmp2_0()
{
    QString pattern = ui->lineEdit->text();
    int n = Text.length();
    int m = pattern.length();

    if (m == 0)
    {
        return 0;
    }

    int *next = new int[m];   // 存储next数组
    buildNext_2(next); // 构建next数组

    int i = 0; // 主串中当前比较的位置
    int j = 0; // 模式串中当前比较的位置

    while (i < n && j < m)
    {
        if (j == -1 || Text[i] == pattern[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j]; // 当前字符不匹配时，根据next数组移动模式串的位置
        }
    }

    delete[] next;

    if (j == m)
    {
        return i - m + 1; // 匹配成功，返回匹配的起始位置
    }

    return -1; // 没有找到匹配的子串

}
void MainWindow::on_pushButton_3_clicked()
{
    int result_3 = kmp2_0();
    match_result("kmp2.0",result_3);
}

