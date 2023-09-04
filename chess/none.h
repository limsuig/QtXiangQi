
#ifndef NONE_H
#define NONE_H

#include "cchessman.h"
#include <typeinfo.h>


class NONE : public CChessman
{
public:
    NONE(QWidget* parent=nullptr);

    virtual QString getClassType()override;

    virtual bool canChange()override;
public:
    int m_id{};
    QPoint m_pos{};

public slots:
    void do_clicked();

};

#endif // NONE_H
