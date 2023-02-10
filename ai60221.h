#ifndef AI60221_H
#define AI60221_H

#include "move.h"
#include "boarddata.h"
#include "piece.h"
#include "mainwindow.h"

#include <QObject>

class ai60221
{
public:
    ai60221(BoardData bdata, MainWindow* mainwindow);
    ai60221(BoardData bdata);
    BoardData data;
    Move genMove(int depth);
    bool hasPiece(string spos);
    vector<string> ignoreBlackPos(vector<string> positions);
    Piece getPieceFromPos(string pos);
    Piece getPieceFromPosDATA(string pos, BoardData bdata);
    int getAbsoluteValue(string type);
    bool hasPieceDATA(string spos, BoardData bdata);
    int minimax(BoardData bdata, int depth, int alpha, int beta, bool maxp);
    vector<string> ignoreWhitePos(vector<string> positions);

    MainWindow *mainwin;
    bool hasMainw = false;
    bool analyzeMode = false;
};

#endif // AI60221_H
