#ifndef STORAGESAVE_H
#define STORAGESAVE_H

#include <QObject>

#include <tinyxml2.h>

// TODO start doing the xx documentation



class StorageSave : public QObject
{
    Q_OBJECT
public:
    explicit StorageSave(QObject *parent = nullptr);

/*
public slots:
    void prologueUpdate(QString);
    void crawltextUpdate(QString);
*/
private:
    tinyxml2::XMLDocument *m_pXmlDoc;

};

#endif // STORAGESAVE_H
