#include"CChessboard.h"
#include <QApplication>
#include <qDebug>



CChessboard::CChessboard(QWidget* parent):QWidget(parent){
    init();



}



//初始化棋盘
void CChessboard::init(){
    this->setGeometry(10,10,m_W,m_H);

    //创建棋子
    chessmans[0]=new JU(this);
    chessmans[1]=new MA(this);
    chessmans[2]=new XIANG(this);
    chessmans[3]=new SHI(this);
    chessmans[4]=new JIANG(this);
    chessmans[5]=new SHI(this);
    chessmans[6]=new XIANG(this);
    chessmans[7]=new MA(this);
    chessmans[8]=new JU(this);
    for(int i=9;i<19;i++){
        chessmans[i]=new NONE(this);
    }
    chessmans[19]=new PAO(this);
    for(int i=20;i<25;i++){
        chessmans[i]=new NONE(this);
    }
    chessmans[25]=new PAO(this);
    chessmans[26]=new NONE(this);
    for(int i=27;i<36;i=i+2){
        chessmans[i]=new BING(this);
        if(i!=35)
            chessmans[i+1]=new NONE(this);
    }
    for(int i=36;i<54;i++){
        chessmans[i]=new NONE(this);
    }

    for(int i=54;i<63;i=i+2){
        chessmans[i]=new BING(this);
        if(i!=62)
            chessmans[i+1]=new NONE(this);
    }
    chessmans[63]=new NONE(this);
    chessmans[64]=new PAO(this);
    for(int i=65;i<70;i++){
        chessmans[i]=new NONE(this);
    }
    chessmans[70]=new PAO(this);
    chessmans[71]=new NONE(this);
    for(int i=72;i<81;i++){
        chessmans[i]=new NONE(this);
    }
    chessmans[81]=new JU(this);
    chessmans[82]=new MA(this);
    chessmans[83]=new XIANG(this);
    chessmans[84]=new SHI(this);
    chessmans[85]=new JIANG(this);
    chessmans[86]=new SHI(this);
    chessmans[87]=new XIANG(this);
    chessmans[88]=new MA(this);
    chessmans[89]=new JU(this);

    //连接信号槽
    for(int i=0;i<90;i++){
        connect(chessmans[i],&CChessman::killed,this,[=](){

            bool isOver=CChessman::killedChessman->getClassType()=="JIANG"?true:false;
            bool isRed=CChessman::killedChessman->isRed;
            //创建一个新的空棋子
            chessmans[i]=new NONE(this);
            //更新位置为要被替换的棋子的位置
            chessmans[i]->updatePos(CChessman::killedChessman->getPos());
            chessmans[i]->m_id=CChessman::killedChessman->m_id;
            CChessman::posArray[chessmans[i]->m_id]={0,0};//空棋子在数组中对应位置的值为{0,0}
            chessmans[i]->show();

            //删除要被替换的棋子
//            delete CChessman::killedChessman;
//            CChessman::killedChessman=nullptr;

            //移走被吃掉的棋子
            CChessman::killedChessman->updatePos({1000,1000});//放到棋盘外
//            CChessman::steps.top().to=CChessman::killedChessman;
            CChessman::steps.top().none=chessmans[i];
            CChessman::killedChessman=nullptr;

            CChessman::posArray[i]={0,0};//更新数组中对应位置的值

            qDebug()<<"被吃掉的棋子id:"<<chessmans[i]->m_id<<chessmans[i]->getPos();

            //判断是否结束
            if(isOver){
                QString win=!isRed?"红胜!":"黑胜!";
                QString color=!isRed?"red":"black";
                gameoverWidget* over=new gameoverWidget(color,win,this);

                connect(over,&gameoverWidget::restart,this,&CChessboard::do_restart);

                over->show();
            }
        });
    }
}

//重写绘图事件，绘制棋盘
void CChessboard::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //设置画笔
    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);//端点样式
    pen.setJoinStyle(Qt::BevelJoin);//连接样式
    painter.setPen(pen);

    //设置画刷
    QBrush brush;
    QPixmap texturePixmap(":/chessboard.jpg");
    brush.setTexture(texturePixmap);//设置材质图片
    brush.setStyle(Qt::NoBrush);//画刷填充样式
    painter.setBrush(brush);
    QRect rect(0,0,this->width(),this->height());//绘图区
    painter.drawRect(rect);//绘制矩形

    //绘制棋盘
    QBrush boardBrush;
    boardBrush.setStyle(Qt::SolidPattern);//画刷填充样式
    painter.setBrush(brush);
    QRect boardRect(m_topLeft.x(),m_topLeft.y(),m_cellLenght*8,m_cellLenght*9);
    painter.drawRect(boardRect);//绘制矩形

    for(int i=1;i<9;i++){
        QLine line(m_topLeft.x(),m_topLeft.y()+i*m_cellLenght,m_topLeft.x()+m_cellLenght*8,m_topLeft.y()+i*m_cellLenght);
        painter.drawLine(line);
    }
    for(int i=1;i<8;i++){
        QLine line(m_topLeft.x()+i*m_cellLenght,m_topLeft.y(),m_topLeft.x()+i*m_cellLenght,m_topLeft.y()+4*m_cellLenght);
        painter.drawLine(line);
    }
    for(int i=1;i<8;i++){
        QLine line(m_topLeft.x()+i*m_cellLenght,m_topLeft.y()+5*m_cellLenght,m_topLeft.x()+i*m_cellLenght,m_topLeft.y()+9*m_cellLenght);
        painter.drawLine(line);
    }
    QLine line(m_topLeft.x()+3*m_cellLenght,m_topLeft.y(),m_topLeft.x()+5*m_cellLenght,m_topLeft.y()+2*m_cellLenght);
    painter.drawLine(line);
    line.setLine(m_topLeft.x()+3*m_cellLenght,m_topLeft.y()+7*m_cellLenght,m_topLeft.x()+5*m_cellLenght,m_topLeft.y()+9*m_cellLenght);
    painter.drawLine(line);
    line.setLine(m_topLeft.x()+3*m_cellLenght,m_topLeft.y()+2*m_cellLenght,m_topLeft.x()+5*m_cellLenght,m_topLeft.y());
    painter.drawLine(line);
    line.setLine(m_topLeft.x()+3*m_cellLenght,m_topLeft.y()+9*m_cellLenght,m_topLeft.x()+5*m_cellLenght,m_topLeft.y()+7*m_cellLenght);
    painter.drawLine(line);

    QFont font;
    font.setPointSize(50);
    painter.setFont(font);
    painter.drawText(QRect(m_topLeft.x(),m_topLeft.y()+4*m_cellLenght,m_topLeft.x()+8*m_cellLenght,m_cellLenght),"\t\t\t\t\t\t\t楚\t河\t\t\t\t\t\t\t汉\t界");

    QPainterPath anglePath;
    QPoint points[]{QPoint(0,0),QPoint(0,15),QPoint(15,15)};
    anglePath.moveTo(points[0]);
    anglePath.lineTo(points[1]);
    anglePath.lineTo(points[2]);

    painter.save();//保存坐标状态
    painter.translate(m_topLeft.x()+5-2*m_cellLenght,m_topLeft.y()+70+2*m_cellLenght);
    for(int i=0;i<4;i++){
        painter.translate(2*m_cellLenght,0);//
        painter.drawPath(anglePath);

        painter.translate(0,3*m_cellLenght);
        painter.drawPath(anglePath);
        painter.translate(0,-3*m_cellLenght);//恢复位置

        painter.rotate(90);//
        painter.translate(25,-15);
        painter.drawPath(anglePath);
        painter.translate(-25,15);
        painter.rotate(-90);

        painter.translate(0,3*m_cellLenght);
        painter.rotate(90);
        painter.translate(25,-15);
        painter.drawPath(anglePath);
        painter.translate(-25,15);
        painter.rotate(-90);
        painter.translate(0,-3*m_cellLenght);

        painter.translate(2*m_cellLenght-25,15);//
        painter.rotate(-90);
        painter.drawPath(anglePath);
        painter.rotate(90);
        painter.translate(25-2*m_cellLenght,-15);

        painter.translate(0,3*m_cellLenght);
        painter.translate(2*m_cellLenght-25,15);
        painter.rotate(-90);
        painter.drawPath(anglePath);
        painter.rotate(90);
        painter.translate(25-2*m_cellLenght,-15);
        painter.translate(0,-3*m_cellLenght);

        painter.translate(2*m_cellLenght-10,40);//
        painter.rotate(-180);
        painter.drawPath(anglePath);
        painter.rotate(180);
        painter.translate(10-2*m_cellLenght,-40);

        painter.translate(0,3*m_cellLenght);
        painter.translate(2*m_cellLenght-10,40);
        painter.rotate(-180);
        painter.drawPath(anglePath);
        painter.rotate(180);
        painter.translate(10-2*m_cellLenght,-40);
        painter.translate(0,-3*m_cellLenght);
    }
    painter.restore();
    painter.translate(m_topLeft.x()+5-5*m_cellLenght,m_topLeft.y()+70+m_cellLenght);
    for(int i=0;i<2;i++){
        painter.translate(6*m_cellLenght,0);//画右上
        painter.drawPath(anglePath);

        painter.translate(0,5*m_cellLenght);//画下半
        painter.drawPath(anglePath);
        painter.translate(0,-5*m_cellLenght);//恢复位置

        painter.rotate(90);//画右下
        painter.translate(25,-15);
        painter.drawPath(anglePath);
        painter.translate(-25,15);
        painter.rotate(-90);

        painter.translate(0,5*m_cellLenght);
        painter.rotate(90);
        painter.translate(25,-15);
        painter.drawPath(anglePath);
        painter.translate(-25,15);
        painter.rotate(-90);
        painter.translate(0,-5*m_cellLenght);

        painter.translate(-25,15);//画左上
        painter.rotate(-90);
        painter.drawPath(anglePath);
        painter.rotate(90);
        painter.translate(25,-15);

        painter.translate(0,5*m_cellLenght);
        painter.translate(-25,15);
        painter.rotate(-90);
        painter.drawPath(anglePath);
        painter.rotate(90);
        painter.translate(25,-15);
        painter.translate(0,-5*m_cellLenght);

        painter.translate(-10,40);//画左下
        painter.rotate(-180);
        painter.drawPath(anglePath);
        painter.rotate(180);
        painter.translate(10,-40);

        painter.translate(0,5*m_cellLenght);
        painter.translate(-10,40);
        painter.rotate(-180);
        painter.drawPath(anglePath);
        painter.rotate(180);
        painter.translate(10,-40);
        painter.translate(0,-5*m_cellLenght);
    }
}

//重新开始
void CChessboard::do_restart(){
    for(int i=0;i<90;i++){
        delete chessmans[i];
        chessmans[i]=nullptr;
    }

    CChessman::count=0;
    CChessman::turnToRed=true;

    CChessman::selectedChessman[0]=nullptr;
    CChessman::selectedChessman[1]=nullptr;

    //清空栈
    while(!CChessman::steps.empty()){
        CChessman::steps.pop();
    }

    init();
}

//悔棋
void CChessboard::do_huiqi(){

    if(!CChessman::steps.empty()){

        CChessman::step s=CChessman::steps.top();
        if(!s.isKill){
            qDebug()<<"!iskill";
            QPoint startPos=s.from->getPos();
            QPoint desPos=s.to->getPos();
            //交换位置
            s.from->updatePos(desPos);
            s.to->updatePos(startPos);

            CChessman::steps.pop();

            //成功交换后改变turnToRed的值
            CChessman::turnToRed=!CChessman::turnToRed;

            //移动后更新在数组中的值,值的位置不重要，数组中有这个值就行。
            CChessman::posArray[s.from->m_id]=s.from->getPos();
        }
        else{
            qDebug()<<"iskill";
            QPoint startPos=s.from->getPos();
            QPoint desPos=s.none->getPos();
            s.from->updatePos(desPos);
            s.to->updatePos(startPos);

            //移动后更新在数组中的值,值的位置不重要，数组中有这个值就行。
            CChessman::posArray[s.from->m_id]=s.from->getPos();
            CChessman::posArray[s.none->m_id]=s.to->getPos();

            //成功交换后改变turnToRed的值
            CChessman::turnToRed=!CChessman::turnToRed;

            //删除作为替换的空棋子
            chessmans[s.none->m_id]=s.to;
            delete s.none;
            s.none=nullptr;

            CChessman::steps.pop();


        }
    }

}

CChessboard::~CChessboard(){

}
