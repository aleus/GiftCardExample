/// @author M. A. Serebrennikov
#include "Providers.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringBuilder>

using namespace sp;

Providers &Providers::instance()
{
    static Providers result;
    return result;
}

//------------------------------------------------------------------------------
Providers::Providers()
    : _db(QSqlDatabase::addDatabase("QSQLITE"))
{
    QString dbFilePath = "./GiftCardsExample.db";

    _db.setDatabaseName(dbFilePath);
    if (!_db.open()) {
        qCritical() << "Can not open DB: " << _db.lastError().driverText();
    }

    createTables();

    // Делаем запрос
    const QUrl url("http://91.240.86.243:2444/files/providers.json");
    QNetworkRequest request(url);
    auto *reply = _nam.get(request);

    qDebug() << "send request to" << url;

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        qDebug() << "request finished" << reply->error();

        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) {
            Q_ASSERT(false); // Пока игнорируем ошибки
            return;
        }

        auto data = reply->readAll();
        auto json = QJsonDocument::fromJson(data);

        auto providersJson = json.object()["providers"].toArray();
        if (providersJson.isEmpty()) {
            Q_ASSERT(false);
            return;
        }

        int count = providersJson.count();
        _providers.reserve(count);

        for (int i=0; i<count; ++i) {
            _providers.append(ProviderPtr::create(providersJson.at(i).toObject()));
        }

        emit loaded();
    });
}

//------------------------------------------------------------------------------
void Providers::createTables()
{
    QSqlQuery query;
    bool isOk = query.exec("CREATE TABLE IF NOT EXISTS `" % _providersTable % "` ("
                   "`id` INTEGER NOT NULL PRIMARY KEY"
                   ", `json` TEXT"
               ") WITHOUT ROWID");

    if (!isOk) {
        qCritical() << "sql error" << query.lastQuery() << "\n" << query.lastError();
        Q_ASSERT(false);
        return;
    }

    isOk = query.exec("CREATE TABLE IF NOT EXISTS `" % _giftCardsTable % "` ("
                   "`id` INTEGER NOT NULL PRIMARY KEY"
                   ", `json` TEXT"
               ") WITHOUT ROWID");

    if (!isOk) {
        qCritical() << "sql error" << query.lastQuery() << "\n" << query.lastError();
        Q_ASSERT(false);
        return;
    }
}
