#include "appitem.h"
#include <QJsonArray>

AppItem::AppItem(QObject *parent)
    : QObject(parent)
    , name("")
    , iconPath("")
{
}

AppItem::AppItem(const QString &name, const QString &iconPath, QObject *parent)
    : QObject(parent)
    , name(name)
    , iconPath(iconPath)
{
}

AppItem::~AppItem()
{
    // 基于Qt父子对象机制自动释放内存
    for (AppItem *app : subApps) {
        if (app) {
            app->deleteLater();
        }
    }
    for (FuncItem *func : funcs) {
        if (func) {
            func->deleteLater();
        }
    }
}

void AppItem::addSubApp(AppItem *app)
{
    if (app) {
        app->setParent(this);
        subApps.append(app);
    }
}

void AppItem::addFunc(FuncItem *func)
{
    if (func) {
        func->setParent(this);
        funcs.append(func);
    }
}

void AppItem::removeSubApp(AppItem *app)
{
    if (app) {
        subApps.removeAll(app);
        app->deleteLater();
    }
}

void AppItem::removeFunc(FuncItem *func)
{
    if (func) {
        funcs.removeAll(func);
        func->deleteLater();
    }
}

QJsonObject AppItem::toJson() const
{
    QJsonObject obj;
    obj["name"] = name;
    obj["iconPath"] = iconPath;
    
    // 序列化子应用
    QJsonArray subAppsArray;
    for (const AppItem *app : subApps) {
        subAppsArray.append(app->toJson());
    }
    obj["subApps"] = subAppsArray;
    
    // 序列化功能项
    QJsonArray funcsArray;
    for (const FuncItem *func : funcs) {
        funcsArray.append(func->toJson());
    }
    obj["funcs"] = funcsArray;
    
    return obj;
}

void AppItem::fromJson(const QJsonObject &obj)
{
    name = obj["name"].toString();
    iconPath = obj["iconPath"].toString();
    
    // 清空现有数据
    for (AppItem *app : subApps) {
        app->deleteLater();
    }
    subApps.clear();
    
    for (FuncItem *func : funcs) {
        func->deleteLater();
    }
    funcs.clear();
    
    // 反序列化子应用
    QJsonArray subAppsArray = obj["subApps"].toArray();
    for (const QJsonValue &value : subAppsArray) {
        AppItem *app = new AppItem(this);
        app->fromJson(value.toObject());
        subApps.append(app);
    }
    
    // 反序列化功能项
    QJsonArray funcsArray = obj["funcs"].toArray();
    for (const QJsonValue &value : funcsArray) {
        FuncItem *func = new FuncItem(this);
        func->fromJson(value.toObject());
        funcs.append(func);
    }
}