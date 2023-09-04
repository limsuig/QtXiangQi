
#ifndef CCHESSBOARD_H
#define CCHESSBOARD_H

#include "CChessman.h"
#include "setting.h"
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>

#include "ju.h"
#include "ma.h"
#include "xiang.h"
#include "shi.h"
#include "jiang.h"
#include "pao.h"
#include "bing.h"
#include "none.h"

#include "gameoverwidget.h"

class CChessboard:public QWidget{
    Q_OBJECT
public:
    CChessman* chessmans[90]{nullptr};

public:
    CChessboard(QWidget* parent=nullptr);
    ~CChessboard();
    void paintEvent(QPaintEvent *event);
    void init();


private:
    int m_cellLenght{setting::cellLenght};
    int m_W{setting::boardWidth};
    int m_H{setting::boardHeigth};
    QPoint m_topLeft{setting::topLeft};//{60，55}

signals:

public slots:
    void do_restart();

    void do_huiqi();

};

#endif // CCHESSBOARD_H
