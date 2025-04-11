#include "person.h"

namespace Objects {

Person::Person(QObject *parent)
    : QObject{parent},
    m_race(GoldenDwarf),
    m_lifeStage(Kid),
    m_age(0)
{
    racesEnum = QMetaEnum::fromType<Race>();
    lifeStagesEnum = QMetaEnum::fromType<LifeStage>();
    ethnicsEnum = QMetaEnum::fromType<Generator::Ethnic>();
}

Person::~Person()
{
    this->deleteLater();
}

QString Person::name() const
{
    return m_name;
}

void Person::setName(const QString &p_name)
{
    if (p_name == m_name)
        return;
    m_name = p_name;
    emit nameChanged();
}

QString Person::surname() const
{
    return m_surname;
}

void Person::setSurname(const QString &p_surname)
{
    if (p_surname == m_surname)
        return;
    m_surname = p_surname;
    emit surnameChanged();
}

Generator::Ethnic Person::ethnic() const
{
    return m_ethnic;
}

void Person::setEthnic(const Generator::Ethnic &p_ethnic)
{
    if (m_ethnic == p_ethnic)
        return;
    m_ethnic = p_ethnic;
    emit ethnicChanged();
}

Person::Race Person::race() const
{
    return m_race;
}

void Person::setRace(Race p_race)
{
    if (p_race == m_race)
        return;
    m_race = p_race;
    emit raceChanged();
}

quint16 Person::age() const
{
    return m_age;
}

void Person::setAge(quint16 p_age)
{
    if (p_age == m_age)
        return;
    m_age = p_age;
    emit ageChanged();
}

QString Person::raceString()
{
    return racesEnum.key(race());
}

Person::LifeStage Person::lifeStage() const
{
    return m_lifeStage;
}

void Person::setLifeStage(const LifeStage &p_lifeStage)
{
    if (p_lifeStage == m_lifeStage)
        return;
    m_lifeStage = p_lifeStage;
    emit lifeStageChanged();
}

QString Person::lifeStageString() const
{
    return lifeStagesEnum.key(lifeStage());
}

QString Person::ethnicString() const
{
    return ethnicsEnum.key(ethnic());
}

std::shared_ptr<Job> Person::job() const
{
    return m_job;
}

void Person::setJob(const std::shared_ptr<Job> &p_job)
{
    m_job = p_job;
}

QMetaEnum Person::getRacesEnum() const
{
    return racesEnum;
}

QMetaEnum Person::getLifeStagesEnum() const
{
    return lifeStagesEnum;
}

} // namespace Objects
