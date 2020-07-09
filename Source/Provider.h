/// @author M. A. Serebrennikov
#pragma once

#include "GiftCard.h"

#include <QObject>
#include <QVector>
#include <QSharedPointer>

class QJsonObject;

namespace sp {

/***************************************************************************//**
 * @brief Provider class.
 ******************************************************************************/
class Provider : public QObject, public QEnableSharedFromThis<Provider>
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title CONSTANT)

    public:
        inline const QString& title() const { return _title; }
        inline const QVector<GiftCardPtr>& giftCards() const { return _giftCards; }
        inline int count() const { return _giftCards.count(); }

    private:
        Provider(const QJsonObject &jsonObject);
        friend class QSharedPointer<Provider>;

    signals:
        void giftCardsBeforeChanged() const;
        void giftCardsChanged() const;

    private:
        QString _title;
        QVector<GiftCardPtr> _giftCards;
};

using ProviderPtr = QSharedPointer<Provider>;
} // namespace sp
