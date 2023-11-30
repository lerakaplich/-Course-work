#include <iostream>
#include "./Headers/YellowBrick.h"

YellowBrick::YellowBrick(int x, int y){
    image.load(":/img/brick_yellow.png");
    xdir = x;
    ydir = y;
    destroyed = false;
    rect = image.rect();
    rect.translate(x, y);
}
YellowBrick::~YellowBrick(){
    std::cout << "YellowBrick deleted" << std::endl;
}
QRect YellowBrick::getRect() {
    return rect;
}

void YellowBrick::setRect(QRect rct) {

    rect = rct;
}

QImage & YellowBrick::getImage() {
    return image;
}

bool YellowBrick::isDestroyed() {
    return destroyed;
}

void YellowBrick::setDestroyed(bool destroy) {
    destroyed = destroy;
}
int YellowBrick::getXDir(){
    return xdir;
}
int YellowBrick::getYDir(){
    return ydir;
}
int YellowBrick::getScore(){
    if (destroyed)
        return score;
    else
        return 0;
}
void YellowBrick::destroy(){
    destroyed = true;
}
void YellowBrick::deleteObject(){
    delete this;
}
