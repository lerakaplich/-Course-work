#pragma once

#include <QWidget>
#include <QVector>
#include <QKeyEvent>
#include "ball.h"
#include "paddle.h"
#include "BlueBrick.h"
#include "YellowBrick.h"
#include "RedBrick.h"
#include "Bonus.h"
#include "list.h"

class Breakout : public QWidget {
public:
    Breakout(QWidget *parent = 0);
    ~Breakout();
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void drawObjects(QPainter *);
    void finishGame(QPainter *, QString);
    void moveObjects();
    void drawScore(QPainter *,int,int,int);
    void startGame();
    void pauseGame();
    void stopGame();
    void victory();
    void checkCollision();
private:
    int x;
    int score = 0;
    int timerId;
    static const int DELAY = 10;
    static const int BOTTOM_EDGE = 750;
    Ball *ball;
    Paddle *paddle;
    List<YellowBrick*> yellowBricks;
    List<RedBrick*> redBricks;
    List<BlueBrick*> blueBricks;
    List<Bonus*> bonuses;
    bool gameOver;
    bool gameWon;
    bool gameStarted;
    bool paused;
    bool gameMenu;
};
