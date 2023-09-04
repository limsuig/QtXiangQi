
#ifndef XIANG_H
#define XIANG_H

#include "cchessman.h"



class XIANG : public CChessman
{
public:
    XIANG(QWidget* parent=nullptr);

    virtual QString getClassType()override;

    virtual bool canChange()override;
public:
    int m_id{};
};

#endif // XIANG_H
