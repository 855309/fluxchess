#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <QMainWindow>
#include <string>
using namespace std;

#include "piece.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void highlightBlock(string pos);
    void boardBlock_clicked();
    void movePiece(string pos, string dest);
    bool canMove(string pos, string dest);
    Piece getPieceFromPos(string pos);
    void clearBoardColors();
    vector<string> ignoreWhitePos(vector<string> positions);
    void exitGame();
    void makeAIMove();
    void changeMMDepth();
    void delay(int millisecondsToWait);
    void toggleAnalyze();
    string get_current_dir();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
