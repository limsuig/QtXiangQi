
#include "shi.h"

SHI::SHI(QWidget* parent):CChessman(parent)
{
    if(CChessman::m_id<45)
        m_label->setText("士");
    else
        m_label->setText("仕");
}

QString SHI::getClassType(){
    return "SHI";
}

bool SHI::canChange(){
    if(CChessman::selectedChessman[0]!=nullptr&&CChessman::selectedChessman[1]!=nullptr){
        desPos=CChessman::selectedChessman[0]->getPos();
        startPos=CChessman::selectedChessman[1]->getPos();

        if(this->isRed){
            //红色棋子，不能出帐篷
            if(this->getPos().y()>555&&(this->getPos().x()>200&&this->getPos().x()<560)){
                //如果前后移动一格且左右平移一格
                if((desPos.y()-startPos.y()==-90||desPos.y()-startPos.y()==90)
                    &&(desPos.x()-startPos.x()==90||desPos.x()-startPos.x()==-90)){
                    return true;
                }
            }
        }
        else{
            //黑色棋子，不能出帐篷
            if(this->getPos().y()<285&&(this->getPos().x()>200&&this->getPos().x()<560)){
                //如果前后移动一格且左右平移一格
                if((desPos.y()-startPos.y()==-90||desPos.y()-startPos.y()==90)&&
                    (desPos.x()-startPos.x()==90||desPos.x()-startPos.x()==-90)){
                    return true;
                }
            }
            else{
                return false;
            }
        }
    }
    return false;

}
