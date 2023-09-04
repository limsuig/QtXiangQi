
#include "jiang.h"

JIANG::JIANG(QWidget* parent):CChessman(parent)
{
    if(CChessman::m_id<45)
        m_label->setText("将");
    else
        m_label->setText("帅");
}

QString JIANG::getClassType(){
    return "JIANG";
}

bool JIANG::canChange(){
    if(CChessman::selectedChessman[0]!=nullptr&&CChessman::selectedChessman[1]!=nullptr){
        desPos=CChessman::selectedChessman[0]->getPos();
        startPos=CChessman::selectedChessman[1]->getPos();

        if(CChessman::selectedChessman[1]->getClassType()=="JIANG"){
            if(barrier(startPos,desPos)==0){
                return true;
            }
        }

        if(this->isRed){
            //红色棋子，不能出帐篷
            if(this->getPos().y()>555&&(this->getPos().x()>200&&this->getPos().x()<560)){
                //如果前后移动一格且没有左右平移
                if((desPos.y()-startPos.y()==-90||desPos.y()-startPos.y()==90)&&desPos.x()-startPos.x()==0){
                    return true;
                }
                //如果左右平移一格并且没有前后移动
                if((desPos.x()-startPos.x()==90||desPos.x()-startPos.x()==-90)&&desPos.y()-startPos.y()==0){
                    return true;
                }
            }
        }
        else{
            //黑色棋子，不能出帐篷
            if(this->getPos().y()<285&&(this->getPos().x()>200&&this->getPos().x()<560)){
                //如果前后移动一格且没有左右平移
                if((desPos.y()-startPos.y()==-90||desPos.y()-startPos.y()==90)&&desPos.x()-startPos.x()==0){
                    return true;
                }
                //如果左右平移一格并且没有前后移动
                if((desPos.x()-startPos.x()==90||desPos.x()-startPos.x()==-90)&&desPos.y()-startPos.y()==0){
                    return true;
                }
            }

            else{
                return false;
            }

        }
    }
}
