#ifndef SPELLWORK_H
#define SPELLWORK_H

#include <QMetaEnum>
#include <QJSEngine>
#include <QJSValue>
#include <QJSValueList>
#include <QJsonObject>
#include <QPair>

#include "MainForm.h"
#include "qsw.h"
#include "events.h"
#include "blp/BLP.h"

#include "plugins/spellinfo/interface.h"

typedef QPair<QJsonObject, SpellInfoInterface*> SpellInfoPluginPair;
typedef QHash<QString, SpellInfoPluginPair> SpellInfoPlugins;

class MainForm;
class LoadingScreen;
class SpellWork : public QObject
{
    Q_OBJECT

    public:
        SpellWork(MainForm *form);
        ~SpellWork() {}

        void loadPlugins();
        bool setActivePlugin(QString name,LoadingScreen* ls=nullptr);
        void setActivePlugin2(QPair<QString, SpellInfoPluginPair> p);
        QPair<QString, SpellInfoPluginPair> GetActivePlugin();

        SpellInfoPlugins getPlugins() const { return m_spellInfoPlugins; }
        SpellInfoInterface* getActivePlugin() const { return m_activeSpellInfoPlugin; }
        QString getActivePluginName() const { return m_activeSpellInfoPluginName; }

        void showInfo(quint32 id, QSW::Pages pageId = QSW::PAGE_MAIN);
        void compare();
        EventList search(quint8 type);

        QMetaEnum getMetaEnum() { return m_metaEnum; }
        void setMetaEnum(const char* enumName);

        MainForm* getForm() { return m_form; }

    private:
        MainForm *m_form;

        QMetaEnum m_metaEnum;

        QByteArray m_templateHtml;
        QByteArray m_styleCss;

        SpellInfoPlugins m_spellInfoPlugins;
        SpellInfoInterface* m_activeSpellInfoPlugin;
        QString m_activeSpellInfoPluginName;
};

#endif // SPELLWORK_H
