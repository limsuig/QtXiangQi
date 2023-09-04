
#ifndef PAO_H
#define PAO_H

#include "cchessman.h"



class PAO : public CChessman
{
public:
    PAO(QWidget* parent=nullptr);

    virtual QString getClassType()override;

    virtual bool canChange()override;
public:
    int m_id{};
};

#endif // PAO_H
