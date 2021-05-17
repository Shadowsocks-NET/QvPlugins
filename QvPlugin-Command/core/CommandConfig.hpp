#pragma once
#include "QJsonStruct.hpp"

#include <QString>

struct CommandPluginConfig
{
    QString beforeConnection;
    QString afterConnection;
    QString beforeDisConnection;
    QString afterDisConnection;
    //
    QString connectionCreated;
    QString connectionRenamed;
    QString connectionUpdated;
    QString connectionDeleted;
    //
    QString setSystemProxy;
    QString clearSystemProxy;
    //
    QJS_PLAIN_JSON(beforeConnection, afterConnection, beforeDisConnection, afterDisConnection, //
                   connectionCreated, connectionRenamed, connectionUpdated, connectionDeleted, //
                   setSystemProxy, clearSystemProxy)
};
