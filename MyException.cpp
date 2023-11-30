#include "./Headers/MyException.h"

MyException::MyException(const char * message) {

    strcpy_s(this->message, message);
    this->code = code;
}

MyException::MyException() {
    std::cout << "Exception was generated" << std::endl;
}

void MyException::show() {
    std::cout << "Base exception was generated" << std::endl;
}
