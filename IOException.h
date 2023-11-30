#pragma once
#include "./Headers/MyException.h"
class IOException : public MyException
{
public :
    IOException(int code,const char* message);
    IOException();
    void show() override;
    int getCode();
};

