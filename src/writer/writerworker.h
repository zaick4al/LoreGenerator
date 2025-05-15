#ifndef WRITERWORKER_H
#define WRITERWORKER_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QTextStream>
#include <objects/person.h>

class WriterWorker : public QObject
{
    Q_OBJECT
public:
    enum Status{
        Ready,
        Writing
    };
    Q_ENUM(Status);
    explicit WriterWorker(QObject *parent = nullptr);
public slots:
    void startTimer();
    void writeData(const QString &p_data, const QString &p_fileName);
    void getStatus();
    void writeFamily(QList<Person_ptr> p_family);
signals:
    void written();
    void currentStatus(Status status);
    void statusChanged();
protected slots:
    void writeNext();
protected:
    void printPerson(QTextStream& p_out, Objects::Person *p_person, int p_depth, bool p_lastChild = false);
    void printPersonDetails(QTextStream& out, Objects::Person* person);
    Status m_status;
    QList<QPair<QString, QString>> m_dataQueue;
    QTimer *m_timer;
    QList<Objects::Person*> m_printedPersons;
};

#endif // WRITERWORKER_H
