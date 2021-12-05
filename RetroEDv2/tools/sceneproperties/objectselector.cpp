#include "includes.hpp"
#include "ui_objectselector.h"

ObjectSelectorv5::ObjectSelectorv5(QList<QString> list, QList<GameObjectInfo> objList, QWidget *parent)
    : QDialog(parent), ui(new Ui::ObjectSelectorv5)
{
    ui->setupUi(this);

    ui->objList->clear();
    objAddList.clear();

    disconnect(ui->buttonBox, nullptr, nullptr, nullptr);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, [this] { this->accept(); });
    connect(ui->buttonBox, &QDialogButtonBox::rejected, [this] { this->reject(); });

    disconnect(ui->objList, nullptr, nullptr, nullptr);
    connect(ui->objList, &QListWidget::itemChanged, [this, list](QListWidgetItem *item) {
        int r = ui->objList->row(item) - list.count();
        if (r >= 0 && r < objAddList.count())
            objAddList[r] = item->checkState() != Qt::Unchecked;
    });

    for (QString &obj : list) {
        // object already exists
        QListWidgetItem *item = new QListWidgetItem();
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
        item->setCheckState(Qt::Checked);
        item->setText(obj);
        ui->objList->addItem(item);
    }

    int id = 0;
    for (auto &obj : objList) {
        if (list.indexOf(obj.name) == -1) { // new object perhaps????
            QListWidgetItem *item = new QListWidgetItem();
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
            item->setText(obj.name);
            ui->objList->addItem(item);

            objIDList.append(id);
            objAddList.append(false);
        }
        id++;
    }
}

ObjectSelectorv5::~ObjectSelectorv5() { delete ui; }

#include "moc_objectselector.cpp"