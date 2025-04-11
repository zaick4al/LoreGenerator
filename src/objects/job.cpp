#include "job.h"

namespace Objects {


std::shared_ptr<Job> Job::fromString(const QString &p_data, QObject *p_parent)
{
    std::shared_ptr<Job> job = std::make_shared<Job>();
    QStringList dataSplit = p_data.trimmed().split(" : ");
    job->setName(dataSplit.at(0));
    job->setDescription(dataSplit.at(1));
    StatsAdjustment adj;
    QStringList descs = dataSplit.last().split(";");
    for(const auto &string : descs){
        QString trimmed = string.trimmed();
        QStringList stat = trimmed.split(" ");
        QString first = stat.first();
        QString last = stat.last();
        if(first == "Strength")
            adj.strength = last.contains("-") ? -last.replace("-","").toInt() : last.replace("+", "").toInt();
        else if(first == "Dexterity")
            adj.dexterity = last.contains("-") ? -last.replace("-","").toInt() : last.replace("+", "").toInt();
        else if(first == "Constitution")
            adj.constitution = last.contains("-") ? -last.replace("-","").toInt() : last.replace("+", "").toInt();
        else if(first == "Intelligence")
            adj.intelligence = last.contains("-") ? -last.replace("-","").toInt() : last.replace("+", "").toInt();
        else if(first == "Perception")
            adj.perception = last.contains("-") ? -last.replace("-","").toInt() : last.replace("+", "").toInt();
        else if(first == "Charisma")
            adj.charisma = last.contains("-") ? -last.replace("-","").toInt() : last.replace("+", "").toInt();
    }
    job->setStatsAdjustments(adj);
    return job;
}

QString Job::name() const
{
    return m_name;
}

void Job::setName(const QString &p_name)
{
    if (m_name == p_name)
        return;
    m_name = p_name;
    emit nameChanged();
}

QString Job::description() const
{
    return m_description;
}

void Job::setDescription(const QString &p_description)
{
    if (m_description == p_description)
        return;
    m_description = p_description;
    emit descriptionChanged();
}

Job::StatsAdjustment Job::statsAdjustments() const
{
    return m_statsAdjustments;
}

void Job::setStatsAdjustments(const StatsAdjustment &p_statsAdjustments)
{
    m_statsAdjustments = p_statsAdjustments;
    emit statsAdjustmentsChanged();
}
Job::Job(QObject *p_parent)
    : QObject{p_parent}
{}
} // namespace Objects
