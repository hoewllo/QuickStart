#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include "icongenerator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    QWidget window;
    window.setWindowTitle("图标生成器测试");
    window.resize(400, 500);
    
    QVBoxLayout *layout = new QVBoxLayout(&window);
    
    // 创建列表显示生成的图标
    QListWidget *listWidget = new QListWidget();
    layout->addWidget(listWidget);
    
    // 测试名称列表
    QStringList testNames = {
        "Chrome",
        "Visual Studio",
        "Photoshop",
        "微信",
        "QQ",
        "记事本",
        "计算器",
        "终端",
        "浏览器",
        "音乐播放器"
    };
    
    // 为每个测试名称生成图标
    for (const QString &name : testNames) {
        QIcon icon = IconGenerator::generateDefaultIcon(name, 64);
        QListWidgetItem *item = new QListWidgetItem(name);
        item->setIcon(icon);
        listWidget->addItem(item);
    }
    
    // 添加测试按钮
    QPushButton *testButton = new QPushButton("测试自定义图标");
    layout->addWidget(testButton);
    
    QObject::connect(testButton, &QPushButton::clicked, [listWidget]() {
        // 测试自定义颜色图标
        QList<QColor> colors = IconGenerator::getDefaultColors();
        QStringList letters = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
        
        for (int i = 0; i < qMin(colors.size(), letters.size()); i++) {
            QIcon icon = IconGenerator::generateIcon(letters[i], colors[i], Qt::white, 64);
            QListWidgetItem *item = new QListWidgetItem(
                QString("颜色%1 - %2").arg(i+1).arg(letters[i]));
            item->setIcon(icon);
            listWidget->addItem(item);
        }
    });
    
    window.show();
    return app.exec();
}