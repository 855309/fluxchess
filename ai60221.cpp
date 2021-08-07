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

ai60221::ai60221(BoardData bdata)
{
    this->data = bdata;
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
    else if(type == "kingW"){
        return 1500;
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
    else if(type == "kingB"){
        return -1500;
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

int ai60221::minimax(Move posmove, BoardData bdata, int depth){
    if(depth == 0){
        return 0;
    }

    vector<boardPair> emul = emulateMove(posmove, bdata);
    cout << "[EMUL] Emulating board: " << posmove.pos << ", " << posmove.dest << endl;

    vector<boardPair> whitePieceXPos;
    for(boardPair epair : emul){
        if(epair.piecetype.back() == 'W'){
            whitePieceXPos.push_back(epair);
        }
    }

    int cval = 0;
    for(boardPair wbpair : whitePieceXPos){
        for(string wbposA : wbpair.positions){
            Piece s;
            s.pos = wbposA;
            s.type = wbpair.piecetype;

            for(string plWpos : ignoreWhitePos(s.getPlayablePositions(BoardData(emul)))){
                if(hasPieceDATA(plWpos, BoardData(emul))){
                    int absval = getAbsoluteValue(getPieceFromPosDATA(plWpos, BoardData(emul)).type);
                    cval += absval + minimax(Move(wbposA, plWpos), BoardData(emul), depth - 1);

                    cout << "[CALC] [MINIMAX] Calculating absolute value: " << absval << " : " << cval << endl;
                }
            }
        }
    }

    return cval;
}

Move ai60221::genMove(int depth){
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
        if(hasPiece(posmove.dest)){
            int val = getAbsoluteValue(posmove.type);

            posmove.value = val;
        }
    }

    for(Move &posmove : possibleMoves){
        posmove.value = minimax(posmove, this->data, depth);
    }

    sort(possibleMoves.begin(), possibleMoves.end(), sortbyval);

    return possibleMoves[0];
}
