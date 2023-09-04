
#include "bing.h"

BING::BING(QWidget* parent):CChessman(parent)
{
    if(CChessman::m_id<45)
        m_label->setText("卒");
    else
        m_label->setText("兵");

    connect(this,&QCheckBox::clicked,this,&BING::do_clicked);


}

bool BING::canChange(){
    if(CChessman::selectedChessman[0]!=nullptr&&CChessman::selectedChessman[1]!=nullptr){
        desPos=CChessman::selectedChessman[0]->getPos();
        startPos=CChessman::selectedChessman[1]->getPos();

        if(this->isRed){
            //红棋子未过河
            if(this->getPos().y()>375){
                //红色棋子如果前进一格且没有左右平移
                if(desPos.y()-startPos.y()==-90&&desPos.x()-startPos.x()==0){
                    return true;
                }
            }
            //过河后
            else{
                if(this->getPos().y()==375){
                    //红色棋子如果前进一格且没有左右平移
                    if(desPos.y()-startPos.y()==-90&&desPos.x()-startPos.x()==0){
                        return true;
                    }
                }
                //红色棋子如果前进一格且没有左右平移
                if(desPos.y()-startPos.y()==-90&&desPos.x()-startPos.x()==0){
                    return true;
                }
                //如果左右平移一格并且没有前后移动
                if((desPos.x()-startPos.x()==90||desPos.x()-startPos.x()==-90)&&desPos.y()-startPos.y()==0){
                    return true;
                }
            }
        }
        else{
            //黑棋子未过河
            if(this->getPos().y()<465){
                if(desPos.y()-startPos.y()==90&&desPos.x()-startPos.x()==0){
                    return true;
                }
            }
            //过河后
            else{
                if(this->getPos().y()==465){
                    if(desPos.y()-startPos.y()==90&&desPos.x()-startPos.x()==0){
                        return true;
                    }
                }
                if(desPos.y()-startPos.y()==90&&desPos.x()-startPos.x()==0){
                    return true;
                }
                if((desPos.x()-startPos.x()==90||desPos.x()-startPos.x()==-90)&&desPos.y()-startPos.y()==0){
                    return true;
                }
                else{
                    return false;
                }
            }
        }
    }
    return false;
}

void BING::do_clicked(){




}

QString BING::getClassType(){
    return "BING";
}
