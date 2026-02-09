#ifndef FUNCCONFIGDIALOG_H
#define FUNCCONFIGDIALOG_H

#include <QDialog>
#include "funcitem.h"

namespace Ui {
class FuncConfigDialog;
}

class FuncConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FuncConfigDialog(QWidget *parent = nullptr);
    ~FuncConfigDialog();
    
    FuncItem* getNewFunc() const;

private slots:
    void onSelectIconClicked();
    void onAddCmdClicked();
    void onDelCmdClicked();
    void onConfirmClicked();
    void onCancelClicked();

private:
    Ui::FuncConfigDialog *ui;
    FuncItem *newFunc;
};

#endif // FUNCCONFIGDIALOG_H