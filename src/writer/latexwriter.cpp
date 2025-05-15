#include "latexwriter.h"

LatexWriter::LatexWriter(QObject *parent)
    : QObject{parent}
{
    m_worker = new WriterWorker;
    m_worker->moveToThread(&m_thread);
    connect(&m_thread, &QThread::finished, m_worker, &QObject::deleteLater);
    connect(this, &LatexWriter::startWorking, m_worker, &WriterWorker::startTimer);
    connect(this, &LatexWriter::writeSettlement, m_worker, &WriterWorker::writeSettlement);
    m_thread.start();
    emit startWorking();
}

LatexWriter::~LatexWriter()
{
    m_thread.quit();
    m_thread.wait();
}

LatexWriter &LatexWriter::instance()
{
    static LatexWriter ltxWriter;
    return ltxWriter;
}

