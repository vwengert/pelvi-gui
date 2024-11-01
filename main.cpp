#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <pelvi.h>

int main( int argc, char* argv[ ] )
{
  qputenv( "QT_IM_MODULE", QByteArray( "qtvirtualkeyboard" ) );

  QGuiApplication app( argc, argv );

  QQmlApplicationEngine engine;
  auto connection = QObject::connect(
    &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
    []() { QCoreApplication::exit( -1 ); }, Qt::QueuedConnection );
  engine.loadFromModule( "pelvigui", "Main" );

  auto pelvi = new Pelvi( nullptr );

  auto result = QGuiApplication::exec();
  QObject::disconnect( connection );
  delete pelvi;
  return result;
}
