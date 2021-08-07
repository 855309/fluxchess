#include "boarddata.h"
#include "strtools.h"

#include <iostream>
using namespace std;

BoardData::BoardData(vector<boardPair> argdata)
{
    this->data = argdata;
}

BoardData::BoardData()
{

}

void BoardData::makeSetupData(){
    string piecedatastr = "pawnW:a2-b2-c2-d2-e2-f2-g2-h2/pawnB:a7-b7-c7-d7-e7-f7-g7-h7/knightW:b1-g1/knightB:b8-g8/bishopW:c1-f1/bishopB:c8-f8/rookW:a1-h1/rookB:a8-h8/queenW:d1/queenB:d8/kingW:e1/kingB:e8";

    for(string piecelocdata : splitstr(piecedatastr, '/')){
        // cout << piecelocdata << endl;

        vector<string> dataspl = splitstr(piecelocdata, ':');

        boardPair bpair;
        bpair.piecetype = dataspl[0];
        // cout << dataspl[1] << endl;
        for(string locp : splitstr(dataspl[1], '-')){
            //cout << locp << endl;
            bpair.positions.push_back(locp);
        }

        this->data.push_back(bpair);
    }
}
