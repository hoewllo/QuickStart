#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "appitem.h"
#include "appconfigdialog.h"
#include "funcconfigdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(AppItem *currentItem = nullptr, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onIconListItemClicked(QListWidgetItem *item);
    void onAddAppClicked();
    void onAddFuncClicked();

private:
    void refreshIconList();
    void saveConfig();
    void loadConfig();

    Ui::MainWindow *ui;
    AppItem *currentItem;
    AppItem *rootItem;
    const QString CONFIG_FILE_PATH = "./config.json";
};
#endif // MAINWINDOW_H

