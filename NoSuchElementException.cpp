#include "./Headers/NoSuchElementException.h"

NoSuchElementException::NoSuchElementException(int code, const char* message) : MyException(message) {
    this->code = code;
}

NoSuchElementException::NoSuchElementException() {
    this->code = 1;
}

int NoSuchElementException::getCode() {
    return code;
}

void NoSuchElementException::show() {
    std::cout << "NoSuchElementException was generated" << std::endl;
    std::cout << "Code: " << this->getCode() << std::endl;
}
