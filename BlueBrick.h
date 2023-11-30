#pragma once
#include <QRect>
#include <QRandomGenerator>
#include "./Headers/RedBrick.h"
#include "./Headers/Bonus.h"

class BlueBrick : public RedBrick
{
public:
    BlueBrick(int, int);
    ~BlueBrick();
    void destroy() override;
    void deleteObject() override;
    bool getActiveBonus();
    Bonus getBonus();
protected:
    int stabillity = 2;
    Bonus *bonus;
    bool activeBonus;
};

