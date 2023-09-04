
#include "ma.h"

MA::MA(QWidget* parent):CChessman(parent)
{

    m_label->setText("马");
}

QString MA::getClassType(){
    return "MA";
}

bool MA::canChange(){
    if(CChessman::selectedChessman[0]!=nullptr&&CChessman::selectedChessman[1]!=nullptr){
        desPos=CChessman::selectedChessman[0]->getPos();
        startPos=CChessman::selectedChessman[1]->getPos();


        //如果上下移动1格并且左右平移2格
        if((desPos.y()-startPos.y()==-90||desPos.y()-startPos.y()==90)
            &&(desPos.x()-startPos.x()==180||desPos.x()-startPos.x()==-180)){

            QPoint des={desPos.x(),startPos.y()};//取出发地的y值，目的地的x值
            if(barrier(startPos,des)==0){
                return true;
            }
            else{
                return false;
            }
        }
        //或者上下移动2格并且左右平移1格
        if((desPos.y()-startPos.y()==-180||desPos.y()-startPos.y()==180)
            &&(desPos.x()-startPos.x()==90||desPos.x()-startPos.x()==-90)){

            QPoint des={startPos.x(),desPos.y()};//取出发地的x值，目的地的y值
            if(barrier(startPos,des)==0){
                return true;
            }
            else{
                return false;
            }
        }
    }
}
