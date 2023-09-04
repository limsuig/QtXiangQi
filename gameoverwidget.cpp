#include "gameoverwidget.h"
#include "ui_gameoverwidget.h"

gameoverWidget::gameoverWidget(QString color,QString win,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameoverWidget)
{
    ui->setupUi(this);

    this->setGeometry(parent->geometry());
    ui->widget->setGeometry({200,295,440,330});

    ui->label_2->setStyleSheet("color:"+color+";");
    ui->label_2->setText(win);
}

gameoverWidget::~gameoverWidget()
{
    delete ui;
}

void gameoverWidget::on_pushButton_clicked()
{
    emit restart();
    close();

}

