
#include "ju.h"

JU::JU(QWidget* parent):CChessman(parent)
{

    m_label->setText("车");
}

QString JU::getClassType(){
    return "JU";
}

bool JU::canChange(){
    if(CChessman::selectedChessman[0]!=nullptr&&CChessman::selectedChessman[1]!=nullptr){
        desPos=CChessman::selectedChessman[0]->getPos();
        startPos=CChessman::selectedChessman[1]->getPos();

        if(barrier(startPos,desPos)==0){
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}
