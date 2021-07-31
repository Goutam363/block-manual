#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sha256.h"
#include<QMessageBox>

std::string int_to_string(int num){
    std::string res="";
    while (num>0) {
        res+=char(num%10+48);
        num/=10;
    }
    for(int i=0,j=res.length()-1;i<j;i++,j--)
    {
        char temp=res[i];
        res[i]=res[j];
        res[j]=temp;
    }
    return res;
}

void MainWindow::calculateHashOfBlock()
{
    QString qstr=ui->lineEdit->text();
    qstr+=ui->lineEdit_2->text();
    qstr+=ui->textEdit->toPlainText();
    std::string str=qstr.toStdString();
    ui->label_5->setText(QString::fromStdString(sha256::hash256_hex_string(str)));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Block");
    ui->lineEdit->setText("1");
    for(int i=0;ui->label_5->text()[0]!='0' || ui->label_5->text()[1]!='0' || ui->label_5->text()[2]!='0';i++){
        ui->lineEdit_2->setText(QString::fromStdString(int_to_string(i)));
        calculateHashOfBlock();
    }
    connect(ui->lineEdit,&QLineEdit::textChanged,[=](){
        calculateHashOfBlock();
    });
    connect(ui->lineEdit_2,&QLineEdit::textChanged,[=](){
        calculateHashOfBlock();
    });
    connect(ui->textEdit,&QTextEdit::textChanged,[=](){
        calculateHashOfBlock();
    });
    connect(ui->pushButton,&QPushButton::pressed,[=](){
        QString qstr=ui->label_5->text();
        QMessageBox message;
        message.setWindowTitle("Mine");
        if(qstr[0]=='0')
        {
            qDebug("Mined Successfully!!!");
            message.setText("Mined Successfully!!!");
            message.setIcon(QMessageBox::Information);
            message.setStandardButtons(QMessageBox::Ok);
            message.exec();
        }
        else
        {
            qDebug("Mining Failed!!! Minimum one 0 required in the starting of the hash-value");
            message.setText("Mining Failed!!!");
            message.setInformativeText("Minimum one 0 required in the starting of the hash-value");
            message.setIcon(QMessageBox::Warning);
            message.setStandardButtons(QMessageBox::Ok);
            message.exec();
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
