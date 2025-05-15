#ifndef PERSONSGENERATOR_H
#define PERSONSGENERATOR_H

#include <QObject>
#include <person.h>

#ifndef PG_INSTANCE
#define PG_INSTANCE PersonsGenerator::instance()
#endif

#define Job_ptr std::shared_ptr<Objects::Job>

class PersonsGenerator : public QObject
{
    Q_OBJECT
public:
    static PersonsGenerator &instance();
    QList<Person_ptr> generatePersons(int p_amount, const QString &p_ethnic = "", const QString &p_lifeStage = "", const QString p_sex = "");
    QList<Person_ptr> generateFamily(Person_ptr p_person = nullptr);
signals:

protected:
    Generator *m_generator = &Generator::instance();
    QHash<Objects::Person::Race, int> m_raceLife;
    QList<Job_ptr> m_jobs;
protected:
    Person_ptr generateNextPerson(const QString &p_ethnic = "", const QString &p_lifeStage = "", const QString p_sex = "");
    void generateFamilyMember(Objects::Person::LifeStage p_lifeStage = Objects::Person::Elder);
    Objects::Person::Race generateRaceByEthnic(std::shared_ptr<Objects::Person> p_person);
    int generateAgeByRace(Person_ptr p_person);
    void setupStarters();
    int getEnumByString(QMetaEnum p_enum, const QString &p_enumValue);
protected:
    explicit PersonsGenerator(QObject *parent = nullptr);
};

#endif // PERSONSGENERATOR_H
