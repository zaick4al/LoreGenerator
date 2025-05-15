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
    m_timer->start(1000);
}

void WriterWorker::writeData(const QString &p_data, const QString &p_fileName)
{
    if(!QDir("Generated").exists())
        QDir().mkdir("Generated");
    if(!QDir("Generated/Persons/").exists())
        QDir().mkdir("Generated/Persons/");
    m_status = Writing;
    QFile file(p_fileName + ".tex");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error: can't open file: " << p_fileName;
        m_status = Ready;
        return;
    }

    QTextStream out(&file);
    out << p_data;
    file.close();

    qDebug() << "File save success: " << p_fileName;
    m_status = Ready;
}

void WriterWorker::getStatus()
{
    emit currentStatus(m_status);
}

void WriterWorker::writeNext()
{
    if (m_dataQueue.isEmpty())
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
    QString fileName = "Generated/Persons/" + p_family.first()->surname();
    QString data;
    QTextStream dataStream(&data);
    QList<Person_ptr> roots;
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
    dataStream << "\\section*{Генеалогическое древо}\n"
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

void WriterWorker::printPerson(QTextStream &p_out, Objects::Person* p_person, int p_depth, bool p_lastChild)
{
    if(m_printedPersons.contains(p_person))
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
    if (p_person->spouse() && !p_person->spouse()->name().isEmpty()) {
        auto spouse = p_person->spouse();
        p_out << "\n" <<  indent << " <3 \n" << indent << nodeSymbol << " "
              << spouse->name() << " "
              << spouse->surname()
              << " (" << spouse->age() << " лет, "
              << spouse->lifeStageString() << ", " << spouse->sexString() << ")";
        m_printedPersons.append(spouse);
    }
    p_out << "\n";

    auto children = p_person->children();
    std::sort(children.begin(), children.end(), [](auto* a, auto* b) {
        return a->age() > b->age();
    });

    for (int i = 0; i < children.size(); ++i) {
        if(m_printedPersons.contains(children[i]))
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
        << "    \\begin{itemize}\n"
        << "      \\item Сила: " << *person->personStats().strength << "\n"
        << "      \\item Ловкость: " << *person->personStats().dexterity << "\n"
        << "      \\item Телосложение: " << *person->personStats().constitution << "\n"
        << "      \\item Интеллект: " << *person->personStats().intelligence << "\n"
        << "      \\item Мудрость: " << *person->personStats().wisdom << "\n"
        << "      \\item Харизма: " << *person->personStats().charisma << "\n"
        << "    \\end{itemize}\n"
        << "\\end{itemize}\n\n";
}
