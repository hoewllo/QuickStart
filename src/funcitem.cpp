#include "funcitem.h"
#include "icongenerator.h"
#include <QJsonArray>
#include <QFile>
#include <QFileInfo>

FuncItem::FuncItem(QObject *parent)
    : QObject(parent)
    , name("")
    , iconPath("")
{
}

FuncItem::FuncItem(const QString &name, const QString &iconPath, const QStringList &cmds, QObject *parent)
    : QObject(parent)
    , name(name)
    , iconPath(iconPath)
    , cmds(cmds)
{
}

QIcon FuncItem::getIcon() const
{
    // 如果图标路径不为空且文件存在，使用指定图标
    if (!iconPath.isEmpty()) {
        QFileInfo fileInfo(iconPath);
        if (fileInfo.exists()) {
            return QIcon(iconPath);
        }
    }
    
    // 否则使用默认图标生成器
    return IconGenerator::generateDefaultIcon(name);
}

void FuncItem::addCmd(const QString &cmd)
{
    if (!cmd.isEmpty() && !cmds.contains(cmd)) {
        cmds.append(cmd);
    }
}

void FuncItem::removeCmd(int index)
{
    if (index >= 0 && index < cmds.size()) {
        cmds.removeAt(index);
    }
}

QJsonObject FuncItem::toJson() const
{
    QJsonObject obj;
    obj["name"] = name;
    obj["iconPath"] = iconPath;
    
    // 序列化命令列表
    QJsonArray cmdsArray;
    for (const QString &cmd : cmds) {
        cmdsArray.append(cmd);
    }
    obj["cmds"] = cmdsArray;
    
    return obj;
}

void FuncItem::fromJson(const QJsonObject &obj)
{
    name = obj["name"].toString();
    iconPath = obj["iconPath"].toString();
    
    // 反序列化命令列表
    cmds.clear();
    QJsonArray cmdsArray = obj["cmds"].toArray();
    for (const QJsonValue &value : cmdsArray) {
        cmds.append(value.toString());
    }
}