
#ifndef JU_H
#define JU_H

#include "cchessman.h"



class JU : public CChessman
{
public:
    JU(QWidget* parent=nullptr);

    virtual QString getClassType()override;

    virtual bool canChange()override;
public:
    int m_id{};
};

#endif // JU_H
