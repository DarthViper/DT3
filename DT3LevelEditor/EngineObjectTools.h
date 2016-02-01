#pragma once
#include <QtCore/QVector>
#include <QtCore/QString>
#include <QtCore/QHash>
#include <QtCore/QMetaClassInfo>
#include "EdLevelTool.hpp"


class EngineObjectTools
{
public:
    static QVector<const QMetaObject *> &toolsForEngineClass(const char *classid) {
        static QVector<const QMetaObject *> no_tools;
        if(!mapping.contains(classid))
            return no_tools;
        return mapping[classid];
    }
    template<class T>
    static void registerToolFor(const char *classid) {
        Q_ASSERT(!mapping[classid].contains(&T::staticMetaObject));
        mapping[classid].push_back(&T::staticMetaObject);
    }
private:
    static QHash<QString,QVector<const QMetaObject *> > mapping;
};

inline QString toolNameFromMetaObject(const QMetaObject *ob) {
    Q_ASSERT(ob!=nullptr);
    if(0==ob->classInfoCount())
        return QString();
    for(int i=ob->classInfoOffset(); i<ob->classInfoCount();++i) {
        if(QString(ob->classInfo(i).name())=="tool_name")
            return ob->classInfo(i).value();
    }
    return QString();
}
