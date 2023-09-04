#ifndef GAMEOVERWIDGET_H
#define GAMEOVERWIDGET_H

#include <QWidget>

namespace Ui {
class gameoverWidget;
}

class gameoverWidget : public QWidget
{
    Q_OBJECT

public:
    explicit gameoverWidget(QString color,QString win,QWidget *parent = nullptr);
    ~gameoverWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::gameoverWidget *ui;

signals:
    void restart();
};

#endif // GAMEOVERWIDGET_H
