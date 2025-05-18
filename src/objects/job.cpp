#include "job.h"
#include <QMetaEnum>

namespace Objects {


std::shared_ptr<Job> Job::fromString(const QString &p_data, QObject *p_parent)
{
    std::shared_ptr<Job> job = std::make_shared<Job>();
    QStringList dataSplit = p_data.trimmed().split(" : ");
    job->setName(dataSplit.at(0));
    job->setDescription(dataSplit.at(1));
    StatsAdjustment adj;
    QStringList descs = dataSplit.at(2).split(";");
    int i = 0;
    for (int i = 0; i < descs.length(); i++) {
        QString value = descs.at(i).trimmed();
        auto valueToSet = value.contains("-") ? -value.replace("-", "").toInt() : value.replace("+",
                          "").toInt();
        switch (i) {
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
    QString availableIns = dataSplit.at(4);
    if (availableIns.contains("'")) {
        QStringList totalAvailables = availableIns.split("'");
        for (const QString &string : totalAvailables) {
            job->addAvailableIn(string);
        }
    } else {
        job->addAvailableIn(availableIns);
    }
    QString specializations = dataSplit.at(3);
    if (specializations.contains("'")) {
        QStringList totalSpecs = specializations.split("'");
        for (const QString &string : totalSpecs) {
            job->addSpecializations(string);
        }
    } else {
        job->addSpecializations(specializations);
    }
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

QList<Enums::SettlementType> Job::availableIn() const
{
    return m_availableIn;
}

void Job::setAvailableIn(const QList<Enums::SettlementType> p_availableIn)
{
    m_availableIn = p_availableIn;
}

void Job::addAvailableIn(const Enums::SettlementType p_availableIn)
{
    m_availableIn << p_availableIn;
}

void Job::addAvailableIn(const QString &p_avIn)
{
    auto setTypeEnum = QMetaEnum::fromType<Enums::SettlementType>();
    bool *ok = new bool;
    *ok = false;
    int enumVal = setTypeEnum.keyToValue(p_avIn.toStdString().c_str(), ok);
    if (!ok) {
        qDebug() << "setType " << p_avIn << " !ok";
        return;
    }
    auto setType = static_cast<Enums::SettlementType>(enumVal);
    addAvailableIn(setType);
}

QList<Enums::JobSpecialization> Job::specializations() const
{
    return m_specializations;
}

void Job::setSpecializations(const QList<Enums::JobSpecialization> p_specializations)
{
    m_specializations = p_specializations;
}

void Job::addSpecializations(const Enums::JobSpecialization p_specialization)
{
    m_specializations << p_specialization;
}

void Job::addSpecializations(const QString &p_spec)
{
    QMetaEnum specEnum = QMetaEnum::fromType<Enums::JobSpecialization>();
    bool *ok = new bool;
    *ok = false;
    int enumVal = specEnum.keyToValue(p_spec.toStdString().c_str(), ok);
    if (!ok) {
        qDebug() << "spec " << p_spec << " !ok";
        return;
    }
    auto specSet = static_cast<Enums::JobSpecialization>(enumVal);
    addSpecializations(specSet);
}
} // namespace Objects
