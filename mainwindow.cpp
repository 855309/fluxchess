#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boarddata.h"
#include "ai60221.h"

#include <iostream>
#include <QLabel>
#include <QLayout>
#include <string>
#include <QPushButton>
#include <QTime>
#include <QFuture>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QInputDialog>
using namespace std;

string chsalphabet = "abcdefgh";

bool canDep = true;
bool haveMove = false;
bool analyzeMode = false;
string moveDep;

BoardData setupData;

int minimaxdepth = 3;

Piece MainWindow::getPieceFromPos(string pos){
    for(boardPair& bpair : setupData.data){
        for(string& bpos : bpair.positions){
            if(bpos == pos){
                return Piece(bpair.piecetype, bpos);
            }
        }
    }
}

void MainWindow::delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while(QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void MainWindow::clearBoardColors(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            string cname = chsalphabet[i] + to_string(j + 1);
            QPushButton *block = this->findChild<QPushButton*>(cname.c_str());

            if((i + j) % 2 != 0){
                block->setStyleSheet("background-color: rgb(240, 217, 181)");
            }
            else{
                block->setStyleSheet("background-color: rgb(181, 136, 99)");
            }
        }
    }
}

bool MainWindow::canMove(string pos, string dest){
    Piece pospc = getPieceFromPos(pos);

    vector<string> positions = ignoreWhitePos(pospc.getPlayablePositions(setupData));

    for(string bpos : positions){
        if(bpos == dest){
            return true;
        }
    }

    return false;
}

void MainWindow::changeMMDepth(){
    bool ok;

    string nm = "Enter depth (default: " + to_string(minimaxdepth) + "):";
    int i = QInputDialog::getInt(this, tr("Change Minimax Depth"), tr(nm.c_str()), minimaxdepth, 0, 100, 1, &ok);

    if(ok){
        minimaxdepth = i;
    }
}

void MainWindow::movePiece(string pos, string dest){
    clearBoardColors();

    cout << "[GEN] Move " << pos << " to " << dest << endl;

    QPushButton *destpb = this->findChild<QPushButton*>(dest.c_str());
    QPushButton *pospb = this->findChild<QPushButton*>(pos.c_str());

    string type;

    for(boardPair& bpair : setupData.data){
        for(int bpoi = 0; bpoi < bpair.positions.size(); bpoi++){
            if(bpair.positions[bpoi] == dest){
                bpair.positions.erase(bpair.positions.begin() + bpoi);

                break;
            }
        }
    }


    for(boardPair& bpair : setupData.data){
        for(string& bpos : bpair.positions){
            if(bpos == pos){
                bpos = dest;

                type = bpair.piecetype;
                break;
            }
        }
    }

    string imgpath = "res/" + type + ".png";
    destpb->setIcon(QIcon(QPixmap(imgpath.c_str())));

    pospb->setIcon(QIcon(QPixmap()));

    // play the move sound
    // soon...
}

bool hasQBPiece(QPushButton *amj){
    for(boardPair bpair : setupData.data){
        for(string pos : bpair.positions){
            if(pos == amj->objectName().toStdString()){
                return true;
            }
        }
    }

    return false;
}

bool hasPiece(string spos){
    for(boardPair bpair : setupData.data){
        for(string pos : bpair.positions){
            if(pos == spos){
                return true;
            }
        }
    }

    return false;
}

vector<string> MainWindow::ignoreWhitePos(vector<string> positions){
    vector<string> npos;
    for(string cpos : positions){
        bool iswhite = false;

        if(hasPiece(cpos)){
            if(getPieceFromPos(cpos).type.back() == 'W'){
                iswhite = true;
            }
        }

        if(!iswhite){
            npos.push_back(cpos);
        }
    }

    return npos;
}

void MainWindow::makeAIMove(){
    ai60221 ai(setupData, this);
    ai.analyzeMode = analyzeMode;

    Move mv = ai.genMove(minimaxdepth);

    movePiece(mv.pos, mv.dest);
}

void MainWindow::highlightBlock(string pos){
    QPushButton *btnxf = this->findChild<QPushButton*>(pos.c_str());
    btnxf->setStyleSheet("background-color: rgb(255, 135, 227)");
}

void MainWindow::boardBlock_clicked(){
    QPushButton *sender = (QPushButton *) QObject::sender();

    string blockname = sender->objectName().toStdString();

    if(haveMove){
        if(hasQBPiece(sender)){
            Piece pc = getPieceFromPos(blockname);
            if(pc.type.back() == 'W'){
                haveMove = true;
                moveDep = blockname;

                // cout << "moveDep REdefined: " << blockname << endl;

                clearBoardColors();

                sender->setStyleSheet("background-color: rgb(153, 134, 118)");

                vector<string> positions = ignoreWhitePos(pc.getPlayablePositions(setupData));
                for(string bpos : positions){
                    QPushButton *btnxf = this->findChild<QPushButton*>(bpos.c_str());
                    btnxf->setStyleSheet("background-color: rgb(69, 245, 148)");
                }
            }
        }

        if(canMove(moveDep, blockname) && canDep){
            movePiece(moveDep, blockname);

            haveMove = false;
            moveDep.clear();

            // wait for gui
            delay(250);

            canDep = false;
            makeAIMove();
            canDep = true;
        }
    }
    else{
        if(hasQBPiece(sender)){
            Piece pc = getPieceFromPos(blockname);
            if(pc.type.back() == 'W'){
                haveMove = true;
                moveDep = blockname;

                // cout << "moveDep defined: " << blockname << endl;

                sender->setStyleSheet("background-color: rgb(153, 134, 118)");

                vector<string> positions = ignoreWhitePos(pc.getPlayablePositions(setupData));
                for(string bpos : positions){
                    QPushButton *btnxf = this->findChild<QPushButton*>(bpos.c_str());
                    btnxf->setStyleSheet("background-color: rgb(69, 245, 148)");
                }
            }
        }
    }
}

void MainWindow::exitGame(){
    exit(0);
}

void MainWindow::toggleAnalyze(){
    analyzeMode = !analyzeMode;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this); // main setup utility

    // connect toolbar buttons
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::exitGame); // quit
    connect(ui->actionChange_Minimax_Depth, &QAction::triggered, this, &MainWindow::changeMMDepth); // change minimax depth
    connect(ui->actionToggle_Analyze_Mode, &QAction::triggered, this, &MainWindow::toggleAnalyze); // toggle analyzeMode

    setupData.makeSetupData();

    // write ready to the status bar
    QLabel *label = new QLabel("Ready.");
    statusBar()->addWidget(label);

    // prevent resizing the window
    this->setMaximumSize(532, 574);
    this->setMinimumSize(532, 574);

    // create board
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            // create the board "number"
            string name = chsalphabet[y] + to_string(8 - x);

            QPushButton *boardBlock = new QPushButton(ui->boardFrame);
            boardBlock->resize(64, 64);
            boardBlock->move(y * 64, x * 64);

            // set the object name and accessible name for identification of the board block
            boardBlock->setObjectName(name.c_str());
            boardBlock->setAccessibleName(name.c_str());

            // check if white or black
            if((x + y) % 2 == 0){
                boardBlock->setStyleSheet("background-color: rgb(240, 217, 181)");
            }
            else{
                boardBlock->setStyleSheet("background-color: rgb(181, 136, 99)");
            }

            boardBlock->setMouseTracking(true);
            boardBlock->setAttribute(Qt::WA_Hover, true);

            // connect the click event
            connect(boardBlock, &QPushButton::clicked, this, &MainWindow::boardBlock_clicked);

            // debug:
            // QLabel *newlabel = new QLabel(name.c_str(), boardBlock);

            // cout << "Created board block: " << name << endl;

            // Icon test

            //boardBlock->setIcon(QIcon(QPixmap("res/white/pawn.png")));
            //boardBlock->setIconSize(QSize(64, 64));

            boardBlock->setIconSize(QSize(64, 64));

            for(boardPair pair : setupData.data){
                for(string pos : pair.positions){
                    if(pos == name){
                        string imgpath = "res/" + pair.piecetype + ".png";

                        boardBlock->setIcon(QIcon(QPixmap(imgpath.c_str())));

                        // cout << "Image placed: " << pos << " - " << pair.piecetype << endl;

                        break;
                    }
                }
            }
        }
    }

    // cout << "All board blocks are positioned." << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

