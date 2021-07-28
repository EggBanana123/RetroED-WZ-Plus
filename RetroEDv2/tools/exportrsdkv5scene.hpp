#ifndef EXPORTRSDKV5SCENE_HPP
#define EXPORTRSDKV5SCENE_HPP

#include <QDialog>

namespace Ui
{
class ExportRSDKv5Scene;
}

class ExportRSDKv5Scene : public QDialog
{
    Q_OBJECT

public:
    explicit ExportRSDKv5Scene(QString path, QWidget *parent = nullptr);
    ~ExportRSDKv5Scene();

    QString m_outputPath     = "";
    bool exportLayers      = true;
    bool exportObjects     = true;
    bool exportChunks      = true;
    bool exportTileConfig  = true;
    bool exportStageConfig = true;

private:
    Ui::ExportRSDKv5Scene *ui;
};

#endif // EXPORTRSDKV5SCENE_HPP