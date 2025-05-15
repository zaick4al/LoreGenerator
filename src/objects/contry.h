#ifndef CONTRY_H
#define CONTRY_H

#include <QObject>
#include <settlement.h>

class Contry : public QObject
{
    Q_OBJECT
public:
    explicit Contry(QObject *parent = nullptr);

signals:

protected:
    QList<Settlement_ptr> m_settlements;
    Person_ptr m_governor;
};

#endif // CONTRY_H
