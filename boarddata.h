#ifndef BOARDDATA_H
#define BOARDDATA_H

#include <string>
#include <vector>
using namespace std;

struct boardPair{
    string piecetype;
    vector<string> positions;
};

class BoardData
{
public:
    BoardData();
    BoardData(vector<boardPair> argdata);
    vector<boardPair> data;

    void makeSetupData();
};

#endif // BOARDDATA_H
