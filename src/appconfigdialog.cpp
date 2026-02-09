#include "appconfigdialog.h"
#include "../ui/ui_appconfigdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QDir>

AppConfigDialog::AppConfigDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AppConfigDialog)
    , newApp(nullptr)
{
    ui->setupUi(this);
    
    // 连接信号槽，使用Qt6新语法
    connect(ui->selectIconBtn, &QPushButton::clicked, this, &AppConfigDialog::onSelectIconClicked);
    connect(ui->confirmBtn, &QPushButton::clicked, this, &AppConfigDialog::onConfirmClicked);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &AppConfigDialog::onCancelClicked);
    
    // 设置图标路径输入框为只读
    ui->iconPathEdit->setReadOnly(true);
}

AppConfigDialog::~AppConfigDialog()
{
    delete ui;
}

void AppConfigDialog::onSelectIconClicked()
{
    // 跨平台文件选择对话框
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("选择应用图标"),
        QDir::currentPath(),
        tr("图片文件 (*.png *.jpg *.ico)"));
    
    if (!fileName.isEmpty()) {
        ui->iconPathEdit->setText(fileName);
    }
}

void AppConfigDialog::onConfirmClicked()
{
    QString appName = ui->appNameEdit->text().trimmed();
    QString iconPath = ui->iconPathEdit->text().trimmed();
    
    // 校验应用名非空
    if (appName.isEmpty()) {
        QMessageBox::warning(this, tr("提示"), tr("应用名不能为空"));
        return;
    }
    
    // 校验图标路径非空且文件存在
    if (iconPath.isEmpty()) {
        QMessageBox::warning(this, tr("提示"), tr("图标文件不能为空"));
        return;
    }
    
    if (!QFile::exists(iconPath)) {
        QMessageBox::warning(this, tr("提示"), tr("图标文件不存在"));
        return;
    }
    
    // 创建新的应用项
    newApp = new AppItem(appName, iconPath, this);
    accept();
}

void AppConfigDialog::onCancelClicked()
{
    reject();
}

AppItem* AppConfigDialog::getNewApp() const
{
    return newApp;
}