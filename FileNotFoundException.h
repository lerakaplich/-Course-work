#pragma once
#include "./Headers/IOException.h"

class FileNotFoundException : public IOException{
    public:
        FileNotFoundException(const char* message,int code);
        FileNotFoundException();
        int getCode();
        void show() override;
};
