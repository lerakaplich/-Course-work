#pragma once

#include <QImage>
#include <QRect>

class YellowBrick
{
public:
    YellowBrick(int, int);
    ~YellowBrick();
    bool isDestroyed();
    void setDestroyed(bool);
    QRect getRect();
    void setRect(QRect);
    QImage & getImage();
    int getXDir();
    int getYDir();
    int getScore();
    virtual void destroy();
    virtual void deleteObject();
protected:
    QImage image;
    QRect rect;
    int score = 10;
    bool destroyed;
    int xdir;
    int ydir;
};
