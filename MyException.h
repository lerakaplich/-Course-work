#pragma once
#include<cstring>
#include<iostream>

using namespace std;

class MyException
{
protected:
    char message[80];
    int code;
public:
    MyException(const char* message);
    MyException();
    virtual void show();
};

