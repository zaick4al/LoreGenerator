#include "settlement.h"

namespace Objects {

QPair<int, int> Settlement::housingMinMax(SettlementType p_type)
{
    switch (p_type) {
    case HugeCity:
        return QPair<int, int>(90, 150);
    case LargeCity:
        return QPair<int, int>(50, 70);
    case MediumCity:
        return QPair<int, int>(30, 50);
    case SmallTown:
        return QPair<int, int>(20, 30);
    case Castle:
        return QPair<int, int>(10, 30);
    case Village:
        return QPair<int, int>(10, 20);
    case Outpost:
        return QPair<int, int>(3, 9);
    }
}

QPair<int, int> Settlement::guardsMinMax(SettlementType p_type)
{
    switch (p_type) {
    case HugeCity:
        return QPair<int, int>(100, 170);
    case LargeCity:
        return QPair<int, int>(60, 80);
    case MediumCity:
        return QPair<int, int>(40, 60);
    case SmallTown:
        return QPair<int, int>(10, 20);
    case Castle:
        return QPair<int, int>(40, 60);
    case Village:
        return QPair<int, int>(1, 10);
    case Outpost:
        return QPair<int, int>(3, 9);
    }
}

Settlement::Settlement(QObject *parent)
    : QObject{parent},
      m_smallHouses(0),
      m_mediumHouses(0),
      m_largeHouses(0)
{}

int Settlement::housingAmount() const
{
    return m_housingAmount;
}

void Settlement::setHousingAmount(int p_housingAmount)
{
    m_housingAmount = p_housingAmount;
}

QList<std::shared_ptr<Family> > Settlement::citizen() const
{
    return m_citizen;
}

void Settlement::setCitizen(const QList<std::shared_ptr<Objects::Family> > &p_citizen)
{
    m_citizen = p_citizen;
}

void Settlement::addFamily(const std::shared_ptr<Family> &p_family)
{
    m_citizen << p_family;
}

void Settlement::addCitizen(const std::shared_ptr<Person> &p_citizen)
{
    auto family = std::make_shared<Family>();
    family->addPerson(p_citizen);
    m_citizen << family;
}

int Settlement::smallHouses() const
{
    return m_smallHouses;
}

void Settlement::setSmallHouses(int p_smallHouses)
{
    m_smallHouses = p_smallHouses;
}

int Settlement::mediumHouses() const
{
    return m_mediumHouses;
}

void Settlement::setMediumHouses(int p_mediumHouses)
{
    m_mediumHouses = p_mediumHouses;
}

int Settlement::largeHouses() const
{
    return m_largeHouses;
}

void Settlement::setLargeHouses(int p_largeHouses)
{
    m_largeHouses = p_largeHouses;
}

Generator::Ethnic Settlement::mainEthnic() const
{
    return m_mainEthnic;
}

void Settlement::setMainEthnic(const Generator::Ethnic &p_mainEthnic)
{
    m_mainEthnic = p_mainEthnic;
}

QString Settlement::settlementName() const
{
    return m_settlementName;
}

void Settlement::setSettlementName(const QString &p_settlementName)
{
    m_settlementName = p_settlementName;
}

int Settlement::population() const
{
    int pop;
    for (const auto &family : m_citizen)
        pop += family->familyCount();
    return pop;
}

int Settlement::area() const
{
    return m_largeHouses * 100 + m_mediumHouses * 50 + m_smallHouses * 20;
}

QHash<QString, int> Settlement::culturePercentages()
{
    QHash<QString, int> cultures;
    cultures.insert("Дварфская", 0);
    cultures.insert("Германская", 0);
    cultures.insert("Бретонская", 0);
    cultures.insert("Арабская", 0);
    cultures.insert("Эльфийская", 0);
    cultures.insert("Инфернальная", 0);
    for (const auto &family : citizen()) {
        auto ethnic = family->persons().first()->ethnic();
        QString key;
        if (ethnic == Generator::Dwarven)
            key = "Дварфская";
        if (ethnic == Generator::Germanic)
            key = "Германская";
        if (ethnic == Generator::Breton)
            key = "Бретонская";
        if (ethnic == Generator::Arabic)
            key = "Арабская";
        if (ethnic == Generator::Elven)
            key = "Эльфийская";
        if (ethnic == Generator::Infernal)
            key = "Инфернальная";
        cultures[key] = cultures.value(key) + 1;
    }
    int familyAmount = citizen().count();
    for (const auto &[key, value] : cultures.asKeyValueRange()) {
        cultures[key] = value * 100 / familyAmount;
    }
    return cultures;
}

} // namespace Objects
