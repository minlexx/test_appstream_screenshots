#include <QDebug>
#include <QDir>
#include <QList>
#include <QLoggingCategory>
#include <QStringBuilder>

#include <QtDebug>

#include <AppStreamQt/image.h>
#include <AppStreamQt/metadata.h>
#include <AppStreamQt/pool.h>
#include <AppStreamQt/screenshot.h>
#include <AppStreamQt/version.h>

#include <cerrno>
#include <cstdlib>

Q_LOGGING_CATEGORY(TEST, "test", QtDebugMsg);

static inline void strAppendFlag(QString &s, const QString &add)
{
    if (s.length()) {
        s.append(QLatin1String(" | "));
    }
    s.append(add);
}

static QString dumpPoolFlags(uint flags)
{
    QString s;
    if (flags & AppStream::Pool::FlagLoadOsCollection) strAppendFlag(s, QStringLiteral("FlagLoadOsCollection"));
    if (flags & AppStream::Pool::FlagLoadOsMetainfo) strAppendFlag(s, QStringLiteral("FlagLoadOsMetainfo"));
    if (flags & AppStream::Pool::FlagLoadOsDesktopFiles) strAppendFlag(s, QStringLiteral("FlagLoadOsDesktopFiles"));
    if (flags & AppStream::Pool::FlagLoadFlatpak) strAppendFlag(s, QStringLiteral("FlagLoadFlatpak"));
    if (flags & AppStream::Pool::FlagIgnoreCacheAge) strAppendFlag(s, QStringLiteral("FlagIgnoreCacheAge"));
    if (flags & AppStream::Pool::FlagResolveAddons) strAppendFlag(s, QStringLiteral("FlagResolveAddons"));
    if (flags & AppStream::Pool::FlagPreferOsMetainfo) strAppendFlag(s, QStringLiteral("FlagPreferOsMetainfo"));
    if (flags & AppStream::Pool::FlagMonitor) strAppendFlag(s, QStringLiteral("FlagMonitor"));
    return s;
}

static QString imageKindToStr(AppStream::Image::Kind kind)
{
    switch (kind) {
    case AppStream::Image::KindUnknown: return QStringLiteral("KindUnknown"); break;
    case AppStream::Image::KindSource: return QStringLiteral("KindSource"); break;
    case AppStream::Image::KindThumbnail: return QStringLiteral("KindThumbnail"); break;
    };
    return QString();
}

static void dumpImage(const AppStream::Image &image)
{
    qCDebug(TEST) << "    " << imageKindToStr(image.kind()) << "; url: " << image.url().toString();
}

void dumpScreenshots(const QList<AppStream::Screenshot> &screenshots)
{
    for (const AppStream::Screenshot &screenshot: screenshots) {
        const QList<AppStream::Image> images = screenshot.images();
        for (const AppStream::Image &image : images) {
            dumpImage(image);
        }
    }
}

QString getExtraDataPath()
{
    return QDir::currentPath() + "/metadata";
}

int main()
{
    AppStream::Pool pool;

    qCDebug(TEST) << "Pool default flags: " << dumpPoolFlags(pool.flags());
    pool.removeFlags(AppStream::Pool::FlagLoadFlatpak | AppStream::Pool::FlagLoadOsMetainfo);
    qCDebug(TEST) << "Pool new flags: " << dumpPoolFlags(pool.flags());

    qCDebug(TEST) << "Adding extra metadata path: " << getExtraDataPath();
    pool.addExtraDataLocation(getExtraDataPath(), AppStream::Metadata::FormatStyleCollection);

    if (!pool.load()) {
        return ENODATA;
    }

    const QList<AppStream::Component> components = pool.components();
    qCDebug(TEST) << "Loaded total " << components.size() << " components";

    const QList<AppStream::Component> ktorrents = pool.componentsById(QLatin1String("org.kde.ktorrent.desktop"));
    qCDebug(TEST) << "Found ktorrent " << ktorrents.size() << " times";
    for (const AppStream::Component &comp : ktorrents) {
        qCDebug(TEST) << "  " << comp.id();

        const QList<AppStream::Screenshot> screenshots = comp.screenshots();
        dumpScreenshots(screenshots);
    }

    return EXIT_SUCCESS;
}
