/// @author M. A. Serebrennikov
#pragma once

#include <QObject>
#include <QSharedPointer>

class QJsonObject;

namespace sp {

/***************************************************************************//**
 * @brief GiftCard class.
 ******************************************************************************/
class GiftCard : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString moneyStr READ moneyStr CONSTANT)
    Q_PROPERTY(QString creditsStr READ creditsStr CONSTANT)
    Q_PROPERTY(QString imageUrl READ imageUrl CONSTANT)

    public:
        inline const QString& moneyStr() const { return _moneyStr; }
        inline const QString& creditsStr() const { return _creditsStr; }
        inline const QString& imageUrl() const { return _imageUrl; }

    private:
        GiftCard(const QJsonObject &jsonObject);
        friend class QSharedPointer<GiftCard>;

    private:
        QString _moneyStr;
        QString _creditsStr;
        QString _imageUrl;
};

using GiftCardPtr = QSharedPointer<GiftCard>;
} // namespace sp
