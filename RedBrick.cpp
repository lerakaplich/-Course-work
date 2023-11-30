#include <iostream>
#include "./Headers/RedBrick.h"

RedBrick::RedBrick(int x, int y) : YellowBrick(x,y){
    image.load(":/img/brick_red.png");
    xdir = x;
    ydir = y;
    score = 20;
    destroyed = false;
    rect = image.rect();
    rect.translate(x, y);
}
RedBrick::~RedBrick(){
    std::cout << "RedBrick deleted" << std::endl;
}
void RedBrick::destroy(){
    if(stabillity == 1){
        image.load(":/img/brick_yellow.png");
        stabillity = 0;
    }
    else
        destroyed = true;
}
void RedBrick::deleteObject(){
    delete this;
}
