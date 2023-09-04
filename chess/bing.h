
#ifndef BING_H
#define BING_H

#include "cchessman.h"
#include <typeinfo.h>


class BING : public CChessman
{
public:
    BING(QWidget* parent=nullptr);

    virtual QString getClassType()override;

    virtual bool canChange()override;

public:
    int m_id{};

signals:

public slots:
    void do_clicked();
};

#endif // BING_H
