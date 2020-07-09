/// @author M. A. Serebrennikov
#include "GiftCard.h"
#include "GiftCardModel.h"
#include "Provider.h"
#include "Providers.h"
#include "ProvidersModel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSortFilterProxyModel>
#include <QQmlContext>
#include <QScreen>

using namespace sp;

static double dp()
{
    #if defined(Q_OS_MAC)
        static double const standardDPI = 72;
    #elif defined(Q_OS_WIN)
        static double const standardDPI = 96;
    #else
        static double const standardDPI = qApp->screens().first()->logicalDotsPerInch();
    #endif

    static const double result = qApp->screens().first()->logicalDotsPerInch() / standardDPI;
    return result;
}

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    // Отключено qml кеширование, т.к. глючат иногда enum'ы.
    qputenv("QML_DISABLE_DISK_CACHE", "1");

    // QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // Не работает в Qt с текстом и другими элементами как надо
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    engine.addImportPath("qrc:///");

    qRegisterMetaType<Provider *>("Provider *");
    qRegisterMetaType<GiftCard *>("GiftCard *");
    qmlRegisterType<ProvidersModel>("Sp", 1, 0, "ProvidersModel");
    qmlRegisterType<GiftCardModel>("Sp", 1, 0, "GiftCardModel");
    qmlRegisterType<QSortFilterProxyModel>("Sp", 1, 0, "QSortFilterProxyModel");

    context->setContextProperty("dp", dp());
    context->setContextProperty("Providers", &ProvidersI);

    engine.load("qrc:/Root.qml");

    return app.exec();
}
