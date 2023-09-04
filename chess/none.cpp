
#include "none.h"




NONE::NONE(QWidget* parent):CChessman(parent)
{


    //覆盖原样式
    QString qss=QString("QCheckBox::indicator{width:60px;height:60px;}"
                          "QCheckBox::indicator:checked{border-radius:35px;border:0px solid;}"
                          "QCheckBox::indicator:unchecked{border-radius:35px;border:0px solid;}"
                          );
    this->setStyleSheet(qss);

    CChessman::isNone=true;

    connect(this,&QCheckBox::clicked,this,&NONE::do_clicked);

    CChessman::posArray[CChessman::m_id]={0,0};//空棋子在数组中对应位置的值为{0,0}

}

void NONE::do_clicked(){
    //空棋子只能被赋值给CChessman::selectedChessman[1]
    qDebug()<<"选中空棋子"<<CChessman::getPos();

    if(CChessman::selectedChessman[0]!=nullptr){
        CChessman::selectedChessman[1]=this;
        QPoint startPos=CChessman::selectedChessman[0]->getPos();
        QPoint desPos=CChessman::selectedChessman[1]->getPos();
        changePos(startPos,desPos);

    }

    if(CChessman::selectedChessman[0]!=nullptr&&CChessman::selectedChessman[1]!=nullptr){
        if(!(CChessman::selectedChessman[0]->isRed==CChessman::turnToRed)||!CChessman::selectedChessman[0]->canChange()){
            startPos=CChessman::selectedChessman[0]->getPos();
            desPos=CChessman::selectedChessman[1]->getPos();
            changePos(startPos,desPos);

            selectedChessman[0]=nullptr;
            selectedChessman[1]=nullptr;

            qDebug()<<"无法移动";
            qDebug()<<(turnToRed?"轮到红色棋子行动":"轮到黑色棋子行动");
        }
        else{


            //成功交换后
            CChessman::turnToRed=!CChessman::turnToRed;
            qDebug()<<(turnToRed?"轮到红色棋子行动":"轮到黑色棋子行动");

            CChessman::step s={false,CChessman::selectedChessman[0],CChessman::selectedChessman[1],nullptr};
            CChessman::steps.push(s);

            selectedChessman[0]=nullptr;
            selectedChessman[1]=nullptr;
        }
    }
}

QString NONE::getClassType(){
    return "NONE";
}

bool NONE::canChange(){

    return true;
}
