#include "./Headers/FileNotFoundException.h"


FileNotFoundException::FileNotFoundException(const char* message, int code) : IOException(code, message) {
  this->code = code;
}

FileNotFoundException::FileNotFoundException() {
  this->code = 3;
}

void FileNotFoundException::show() {
  std::cout << "FileNotFoundException was generated" << std::endl;
  std::cout << "Code: " << this->getCode() << std::endl;
}

int FileNotFoundException::getCode() {
  return code;
}
