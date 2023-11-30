#pragma once

#include <QImage>
#include <QRect>

class Ball {

    public:
        Ball();
        ~Ball();
        void resetState();
        void autoMove();
        void setXDir(int);
        void setYDir(int);
        int getXDir();
        int getYDir();
        QRect getRect();
        QImage & getImage();
    private:
        int xdir;
        int ydir;
        QImage image;
        QRect rect;
        static const int INITIAL_X = 375;
        static const int INITIAL_Y = 680;
        static const int RIGHT_EDGE = 800;
};
