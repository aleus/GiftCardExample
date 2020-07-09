/// @author M. A. Serebrennikov
#pragma once

#include <QObject>

#include <QAbstractListModel>

namespace sp {

/***************************************************************************//**
 * @brief ProvidersModel class.
 ******************************************************************************/
class ProvidersModel : public QAbstractListModel
{
    Q_OBJECT

    public:
        ProvidersModel(QObject *parent = nullptr);

        //----------------------------------------------------------------------
        // Override
        //----------------------------------------------------------------------
        int rowCount (const QModelIndex & parent = QModelIndex()) const override;
        QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const override;
        QHash<int, QByteArray> roleNames() const override;

    signals:
        void providerChanged() const;
};
} // namespace sp
