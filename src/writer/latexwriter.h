#ifndef LATEXWRITER_H
#define LATEXWRITER_H

#include <QObject>
#include <writer/writerworker.h>
#include <person.h>
#include <QThread>
#include <QTimer>

#ifndef WRITER
#define WRITER LatexWriter::instance()
#endif

class LatexWriter : public QObject
{
    Q_OBJECT
protected:
    explicit LatexWriter(QObject *parent = nullptr);
    ~LatexWriter();
public:
    static LatexWriter &instance();
signals:
    void writeFamily(QList<Person_ptr> p_family);
    void getStatus();
    void startWorking();

protected:
    QThread m_thread;
    WriterWorker *m_worker;
};

#endif // LATEXWRITER_H
