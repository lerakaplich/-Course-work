#pragma once

#include <QImage>
#include <QRect>

class Paddle {
    public:
        Paddle();
        ~Paddle();
        void resetState();
        void move();
        void move(int);
        void setDx(int);
        QRect getRect();
        QImage & getImage();
    private:
        QImage image;
        QRect rect;
        int dx;
        static const int INITIAL_X = 335;//400
        static const int INITIAL_Y = 700;
};
