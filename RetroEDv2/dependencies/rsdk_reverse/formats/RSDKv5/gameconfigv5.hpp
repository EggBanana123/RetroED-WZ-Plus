#ifndef GAMECONFIG_V5_H
#define GAMECONFIG_V5_H

namespace RSDKv5
{

class GameConfig
{
public:
    class WAVConfiguration
    {
    public:
        QString m_name           = "SFX.wav";
        byte m_maxConcurrentPlay = 1;

        WAVConfiguration() {}
        WAVConfiguration(QString name, byte maxPlays)
        {
            m_name              = name;
            m_maxConcurrentPlay = maxPlays;
        }
        WAVConfiguration(Reader &reader) { read(reader); }

        inline void read(Reader reader)
        {
            m_name              = reader.readString();
            m_maxConcurrentPlay = reader.read<byte>();
        }

        inline void write(Writer &writer)
        {
            writer.write(m_name);
            writer.write(m_maxConcurrentPlay);
        }
    };

    class SceneInfo
    {
    public:
        QString m_name    = "Scene";
        QString m_folder  = "";
        QString m_sceneID = "";
        byte m_modeFilter = 0;

        SceneInfo() {}
        SceneInfo(Reader &reader, bool readMode = true) { read(reader, readMode); }

        inline void read(Reader &reader, bool readMode = true)
        {
            m_name    = reader.readString();
            m_folder  = reader.readString();
            m_sceneID = reader.readString();
            if (readMode)
                m_modeFilter = reader.read<byte>();
        }

        inline void write(Writer &writer, bool readMode = true)
        {
            writer.write(m_name);
            writer.write(m_folder);
            writer.write(m_sceneID);

            if (readMode)
                writer.write(m_modeFilter);
        }
    };

    class Category
    {
    public:
        QString m_name = "New Category";
        QList<SceneInfo> m_scenes;

        Category()
        {
            m_name = "New Category";
            m_scenes.clear();
            m_scenes.append(SceneInfo());
        }
        Category(Reader &reader, bool readMode = true) { read(reader, readMode); }

        inline void read(Reader &reader, bool readMode = true)
        {
            m_name = reader.readString();

            byte sceneCount = reader.read<byte>();
            m_scenes.clear();
            for (int i = 0; i < sceneCount; ++i) m_scenes.append(SceneInfo(reader, readMode));
        }

        inline void write(Writer &writer, bool readMode = true)
        {
            writer.write(m_name);

            writer.write((byte)m_scenes.count());
            for (SceneInfo &scene : m_scenes) scene.write(writer, readMode);
        }
    };

    class ConfigurableMemoryEntry
    {
    public:
        int m_index;
        QList<int> m_values;

        ConfigurableMemoryEntry() {}
        ConfigurableMemoryEntry(Reader &reader) { read(reader); }

        void read(Reader &reader)
        {
            m_index   = reader.read<int>();
            int count = reader.read<int>();
            m_values.clear();
            for (int i = 0; i < count; ++i) m_values.append(reader.read<int>());
        }

        inline void write(Writer &writer)
        {
            writer.write(m_index);
            writer.write((int)m_values.count());
            for (int &val : m_values) writer.write(val);
        }
    };

    GameConfig() {}
    GameConfig(QString filename, bool oldVer = false) { read(filename, oldVer); }
    GameConfig(Reader &reader, bool oldVer = false) { read(reader, oldVer); }

    inline void read(QString filename, bool oldVer = false)
    {
        Reader reader(filename);
        read(reader, oldVer);
    }
    void read(Reader &reader, bool oldVer = false);

    inline void write(QString filename)
    {
        if (filename == "")
            filename = m_filename;
        if (filename == "")
            return;
        Writer writer(filename);
        write(writer);
    }
    void write(Writer &writer);

    byte m_signature[4] = { 'C', 'F', 'G', 0 };

    QString gameTitle            = "RSDKv5 Game";
    QString gameSubtitle         = "Powered By the Retro Engine!";
    QString version              = "1.06.0";
    byte startSceneCategoryIndex = 0;
    ushort startSceneIndex       = 0;

    QList<QString> objects;
    RSDKv5::Palette palettes[8];
    QList<WAVConfiguration> sfx;

    QList<Category> sceneCategories;
    QList<ConfigurableMemoryEntry> globalVariables;

    QString m_filename = "";
    bool readMode      = false;
};

} // namespace RSDKv5

#endif // GAMECONFIG_V5_H