#pragma once
#include <QRect>
#include "./Headers/YellowBrick.h"

class RedBrick : public YellowBrick
{
public:
    RedBrick(int, int);
    ~RedBrick();
    void destroy() override;
    void deleteObject() override;
protected:
    int stabillity = 1;
};
