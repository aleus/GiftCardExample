/// @author M. A. Serebrennikov
#pragma once

#include "Provider.h"

#include <QNetworkAccessManager>
#include <QObject>
#include <QVector>

namespace sp {

#define ProvidersI Providers::instance()

/***************************************************************************//**
 * @brief Providers class.
 ******************************************************************************/
class Providers : public QObject
{
    Q_OBJECT

    public:
        static Providers& instance();

        /** Возвращает true, если список провайдеров был загружен с сервера. */
        inline bool isLoaded() const { return _isLoaded; }

        /** Возвращает количество провайдеров. */
        inline int count() const { return _providers.count(); }

        /** Возвращает список провайдеров. */
        inline const QVector<ProviderPtr>& providers() const { return _providers; }

    private:
        Providers();

    signals:
        /** Провайдеры загружены из сети. */
        void loaded() const;

    private:
        QNetworkAccessManager _nam;
        QVector<ProviderPtr> _providers;
        bool _isLoaded = false;
};
} // namespace sp
