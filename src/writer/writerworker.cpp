#include "writerworker.h"
#include <QFile>
#include <QDir>

WriterWorker::WriterWorker(QObject *parent)
    : QObject{parent}, m_status(Ready)
{
}

void WriterWorker::startTimer()
{
    m_timer = new QTimer();
    m_timer->moveToThread(this->thread());
    connect(m_timer, &QTimer::timeout, this, &WriterWorker::writeNext);
    connect(this, &WriterWorker::statusChanged, this, &WriterWorker::writeNext);
    m_timer->start(1000);
}

void WriterWorker::writeData(const QString &p_data, const QString &p_fileName)
{
    if (!QDir("Generated").exists())
        QDir().mkdir("Generated");
    m_status = Writing;
    emit statusChanged();
    QFile file(p_fileName);
    QString starterData;
    bool existedData = false;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream dataStream(&starterData);
        dataStream << "\\documentclass{article}\n"
                   << "\\usepackage[utf8]{inputenc}\n"
                   << "\\usepackage[T1]{fontenc}\n"
                   << "\\usepackage[russian]{babel}\n"
                   << "\\usepackage{pmboxdraw}\n"
                   << "\\usepackage{textcomp}\n"
                   << "\\usepackage{enumitem}\n"
                   << "\\usepackage{listings}\n"
                   << "\\usepackage{graphicx}\n\n"
                   << "\\begin{document}\n\n";
    } else {
        starterData = file.readAll();
        starterData.replace("\\end{document}", "");
        existedData = true;
    }
    file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error: can't open file: " << p_fileName;
        m_status = Ready;
        emit statusChanged();
        return;
    }
    QTextStream out(&file);
    out << starterData;
    if(existedData)
        out << "\\newpage";
    out << p_data;
    file.close();

    qDebug() << "File save success: " << p_fileName;
    m_status = Ready;
    emit statusChanged();
}

void WriterWorker::getStatus()
{
    emit currentStatus(m_status);
}

void WriterWorker::writeNext()
{
    if (m_dataQueue.isEmpty() || m_status != Ready)
        return m_timer->start(1000);
    if (m_timer->isActive())
        m_timer->stop();
    auto data = m_dataQueue.first();
    m_dataQueue.removeFirst();
    writeData(data.first, data.second);
    writeNext();
}

void WriterWorker::writeFamily(QList<std::shared_ptr<Objects::Person> > p_family)
{
    QString fileName = "Generated/persons.tex";
    QString data;
    QTextStream dataStream(&data);
    QList<Person_ptr> roots;
    dataStream << "\\section*{Генеалогическое древо семьи " <<
               p_family.first()->surname() << "}\n"
               << "\\begin{verbatim}\n";

    for (Person_ptr &person : p_family) {
        if (person->parents().isEmpty()) {
            roots.append(person);
        }
    }

    for (Person_ptr &root : roots) {
        printPerson(dataStream, root.get(), 0);
    }
    dataStream << "\\end{verbatim}\n\n" << "\\newpage";
    m_printedPersons.clear();
    dataStream << "\\section*{Характеристики персонажей}\n";
    for (Person_ptr &person : p_family) {
        printPersonDetails(dataStream, person.get());
    }
    dataStream << "\\end{document}";
    m_dataQueue << QPair(data, fileName);
}

void WriterWorker::printPerson(QTextStream &p_out, Objects::Person* p_person, int p_depth,
                               bool p_lastChild)
{
    if (m_printedPersons.contains(p_person))
        return;
    QString indent;
    for (int i = 0; i < p_depth; ++i) {
        indent += (i == p_depth - 1) ? "    " : "    │";
    }

    QString nodeSymbol;
    if (p_depth == 0) {
        nodeSymbol = "-";
    } else {
        nodeSymbol = p_lastChild ? "└──" : "├──";
    }

    p_out << indent << nodeSymbol << " "
          << p_person->name() << " "
          << p_person->surname()
          << " (" << p_person->age() << " лет, "
          << p_person->lifeStageString() << ", " << p_person->sexString() << ")";
    m_printedPersons.append(p_person);
    if (auto spouse = p_person->spouse(); spouse && !m_printedPersons.contains(spouse)) {
        p_out << "\n" <<  indent << " <3 \n" << indent << nodeSymbol << " "
              << spouse->name() << " "
              << spouse->surname()
              << " (" << spouse->age() << " лет, "
              << spouse->lifeStageString() << ", " << spouse->sexString() << ")";
        m_printedPersons.append(spouse);
    }
    p_out << "\n";

    auto children = p_person->children();
    std::sort(children.begin(), children.end(), [](auto * a, auto * b) {
        return a->age() > b->age();
    });

    for (int i = 0; i < children.size(); ++i) {
        if (m_printedPersons.contains(children[i]))
            continue;
        printPerson(p_out, children[i], p_depth + 1, i == children.size() - 1);
    }
}

void WriterWorker::printPersonDetails(QTextStream &out, Objects::Person *person)
{
    out << "\\subsection*{" << person->name () << " " << person->surname() << "}\n" <<
           "\\begin{itemize}[leftmargin=*]\n"
        << "  \\item \\textbf{Возраст}: " << person->age() << " лет\n"
        << "  \\item \\textbf{Стадия жизни}: " << person->lifeStageString() << "\n"
        << "  \\item \\textbf{Раса}: " << person->raceString() << "\n"
        // << "  \\item \\textbf{Работа}: " << person->getJobInfo() << "\n"
        << "  \\item \\textbf{Характеристики}:\n"
        << "\\end{itemize}\n\n";
    out << "\\begin{center}\n"
        << "\\begin{tabular}{|l|c|}\n"
        << "\\hline\n"
        << "\\textbf{Характеристика} & \\textbf{Значение} \\\\\n"
        << "\\hline\n"
        << "Сила & " << *person->personStats().strength << " \\\\\n"
        << "\\hline\n"
        << "Ловкость & " << *person->personStats().dexterity << " \\\\\n"
        << "\\hline\n"
        << "Телосложение & " << *person->personStats().constitution << " \\\\\n"
        << "\\hline\n"
        << "Интеллект & " << *person->personStats().intelligence << " \\\\\n"
        << "\\hline\n"
        << "Мудрость & " << *person->personStats().wisdom << " \\\\\n"
        << "\\hline\n"
        << "Харизма & " << *person->personStats().charisma << " \\\\\n"
        << "\\hline\n"
        << "\\end{tabular}\n"
        << "\\end{center}\n\n";
}
