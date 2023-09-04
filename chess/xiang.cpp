
#include "xiang.h"

XIANG::XIANG(QWidget* parent):CChessman(parent)
{
    if(CChessman::m_id<45)
        m_label->setText("象");
    else
        m_label->setText("相");
}

QString XIANG::getClassType(){
    return "XIANG";
}

bool XIANG::canChange(){

    if(CChessman::selectedChessman[0]!=nullptr&&CChessman::selectedChessman[1]!=nullptr){
        desPos=CChessman::selectedChessman[0]->getPos();
        startPos=CChessman::selectedChessman[1]->getPos();

        if(this->isRed){
            //红色棋子未过河
            if(this->getPos().y()>375){
                //如果前后移动2格并且左右平移2格
                if((desPos.y()-startPos.y()==-180||desPos.y()-startPos.y()==180)
                    &&(desPos.x()-startPos.x()==180||desPos.x()-startPos.x()==-180)){
                    QPoint midxStart={startPos.x()+(desPos.x()-startPos.x())/2,startPos.y()};//取x轴上的中点，出发地的y值
                    QPoint midxDes={startPos.x()+(desPos.x()-startPos.x())/2,desPos.y()};//取x轴上的中点，目的地的y值
                    if(barrier(midxStart,midxDes)==0){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
            }
        }
        else{
            //黑色棋子未过河
            if(this->getPos().y()<465){
                //如果前后移动2格并且左右平移2格
                if((desPos.y()-startPos.y()==-180||desPos.y()-startPos.y()==180)
                    &&(desPos.x()-startPos.x()==180||desPos.x()-startPos.x()==-180)){
                    QPoint midxStart={startPos.x()+(desPos.x()-startPos.x())/2,startPos.y()};//取x轴上的中点，出发地的y值
                    QPoint midxDes={startPos.x()+(desPos.x()-startPos.x())/2,desPos.y()};//取x轴上的中点，目的地的y值
                    if(barrier(midxStart,midxDes)==0){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
            }
        }
    }
}
