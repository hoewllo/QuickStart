#include "funcconfigdialog.h"
#include "../ui/ui_funcconfigdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QProcess>

FuncConfigDialog::FuncConfigDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FuncConfigDialog)
    , newFunc(nullptr)
{
    ui->setupUi(this);
    
    // 连接信号槽，使用Qt6新语法
    connect(ui->selectIconBtn, &QPushButton::clicked, this, &FuncConfigDialog::onSelectIconClicked);
    connect(ui->addCmdBtn, &QPushButton::clicked, this, &FuncConfigDialog::onAddCmdClicked);
    connect(ui->delCmdBtn, &QPushButton::clicked, this, &FuncConfigDialog::onDelCmdClicked);
    connect(ui->confirmBtn, &QPushButton::clicked, this, &FuncConfigDialog::onConfirmClicked);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &FuncConfigDialog::onCancelClicked);
    
    // 设置图标路径输入框为只读
    ui->iconPathEdit->setReadOnly(true);
}

FuncConfigDialog::~FuncConfigDialog()
{
    delete ui;
}

void FuncConfigDialog::onSelectIconClicked()
{
    // 跨平台文件选择对话框
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("选择功能图标"),
        QDir::currentPath(),
        tr("图片文件 (*.png *.jpg *.ico)"));
    
    if (!fileName.isEmpty()) {
        ui->iconPathEdit->setText(fileName);
    }
}

void FuncConfigDialog::onAddCmdClicked()
{
    // 跨平台文件选择对话框，按系统自动适配过滤规则
    QString filter;
#ifdef Q_OS_WIN
    filter = tr("可执行文件 (*.exe)");
#else
    filter = tr("可执行文件 (*.sh *.bin *)");
#endif
    
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("选择可执行文件"),
        QDir::currentPath(),
        filter);
    
    if (!fileName.isEmpty()) {
        // 检查是否已存在
        bool exists = false;
        for (int i = 0; i < ui->cmdListWidget->count(); ++i) {
            if (ui->cmdListWidget->item(i)->text() == fileName) {
                exists = true;
                break;
            }
        }
        
        if (!exists) {
            ui->cmdListWidget->addItem(fileName);
        }
    }
}

void FuncConfigDialog::onDelCmdClicked()
{
    QListWidgetItem *currentItem = ui->cmdListWidget->currentItem();
    if (currentItem) {
        delete currentItem;
    }
}

void FuncConfigDialog::onConfirmClicked()
{
    QString funcName = ui->funcNameEdit->text().trimmed();
    QString iconPath = ui->iconPathEdit->text().trimmed();
    
    // 校验功能名非空
    if (funcName.isEmpty()) {
        QMessageBox::warning(this, tr("提示"), tr("功能名不能为空"));
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
    
    // 校验命令列表非空
    if (ui->cmdListWidget->count() == 0) {
        QMessageBox::warning(this, tr("提示"), tr("命令列表不能为空"));
        return;
    }
    
    // 收集命令列表
    QStringList cmds;
    for (int i = 0; i < ui->cmdListWidget->count(); ++i) {
        cmds.append(ui->cmdListWidget->item(i)->text());
    }
    
    // 创建新的功能项
    newFunc = new FuncItem(funcName, iconPath, cmds, this);
    accept();
}

void FuncConfigDialog::onCancelClicked()
{
    reject();
}

FuncItem* FuncConfigDialog::getNewFunc() const
{
    return newFunc;
}