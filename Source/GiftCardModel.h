/// @author M. A. Serebrennikov
#pragma once

#include "Provider.h"

#include <QAbstractListModel>

namespace sp {

/***************************************************************************//**
 * @brief GiftCardModel class.
 ******************************************************************************/
class GiftCardModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(Provider* provider READ providerRaw WRITE setProvider NOTIFY providerChanged)

    public:
        GiftCardModel(QObject *parent = nullptr);

        //--------------------------------------------------------------------
        // Get
        //--------------------------------------------------------------------
        inline ProviderPtr provider() const { return _provider; }
        inline Provider* providerRaw() const { return _provider.data(); }

        //--------------------------------------------------------------------
        // Set
        //--------------------------------------------------------------------
        /** Устанавливает провайдер из QML. Обязательное действие. */
        void setProvider(Provider *provider);

        //----------------------------------------------------------------------
        // Override
        //----------------------------------------------------------------------
        int rowCount (const QModelIndex & parent = QModelIndex()) const override;
        QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const override;
        QHash<int, QByteArray> roleNames() const override;

    signals:
        void providerChanged() const;

    private:
        ProviderPtr _provider;
};
} // namespace sp
