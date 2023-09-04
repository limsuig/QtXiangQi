
#ifndef SETTING_H
#define SETTING_H

#include <QPoint>


namespace setting {
const int boardWidth{840},boardHeigth{920};//棋盘宽高
const int cellLenght{90};//棋盘网格大小
const QPoint topLeft{(boardWidth-8*cellLenght)/2,(boardHeigth-9*cellLenght)/2};//棋盘网格左上角{60，55}
const int chessmanSize{80};//棋子大小
const QPoint ChessmanTopLeft{topLeft.x()-chessmanSize/2,topLeft.y()-chessmanSize/2};//棋子左上角

}
#endif // SETTING_H
