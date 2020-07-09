/// @author M. A. Serebrennikov
#include "Provider.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QQmlEngine>

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
}
