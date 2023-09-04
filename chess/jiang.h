
#ifndef JIANG_H
#define JIANG_H

#include "cchessman.h"



class JIANG : public CChessman
{
public:
    JIANG(QWidget* parent=nullptr);

    virtual QString getClassType()override;

    virtual bool canChange()override;

public:
    int m_id{};
};

#endif // JIANG_H
