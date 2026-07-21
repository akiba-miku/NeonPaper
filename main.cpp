#include <QGuiApplication>
#include <QQmlApplicationEngine>

// 创建 QT 应用 和 QML 引擎
int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.loadFromModule("NeonPaper", "Main");

  if (engine.rootObjects().isEmpty()) {
    return 1;
  }

  return app.exec();
}
