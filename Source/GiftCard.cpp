/// @author M. A. Serebrennikov
#include "GiftCard.h"
#include "Providers.h"

#include <QDebug>
#include <QJsonObject>
#include <QLocale>
#include <QQmlEngine>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringBuilder>
#include <QJsonDocument>

using namespace sp;

GiftCard::GiftCard(const QJsonObject &jsonObject)
{
    Q_ASSERT(!jsonObject.isEmpty());

    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    auto title = jsonObject["title"].toString();
    auto credits = jsonObject["credits"].toInt();
    _moneyStr = title.left(title.indexOf(' '));
    _creditsStr = QLocale::system().toString(credits);
    _imageUrl = jsonObject["image_url"].toString();

    qDebug() << "giftCard" << title;

    // Добавляем в БД
    int id = jsonObject["id"].toInt();
    QJsonDocument json(jsonObject);

    QSqlQuery query;
    query.prepare("INSERT OR IGNORE INTO `" % Providers::giftCardsTable() % "` ("
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
