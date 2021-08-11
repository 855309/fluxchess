#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
