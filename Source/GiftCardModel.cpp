/// @author M. A. Serebrennikov
#include "GiftCardModel.h"
#include "GiftCard.h"

using namespace sp;

GiftCardModel::GiftCardModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

//------------------------------------------------------------------------------
void GiftCardModel::setProvider(Provider *provider)
{
    if (_provider) {
        disconnect(_provider.data(), nullptr, this, nullptr);
    }

    emit beginResetModel();
    _provider = provider->sharedFromThis();
    emit endResetModel();

    connect(provider, &Provider::giftCardsBeforeChanged, this, [this]() {
        emit beginResetModel();
    });
    connect(provider, &Provider::giftCardsChanged, this, [this]() {
        emit endResetModel();
    });
}

//------------------------------------------------------------------------------
int GiftCardModel::rowCount(const QModelIndex &/*parent*/) const
{
    return _provider ? _provider->count() : 0;
}

//------------------------------------------------------------------------------
QVariant GiftCardModel::data(const QModelIndex &index, int role) const
{
    if (!_provider) {
        return {};
    }

    Q_ASSERT(index.row() >= 0);
    if (!index.isValid() || index.row() >= _provider->count()) {
        return {};
    }

    switch (role) {
        case 0:
            return QVariant::fromValue(_provider->giftCards().value(index.row()).data());

        default:
            Q_ASSERT(false);
            return {};
    }
}

//------------------------------------------------------------------------------
QHash<int, QByteArray> GiftCardModel::roleNames() const
{
    static QHash<int, QByteArray> result = {{0, "giftCard"}};
    return result;
}
