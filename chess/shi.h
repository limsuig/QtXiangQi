
#ifndef SHI_H
#define SHI_H

#include "cchessman.h"



class SHI : public CChessman
{
public:
    SHI(QWidget* parent=nullptr);

    virtual QString getClassType()override;

    virtual bool canChange()override;
public:
    int m_id{};
};

#endif // SHI_H
