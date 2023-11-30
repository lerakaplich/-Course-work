#pragma once
#include "./Headers/MyException.h"
class NoSuchElementException : public MyException
{
public:
    NoSuchElementException(int code, const char* message);
    NoSuchElementException();
    void show() override;
    int getCode();
};

