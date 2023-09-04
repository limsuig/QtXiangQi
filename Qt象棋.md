# Qt象棋

## 一、程序概述

> 本程序使用Qt实现了中国象棋的下棋规则和悔棋功能。

## 二、代码说明

### 棋盘类CChessboard

> ​	棋盘类`CChessboard`，负责绘制棋盘、创建棋子类`CChessman`、判定胜负、重新开始功能和悔棋功能。

#### 绘制棋盘

重写`paintEvent`事件，从{60，55}的位置开始画线。

```C++
void CChessboard::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //设置画笔
    QPen pen;
    pen.setWidth(4);//线条粗细
    pen.setColor(Qt::black);//线条颜色
    pen.setStyle(Qt::SolidLine);//线条样式
    pen.setCapStyle(Qt::FlatCap);//端点样式
    pen.setJoinStyle(Qt::BevelJoin);//连接样式
    painter.setPen(pen);
    //设置画刷，绘制背景
    QBrush brush;
    QPixmap texturePixmap(":/chessboard.jpg");
    brush.setTexture(texturePixmap);//设置材质图片
    brush.setStyle(Qt::NoBrush);//画刷填充样式
    painter.setBrush(brush);
    QRect rect(0,0,this->width(),this->height());//绘图区
    painter.drawRect(rect);//绘制矩形
    //设置画刷，绘制棋盘
    QBrush boardBrush;
    boardBrush.setStyle(Qt::SolidPattern);//画刷填充样式
    painter.setBrush(brush);
    QRect boardRect(m_topLeft.x(),m_topLeft.y(),m_cellLenght*8,m_cellLenght*9);//先画最外一圈矩形
    painter.drawRect(boardRect);//绘制矩形
	//画8条横线
    for(int i=1;i<9;i++){
        //m_topLeft={60,55}，line(起始点x坐标，起始点y坐标，结束点x坐标，结束点y坐标)
        QLine line(m_topLeft.x(),m_topLeft.y()+i*m_cellLenght,m_topLeft.x()+m_cellLenght*8,m_topLeft.y()+i*m_cellLenght);
        painter.drawLine(line);
    }
    ...
    //添加“楚河汉界”字样
    QFont font;
    font.setPointSize(50);//字体大小
    painter.setFont(font);
    painter.drawText(QRect(m_topLeft.x(),m_topLeft.y()+4*m_cellLenght,m_topLeft.x()+8*m_cellLenght,m_cellLenght),"\t\t\t\t\t\t\t楚\t河\t\t\t\t\t\t\t汉\t界");
    //创建一个直角路径
    QPainterPath anglePath;
    QPoint points[]{QPoint(0,0),QPoint(0,15),QPoint(15,15)};
    anglePath.moveTo(points[0]);
    anglePath.lineTo(points[1]);
    anglePath.lineTo(points[2]);
    //绘制直角
	painter.save();//保存坐标状态
    painter.translate(m_topLeft.x()+5-2*m_cellLenght,m_topLeft.y()+70+2*m_cellLenght);//设置起始位置再向左偏移一个间隔（2*m_cellLenght）
    for(int i=0;i<4;i++){
        //画右上的直角
        painter.translate(2*m_cellLenght,0);//向右偏移一个间隔（2*m_cellLenght）
        painter.drawPath(anglePath);
        //恢复位置
        painter.translate(0,3*m_cellLenght);
        painter.drawPath(anglePath);
        painter.translate(0,-3*m_cellLenght);
        ...
    }
```

效果图：

![棋盘](E:\Users\limsuig\Documents\Qt Projects\XIANGQI\棋盘.png)

#### 创建棋子类

棋子类的实例会根据自身被创建时的`m_id`确定自己在棋盘上的位置，所以初始化棋盘时无需指定每个棋子的位置，只需要确定棋子的类型。一共创建90个棋子，其中有58个`NONE`类型的棋子。

```C++
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
    for(int i=9;i<19;i++)
        chessmans[i]=new NONE(this);
    chessmans[19]=new PAO(this);
    for(int i=20;i<25;i++)
        chessmans[i]=new NONE(this);
    chessmans[25]=new PAO(this);
    chessmans[26]=new NONE(this);
    for(int i=27;i<36;i=i+2){
        chessmans[i]=new BING(this);
        if(i!=35)
            chessmans[i+1]=new NONE(this);
    }
    for(int i=36;i<54;i++)
        chessmans[i]=new NONE(this);
    for(int i=54;i<63;i=i+2){
        chessmans[i]=new BING(this);
        if(i!=62)
            chessmans[i+1]=new NONE(this);
    }
    chessmans[63]=new NONE(this);
    chessmans[64]=new PAO(this);
    for(int i=65;i<70;i++)
        chessmans[i]=new NONE(this);
    chessmans[70]=new PAO(this);
    chessmans[71]=new NONE(this);
    for(int i=72;i<81;i++)
        chessmans[i]=new NONE(this);
    chessmans[81]=new JU(this);
    chessmans[82]=new MA(this);
    chessmans[83]=new XIANG(this);
    chessmans[84]=new SHI(this);
    chessmans[85]=new JIANG(this);
    chessmans[86]=new SHI(this);
    chessmans[87]=new XIANG(this);
    chessmans[88]=new MA(this);
    chessmans[89]=new JU(this);
```

效果图：

![棋子](E:\Users\limsuig\Documents\Qt Projects\XIANGQI\棋子.png)

#### 判定胜负

创建棋子实例的同时连接信号槽，用于处理吃子同时判断被吃掉的棋子是否为“将”或“帅”，如果是，则弹出结束窗口。

```C++
//连接信号槽
    for(int i=0;i<90;i++){
        connect(chessmans[i],&CChessman::killed,this,[=](){
            bool isOver=CChessman::killedChessman->getClassType()=="JIANG"?true:false;//判断被吃掉的棋子类型
            bool isRed=CChessman::killedChessman->isRed;//判断被吃掉的棋子是否为红方
            //创建一个新的空棋子，替换被吃掉的棋子
            chessmans[i]=new NONE(this);
            //更新空棋子位置为要被吃掉的棋子的位置
            chessmans[i]->updatePos(CChessman::killedChessman->getPos());
            chessmans[i]->m_id=CChessman::killedChessman->m_id;
            CChessman::posArray[chessmans[i]->m_id]={0,0};//空棋子在数组中对应位置的值为{0,0}
            chessmans[i]->show();
            //移走被吃掉的棋子
            CChessman::killedChessman->updatePos({1000,1000});//放到棋盘外
            CChessman::steps.top().none=chessmans[i];//获取新创建的空棋子
            CChessman::killedChessman=nullptr;     
            //更新数组中对应位置的值
            CChessman::posArray[i]={0,0};
            //判断是否结束
            if(isOver){
                QString win=!isRed?"红胜!":"黑胜!";
                QString color=!isRed?"red":"black";
                gameoverWidget* over=new gameoverWidget(color,win,this);//创建游戏结束窗口，传入获胜方信息
                //连接信号槽,点击结束窗口中的“确定”按钮将执行CChessboard的do_restart槽函数
                connect(over,&gameoverWidget::restart,this,&CChessboard::do_restart);
                over->show();//显示窗口
            }
        });
    }
```

#### 重新开始 

```C++
//重新开始
void CChessboard::do_restart(){
    //释放所有棋子
    for(int i=0;i<90;i++){
        delete chessmans[i];
        chessmans[i]=nullptr;
    }
    //将CChessman类的静态成员设置为初始值
    CChessman::count=0;
    CChessman::turnToRed=true;
    CChessman::selectedChessman[0]=nullptr;
    CChessman::selectedChessman[1]=nullptr;
    //清空栈
    while(!CChessman::steps.empty()){
        CChessman::steps.pop();
    }
    //初始化棋盘
    init();
}
```

#### 悔棋

创建一个栈用来存储每次走棋的信息，点击“悔棋”按钮发射信号，槽函数中取出栈顶数据执行操作后弹出栈顶数据。

```C++
typedef struct step{
        bool isKill;
        CChessman* from;//指向行动的棋子
        CChessman* to;//指向目的地的空棋子或被吃掉的棋子
        CChessman* none;//指向替换被吃掉的棋子的棋子
} step;
static std::stack<step> steps;
```

走棋结束后插入一个stpe：

```C++
step s={true,selectedChessman[0],nullptr,nullptr};
//CChessman::step s={false,CChessman::selectedChessman[0],CChessman::selectedChessman[1],nullptr};
steps.push(s);
```

槽函数

```C++
void CChessboard::do_huiqi(){
    if(!CChessman::steps.empty()){
        CChessman::step s=CChessman::steps.top();//取出栈顶元素
        //判断走棋类型
        if(!s.isKill){
            QPoint startPos=s.from->getPos();
            QPoint desPos=s.to->getPos();
            //交换位置
            s.from->updatePos(desPos);
            s.to->updatePos(startPos);
            //悔棋后要改变turnToRed的值
            CChessman::turnToRed=!CChessman::turnToRed;
            //悔棋后更新在数组中的值
            CChessman::posArray[s.from->m_id]=s.from->getPos();
            //操作完毕后弹出栈顶元素
            CChessman::steps.pop();
        }
        else{
            QPoint startPos=s.from->getPos();
            QPoint desPos=s.none->getPos();
            s.from->updatePos(desPos);
            s.to->updatePos(startPos);
            //悔棋后更新在数组中的值
            CChessman::posArray[s.from->m_id]=s.from->getPos();
            CChessman::posArray[s.none->m_id]=s.to->getPos();
            CChessman::turnToRed=!CChessman::turnToRed;
            //删除作为替换的空棋子
            chessmans[s.none->m_id]=s.to;//获取恢复的棋子
            delete s.none;
            s.none=nullptr;
            //操作完毕后弹出栈顶元素
            CChessman::steps.pop();
        }
    }
}
```

### 棋子类CChessman

> 棋子类`CChessman`，继承自`QCheckBoc`类，负责实现棋子样式和走棋规则。棋子类`CChessman`作为基类派生出具体的`JU`类、`MA`类、`XIANG`类、`SHI`类、`JIANG`类、`PAO`类、`BING`类和`NONE`类。基类实现棋子样式的设置、`QCheckBox::clicked`信号的处理、实现改变棋位置功能、获取棋子位置功能和计算棋子与目的地之间的障碍数。子类实现各自的`canChange()`方法和`getClassType()`方法，判断是否能移动和获取子类的类型，以及在构造函数中设置棋子名字。
>
> 棋盘上有90个棋子（58个“NONE”类型的棋子，它们不显示在棋盘上），当点击一个棋子时，选中这个棋子，然后再点击目的地（实际上是点击了目的地上的空棋子）就会交换两个棋子的位置，从而实现棋子移动的效果。如果目的地上的不是空棋子，而是敌方棋子，同样是两个棋子交换位置，然后敌方棋子被替换为新创建的空棋子。

#### 棋子样式

CChessman类有一个静态成员变量`count`，执行构造函数时将`count`的值赋给成员变量`m_id`，`m_id`小于45的是处于棋盘上半的黑色棋子（空棋子会用新的样式覆盖）。

```C++
CChessman::CChessman(QWidget* parent):QCheckBox(parent)
{
    m_id=CChessman::count++;//根据创建实例的顺序给m_id赋值
    isRed=(m_id<45?false:true);//确定棋子颜色
    QPoint tp=setting::ChessmanTopLeft;//起始位置
    int offset=setting::cellLenght;//偏移量为棋盘网格大小
    tp={tp.x()+(m_id%9)*offset,tp.y()+(m_id/9)*offset};//根据m_id的值设置棋子的初始位置，从左往右，从上到下
    this->setGeometry(tp.x(),tp.y(),size,size);//设置棋子位置和尺寸
    m_pos=tp;//保存棋子位置
    posArray[m_id]=m_pos;//将位置信息存放进数组
    m_label=new QLabel("",this);//显示棋子名字，在子类的构造函数中会具体设置
    m_label->setGeometry(14,7,60,60);
    //定义样式
    QString color{"black"};
    if(m_id>44)
        color="red";//后半部分的棋子为红色
    m_label->setStyleSheet("QLabel{color:"+color+";font:38pt;}");//标签样式
    //复选框样式
    QString qss=QString("QCheckBox{"
                          "background-color:white;"
                          "border-radius:40px;"
                          "border:5px solid "+color+";"
                          "}"
                          "QCheckBox::indicator{width:60px;height:60px;}"
                          "QCheckBox::indicator:checked{border-radius:35px;border:5px solid green;}"//复选框勾选时的样式
                          "QCheckBox::indicator:unchecked{border-radius:35px;border:0px solid;}"//复选框未勾选时的样式
                          );
    this->setStyleSheet(qss);//设置样式
    connect(this,&QCheckBox::clicked,this,&CChessman::do_clicked);
    this->show();
}
```

#### 点击棋子

被点击时判断是否已勾选，如果是，则返回；如果不是，则将指向自身的指针存入`CChessman::selectedChessman[0]`中，当点击另一个棋子时，判断与上一个被点击的棋子是否是同阵营，如果是，则将`CChessman::selectedChessman[0]`中的值改为指向自身的指针，如果不是，则将`CChessman::selectedChessman[1]`中的值设置为指向自身的指针。

```C++
CChessman* CChessman::selectedChessman[2]{}
CChessman* CChessman::killedChessman{};
void CChessman::do_clicked(){
    //如果点击了空棋子，则不执行父类中的do_clicked
    if(this->isNone){
        return;
    }
    //如果勾选，需要保证同阵营只有一个被勾选
    if(this->isChecked()){
        //如果未选中任何棋子
        if(selectedChessman[0]==nullptr){
            selectedChessman[0]=this;//存入数组
        }
        //如果只选中一个棋子
        else{
            //如果上一个棋子与当前棋子同一阵营
            if(selectedChessman[0]->isRed==this->isRed){
                selectedChessman[0]->setChecked(false);//将上一个棋子取消勾选
                selectedChessman[0]=this;//重新设置
            }
            //如果不同阵营
            else{
                selectedChessman[1]=this;//存入数组
                //当selectedChessman中的两个元素都不为空时，交换其指向的两个棋子的位置
                QPoint startPos=selectedChessman[0]->getPos();
                QPoint desPos=selectedChessman[1]->getPos();
                changePos(startPos,desPos);
            }
        }
    }
    //如果取消勾选棋子，则selectedChessman中的两个值都设为空
    else{
        selectedChessman[0]=nullptr;
        selectedChessman[1]=nullptr;
    }
    //判断是否能移动，如果不能则再交换回来
    if(selectedChessman[0]!=nullptr&&selectedChessman[1]!=nullptr){
        //如果未轮到本阵营或不符合移动规则，则将selectedChessman中指向的两个棋子的位置再交换一遍，实现无法移动的效果
        if(!(selectedChessman[0]->isRed==turnToRed)||!selectedChessman[0]->canChange()){
            startPos=selectedChessman[0]->getPos();
            desPos=selectedChessman[1]->getPos();
            changePos(startPos,desPos);
            //清空selectedChessman中的值
            selectedChessman[0]=nullptr;
            selectedChessman[1]=nullptr;
            qDebug()<<(turnToRed?"轮到红色棋子行动":"轮到黑色棋子行动");
        }
        //如果能移动，即selectedChessman[0]吃掉了selectedChessman[1]
        else{
            //存储本次走棋的信息
            step s={true,selectedChessman[0],selectedChessman[1],nullptr};
            steps.push(s);
            //发射吃子信号
            killedChessman=selectedChessman[1];
            emit killed();

            //走棋结束后改变turnToRed的值
            turnToRed=!turnToRed;
            qDebug()<<(turnToRed?"轮到红色棋子行动":"轮到黑色棋子行动");
            //清空selectedChessman中的值
            selectedChessman[0]=nullptr;
            selectedChessman[1]=nullptr;
        }
    }
}
```

#### 计算障碍

棋子在棋盘上的位置信息存储进一个QPoint数组`CChessman::posArray[90]`里（静态成员变量），实际上只需要存放32个值，剩下的值全是{0，0}。数组的索引与棋子的m_id相同。在`barrier()`方法中遍历posArray数组得到出发点到目的地之间的棋子个数

```C++
QPoint CChessman::posArray[90]{{0,0}};
int CChessman::barrier(const QPoint& startPos,const QPoint& desPos){
    int res=0;
    //如果是在y轴上移动
    if(startPos.x()==desPos.x()){
        //从上到下
        if(startPos.y()<desPos.y()){
            for(int i=0;i<90;i++){
                //找到y轴上大于出发地小于目的地的元素
                if(posArray[i].x()==startPos.x()&&posArray[i].y()>startPos.y()&&posArray[i].y()<desPos.y())
                    res++;
            }
        }
        //从下到上
        if(startPos.y()>desPos.y()){
            for(int i=0;i<90;i++){
                //找到y轴上小于出发地大于目的地的元素
                if(posArray[i].x()==startPos.x()&&posArray[i].y()<startPos.y()&&posArray[i].y()>desPos.y())
                    res++;
            }
        }
    }
    else{
        //如果是在x轴上移动
        if(startPos.y()==desPos.y()){
            //从左到右
            if(startPos.x()<desPos.x()){
                for(int i=0;i<90;i++){
                    //找到x轴上大于出发地小于目的地的元素
                    if(posArray[i].y()==startPos.y()&&posArray[i].x()>startPos.x()&&posArray[i].x()<desPos.x())
                        res++;
                }
            }
            //从右到左
            if(startPos.x()>desPos.x()){
                for(int i=0;i<90;i++){
                    //找到x轴上小于出发地大于目的地的元素
                    if(posArray[i].y()==startPos.y()&&posArray[i].x()<startPos.x()&&posArray[i].x()>desPos.x())
                        res++;
                }
            }
        }
        else{
            //如果斜方向移动将返回值设置为100
            res=100;
        }
    }
    return res;
}
```

#### 走棋规则

分别实现每个子类的`canChange()`方法。

炮：

```C++
bool PAO::canChange(){
    if(CChessman::selectedChessman[0]!=nullptr&&CChessman::selectedChessman[1]!=nullptr){
        //由于两个棋子已经交换位置，所以这里目的地与出发地要颠倒一下
        desPos=CChessman::selectedChessman[0]->getPos();
        startPos=CChessman::selectedChessman[1]->getPos();
        //如果吃子，判断是否中间有1个棋子
        if(CChessman::selectedChessman[1]->getClassType()!="NONE"){
            if(barrier(startPos,desPos)==1)
                return true;
            else
                return false;
        }
        //如果不吃子，判断是否没有障碍
        else{
            if(barrier(startPos,desPos)==0)
                return true;
            else
                return false;
        }
    }
}
```

兵：

```C++
bool BING::canChange(){
    if(CChessman::selectedChessman[0]!=nullptr&&CChessman::selectedChessman[1]!=nullptr){
        desPos=CChessman::selectedChessman[0]->getPos();
        startPos=CChessman::selectedChessman[1]->getPos();
        //判断棋子颜色
        if(this->isRed){
            //红棋子未过河
            if(this->getPos().y()>375){
                //红色棋子如果前进一格且没有左右平移
                if(desPos.y()-startPos.y()==-90&&desPos.x()-startPos.x()==0)
                    return true;
            }
            //过河后
            else{
                if(this->getPos().y()==375){
                    //红色棋子如果前进一格且没有左右平移
                    if(desPos.y()-startPos.y()==-90&&desPos.x()-startPos.x()==0)
                        return true;
                }
                //红色棋子如果前进一格且没有左右平移
                if(desPos.y()-startPos.y()==-90&&desPos.x()-startPos.x()==0)
                    return true;
                //如果左右平移一格并且没有前后移动
                if((desPos.x()-startPos.x()==90||desPos.x()-startPos.x()==-90)&&desPos.y()-startPos.y()==0)
                    return true;
            }
        }
        else{
            //黑棋子未过河
            if(this->getPos().y()<465){
                if(desPos.y()-startPos.y()==90&&desPos.x()-startPos.x()==0)
                    return true;
            }
            //过河后
            else{
                if(this->getPos().y()==465){
                    if(desPos.y()-startPos.y()==90&&desPos.x()-startPos.x()==0)
                        return true;
                }
                if(desPos.y()-startPos.y()==90&&desPos.x()-startPos.x()==0)
                    return true;
                if((desPos.x()-startPos.x()==90||desPos.x()-startPos.x()==-90)&&desPos.y()-startPos.y()==0)
                    return true;
                else
                    return false;
            }
        }
    }
    return false;
}
```

将：

```C++
bool JIANG::canChange(){
    if(CChessman::selectedChessman[0]!=nullptr&&CChessman::selectedChessman[1]!=nullptr){
        desPos=CChessman::selectedChessman[0]->getPos();
        startPos=CChessman::selectedChessman[1]->getPos();
        //直接飞过去
        if(CChessman::selectedChessman[1]->getClassType()=="JIANG"){
            if(barrier(startPos,desPos)==0)
                return true;
        }
        if(this->isRed){
            //红色棋子，不能出帐篷
            if(this->getPos().y()>555&&(this->getPos().x()>200&&this->getPos().x()<560)){
                //如果前后移动一格且没有左右平移
                if((desPos.y()-startPos.y()==-90||desPos.y()-startPos.y()==90)&&desPos.x()-startPos.x()==0)
                    return true;
                //如果左右平移一格并且没有前后移动
                if((desPos.x()-startPos.x()==90||desPos.x()-startPos.x()==-90)&&desPos.y()-startPos.y()==0)
                    return true;
            }
        }
        else{
            //黑色棋子，不能出帐篷
            if(this->getPos().y()<285&&(this->getPos().x()>200&&this->getPos().x()<560)){
                //如果前后移动一格且没有左右平移
                if((desPos.y()-startPos.y()==-90||desPos.y()-startPos.y()==90)&&desPos.x()-startPos.x()==0)
                    return true;
                //如果左右平移一格并且没有前后移动
                if((desPos.x()-startPos.x()==90||desPos.x()-startPos.x()==-90)&&desPos.y()-startPos.y()==0)
                    return true;
            }
            else
                return false;
        }
    }
}
```

车：

```C++
bool JU::canChange(){
    if(CChessman::selectedChessman[0]!=nullptr&&CChessman::selectedChessman[1]!=nullptr){
        desPos=CChessman::selectedChessman[0]->getPos();
        startPos=CChessman::selectedChessman[1]->getPos();
        if(barrier(startPos,desPos)==0)
            return true;
        else
            return false;
    }
    return false;
}
```

马：

```C++
bool MA::canChange(){
    if(CChessman::selectedChessman[0]!=nullptr&&CChessman::selectedChessman[1]!=nullptr){
        desPos=CChessman::selectedChessman[0]->getPos();
        startPos=CChessman::selectedChessman[1]->getPos();
        //如果上下移动1格并且左右平移2格（横走）
        if((desPos.y()-startPos.y()==-90||desPos.y()-startPos.y()==90)&&(desPos.x()-startPos.x()==180||desPos.x()-startPos.x()==-180)){
            QPoint des={desPos.x(),startPos.y()};//取出发地的y值，目的地的x值
            if(barrier(startPos,des)==0)
                return true;
            else
                return false;
        }
        //或者上下移动2格并且左右平移1格（竖走）
        if((desPos.y()-startPos.y()==-180||desPos.y()-startPos.y()==180)&&(desPos.x()-startPos.x()==90||desPos.x()-startPos.x()==-90)){
            QPoint des={startPos.x(),desPos.y()};//取出发地的x值，目的地的y值
            if(barrier(startPos,des)==0)
                return true;
            else
                return false;
        }
    }
}

```

象：

```C++
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
                    if(barrier(midxStart,midxDes)==0)
                        return true;
                    else
                        return false;
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
                    if(barrier(midxStart,midxDes)==0)
                        return true;
                    else
                        return false;
                }
            }
        }
    }
}
```

士：

```C++
bool SHI::canChange(){
    if(CChessman::selectedChessman[0]!=nullptr&&CChessman::selectedChessman[1]!=nullptr){
        desPos=CChessman::selectedChessman[0]->getPos();
        startPos=CChessman::selectedChessman[1]->getPos();
        if(this->isRed){
            //红色棋子，不能出帐篷
            if(this->getPos().y()>555&&(this->getPos().x()>200&&this->getPos().x()<560)){
                //如果前后移动一格且左右平移一格（斜着走）
                if((desPos.y()-startPos.y()==-90||desPos.y()-startPos.y()==90)
                    &&(desPos.x()-startPos.x()==90||desPos.x()-startPos.x()==-90))
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        else{
            //黑色棋子，不能出帐篷
            if(this->getPos().y()<285&&(this->getPos().x()>200&&this->getPos().x()<560)){
                //如果前后移动一格且左右平移一格
                if((desPos.y()-startPos.y()==-90||desPos.y()-startPos.y()==90)&&
                    (desPos.x()-startPos.x()==90||desPos.x()-startPos.x()==-90))
                    return true;
                 else
                    return false;
            }
            else{
                return false;
            }
        }
    }
    return false;
}
```

#### NONE棋子

当点击none棋子时，父类的`do_clicked()`函数什么也不做，然后执行NONE类自己的`do_clicked()`函数。

```C++
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
    //指向空棋子的指针只能被赋值给CChessman::selectedChessman[1]，如果没有选中任何非空棋子，那么点击空棋子将什么也不做
    if(CChessman::selectedChessman[0]!=nullptr){
        CChessman::selectedChessman[1]=this;
        QPoint startPos=CChessman::selectedChessman[0]->getPos();
        QPoint desPos=CChessman::selectedChessman[1]->getPos();
        changePos(startPos,desPos);//与上一个被点击的棋子交换位置
    }
    if(CChessman::selectedChessman[0]!=nullptr&&CChessman::selectedChessman[1]!=nullptr){
        //未轮到本阵营或不符合移动规则，与上一个被点击的棋子交换位置，实现不能移动的效果
        if(!(CChessman::selectedChessman[0]->isRed==CChessman::turnToRed)||!CChessman::selectedChessman[0]->canChange()){
            startPos=CChessman::selectedChessman[0]->getPos();
            desPos=CChessman::selectedChessman[1]->getPos();
            changePos(startPos,desPos);
            selectedChessman[0]=nullptr;
            selectedChessman[1]=nullptr;
            qDebug()<<(turnToRed?"轮到红色棋子行动":"轮到黑色棋子行动");
        }
        else{
            CChessman::turnToRed=!CChessman::turnToRed;
            qDebug()<<(turnToRed?"轮到红色棋子行动":"轮到黑色棋子行动");
            CChessman::step s={false,CChessman::selectedChessman[0],CChessman::selectedChessman[1],nullptr};
            CChessman::steps.push(s);
            selectedChessman[0]=nullptr;
            selectedChessman[1]=nullptr;
        }
    }
}
```





















