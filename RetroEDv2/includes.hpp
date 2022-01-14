#ifndef INCLUDES_H
#define INCLUDES_H

#define RETROED_VER   (0x100)
#define RETROED_DEBUG (1)

// QT
#include <QtCore>
#include <QStringList>
#include <QColorDialog>
#include <QDebug>
#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QImage>
#include <QLabel>
#include <QLayout>
#include <QListWidget>
#include <QMdiArea>
#include <QToolButton>
#include <QWidget>
#include <QtEndian>
#include <QTreeView>
#include <QtGui>
#include <QtWidgets>
#include <QMainWindow>
#include <QFileSystemModel>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QMenu>
#include <QMetaType>
#include <QDomElement>

typedef signed char sbyte;
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long int64;
typedef unsigned long long uint64;

enum Event {
    RE_EVENT_SAVE = QEvent::User + 64,
    RE_EVENT_OPEN,
    RE_EVENT_NEW,
    RE_EVENT_SAVE_AS,
    RE_EVENT_UNDO,
    RE_EVENT_REDO,
};

class REAppEvent : public QEvent
{
public:
    REAppEvent(int event) : QEvent(static_cast<QEvent::Type>(event)) {}

    static const QEvent::Type type;
};

// RSDK
#include "dependencies/rsdk_reverse/rsdkreverse.hpp"

// Misc/Utils
#include "utils/retroedutils.hpp"
#include "utils/vectors.hpp"
#include "utils/colour.hpp"
#include "utils/palette.hpp"
#include "utils/shaders.hpp"
#include "utils/workingdirmanager.hpp"

// RSDKv5 Link
#include "tools/gamelink/gamelink.hpp"

// Formats
#include "utils/appconfig.hpp"
#include "utils/staticobjectinfo.hpp"

// Compilers
#include "tools/compiler/compilerv1.hpp"
#include "tools/compiler/compilerv2.hpp"
#include "tools/compiler/compilerv3.hpp"
#include "tools/compiler/compilerv4.hpp"

// Decompilers
#include "tools/decompiler/decompilerv1.hpp"
#include "tools/decompiler/decompilerv3.hpp"
#include "tools/decompiler/decompilerv4.hpp"

// Form Utils
#include "tools/utils/propertygrid.hpp"

#include "tools/sceneviewer.hpp"
#include "tools/sceneproperties/sceneproperties.hpp"
#include "tools/sceneproperties/scenelayerproperties.hpp"
#include "tools/sceneproperties/sceneobjectproperties.hpp"
#include "tools/sceneproperties/scenescrollproperties.hpp"
#include "tools/sceneproperties/scenetileproperties.hpp"
#include "tools/sceneproperties/sceneexportimgoptions.hpp"

#include "tools/sceneproperties/scenepropertiesv5.hpp"
#include "tools/sceneproperties/scenelayerpropertiesv5.hpp"
#include "tools/sceneproperties/sceneobjectpropertiesv5.hpp"
#include "tools/sceneproperties/scenescrollpropertiesv5.hpp"
#include "tools/sceneproperties/scenetilepropertiesv5.hpp"
#include "tools/sceneproperties/scenestamppropertiesv5.hpp"
#include "tools/sceneproperties/objectselector.hpp"
#include "tools/sceneviewerv5.hpp"

#include "tools/sceneproperties/stageconfigeditorv1.hpp"
#include "tools/sceneproperties/stageconfigeditorv2.hpp"
#include "tools/sceneproperties/stageconfigeditorv3.hpp"
#include "tools/sceneproperties/stageconfigeditorv4.hpp"
#include "tools/sceneproperties/stageconfigeditorv5.hpp"
#include "tools/sceneproperties/chunkeditor.hpp"
#include "tools/sceneproperties/tileseteditor.hpp"

#include "tools/animationeditor/animsheetselector.hpp"

// Forms
#include "tools/gameconfigeditorv1.hpp"
#include "tools/gameconfigeditorv2.hpp"
#include "tools/gameconfigeditorv3.hpp"
#include "tools/gameconfigeditorv4.hpp"
#include "tools/gameconfigeditorv5.hpp"
#include "tools/animationeditor.hpp"
#include "tools/modelmanager.hpp"
#include "tools/gfxtool.hpp"
#include "tools/paletteeditor.hpp"
#include "tools/paletteeditor/colourdialog.hpp"
#include "tools/rsdkunpacker.hpp"
#include "tools/scriptcompiler.hpp"
#include "tools/scriptunpacker.hpp"
#include "tools/sceneeditor.hpp"
#include "tools/sceneeditorv5.hpp"
#include "tools/userdbmanager.hpp"
#include "tools/rsvtool.hpp"

#include "mainwindow.hpp"

extern QString homeDir;
extern QString appDir;
extern AppConfig appConfig;

extern QLabel *statusLabel;

extern QVector3D *vertsPtr;
extern QVector2D *tVertsPtr;

extern SceneEditor *scnEditor;
extern SceneEditorv5 *v5Editor;

void printLog(QString msg);
void setStatus(QString status);

void refreshScnEditorVerts(int w, int h);

#endif // INCLUDES_H
