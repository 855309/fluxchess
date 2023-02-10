/*

 d'b 8                      8
 8   8                      8
o8P  8 o    o `o  o' .oPYo. 8oPYo. .oPYo. .oPYo. .oPYo.
 8   8 8    8  `bd'  8    ' 8    8 8oooo8 Yb..   Yb..
 8   8 8    8  d'`b  8    . 8    8 8.       'Yb.   'Yb.
 8   8 `YooP' o'  `o `YooP' 8    8 `Yooo' `YooP' `YooP'
:..::..:.....:..:::..:.....:..:::..:.....::.....::.....:
::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::

fluxchess
---------

author: fikret0 (a.k.a 85530)
license: MIT License

6 August 2021

*/

#include "mainwindow.h"

#include <QApplication>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    cout
        << endl
        << " d'b 8                      8" << endl
        << " 8   8                      8" << endl
        << "o8P  8 o    o `o  o' .oPYo. 8oPYo. .oPYo. .oPYo. .oPYo." << endl
        << " 8   8 8    8  `bd'  8    ' 8    8 8oooo8 Yb..   Yb.." << endl
        << " 8   8 8    8  d'`b  8    . 8    8 8.       'Yb.   'Yb." << endl
        << " 8   8 `YooP' o'  `o `YooP' 8    8 `Yooo' `YooP' `YooP'" << endl
        << ":..::..:.....:..:::..:.....:..:::..:.....::.....::.....:" << endl
        << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl
        << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl << endl;

    cout << "fluxchess" << endl << "---------" << endl;
    cout << "author: 85530 (github: @855309)" << endl;
    cout << "license: MIT License" << endl;
    cout << "Initial commit: 6 August 2021" << endl;
    cout << "Fix: 10 February 2023" << endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
