/// @author M. A. Serebrennikov
#include "GiftCard.h"

#include <QDebug>
#include <QJsonObject>
#include <QLocale>
#include <QQmlEngine>

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
}
