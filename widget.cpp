
#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setGeometry(900,50,1000,950);
    m_board=new CChessboard(this);

    connect(this,&Widget::huiqi,m_board,&CChessboard::do_huiqi);
    connect(this,&Widget::restart,m_board,&CChessboard::do_restart);
}

Widget::~Widget()
{
    delete ui;
}


//悔棋按钮
void Widget::on_pushButton_clicked()
{
    emit huiqi();
}


void Widget::on_pushButton_2_clicked()
{
    emit restart();
}

