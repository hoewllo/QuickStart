#ifndef APPCONFIGDIALOG_H
#define APPCONFIGDIALOG_H

#include <QDialog>
#include "appitem.h"

namespace Ui {
class AppConfigDialog;
}

class AppConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AppConfigDialog(QWidget *parent = nullptr);
    ~AppConfigDialog();
    
    AppItem* getNewApp() const;

private slots:
    void onSelectIconClicked();
    void onConfirmClicked();
    void onCancelClicked();

private:
    Ui::AppConfigDialog *ui;
    AppItem *newApp;
};

#endif // APPCONFIGDIALOG_H