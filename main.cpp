#include <QIcon>
#include <QApplication>
#include "./Headers/breakout.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);
  app.setWindowIcon(QIcon(":/img/breakout.png"));
  Breakout window;

  window.setFixedSize(QSize(800, 750));//660 900
  window.setWindowTitle("Arcanoid");
  window.show();

  return app.exec();
}
