#include "move.h"
using namespace std;

Move::Move()
{

}

Move::Move(string pos, string dest)
{
    this->pos = pos;
    this->dest = dest;

    this->value = 0;
}

Move::Move(string pos, string dest, string type)
{
    this->pos = pos;
    this->dest = dest;
    this->type = type;

    this->value = 0;
}
