/// @author M. A. Serebrennikov
#include "Providers.h"
#include "ProvidersModel.h"

using namespace sp;

ProvidersModel::ProvidersModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(&ProvidersI, &Providers::loaded, this, [this]() {
        emit beginResetModel();
        emit endResetModel();
    });
}

//------------------------------------------------------------------------------
int ProvidersModel::rowCount(const QModelIndex &/*parent*/) const
{
    return ProvidersI.count();
}

//------------------------------------------------------------------------------
QVariant ProvidersModel::data(const QModelIndex &index, int role) const
{
    Q_ASSERT(index.row() >= 0);
    if (!index.isValid() || index.row() >= ProvidersI.count()) {
        return {};
    }

    switch (role) {
        case 0:
            return QVariant::fromValue(ProvidersI.providers().value(index.row()).data());

        default:
            Q_ASSERT(false);
            return {};
    }
}

//------------------------------------------------------------------------------
QHash<int, QByteArray> ProvidersModel::roleNames() const
{
    static QHash<int, QByteArray> result = {{0, "provider"}};
    return result;
}
