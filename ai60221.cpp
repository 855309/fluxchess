#include "ai60221.h"

#include <iomanip>
#include <map>
#include <random>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <QFuture>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QMainWindow>

ai60221::ai60221(BoardData bdata, MainWindow *mainwindow)
{
    this->data = bdata;

    this->mainwin = mainwindow;
    this->hasMainw = true;
}

ai60221::ai60221(BoardData bdata)
{
    this->data = bdata;

    this->hasMainw = false;
}

bool ai60221::hasPiece(string spos){
    for(boardPair bpair : this->data.data){
        for(string pos : bpair.positions){
            if(pos == spos){
                return true;
            }
        }
    }

    return false;
}

bool ai60221::hasPieceDATA(string spos, BoardData bdata){
    for(boardPair bpair : bdata.data){
        for(string pos : bpair.positions){
            if(pos == spos){
                return true;
            }
        }
    }

    return false;
}

vector<string> ai60221::ignoreBlackPos(vector<string> positions){
    vector<string> npos;
    for(string cpos : positions){
        bool isblack = false;

        if(hasPiece(cpos)){
            if(getPieceFromPos(cpos).type.back() == 'B'){
                isblack = true;
            }
        }

        if(!isblack){
            npos.push_back(cpos);
        }
    }

    return npos;
}

vector<string> ai60221::ignoreWhitePos(vector<string> positions){
    vector<string> npos;
    for(string cpos : positions){
        bool iswhite = false;

        if(hasPiece(cpos)){
            if(getPieceFromPos(cpos).type.back() == 'W'){
                iswhite = true;
            }
        }

        if(!iswhite){
            npos.push_back(cpos);
        }
    }

    return npos;
}

Piece ai60221::getPieceFromPos(string pos){
    for(boardPair& bpair : this->data.data){
        for(string& bpos : bpair.positions){
            if(bpos == pos){
                return Piece(bpair.piecetype, bpos);
            }
        }
    }
}

Piece ai60221::getPieceFromPosDATA(string pos, BoardData bdata){
    for(boardPair& bpair : bdata.data){
        for(string& bpos : bpair.positions){
            if(bpos == pos){
                return Piece(bpair.piecetype, bpos);
            }
        }
    }
}

int ai60221::getAbsoluteValue(string type){
    // White
    if(type == "pawnW"){
        return 1;
    }
    else if(type == "knightW"){
        return 3;
    }
    else if(type == "bishopW"){
        return 3;
    }
    else if(type == "rookW"){
        return 5;
    }
    else if(type == "queenW"){
        return 9;
    }
    // Black
    else if(type == "pawnB"){
        return -1;
    }
    else if(type == "knightB"){
        return -3;
    }
    else if(type == "bishopB"){
        return -3;
    }
    else if(type == "rookB"){
        return -5;
    }
    else if(type == "queenB"){
        return -9;
    }
    else{
        return 0;
    }
}

bool sortbyval(Move m1, Move m2){
    return m1.value > m2.value;
}

vector<boardPair> emulateMove(Move move, BoardData mdata){
    BoardData tmpdata = mdata;
    for(boardPair& bpair : tmpdata.data){
        for(int bpoi = 0; bpoi < bpair.positions.size(); bpoi++){
            if(bpair.positions[bpoi] == move.dest){
                bpair.positions.erase(bpair.positions.begin() + bpoi);

                break;
            }
        }
    }


    for(boardPair& bpair : tmpdata.data){
        for(string& bpos : bpair.positions){
            if(bpos == move.pos){
                bpos = move.dest;

                break;
            }
        }
    }

    return tmpdata.data;
}

int delayMS = 7;

int ai60221::minimax(BoardData bdata, int depth, int alpha, int beta, bool maxp){
    if(depth == 0){
        int val = 0;
        for(boardPair emp : bdata.data){
            for(string emps : emp.positions){
                val += getAbsoluteValue(emp.piecetype);
            }
        }
        return val;
    }

    if(maxp) {
        int value = INT_MIN;
        for(boardPair p : bdata.data){
            for(string pos : p.positions){
                Piece xp = Piece(p.piecetype, pos);
                for(string nwpos : xp.getPlayablePositions(bdata)){
                    Move m = Move(pos, nwpos);
                    vector<boardPair> res = emulateMove(m, bdata);
                    value = max(value, minimax(BoardData(res), depth - 1, alpha, beta, false));

                    if(value > beta){
                        return value;
                    }

                    alpha = max(alpha, value);
                }
            }
        }

        return value;
    }
    else{
        int value = INT_MAX;
        for(boardPair p : bdata.data){
            for(string pos : p.positions){
                Piece xp = Piece(p.piecetype, pos);
                for(string nwpos : xp.getPlayablePositions(bdata)){
                    Move m = Move(pos, nwpos);
                    vector<boardPair> res = emulateMove(m, bdata);
                    value = min(value, minimax(BoardData(res), depth - 1, alpha, beta, true));

                    if(value < alpha){
                        return value;
                    }

                    beta = min(beta, value);
                }
            }
        }

        return value;
    }
}

Move ai60221::genMove(int depth){
    // mainwin->highlightBlock("a1");

    vector<Move> possibleMoves;

    for(boardPair pair : this->data.data){
        if(pair.piecetype.back() == 'B'){
            cout << "[GEN] Controlling move: " << pair.piecetype << endl;
            for(string pos : pair.positions){
                Piece p;
                p.pos = pos;
                p.type = pair.piecetype;

                for(string plpos : ignoreBlackPos(p.getPlayablePositions(data))){
                    possibleMoves.push_back(Move(pos, plpos, pair.piecetype));
                }
            }
        }
    }

    for(Move &posmove : possibleMoves){
        BoardData k = BoardData(this->data);
        BoardData f = BoardData(emulateMove(posmove, k));
        posmove.value = -minimax(f, depth, INT_MIN, INT_MAX, true);
    }

    sort(possibleMoves.begin(), possibleMoves.end(), sortbyval);

    return possibleMoves[0];
}
