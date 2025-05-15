#include "personsgenerator.h"
#include <QElapsedTimer>
#include <generation/generator.h>
#include <writer/latexwriter.h>

PersonsGenerator &PersonsGenerator::instance()
{
    static PersonsGenerator personsGen;
    return personsGen;
}

QList<Person_ptr> PersonsGenerator::generatePersons(int p_amount, const QString &p_ethnic, const QString &p_lifeStage, const QString p_sex)
{
    QList<Person_ptr> persons;
    for (int i = 0; i < p_amount; i++)
        persons << generateNextPerson(p_ethnic, p_lifeStage, p_sex);
    return persons;
}

QList<Person_ptr> PersonsGenerator::generateFamily(Person_ptr p_person){
    QList<Person_ptr> family;
    auto firstPerson = p_person ? p_person : generateNextPerson();
    family << firstPerson;
    QMetaEnum lifeStages = Objects::Person::getLifeStagesEnum();
    auto generateChildren = [=, this](Objects::Person *parent = nullptr, Objects::Person *secondParent = nullptr){
        QList<Person_ptr> retFamily;
        int amount = generateBounded(1, 10);
        for(int i = 0; i < amount; i++)
        {
            int lstg = generateBounded(20) > 14 ? 1 : 0;
            auto person = generateNextPerson(firstPerson->ethnicString(), lifeStages.key(lstg));
            person->setSurname(firstPerson->surname());
            if(parent){
                person->addParent(parent);
                parent->addChild(person.get());
                if(parent->age() < person->age())
                    person->setAge(parent->age() * generateBounded(2, 6) / 10);
            }
            if(secondParent){
                person->addParent(secondParent);
                secondParent->addChild(person.get());
                if(secondParent->age() < person->age())
                    person->setAge(parent->age() * generateBounded(2, 6) / 10);
            }
            retFamily << person;
        }
        return retFamily;
    };
    auto generateSpouse = [&, this](Person_ptr p_spouseTo){
        int gen = generateBounded(0, 20);
        if (gen < 8)
            return;
        auto spouse = generateNextPerson(p_spouseTo->ethnicString(), p_spouseTo->lifeStageString(),
                           p_spouseTo->sex() == Generator::Male ? "Female" : "Male");

        spouse->setSurname(p_spouseTo->surname());
        auto stage = p_spouseTo->lifeStage();
        spouse->setLifeStage(stage);
        int age;
        auto lifeLength = m_raceLife.value(spouse->race());
        switch(stage){
        case Objects::Person::Kid:
            age = generateBounded(int(lifeLength*0.06));
        case Objects::Person::Teen:
            age = generateBounded(int(lifeLength*0.07), int(lifeLength*0.2));
        case Objects::Person::Adult:
            age = generateBounded(int(lifeLength*0.21), int(lifeLength*0.8));
        case Objects::Person::Elder:
            age = generateBounded(int(lifeLength*0.81), lifeLength);
        }
        p_spouseTo->setSpouse(spouse.get());
        spouse->setSpouse(p_spouseTo.get());
        family.append(spouse);
    };
    if(firstPerson->lifeStage() == Objects::Person::Kid || firstPerson->lifeStage() == Objects::Person::Teen){
        family.append(generateChildren());
        return family;
    }
    generateSpouse(firstPerson);
    if(firstPerson->lifeStage() == Objects::Person::Adult){
        int gen = generateBounded(0, 20);
        generateSpouse(firstPerson);
        if(gen > 7 || firstPerson->spouse() && gen > 4){
            family.append(generateChildren(firstPerson.get()));
            if(firstPerson->spouse())
                firstPerson->spouse()->setChildren(firstPerson->children());
        }
        return family;
    }
    auto adults = generateChildren();
    for(auto adult : adults){
        auto lifeLength = m_raceLife.value(adult->race());
        adult->setAge(generateBounded(int(lifeLength*0.21), int(lifeLength*0.8)));
        adult->setLifeStage(Objects::Person::Adult);
        generateSpouse(adult);
        int gen = generateBounded(20);
        family.append(adult);
        if(gen > 7 || adult->spouse() &&  gen > 3){
            if(adult->spouse()){
                family.append(generateChildren(adult.get(), adult->spouse()));
                adult->spouse()->setChildren(adult->children());
            }
            else
                family.append(generateChildren(adult.get()));
        }
        firstPerson->addChild(adult.get());
        adult->addParent(firstPerson.get());
        if(firstPerson->spouse())
            adult->addParent(firstPerson->spouse());
    }
    if(firstPerson->spouse())
        firstPerson->spouse()->setChildren(firstPerson->children());
    return family;
}

Person_ptr PersonsGenerator::generateNextPerson(const QString &p_ethnic, const QString &p_lifeStage, const QString p_sex)
{
    auto person = std::make_shared<Objects::Person>(this);
    Generator::Ethnic ethnic;
    if(p_ethnic.isEmpty())
        ethnic = static_cast<Generator::Ethnic>(generateBounded(m_generator->ethnicAmount()));
    else {
        auto ethnicsEnum = Objects::Person::getEthnicsEnum();
        int value = getEnumByString(ethnicsEnum, p_ethnic);
        Q_ASSERT(value >= 0);
        ethnic = static_cast<Generator::Ethnic>(value);
    }
    Generator::Sex sex;
    if(p_sex.isEmpty())
        sex = generateBounded(0, 20) > 10 ? Generator::Sex::Female : Generator::Sex::Male;
    else {
        auto sexEnum = Objects::Person::getSexEnum();
        int value = getEnumByString(sexEnum, p_sex);
        Q_ASSERT(value >= 0);
        sex = (Generator::Sex)value;
    }
    person->setSex(sex);
    person->setEthnic(ethnic);
    person->setName(m_generator->generateName(ethnic, sex));
    person->setSurname(m_generator->generateSurname(ethnic));
    person->setRace(generateRaceByEthnic(person));
    int age;
    *person->personStats().strength = generateBounded(8, 22);
    *person->personStats().dexterity = generateBounded(8, 22);
    *person->personStats().intelligence = generateBounded(8, 22);
    *person->personStats().constitution = generateBounded(8, 22);
    *person->personStats().wisdom = generateBounded(8, 22);
    *person->personStats().charisma = generateBounded(8, 22);
    if(p_lifeStage.isEmpty())
        age = generateAgeByRace(person);
    else{
        auto lifeStagesEnum = Objects::Person::getLifeStagesEnum();
        int value = getEnumByString(lifeStagesEnum, p_lifeStage);
        Q_ASSERT(value >= 0);
        Objects::Person::LifeStage stage = static_cast<Objects::Person::LifeStage>(value);
        auto lifeLength = m_raceLife.value(person->race());
        switch(stage){
        case Objects::Person::Kid:
            age = generateBounded(int(lifeLength*0.06));
        case Objects::Person::Teen:
            age = generateBounded(int(lifeLength*0.07), int(lifeLength*0.2));
        case Objects::Person::Adult:
            age = generateBounded(int(lifeLength*0.21), int(lifeLength*0.8));
        case Objects::Person::Elder:
            age = generateBounded(int(lifeLength*0.81), lifeLength);
        }
        person->setAge(age);
        person->setLifeStage(stage);
        return person;
    }
    person->setAge(age);
    auto lifeLength = m_raceLife.value(person->race());
    if (age <= int(lifeLength * 0.06))
        person->setLifeStage(Objects::Person::Kid);
    else if (age <= int(lifeLength * 0.2))
        person->setLifeStage(Objects::Person::Teen);
    else if (age <= int(lifeLength * 0.8))
        person->setLifeStage(Objects::Person::Adult);
    else
        person->setLifeStage(Objects::Person::Elder);
    return person;
}

Objects::Person::Race PersonsGenerator::generateRaceByEthnic(std::shared_ptr<Objects::Person> p_person)
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
        bool isHuman = generateBounded(20) > 7;
        if(isHuman)
            return generateBounded(20) > 10 ? Objects::Person::QualtianHuman : Objects::Person::ViteanHuman;
        bool isElf = generateBounded(20) > 15;
        if(isElf)
            return static_cast<Objects::Person::Race>(generateBounded(12, 13));
        int gen = generateBounded(20);
        if(gen > 15)
            return Objects::Person::Vampire;
        else if(gen > 10)
            return Objects::Person::Tiefling;
        else if(gen > 5)
            return Objects::Person::Halfling;
        else
            return Objects::Person::Halforc;
    }
    case Generator::Germanic: {
        bool isHuman = generateBounded(20) > 7;
        if(isHuman)
            return generateBounded(20) > 10 ? Objects::Person::NortkinHuman : Objects::Person::ViteanHuman;
        bool isDwarf = generateBounded(20) > 9;
        if(isDwarf){
            int generation = generateBounded(3);
            return generation > 2 ? Objects::Person::WhitemountDwarf : static_cast<Objects::Person::Race>(generation);
        }
        bool isElf = generateBounded(20) > 15;
        if(isElf)
            return static_cast<Objects::Person::Race>(generateBounded(12, 14));
        return generateBounded(20) > 10 ? Objects::Person::Tiefling : Objects::Person::Halforc;
    }
    case Generator::Dwarven: {
        int gen = generateBounded(4);
        return static_cast<Objects::Person::Race>(gen);
    }
    case Generator::Elven: {
        int gen = generateBounded(12, 15);
        return static_cast<Objects::Person::Race>(gen);
    }
    }
    return Objects::Person::ViteanHuman;
}

int PersonsGenerator::generateAgeByRace(std::shared_ptr<Objects::Person> p_person)
{
    return generateBounded(m_raceLife.value(p_person->race()));
}

void PersonsGenerator::setupStarters()
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
    // QString fileName = ":/resource/npc/jobs.txt";
    // QStringList data = Generator::instance().getData(fileName);
    // for (const QString &string : data) {
    //     m_jobs << Objects::Job::fromString(string);
    // }
}

int PersonsGenerator::getEnumByString(QMetaEnum p_enum, const QString &p_enumValue)
{
    for(int value = 0; value < p_enum.keyCount(); value++){
        if(auto eValue = QString(p_enum.key(value)) ; eValue == p_enumValue)
        {
            return value;
        }
    }
    return -1;
}

PersonsGenerator::PersonsGenerator(QObject *parent)
    : QObject{parent}
{
    setupStarters();
}
