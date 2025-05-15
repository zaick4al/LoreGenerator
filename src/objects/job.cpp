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
    int i = 0;
    for (int i = 0; i < descs.length(); i++) {
        QString value = descs.at(i).trimmed();
        auto valueToSet = value.contains("-") ? -value.replace("-", "").toInt() : value.replace("+", "").toInt();
        switch(i){
        case 0:
            adj.strength = valueToSet;
            break;
        case 1:
            adj.dexterity = valueToSet;
            break;
        case 2:
            adj.constitution = valueToSet;
            break;
        case 3:
            adj.intelligence = valueToSet;
            break;
        case 4:
            adj.perception = valueToSet;
            break;
        case 5:
            adj.charisma = valueToSet;
            break;
        default:
            break;
        }
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
