#ifndef STRTOOLS_H
#define STRTOOLS_H

#include <vector>
#include <string>
using namespace std;

string ltrim(string s);
string rtrim(string s);
string trim(string s);
vector<string> splitstr(string origin, char delimiter);
vector<string> splitstrcount(string origin, char delimiter, int count);

#endif // STRTOOLS_H
