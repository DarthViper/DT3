#pragma once

#include <QObject>
#include <QHash>

// source : http://www.mimec.org/node/350
class EditorObjectFactory
{
public:
    template<typename T>
    static void registerClass()
    {
        constructors().insert( T::staticMetaObject.className(), &constructorHelper<T> );
    }
    template<typename T>
    static T* createObjectT( const QString& className, QObject* parent = NULL )
    {
        QObject *res = createObject(className,parent);
        return qobject_cast<T *>(res);
    }
    static QObject* createObject( const QString& className, QObject* parent = NULL )
    {
        Constructor constructor = constructors().value( className );
        Q_ASSERT(constructor != NULL);
        return (*constructor)( parent );
    }

private:
    typedef QObject* (*Constructor)( QObject* parent );

    template<typename T>
    static QObject* constructorHelper( QObject* parent )
    {
        return new T( parent );
    }

    static QHash<QString, Constructor>& constructors()
    {
        static QHash<QString, Constructor> instance;
        return instance;
    }
};
