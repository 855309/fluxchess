#ifndef PIECE_H
#define PIECE_H

#include <string>
#include "boarddata.h"
using namespace std;

class smpPair{
public:
    smpPair(int x, int y);
    int x;
    int y;
};

class Piece
{
public:
    Piece();
    Piece(string atype, string apos);
    string type;
    string pos;

    vector<string> getPlayablePositions(BoardData data);
};

#endif // PIECE_H
