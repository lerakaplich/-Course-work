#pragma once

#include <QImage>
#include <QRect>

class Bonus
{
public:
    Bonus(int, int, int);
    ~Bonus();
    void autoMove();
    void deleteObject();
    void resetState();
    bool isDestroyed();
    int getBonus(int);
    QRect getRect();
    QImage & getImage();
private:
    int xdir;
    int ydir;
    int typeBonus;
    bool destroyed;
    QImage image;
    QRect rect;
    int INITIAL_X;
    int INITIAL_Y;
};

