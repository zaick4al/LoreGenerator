#include "utils.h"

Utils &Utils::instance()
{
    static Utils instance;
    return instance;
}

QString Utils::raceString(Objects::Person::Race p_race) const
{
    return m_raceString.value(p_race);
}

Utils::Utils(QObject *parent)
    : QObject{parent}
{
    for (int i = 0; i < 23; i++) {
        auto race = static_cast<Objects::Person::Race>(i);
        QString enumName = QMetaEnum::fromType<Objects::Person::Race>().enumName();
        m_raceString.insert(race, enumName);
    }
}
