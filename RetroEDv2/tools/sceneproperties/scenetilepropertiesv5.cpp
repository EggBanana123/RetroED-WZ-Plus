#include "includes.hpp"
#include "ui_scenetilepropertiesv5.h"

SceneTilePropertiesv5::SceneTilePropertiesv5(QWidget *parent)
    : QWidget(parent), ui(new Ui::SceneTilePropertiesv5)
{
    ui->setupUi(this);
}

SceneTilePropertiesv5::~SceneTilePropertiesv5() { delete ui; }

void SceneTilePropertiesv5::setupUI(RSDKv5::TileConfig::CollisionMask *cmA,
                                    RSDKv5::TileConfig::CollisionMask *cmB, ushort *tile,
                                    QImage tileImg)
{
    unsetUI();

    if (!cmA || !cmB || !tile)
        return;
    m_cmask[0] = cmA;
    m_cmask[1] = cmB;

    m_tileImg = tileImg;

    ui->flipX->setChecked(Utils::getBit(*tile, 10));
    ui->flipY->setChecked(Utils::getBit(*tile, 11));
    ui->solidTopA->setChecked(Utils::getBit(*tile, 12));
    ui->solidLRBA->setChecked(Utils::getBit(*tile, 13));
    ui->solidTopB->setChecked(Utils::getBit(*tile, 14));
    ui->solidLRBB->setChecked(Utils::getBit(*tile, 15));

    ui->colYFlip->setChecked(m_cmask[m_collisionLyr]->flipY);

    ui->behaviour->setValue(m_cmask[m_collisionLyr]->behaviour);
    ui->floorAngle->setValue(m_cmask[m_collisionLyr]->floorAngle);
    ui->roofAngle->setValue(m_cmask[m_collisionLyr]->roofAngle);
    ui->lWallAngle->setValue(m_cmask[m_collisionLyr]->lWallAngle);
    ui->rWallAngle->setValue(m_cmask[m_collisionLyr]->rWallAngle);

    ui->tID->setText("Tile ID: " + QString::number(*tile & 0x3FF));

    connect(ui->cLayer, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int v) {
        m_collisionLyr = (byte)v;
        if (m_collisionLyr >= 3)
            m_collisionLyr = 3;

        ui->colYFlip->blockSignals(true);
        ui->behaviour->blockSignals(true);
        ui->floorAngle->blockSignals(true);
        ui->roofAngle->blockSignals(true);
        ui->lWallAngle->blockSignals(true);
        ui->rWallAngle->blockSignals(true);

        ui->colYFlip->setChecked(m_cmask[m_collisionLyr]->flipY);
        ui->behaviour->setValue(m_cmask[m_collisionLyr]->behaviour);
        ui->floorAngle->setValue(m_cmask[m_collisionLyr]->floorAngle);
        ui->roofAngle->setValue(m_cmask[m_collisionLyr]->roofAngle);
        ui->lWallAngle->setValue(m_cmask[m_collisionLyr]->lWallAngle);
        ui->rWallAngle->setValue(m_cmask[m_collisionLyr]->rWallAngle);

        ui->colYFlip->blockSignals(false);
        ui->behaviour->blockSignals(false);
        ui->floorAngle->blockSignals(false);
        ui->roofAngle->blockSignals(false);
        ui->lWallAngle->blockSignals(false);
        ui->rWallAngle->blockSignals(false);
    });

    connect(ui->colYFlip, &QCheckBox::toggled, [this](bool v) { m_cmask[m_collisionLyr]->flipY = v; });

    connect(ui->behaviour, QOverload<int>::of(&QSpinBox::valueChanged),
            [this](int v) { m_cmask[m_collisionLyr]->behaviour = (byte)v; });

    connect(ui->floorAngle, QOverload<int>::of(&QSpinBox::valueChanged),
            [this](int v) { m_cmask[m_collisionLyr]->floorAngle = (byte)v; });

    connect(ui->roofAngle, QOverload<int>::of(&QSpinBox::valueChanged),
            [this](int v) { m_cmask[m_collisionLyr]->roofAngle = (byte)v; });

    connect(ui->lWallAngle, QOverload<int>::of(&QSpinBox::valueChanged),
            [this](int v) { m_cmask[m_collisionLyr]->lWallAngle = (byte)v; });

    connect(ui->rWallAngle, QOverload<int>::of(&QSpinBox::valueChanged),
            [this](int v) { m_cmask[m_collisionLyr]->rWallAngle = (byte)v; });

    connect(ui->editCollision, &QPushButton::clicked, [&] {
        TileCollisionWidgetv5 *edit = new TileCollisionWidgetv5();
        edit->m_cmask               = m_cmask[m_collisionLyr];
        edit->m_tileImg             = m_tileImg;
        edit->setWindowTitle("Edit Collision");
        edit->exec();
    });
}
void SceneTilePropertiesv5::unsetUI()
{

    if (!m_cmask[0] || !m_cmask[1]) // already unset
        return;

    ui->tID->setText("Tile ID: ");

    disconnect(ui->colYFlip, nullptr, nullptr, nullptr);
    disconnect(ui->floorAngle, nullptr, nullptr, nullptr);
    disconnect(ui->roofAngle, nullptr, nullptr, nullptr);
    disconnect(ui->lWallAngle, nullptr, nullptr, nullptr);
    disconnect(ui->rWallAngle, nullptr, nullptr, nullptr);
    disconnect(ui->behaviour, nullptr, nullptr, nullptr);

    disconnect(ui->editCollision, nullptr, nullptr, nullptr);

    m_cmask[0] = nullptr;
    m_cmask[1] = nullptr;
}

#include "moc_scenetilepropertiesv5.cpp"

TileCollisionWidgetv5::TileCollisionWidgetv5(QWidget *parent) : QDialog(parent)
{
    setMouseTracking(true);
}

void TileCollisionWidgetv5::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    QRectF rect(0, 0, (qreal)width() / 16, (qreal)height() / 16);
    p.drawImage(QRect(0, 0, width(), height()), m_tileImg);

    if (!m_cmask->flipY) {
        for (byte y = 0; y < 16; ++y) {
            for (byte x = 0; x < 16; ++x) {
                if (m_cmask->collision[x].height <= y) {
                    QPen pen(qApp->palette().base(), 2);
                    p.setPen(pen);
                    p.setBrush(QColor(0x00FF00));

                    if (!m_cmask->collision[x].solid)
                        p.setBrush(p.brush().color().darker(255));

                    p.drawRect(rect.translated(x * (qreal)width() / 16, y * (qreal)height() / 16));
                }
            }
        }
    }
    else {
        for (int y = 15; y > -1; --y) {
            for (int x = 15; x > -1; --x) {
                if (m_cmask->collision[x].height >= y) {

                    QPen pen(qApp->palette().base(), 2);
                    p.setPen(pen);
                    p.setBrush(QColor(0x00FF00));

                    if (!m_cmask->collision[x].solid)
                        p.setBrush(p.brush().color().darker(255));

                    p.drawRect(rect.translated(x * (qreal)width() / 16, y * (qreal)height() / 16));
                }
            }
        }
    }
}

void TileCollisionWidgetv5::leaveEvent(QEvent *)
{
    m_highlight = -1;
    update();
}

void TileCollisionWidgetv5::mousePressEvent(QMouseEvent *event)
{
    short x = floor((float)(event->x() / ((qreal)width() / 16)));
    if (x > 15)
        x = 15;

    if (x < 0)
        x = 0;

    m_selection = m_highlight;
    m_pressedL  = (event->button() & Qt::LeftButton) == Qt::LeftButton;
    m_pressedR  = (event->button() & Qt::RightButton) == Qt::RightButton;

    if (m_pressedR)
        m_enabling = !m_cmask->collision[x].solid;
}

void TileCollisionWidgetv5::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_pressedL)
        m_pressedL = !((event->button() & Qt::LeftButton) == Qt::LeftButton);
    if (m_pressedR)
        m_pressedR = !((event->button() & Qt::RightButton) == Qt::RightButton);
}

void TileCollisionWidgetv5::mouseMoveEvent(QMouseEvent *event)
{
    short x = floor((float)(event->x() / ((qreal)width() / 16)));
    short y = floor((float)(event->y() / ((qreal)height() / 16)));

    if (x > 15)
        x = 15;

    if (y > 15)
        y = 15;

    if (x < 0)
        x = 0;

    if (y < 0)
        y = 0;

    m_highlight = x % 16 + y * 16;

    if (m_pressedR)
        m_cmask->collision[x].solid = m_enabling;

    if (m_pressedL)
        m_cmask->collision[x].height = y;

    update();
}