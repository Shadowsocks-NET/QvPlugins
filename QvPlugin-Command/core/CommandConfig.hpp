#pragma once

#include "QvPlugin/Utils/JsonConversion.hpp"

#include <QString>

struct CommandPluginConfig
{
    QString beforeConnection;
    QString afterConnection;
    QString beforeDisConnection;
    QString afterDisConnection;

    QString connectionCreated;
    QString connectionRenamed;
    QString connectionUpdated;
    QString connectionDeleted;

    QString setSystemProxy;
    QString clearSystemProxy;

    QJS_JSON(F(beforeConnection, afterConnection, beforeDisConnection, afterDisConnection, //
               connectionCreated, connectionRenamed, connectionUpdated, connectionDeleted, //
               setSystemProxy, clearSystemProxy))
};
