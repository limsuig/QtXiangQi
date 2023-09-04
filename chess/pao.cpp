
#include "pao.h"

PAO::PAO(QWidget* parent):CChessman(parent)
{
    if(CChessman::m_id<45)
        m_label->setText("炮");
    else
        m_label->setText("砲");
}

QString PAO::getClassType(){
    return "PAO";
}

bool PAO::canChange(){
    if(CChessman::selectedChessman[0]!=nullptr&&CChessman::selectedChessman[1]!=nullptr){
        //由于两个棋子已经交换位置，所以这里目的地与出发地要颠倒一下
        desPos=CChessman::selectedChessman[0]->getPos();
        startPos=CChessman::selectedChessman[1]->getPos();

        //如果吃子，判断是否中间有1个棋子
        if(CChessman::selectedChessman[1]->getClassType()!="NONE"){
            if(barrier(startPos,desPos)==1){
                return true;
            }
            else{
                return false;
            }
        }
        //如果不吃子，判断是否没有障碍
        else{
            if(barrier(startPos,desPos)==0){
                return true;
            }
            else{
                return false;
            }
        }
    }
}
