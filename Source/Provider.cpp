/// @author M. A. Serebrennikov
#include "Provider.h"
#include "Providers.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QQmlEngine>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringBuilder>
#include <QJsonDocument>

using namespace sp;

Provider::Provider(const QJsonObject &jsonObject)
{
    Q_ASSERT(!jsonObject.isEmpty());

    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    _title = jsonObject["title"].toString();
    qDebug() << "\nprovider" << _title;

    auto giftsCardsJson = jsonObject["gift_cards"].toArray();

    if (!giftsCardsJson.count()) {
        Q_ASSERT(false);
        return;
    }

    const int count = giftsCardsJson.count();
    _giftCards.reserve(count);

    for (int i=0; i<count; ++i) {
        _giftCards.append(GiftCardPtr::create(giftsCardsJson.at(i).toObject()));
    }

    // Добавляем в БД
    int id = jsonObject["id"].toInt();
    QJsonDocument json(jsonObject);

    QSqlQuery query;
    query.prepare("INSERT OR IGNORE INTO `" % Providers::providersTable() % "` ("
                   "`id`"
                   ",`json`"
                  ") VALUES (?,?)");

    query.addBindValue(id);
    query.addBindValue(QString::fromUtf8(json.toJson(QJsonDocument::Compact)));

    bool isOk = query.exec();
    if (!isOk) {
        qCritical() << "sql error" << query.lastQuery() << "\n" << query.lastError();
        Q_ASSERT(false);
        return;
    }
}
