#ifndef MOVE_H
#define MOVE_H

#include <string>
using namespace std;

class Move
{
public:
    Move();
    Move(string pos, string dest);
    Move(string pos, string dest, string type);
    string pos;
    string dest;
    string type;

    int value;
};

#endif // MOVE_H
