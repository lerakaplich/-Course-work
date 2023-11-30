#include <iostream>
#include "./Headers/BlueBrick.h"

BlueBrick::BlueBrick(int x, int y) : RedBrick(x,y){
    image.load(":/img/brick_blue.png");
    xdir = x;
    ydir = y;
    QRandomGenerator *rg = QRandomGenerator::global();
    if (rg->bounded(1, 10) % 2 == 0){
        bonus = new Bonus(x,y,1);
        activeBonus = true;
    }else
        activeBonus = false;
    score = 50;
    destroyed = false;
    rect = image.rect();
    rect.translate(x, y);
}
BlueBrick::~BlueBrick(){
    std::cout << "BlueBrick deleted" << std::endl;
}
Bonus BlueBrick::getBonus(){
    return *bonus;
}
bool BlueBrick::getActiveBonus(){
    if(destroyed)
        return activeBonus;
    else
        return false;
}
void BlueBrick::destroy(){
    switch (stabillity) {
    case 2:
        image.load(":/img/brick_blue1.png");
        stabillity--;
        break;
    case 1:
        image.load(":/img/brick_blue2.png");
        stabillity--;
        break;
    case 0:
        destroyed = true;
        break;
    }
}
void BlueBrick::deleteObject(){
    delete this;
}
