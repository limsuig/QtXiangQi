
#include "cchessman.h"
#include "qevent.h"


int CChessman::count{0};
QPoint CChessman::desPos{};
QPoint CChessman::startPos{};

CChessman* CChessman::selectedChessman[2]{};
CChessman* CChessman::killedChessman{};
bool CChessman::turnToRed{true};

QPoint CChessman::posArray[90]{{0,0}};
std::stack<CChessman::step> CChessman::steps;

CChessman::CChessman(QWidget* parent):QCheckBox(parent)
{
    m_id=CChessman::count++;//根据创建实例的顺序给m_id赋值
    isRed=(m_id<45?false:true);

    QPoint tp=setting::ChessmanTopLeft;

    int offset=setting::cellLenght;//偏移量为棋盘网格大小
    tp={tp.x()+(m_id%9)*offset,tp.y()+(m_id/9)*offset};//根据m_id的值设置棋子的初始位置，从左往右，从上到下
    this->setGeometry(tp.x(),tp.y(),size,size);//设置棋子位置和尺寸
    m_pos=tp;//保存棋子位置

    posArray[m_id]=m_pos;//

    m_label=new QLabel("",this);
    m_label->setGeometry(14,7,60,60);

    QString color{"black"};
    if(m_id>44)
        color="red";//后半部分的棋子为红色

    m_label->setStyleSheet("QLabel{color:"+color+";font:38pt;}");

    QString qss=QString("QCheckBox{"
                          "background-color:white;"
                          "border-radius:40px;"
                          "border:5px solid "+color+";"
                          "}"
                          "QCheckBox::indicator{width:60px;height:60px;}"
                          "QCheckBox::indicator:checked{border-radius:35px;border:5px solid green;}"//复选框勾选时的样式
                          "QCheckBox::indicator:unchecked{border-radius:35px;border:0px solid;}"//复选框未勾选时的样式
                          );
    this->setStyleSheet(qss);

    connect(this,&QCheckBox::clicked,this,&CChessman::do_clicked);

    this->show();
}


void CChessman::do_clicked(){

    //如果点击了空棋子，则不执行父类中的do_clicked
    if(this->isNone){
        return;
    }

    //如果勾选，需要保证同阵营只有一个被勾选
    if(this->isChecked()){
        //如果未选中任何棋子
        if(selectedChessman[0]==nullptr){
            selectedChessman[0]=this;
            qDebug()<<"-------选中棋子[0]"<<selectedChessman[0]->m_id<<(this->getPos().x()+70)/90<<(this->getPos().y()+75)/90;
        }
        //如果只选中一个棋子
        else{

            //如果上一个棋子与当前棋子同一阵营
            if(selectedChessman[0]->isRed==this->isRed){
                selectedChessman[0]->setChecked(false);//将上一个棋子取消勾选
                selectedChessman[0]=this;//重新设置
                qDebug()<<"重新选择棋子[0]:"<<selectedChessman[0]->m_id<<(this->getPos().x()+70)/90<<(this->getPos().y()+75)/90;
            }
            //如果不同阵营
            else{
                selectedChessman[1]=this;//
                qDebug()<<"选中棋子[1]:"<<selectedChessman[1]->m_id<<(this->getPos().x()+70)/90<<(this->getPos().y()+75)/90;

                QPoint startPos=selectedChessman[0]->getPos();
                QPoint desPos=selectedChessman[1]->getPos();

                changePos(startPos,desPos);

            }
        }
    }
    else{
        selectedChessman[0]=nullptr;
        selectedChessman[1]=nullptr;
        qDebug()<<"清空selectedChessman";
    }

    //判断是否能移动，如果不能则再交换回来
    if(selectedChessman[0]!=nullptr&&selectedChessman[1]!=nullptr){

        //不能移动
        //未轮到本阵营或不符合移动规则
        if(!(selectedChessman[0]->isRed==turnToRed)||!selectedChessman[0]->canChange()){
            startPos=selectedChessman[0]->getPos();
            desPos=selectedChessman[1]->getPos();
            changePos(startPos,desPos);

            selectedChessman[0]=nullptr;
            selectedChessman[1]=nullptr;

            qDebug()<<"无法移动";
            qDebug()<<(turnToRed?"轮到红色棋子行动":"轮到黑色棋子行动");


        }
        else{

            step s={true,selectedChessman[0],selectedChessman[1],nullptr};
            steps.push(s);

            //发射信号
            killedChessman=selectedChessman[1];
            emit killed();



            //成功交换后改变turnToRed的值
            turnToRed=!turnToRed;
            qDebug()<<(turnToRed?"轮到红色棋子行动":"轮到黑色棋子行动");



            selectedChessman[0]=nullptr;
            selectedChessman[1]=nullptr;

        }


    }
}



bool CChessman::canChange(){
    qDebug()<<"父类，canChange";
    return true;
}
void CChessman::changePos(QPoint& startPos,QPoint& desPos){

    selectedChessman[0]->updatePos(desPos);
    selectedChessman[1]->updatePos(startPos);
    qDebug()<<"=========交换位置=================";
    qDebug()<<"[1]startPos"<<startPos<<">>>[0]desPos"<<desPos;

    selectedChessman[0]->setChecked(false);//取消勾选
    selectedChessman[1]->setChecked(false);//取消勾选

    //移动后更新在数组中的值,值的位置不重要，数组中有这个值就行。
    posArray[selectedChessman[0]->m_id]=selectedChessman[0]->getPos();
}

QString CChessman::getClassType(){
    return "CCHessman";
}

int CChessman::barrier(const QPoint& startPos,const QPoint& desPos){
    int res=0;

    //如果是在x轴上移动
    if(startPos.x()==desPos.x()){
        if(startPos.y()<desPos.y()){
            for(int i=0;i<90;i++){
                if(posArray[i].x()==startPos.x()&&posArray[i].y()>startPos.y()&&posArray[i].y()<desPos.y()){
                    qDebug()<<posArray[i];
                    res++;
                }
            }
        }
        if(startPos.y()>desPos.y()){
            for(int i=0;i<90;i++){
                if(posArray[i].x()==startPos.x()&&posArray[i].y()<startPos.y()&&posArray[i].y()>desPos.y()){
                    qDebug()<<posArray[i];
                    res++;
                }
            }
        }
    }
    else{
        //如果是在y轴上移动
        if(startPos.y()==desPos.y()){
            if(startPos.x()<desPos.x()){
                for(int i=0;i<90;i++){
                    if(posArray[i].y()==startPos.y()&&posArray[i].x()>startPos.x()&&posArray[i].x()<desPos.x()){
                        qDebug()<<posArray[i];
                        res++;
                    }
                }
            }
            if(startPos.x()>desPos.x()){
                for(int i=0;i<90;i++){
                    if(posArray[i].y()==startPos.y()&&posArray[i].x()<startPos.x()&&posArray[i].x()>desPos.x()){
                        qDebug()<<posArray[i];
                        res++;
                    }
                }
            }
        }
        else{
            //如果斜方向移动将返回值设置为100
            qDebug()<<"斜方向移动";
            res=100;
        }
    }

    qDebug()<<res<<"个障碍";
    return res;
}

void CChessman::updatePos(const QPoint& pos){
    this->setGeometry(pos.x(),pos.y(),size,size);
    this->m_pos=pos;//更新成员变量
}

QPoint CChessman::getPos()const{
    return m_pos;
}

CChessman::~CChessman(){

}
