#include <QPainter>
#include <QApplication>
#include "./Headers/breakout.h"
#include <QRandomGenerator>
#include <QDateTime>
#include <QCoreApplication>
#include <QDateTime>
#include <iostream>

using namespace std;

Breakout::Breakout(QWidget *parent): QWidget(parent) {
    QPixmap background(":/img/backgroundMenu.png");
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);
    x = 0;
    gameOver = false;
    gameWon = false;
    paused = false;
    gameMenu = true;
    gameStarted = false;
    ball = new Ball();
    paddle = new Paddle();
}

Breakout::~Breakout() {
    delete ball;
    delete paddle;

    yellowBricks.clearList();
}

void Breakout::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);

    if (gameOver) {
        finishGame(&painter, "Game lost");
    }
    else if(gameWon) {
        finishGame(&painter, "Victory");
    }
    else {
        drawObjects(&painter);
    }
}

void Breakout::finishGame(QPainter *painter, QString message) {

    if(QString::compare(message,"Game lost") != 0)
    {
        QPixmap background(":/img/backgroundGameLost.png");
        QPalette palette;
        palette.setBrush(QPalette::Window, background);
        this->setPalette(palette);
        drawScore(painter,300,450, 30);
    }
    else
    {
        QPixmap background(":/img/backgroundVictory.png");
        QPalette palette;
        palette.setBrush(QPalette::Window, background);
        this->setPalette(palette);
        drawScore(painter,300,450,30);
    }
}

void Breakout::drawObjects(QPainter *painter) {
    if(!gameMenu)
    {
        painter->drawImage(ball->getRect(), ball->getImage());
        painter->drawImage(paddle->getRect(), paddle->getImage());

        for (int i = 0; i < bonuses.getSize(); ++i) {
            if((bonuses.peek(i))->isDestroyed())
                painter->drawImage((bonuses.peek(i))->getRect(), (bonuses.peek(i))->getImage());
        }

        drawScore(painter,10,50,15);

        for (int i=0; i<yellowBricks.getSize(); i++) {
            if (!(yellowBricks.peek(i))->isDestroyed()) {
                painter->drawImage((yellowBricks.peek(i))->getRect(), (yellowBricks.peek(i))->getImage());
            }
        }
        for (int i=0; i<redBricks.getSize(); i++) {
            if (!(redBricks.peek(i))->isDestroyed()) {
                painter->drawImage((redBricks.peek(i))->getRect(), (redBricks.peek(i))->getImage());
            }
        }
        for (int i=0; i<blueBricks.getSize(); i++) {
            if (!(blueBricks.peek(i))->isDestroyed()) {
                painter->drawImage((blueBricks.peek(i))->getRect(), (blueBricks.peek(i))->getImage());
            }
        }
    }

}

void Breakout::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);

    moveObjects();
    checkCollision();
    repaint();
}

void Breakout::moveObjects() {
    ball->autoMove();
    paddle->move();
    for (int i = 0; i < bonuses.getSize(); ++i) {
        (bonuses.peek(i))->autoMove();
    }
}

void Breakout::keyReleaseEvent(QKeyEvent *event) {

    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
    {
        if(paddle->getRect().left() <= 10)
            paddle->move(10);
        paddle->setDx(0);
    }

    if(event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
    {
        if(paddle->getRect().right() >= 790)
            paddle->move(690);
        paddle->setDx(0);
    }
}

void Breakout::keyPressEvent(QKeyEvent *event) {

    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
    {
        if(paddle->getRect().left() <= 10) {
            paddle->setDx(0);
            paddle->move(10);
        }
        else
            paddle->setDx(-2);
    }

    if(event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
    {
        if(paddle->getRect().right() >= 790) {
            paddle->setDx(0);
            paddle->move(690);
        }
        else
            paddle->setDx(2);
    }

    switch (event->key()) {
    case Qt::Key_P:
        pauseGame();
        break;

    case Qt::Key_Space:
        startGame();
        break;

    case Qt::Key_Escape:
        qApp->exit();
        break;

    default:
        QWidget::keyPressEvent(event);
    }
}

void Breakout::startGame() {
    if (!gameStarted) {
        QPixmap background(":/img/background.png");
        QPalette palette;
        palette.setBrush(QPalette::Window, background);
        this->setPalette(palette);

        ball->resetState();
        paddle->resetState();

        yellowBricks.clearList();
        redBricks.clearList();
        blueBricks.clearList();
        bonuses.clearList();

        QRandomGenerator *rg = QRandomGenerator::global();

        for (int i=0; i<5; i++) {
            for (int j=0; j<6; j++) {
                if (rg->bounded(1, 10) % 2 == 0)
                    yellowBricks.pushBack(new YellowBrick(j * 90 + 130, i * 30 + 100));
                else {
                    redBricks.pushBack(new RedBrick(j * 90 + 130, i * 30 + 100));
                    if (rg->bounded(1, 10) %2 == 0){
                        redBricks.popBack();
                        blueBricks.pushBack(new BlueBrick(j * 90 + 130, i * 30 + 100));
                    }
                }
            }
        }

        gameOver = false;
        gameWon = false;
        gameStarted = true;
        gameMenu = false;
        timerId = startTimer(DELAY);
    }
}

void Breakout::pauseGame() {
    if (paused) {
        timerId = startTimer(DELAY);
        paused = false;
    }
    else {
        paused = true;
        std::cout << "Pause" << std::endl;
        killTimer(timerId);

    }
}

void Breakout::stopGame() {
    killTimer(timerId);
    gameOver = true;
    gameStarted = false;

}

void Breakout::victory() {
    killTimer(timerId);
    gameWon = true;
    gameStarted = false;
}

void Breakout::drawScore(QPainter *painter, int x, int y, int size){
    QString stringNumber;
    std::cout << score<<std::endl;
    QString messageScore = "Score: " + stringNumber.setNum(score);
    QFont font("Courier", size, QFont::DemiBold);
    QFontMetrics fm(font);
    painter->setFont(font);
    painter->translate(QPoint(0, 0));
    painter->drawText(messageScore.length()/2 + x, y, messageScore);

}

void Breakout::checkCollision() {
    if (ball->getRect().bottom() > BOTTOM_EDGE) {
        stopGame();
    }

    for (int i = 0; i < bonuses.getSize(); ++i)
        if((bonuses.peek(i))->getRect().bottom() > BOTTOM_EDGE)
            bonuses.erase(i);

    for (int i = 0; i < bonuses.getSize(); ++i) {
        if(((bonuses.peek(i))->getRect()).intersects(paddle->getRect())){
            score = (bonuses.peek(i))->getBonus(score);
            bonuses.erase(i);
        }
    }

    if (ball->getRect().bottom() < 0) {
        QRandomGenerator *rg = QRandomGenerator::global();
        if (rg->bounded(1, 10) % 2 == 0) {
            ball->setXDir(-1);
        }
        else    {
            ball->setXDir(1);
        }
        ball->setYDir(+2);
    }

    int numberOfBlocks = 0;

    for (int i=0; i<yellowBricks.getSize(); i++)
        if ((yellowBricks.peek(i))->isDestroyed())
            numberOfBlocks++;

    for (int i=0; i<redBricks.getSize(); i++)
        if ((redBricks.peek(i))->isDestroyed())
            numberOfBlocks++;

    for (int i=0; i<blueBricks.getSize(); i++)
        if ((blueBricks.peek(i))->isDestroyed())
            numberOfBlocks++;


    if (numberOfBlocks == 30) {
        victory();
    }

    if ((ball->getRect()).intersects(paddle->getRect())) {
        int paddleLPos = paddle->getRect().left();
        int ballLPos = ball->getRect().left();

        int first = paddleLPos + 3;
        int second = paddleLPos + 25;
        int third = paddleLPos + 50;
        int fourth = paddleLPos + 75;

        if (ballLPos < first) {
            ball->setXDir(-1);
            ball->setYDir(-2);
        }

        if (ballLPos >= first && ballLPos < second) {
            ball->setXDir(-1);
            ball->setYDir(-1*ball->getYDir());
        }

        if (ballLPos >= second && ballLPos < third) {
            ball->setXDir(0);
            ball->setYDir(-3);
        }

        if (ballLPos >= third && ballLPos < fourth) {
            ball->setXDir(1);
            ball->setYDir(-1*ball->getYDir());
        }

        if (ballLPos > fourth) {
            ball->setXDir(1);
            ball->setYDir(-2);
        }
    }

    for (int i=0; i<yellowBricks.getSize(); i++) {
        if ((ball->getRect()).intersects((yellowBricks.peek(i))->getRect())) {
            int ballLeft = ball->getRect().left();
            int ballHeight = ball->getRect().height();
            int ballWidth = ball->getRect().width();
            int ballTop = ball->getRect().top();

            QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
            QPoint pointLeft(ballLeft - 1, ballTop);
            QPoint pointTop(ballLeft, ballTop -1);
            QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);

            if (!(yellowBricks.peek(i))->isDestroyed()) {
                //x
                if((yellowBricks.peek(i))->getRect().contains(pointRight)) {
                    ball->setXDir(-1);
                }
                else if((yellowBricks.peek(i))->getRect().contains(pointLeft)) {
                    ball->setXDir(1);
                }
                //y
                if((yellowBricks.peek(i))->getRect().contains(pointTop)) {
                    ball->setYDir(2);
                }
                else if((yellowBricks.peek(i))->getRect().contains(pointBottom)) {
                    ball->setYDir(-2);
                }
                (yellowBricks.peek(i))->destroy();
                score += (yellowBricks.peek(i))->getScore();
            }
        }
    }

    for (int i=0; i<redBricks.getSize(); i++) {
        if ((ball->getRect()).intersects((redBricks.peek(i))->getRect())) {
            int ballLeft = ball->getRect().left();
            int ballHeight = ball->getRect().height();
            int ballWidth = ball->getRect().width();
            int ballTop = ball->getRect().top();

            QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
            QPoint pointLeft(ballLeft - 1, ballTop);
            QPoint pointTop(ballLeft, ballTop -1);
            QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);

            if (!(redBricks.peek(i))->isDestroyed()) {
                //x
                if((redBricks.peek(i))->getRect().contains(pointRight)) {
                    ball->setXDir(-1);
                }
                else if((redBricks.peek(i))->getRect().contains(pointLeft)) {
                    ball->setXDir(1);
                }
                //y
                if((redBricks.peek(i))->getRect().contains(pointTop)) {
                    ball->setYDir(2);
                }
                else if((redBricks.peek(i))->getRect().contains(pointBottom)) {
                    ball->setYDir(-2);
                }

                (redBricks.peek(i))->destroy();
                score += (redBricks.peek(i))->getScore();
            }
        }
    }

    for (int i=0; i<blueBricks.getSize(); i++) {
        if ((ball->getRect()).intersects((blueBricks.peek(i))->getRect())) {
            int ballLeft = ball->getRect().left();
            int ballHeight = ball->getRect().height();
            int ballWidth = ball->getRect().width();
            int ballTop = ball->getRect().top();

            QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
            QPoint pointLeft(ballLeft - 1, ballTop);
            QPoint pointTop(ballLeft, ballTop -1);
            QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);

            if (!(blueBricks.peek(i))->isDestroyed()) {
                //x
                if((blueBricks.peek(i))->getRect().contains(pointRight)) {
                    ball->setXDir(-1);
                }
                else if((blueBricks.peek(i))->getRect().contains(pointLeft)) {
                    ball->setXDir(1);
                }
                //y
                if((blueBricks.peek(i))->getRect().contains(pointTop)) {
                    ball->setYDir(2);
                }
                else if((blueBricks.peek(i))->getRect().contains(pointBottom)) {
                    ball->setYDir(-2);
                }

                (blueBricks.peek(i))->destroy();
                score += (blueBricks.peek(i))->getScore();

                if((blueBricks.peek(i))->getActiveBonus()){
                    bonuses.pushBack(new Bonus((blueBricks.peek(i))->getXDir(),(blueBricks.peek(i))->getYDir(),1));
                    //bonuses.push_back(blueBricks[i]->getBonus());
                }

            }
        }
    }
}
