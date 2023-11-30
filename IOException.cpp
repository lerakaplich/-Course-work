#include "./Headers/IOException.h"

IOException::IOException(int code,const char * message) : MyException(message){
    this->code = code;
}

IOException::IOException() {
    this->code = 2;
}

int IOException::getCode() {
    return code;
}

void IOException::show() {
    std::cout << "IOException was generated" << std::endl;
    std::cout << "Code: " << this->getCode() << std::endl;
}
