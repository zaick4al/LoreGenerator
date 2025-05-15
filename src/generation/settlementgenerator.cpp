#include "settlementgenerator.h"
#include <loregenerator.h>

SettlementGenerator::SettlementGenerator(QObject *parent)
    : QObject{parent}
{
    setupStarters();
}

void SettlementGenerator::setupStarters()
{
    auto metaEnum = QMetaEnum::fromType<Objects::Settlement::SettlementType>();
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        auto fileName = ":/resource/settlement/jobs/" + QString(metaEnum.key(i)).toLower() + ".txt";
        QStringList data = Generator::instance().getData(fileName);
        QList<Job_ptr> jobs;
        for (const QString &string : data) {
            auto job = Objects::Job::fromString(string);
            jobs << job;
        }
        m_jobs.insert(static_cast<Objects::Settlement::SettlementType>(i), jobs);
    }
}

Settlement_ptr SettlementGenerator::generateSettlement(Objects::Settlement::SettlementType p_type,
        Generator::Ethnic p_ethnic)
{
    Settlement_ptr settlement = std::make_shared<Objects::Settlement>();
    auto minMax = Objects::Settlement::housingMinMax(p_type);
    settlement->setHousingAmount(generateBounded(minMax.first, minMax.second));
    auto name = Generator::instance().generateSettlementName(p_ethnic);
    settlement->setSettlementName(name);
    QList<Family_ptr> families;
    auto jobs = m_jobs.value(p_type);
    for (int i = 0; i < settlement->housingAmount(); i++) {
        auto family = std::make_shared<Objects::Family>();
        auto randomFactor = generateBounded(1, 20);
        Person_ptr person;
        if (randomFactor > 12)
            person = LOREGEN.personGenerator()->generatePersons(1).first();
        else
            person = LOREGEN.personGenerator()->generatePersons(1,
                     Objects::Person::getEthnicsEnum().key(p_ethnic), "Elder").first();
        auto familyPersons = LOREGEN.personGenerator()->generateFamily(person);
        for (const auto familyMember : familyPersons) {
            if (familyMember->lifeStage() == Objects::Person::Kid
                    || familyMember->lifeStage() == Objects::Person::Teen)
                continue;
            auto job = jobs.value(generateBounded(jobs.length() - 1));
            familyMember->setJob(job);
        }
        if (familyPersons.length() > 15)
            settlement->setLargeHouses(settlement->largeHouses() + 1);
        else if (familyPersons.length() > 8)
            settlement->setMediumHouses(settlement->mediumHouses() + 1);
        else
            settlement->setSmallHouses(settlement->smallHouses() + 1);
        family->setPersons(familyPersons);
        families << family;
    }
    settlement->setCitizen(families);
    return settlement;
}
