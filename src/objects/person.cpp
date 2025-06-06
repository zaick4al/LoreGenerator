#include "person.h"

namespace Objects {

Person::Person(QObject *parent)
    : QObject{parent},
      m_race(Enums::GoldenDwarf),
      m_lifeStage(Enums::Kid),
      m_age(0),
      m_spouse(nullptr)
{
    racesEnum = QMetaEnum::fromType<Enums::Race>();
    lifeStagesEnum = QMetaEnum::fromType<Enums::LifeStage>();
    ethnicsEnum = QMetaEnum::fromType<Enums::Ethnic>();
}

Person::~Person()
{
    // this->deleteLater();
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

Enums::Ethnic Person::ethnic() const
{
    return m_ethnic;
}

void Person::setEthnic(const Enums::Ethnic &p_ethnic)
{
    if (m_ethnic == p_ethnic)
        return;
    m_ethnic = p_ethnic;
    emit ethnicChanged();
}

Enums::Race Person::race() const
{
    return m_race;
}

void Person::setRace(Enums::Race p_race)
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

QString Person::raceRuString()
{
    switch (race()) {
    case Enums::GoldenDwarf:
        return "Золотой дварф";
    case Enums::GrayrockDwarf:
        return "Серокаменный дварф";
    case Enums::BlackoreDwarf:
        return "Чернорудный дварф";
    case Enums::WhitemountDwarf:
        return "Белогорый дварф";
    case Enums::StormveilDwarf:
        return "Дварф штормовой завесы";
    case Enums::QuariteHuman:
        return "Человек-кварит";
    case Enums::ViteanHuman:
        return "Человек-витеанец";
    case Enums::NortkinHuman:
        return "Человек-норткин";
    case Enums::IrvisianHuman:
        return "Человек-ирвисианец";
    case Enums::TaikonianHuman:
        return "Человек-тайконец";
    case Enums::BeinianHuman:
        return "Человек-бейнит";
    case Enums::QualtianHuman:
        return "Человек-квалтиец";
    case Enums::WoodElf:
        return "Древесный эльф";
    case Enums::JadeElf:
        return "Нефритовый эльф";
    case Enums::IceElf:
        return "Морозный эльф";
    case Enums::SandElf:
        return "Песчаный эльф";
    case Enums::Halfling:
        return "Полурослик";
    case Enums::Fishman:
        return "Рыболюд";
    case Enums::Tiefling:
        return "Тифлинг";
    case Enums::Demon:
        return "Демон";
    case Enums::Deuna:
        return "Деуна";
    case Enums::Vampire:
        return "Вампир";
    case Enums::Halforc:
        return "Полуорк";
    }
    return "Человек-витеанец";
}

Enums::LifeStage Person::lifeStage() const
{
    return m_lifeStage;
}

void Person::setLifeStage(const Enums::LifeStage &p_lifeStage)
{
    if (p_lifeStage == m_lifeStage)
        return;
    m_lifeStage = p_lifeStage;
    emit lifeStageChanged();
}

QString Person::lifeStageString() const
{
    switch (lifeStage()) {
    case Enums::Elder:
        return "Пожилой";
    case Enums::Adult:
        return "Взрослый";
    case Enums::Teen:
        return "Подросток";
    case Enums::Kid:
        return "Дитя";

    }
}

QString Person::ethnicString() const
{
    switch (ethnic()) {
    case Enums::Arabic:
        return "Арабская";
    case Enums::Breton:
        return "Бретонская";
    case Enums::Germanic:
        return "Германская";
    case Enums::Dwarven:
        return "Дварфская";
    case Enums::Elven:
        return "Эльфийская";
    case Enums::Infernal:
        return "Инфернальная";
    }
}

std::shared_ptr<Job> Person::job() const
{
    return m_job;
}

void Person::setJob(const std::shared_ptr<Job> &p_job)
{
    m_job = p_job;
    auto adjusts = m_job->statsAdjustments();
    *m_personStats.strength += adjusts.strength;
    *m_personStats.dexterity += adjusts.dexterity;
    *m_personStats.charisma += adjusts.charisma;
    *m_personStats.constitution += adjusts.constitution;
    *m_personStats.intelligence += adjusts.intelligence;
    *m_personStats.wisdom += adjusts.perception;
}

QMetaEnum Person::getRacesEnum()
{
    return QMetaEnum::fromType<Enums::Race>();
}

QMetaEnum Person::getLifeStagesEnum()
{
    return QMetaEnum::fromType<Enums::LifeStage>();
}

QMetaEnum Person::getEthnicsEnum()
{
    return QMetaEnum::fromType<Enums::Ethnic>();
}

QMetaEnum Person::getSexEnum()
{
    return QMetaEnum::fromType<Enums::Sex>();
}

Enums::Sex Person::sex() const
{
    return m_sex;
}

void Person::setSex(const Enums::Sex &newSex)
{
    m_sex = newSex;
}

QString Person::sexString() const
{
    switch (sex()) {
    case Enums::Male:
        return "Мужчина";
    case Enums::Female:
        return "Женщина";
    }
}

Person *Person::spouse() const
{
    return m_spouse;
}

void Person::setSpouse(Person *newSpouse)
{
    m_spouse = newSpouse;
}

QList<Person *> Person::parents() const
{
    return m_parents;
}

void Person::setParents(const QList<Person *> &newParents)
{
    m_parents = newParents;
}

void Person::addParent(Person *p_parent)
{
    if (m_parents.contains(p_parent))
        return;
    m_parents.append(p_parent);
}

QList<Person *> Person::children() const
{
    return m_children;
}

void Person::setChildren(const QList<Person *> &newChildren)
{
    m_children = newChildren;
}

void Person::addChild(Person *p_child)
{
    if (m_children.contains(p_child))
        return;
    m_children.append(p_child);
}

Person::Stats &Person::personStats()
{
    return m_personStats;
}

void Person::setPersonStats(const Stats &p_personStats)
{
    m_personStats = p_personStats;
}

} // namespace Objects
