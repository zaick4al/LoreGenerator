#include "person.h"

namespace Objects {

Person::Person(QObject *parent)
    : QObject{parent},
      m_race(Generator::GoldenDwarf),
      m_lifeStage(Kid),
      m_age(0),
      m_spouse(nullptr)
{
    racesEnum = QMetaEnum::fromType<Generator::Race>();
    lifeStagesEnum = QMetaEnum::fromType<LifeStage>();
    ethnicsEnum = QMetaEnum::fromType<Generator::Ethnic>();
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

Generator::Race Person::race() const
{
    return m_race;
}

void Person::setRace(Generator::Race p_race)
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
    case Generator::GoldenDwarf:
        return "Золотой дварф";
    case Generator::GrayrockDwarf:
        return "Серокаменный дварф";
    case Generator::BlackoreDwarf:
        return "Чернорудный дварф";
    case Generator::WhitemountDwarf:
        return "Белогорый дварф";
    case Generator::StormveilDwarf:
        return "Дварф штормовой завесы";
    case Generator::QuariteHuman:
        return "Человек-кварит";
    case Generator::ViteanHuman:
        return "Человек-витеанец";
    case Generator::NortkinHuman:
        return "Человек-норткин";
    case Generator::IrvisianHuman:
        return "Человек-ирвисианец";
    case Generator::TaikonianHuman:
        return "Человек-тайконец";
    case Generator::BeinianHuman:
        return "Человек-бейнит";
    case Generator::QualtianHuman:
        return "Человек-квалтиец";
    case Generator::WoodElf:
        return "Древесный эльф";
    case Generator::JadeElf:
        return "Нефритовый эльф";
    case Generator::IceElf:
        return "Морозный эльф";
    case Generator::SandElf:
        return "Песчаный эльф";
    case Generator::Halfling:
        return "Полурослик";
    case Generator::Fishman:
        return "Рыболюд";
    case Generator::Tiefling:
        return "Тифлинг";
    case Generator::Demon:
        return "Демон";
    case Generator::Deuna:
        return "Деуна";
    case Generator::Vampire:
        return "Вампир";
    case Generator::Halforc:
        return "Полуорк";
    }
    return "Человек-витеанец";
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
    switch (lifeStage()) {
    case Elder:
        return "Пожилой";
    case Adult:
        return "Взрослый";
    case Teen:
        return "Подросток";
    case Kid:
        return "Дитя";

    }
}

QString Person::ethnicString() const
{
    switch (ethnic()) {
    case Generator::Arabic:
        return "Арабская";
    case Generator::Breton:
        return "Бретонская";
    case Generator::Germanic:
        return "Германская";
    case Generator::Dwarven:
        return "Дварфская";
    case Generator::Elven:
        return "Эльфийская";
    case Generator::Infernal:
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
    return QMetaEnum::fromType<Generator::Race>();
}

QMetaEnum Person::getLifeStagesEnum()
{
    return QMetaEnum::fromType<LifeStage>();
}

QMetaEnum Person::getEthnicsEnum()
{
    return QMetaEnum::fromType<Generator::Ethnic>();
}

QMetaEnum Person::getSexEnum()
{
    return QMetaEnum::fromType<Generator::Sex>();
}

Generator::Sex Person::sex() const
{
    return m_sex;
}

void Person::setSex(const Generator::Sex &newSex)
{
    m_sex = newSex;
}

QString Person::sexString() const
{
    switch (sex()) {
    case Generator::Male:
        return "Мужчина";
    case Generator::Female:
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
