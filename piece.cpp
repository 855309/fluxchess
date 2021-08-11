#include "piece.h"
#include <iostream>
#include <string>
using namespace std;

smpPair::smpPair(int x, int y){
    this->x = x;
    this->y = y;
}

Piece::Piece()
{

}

Piece::Piece(string atype, string apos){
    this->type = atype;
    this->pos = apos;
}

string psalphabet = "abcdefghijklmn";

bool hasPiece(BoardData sylas, string spos){
    for(boardPair bpair : sylas.data){
        for(string pos : bpair.positions){
            if(pos == spos){
                return true;
            }
        }
    }

    return false;
}

string smppairToSpos(smpPair pair){
    return psalphabet[pair.x] + to_string(pair.y);
}

vector<string> Piece::getPlayablePositions(BoardData data){
    vector<string> positions;
    vector<smpPair> intpositions;

    char col = this->type.at(this->type.size() - 1);

    int x, y;

    for(int i = 0; i < psalphabet.size(); i++){
        if(psalphabet[i] == this->pos[0]){
            x = i;
            break;
        }
    }

    y = stoi(this->pos.substr(1, this->pos.size() - 1));

    string piecetype = this->type.substr(0, this->type.size() - 1);
    if(piecetype == "knight"){
        intpositions.push_back(smpPair(x + 1, y + 2));
        intpositions.push_back(smpPair(x - 1, y + 2));

        intpositions.push_back(smpPair(x + 1, y - 2));
        intpositions.push_back(smpPair(x - 1, y - 2));

        intpositions.push_back(smpPair(x + 2, y + 1));
        intpositions.push_back(smpPair(x - 2, y + 1));

        intpositions.push_back(smpPair(x + 2, y - 1));
        intpositions.push_back(smpPair(x - 2, y - 1));
    }
    else if(piecetype == "pawn"){
        if(col == 'W'){
            smpPair fw(x, y + 1);
            if(!hasPiece(data, smppairToSpos(fw))){
                intpositions.push_back(fw);
            }

            if(y == 2){
                smpPair ffw(x, y + 2);
                if(!hasPiece(data, smppairToSpos(ffw))){
                    intpositions.push_back(ffw);
                }
            }

            smpPair sg(x + 1, y + 1);
            smpPair sl(x - 1, y + 1);
            if(hasPiece(data, smppairToSpos(sg))){
                intpositions.push_back(sg);
            }
            if(hasPiece(data, smppairToSpos(sl))){
                intpositions.push_back(sl);
            }
        }

        if(col == 'B'){
            smpPair fw(x, y - 1);
            if(!hasPiece(data, smppairToSpos(fw))){
                intpositions.push_back(fw);
            }

            if(y == 7){
                smpPair ffw(x, y - 2);
                if(!hasPiece(data, smppairToSpos(ffw))){
                    intpositions.push_back(ffw);
                }
            }

            smpPair sg(x + 1, y - 1);
            smpPair sl(x - 1, y - 1);
            if(hasPiece(data, smppairToSpos(sg))){
                intpositions.push_back(sg);
            }
            if(hasPiece(data, smppairToSpos(sl))){
                intpositions.push_back(sl);
            }
        }
    }
    else if(piecetype == "rook"){
        for(int ycur = y + 1; ycur <= 8; ycur++){
            smpPair py(x, ycur);
            intpositions.push_back(py);

            if(hasPiece(data, smppairToSpos(py))){
                break;
            }
        }

        for(int ycur = y - 1; ycur >= 1; ycur--){
            smpPair py(x, ycur);
            intpositions.push_back(py);

            if(hasPiece(data, smppairToSpos(py))){
                break;
            }
        }

        for(int xcur = x + 1; xcur < 8; xcur++){
            smpPair py(xcur, y);
            intpositions.push_back(py);

            if(hasPiece(data, smppairToSpos(py))){
                break;
            }
        }

        for(int xcur = x - 1; xcur >= 0; xcur--){
            smpPair py(xcur, y);
            intpositions.push_back(py);

            if(hasPiece(data, smppairToSpos(py))){
                break;
            }
        }
    }
    else if(piecetype == "bishop"){
        for(int xcur = x + 1, ycur = y + 1; xcur < 8 && ycur <= 8; xcur++, ycur++){
            smpPair py(xcur, ycur);
            intpositions.push_back(py);

            if(hasPiece(data, smppairToSpos(py))){
                break;
            }
        }

        for(int xcur = x - 1, ycur = y + 1; xcur >= 0 && ycur <= 8; xcur--, ycur++){
            smpPair py(xcur, ycur);
            intpositions.push_back(py);

            if(hasPiece(data, smppairToSpos(py))){
                break;
            }
        }

        for(int xcur = x - 1, ycur = y - 1; xcur >= 0 && ycur >= 1; xcur--, ycur--){
            smpPair py(xcur, ycur);
            intpositions.push_back(py);

            if(hasPiece(data, smppairToSpos(py))){
                break;
            }
        }

        for(int xcur = x + 1, ycur = y - 1; xcur < 8 && ycur >= 1; xcur++, ycur--){
            smpPair py(xcur, ycur);
            intpositions.push_back(py);

            if(hasPiece(data, smppairToSpos(py))){
                break;
            }
        }
    }
    else if(piecetype == "queen"){
        // bishop
        for(int xcur = x + 1, ycur = y + 1; xcur < 8 && ycur <= 8; xcur++, ycur++){
            smpPair py(xcur, ycur);
            intpositions.push_back(py);

            if(hasPiece(data, smppairToSpos(py))){
                break;
            }
        }

        for(int xcur = x - 1, ycur = y + 1; xcur >= 0 && ycur <= 8; xcur--, ycur++){
            smpPair py(xcur, ycur);
            intpositions.push_back(py);

            if(hasPiece(data, smppairToSpos(py))){
                break;
            }
        }

        for(int xcur = x - 1, ycur = y - 1; xcur >= 0 && ycur >= 1; xcur--, ycur--){
            smpPair py(xcur, ycur);
            intpositions.push_back(py);

            if(hasPiece(data, smppairToSpos(py))){
                break;
            }
        }

        for(int xcur = x + 1, ycur = y - 1; xcur < 8 && ycur >= 1; xcur++, ycur--){
            smpPair py(xcur, ycur);
            intpositions.push_back(py);

            if(hasPiece(data, smppairToSpos(py))){
                break;
            }
        }

        // rook
        for(int ycur = y + 1; ycur <= 8; ycur++){
            smpPair py(x, ycur);
            intpositions.push_back(py);

            if(hasPiece(data, smppairToSpos(py))){
                break;
            }
        }

        for(int ycur = y - 1; ycur >= 1; ycur--){
            smpPair py(x, ycur);
            intpositions.push_back(py);

            if(hasPiece(data, smppairToSpos(py))){
                break;
            }
        }

        for(int xcur = x + 1; xcur < 8; xcur++){
            smpPair py(xcur, y);
            intpositions.push_back(py);

            if(hasPiece(data, smppairToSpos(py))){
                break;
            }
        }

        for(int xcur = x - 1; xcur >= 0; xcur--){
            smpPair py(xcur, y);
            intpositions.push_back(py);

            if(hasPiece(data, smppairToSpos(py))){
                break;
            }
        }
    }
    else if(piecetype == "king"){
        intpositions.push_back(smpPair(x, y + 1));
        intpositions.push_back(smpPair(x, y - 1));
        intpositions.push_back(smpPair(x + 1, y));
        intpositions.push_back(smpPair(x + 1, y + 1));
        intpositions.push_back(smpPair(x + 1, y - 1));
        intpositions.push_back(smpPair(x - 1, y));
        intpositions.push_back(smpPair(x - 1, y + 1));
        intpositions.push_back(smpPair(x - 1, y - 1));
    }

    for(int i = 0; i < intpositions.size(); i++){
        smpPair cpair = intpositions[i];

        bool xexpl = cpair.x >= 8 || cpair.x < 0;
        bool yexpl = cpair.y > 8 || cpair.y <= 0;
        if(!xexpl && !yexpl){
            positions.push_back(smppairToSpos(cpair));
            // cout << "Pos: " << smppairToSpos(cpair) << endl;
        }
    }

    return positions;
}
