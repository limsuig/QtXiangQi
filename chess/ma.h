
#ifndef MA_H
#define MA_H

#include "cchessman.h"



class MA : public CChessman
{
public:
    MA(QWidget* parent=nullptr);

    virtual QString getClassType()override;

    virtual bool canChange()override;
public:
    int m_id{};
};

#endif // MA_H
