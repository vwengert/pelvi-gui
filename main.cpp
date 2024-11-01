#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <database.h>

int main(int argc, char *argv[]) {
  qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

  QGuiApplication app(argc, argv);

  auto *database = new Database();
  if (!database->openDatabase("pelvi.db")) {
    return -1;
  }

  QQmlApplicationEngine engine;
  auto connection = QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.loadFromModule("pelvigui", "Main");

  auto result = QGuiApplication::exec();
  QObject::disconnect(connection);
  return result;
}
