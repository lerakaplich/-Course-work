#include <iostream>
#include "./Headers/Bonus.h"

Bonus::Bonus(int x, int y, int type) {
    INITIAL_X = x + 35;
    INITIAL_Y = y;
    typeBonus = type;
    xdir = 0;
    ydir = +1;
    destroyed = true;
    image.load(":/img/bonus.png");
    rect = image.rect();
    resetState();
}
Bonus::~Bonus(){
    std::cout<<"Bonus deleted"<<std::endl;
}
void Bonus::deleteObject(){
    delete this;
}
void Bonus::resetState() {
    rect.moveTo(INITIAL_X, INITIAL_Y);
}
bool Bonus::isDestroyed(){
    return destroyed;
}
QRect Bonus::getRect() {

    return rect;
}

QImage & Bonus::getImage() {

    return image;
}

void Bonus::autoMove() {

    rect.translate(xdir, ydir);
}
int Bonus::getBonus(int score){
    switch (typeBonus) {
    case 1:
        score *=2;
        break;
    }
    return score;
}
