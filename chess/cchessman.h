
#ifndef CCHESSMAN_H
#define CCHESSMAN_H

#include <QCheckBox>
#include <QLabel>
#include <QPoint>
#include "setting.h"
#include <stack>



class CChessman : public QCheckBox
{
    Q_OBJECT
public:
    static int count;
    static QPoint desPos;
    static QPoint startPos;
    static CChessman* selectedChessman[2];
    static CChessman* killedChessman;
    static bool turnToRed;
    static QPoint posArray[90];

    typedef struct step{
        bool isKill;
        CChessman* from;
        CChessman* to;
        CChessman* none;
    } step;
    static std::stack<step> steps;


public:
    int m_id{};
    QLabel* m_label{};
    QPoint m_pos{};

    bool isRed{true};
    bool isNone{false};

    int size=setting::chessmanSize;



public:
    CChessman(QWidget* parent=nullptr);
    ~CChessman();

    QPoint getPos()const;

    void changePos(QPoint& startPos,QPoint& desPos);

    virtual bool canChange();//判断是否能交换位置

    void updatePos(const QPoint& pos);

    virtual QString getClassType();

    int barrier(const QPoint& startPos,const QPoint& desPos);

signals:

    void killed();

public slots:
    void do_clicked();


};

#endif // CCHESSMAN_H


