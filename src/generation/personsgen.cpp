#include "personsgen.h"
#include <QElapsedTimer>
#include <generation/generator.h>

PersonsGen::PersonsGen(QObject *parent)
    : QObject{parent}
{
    QElapsedTimer timer;
    timer.start();
    setupStarters();
    generatePersons(1000);
    auto index = generateBounded(m_persons.count() - 1);
    auto person = m_persons.at(index);
}

void PersonsGen::generatePersons(int p_amount)
{
    for (int i = 0; i < p_amount; i++)
        generateNextPerson();
}

void PersonsGen::generateNextPerson()
{
    auto person = std::make_shared<Objects::Person>(this);
    auto ethnic = static_cast<Generator::Ethnic>(generateBounded(m_generator->ethnicAmount()));
    auto sex = static_cast<Generator::Sex>(generateBounded(m_generator->sexAmount()));
    auto job = m_jobs.value(generateBounded(m_jobs.count() - 1));
    person->setEthnic(ethnic);
    person->setName(m_generator->generateName(ethnic, sex));
    person->setSurname(m_generator->generateSurname(ethnic));
    person->setRace(generateRaceByEthnic(person));
    person->setAge(generateAgeByRace(person));
    auto age = person->age();
    auto lifeLength = m_raceLife.value(person->race());
    if (age <= int(lifeLength * 0.06))
        person->setLifeStage(Objects::Person::Kid);
    else if (age <= int(lifeLength * 0.2))
        person->setLifeStage(Objects::Person::Teen);
    else if (age <= int(lifeLength * 0.8))
        person->setLifeStage(Objects::Person::Adult);
    else
        person->setLifeStage(Objects::Person::Elder);
    person->setJob(job);
    m_persons << person;
}

Objects::Person::Race PersonsGen::generateRaceByEthnic(std::shared_ptr<Objects::Person> p_person)
{
    switch (p_person->ethnic()) {
    case Generator::Arabic: {
        auto gen = generateBounded(3);
        switch (gen) {
        case 0:
            return Objects::Person::QuariteHuman;
        case 1:
            return Objects::Person::SandElf;
        case 2:
            return Objects::Person::Deuna;
        case 3:
            return Objects::Person::Halfling;
        }
    }
    case Generator::Breton: {
        auto gen = generateBounded(7);
        switch (gen) {
        case 0:
            return Objects::Person::QualtianHuman;
        case 1:
            return Objects::Person::ViteanHuman;
        case 2:
            return Objects::Person::Halfling;
        case 3:
            return Objects::Person::Vampire;
        case 4:
            return Objects::Person::WoodElf;
        case 5:
            return Objects::Person::JadeElf;
        case 6:
            return Objects::Person::Halforc;
        case 7:
            return Objects::Person::Tiefling;
        }
    }
    case Generator::Germanic: {
        int gen = generateBounded(9);
        switch (gen) {
        case 0:
            return Objects::Person::GoldenDwarf;
        case 1:
            return Objects::Person::WhitemountDwarf;
        case 2:
            return Objects::Person::GrayrockDwarf;
        case 3:
            return Objects::Person::ViteanHuman;
        case 4:
            return Objects::Person::NortkinHuman;
        case 5:
            return Objects::Person::IceElf;
        case 6:
            return Objects::Person::WoodElf;
        case 7:
            return Objects::Person::JadeElf;
        case 8:
            return Objects::Person::Halforc;
        case 9:
            return Objects::Person::Tiefling;
        }
    }
    case Generator::Dwarven: {
        int gen = generateBounded(4);
        switch (gen) {
        case 0:
            return Objects::Person::GoldenDwarf;
        case 1:
            return Objects::Person::WhitemountDwarf;
        case 2:
            return Objects::Person::GrayrockDwarf;
        case 3:
            return Objects::Person::BlackoreDwarf;
        case 4:
            return Objects::Person::StormveilDwarf;
        }
    }
    case Generator::Elven: {
        int gen = generateBounded(4);
        switch (gen) {
        case 0:
            return Objects::Person::WoodElf;
        case 1:
            return Objects::Person::IceElf;
        case 2:
            return Objects::Person::SandElf;
        case 3:
            return Objects::Person::JadeElf;
        }
    }
    }
    return Objects::Person::ViteanHuman;
}

int PersonsGen::generateAgeByRace(std::shared_ptr<Objects::Person> p_person)
{
    QString race = p_person->raceString().toLower();
    return generateBounded(m_raceLife.value(p_person->race()));
}

void PersonsGen::setupStarters()
{
    auto racesEnum = QMetaEnum::fromType<Objects::Person::Race>();
    for (int i = 0; i < racesEnum.keyCount(); i++) {
        QString race = QString(racesEnum.key(i)).trimmed().toLower();
        auto enumValue = static_cast<Objects::Person::Race>(racesEnum.value(i));
        if (race.contains("human")) {
            m_raceLife.insert(enumValue, 110);
        } else if (race.contains("dwarf")) {
            m_raceLife.insert(enumValue, 450);
        } else if (race.contains("elf")) {
            m_raceLife.insert(enumValue, 3000);
        } else {
            if (race == "halfling") {
                m_raceLife.insert(enumValue, 60);
            } else if (race == "fishman") {
                m_raceLife.insert(enumValue, 180);
            } else if (race == "tiefling") {
                m_raceLife.insert(enumValue, 600);
            } else if (race == "demon") {
                m_raceLife.insert(enumValue, 320);
            } else if (race == "deuna") {
                m_raceLife.insert(enumValue, 9000);
            } else if (race == "vampire") {
                m_raceLife.insert(enumValue, 9000);
            } else if(race == "halforc") {
                m_raceLife.insert(enumValue, 110);
            }
        }
    }
    QString fileName = ":/resource/npc/jobs.txt";
    QStringList data = Generator::instance().getData(fileName);
    for (const QString &string : data) {
        m_jobs << Objects::Job::fromString(string);
    }
}
