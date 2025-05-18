#ifndef PERSONSGENERATOR_H
#define PERSONSGENERATOR_H

#include <QObject>
#include <person.h>

#define Job_ptr std::shared_ptr<Objects::Job>

class PersonsGenerator : public QObject
{
    Q_OBJECT
public:
    explicit PersonsGenerator(QObject *parent = nullptr);
public:
    QList<Person_ptr> generatePersons(int p_amount, const QString &p_ethnic = "", const QString &p_lifeStage = "", const QString p_sex = "");
    QList<Person_ptr> generateFamily(Person_ptr p_person = nullptr);
signals:

protected:
    Generator *m_generator = &Generator::instance();
    QHash<Generator::Race, int> m_raceLife;
    QList<Job_ptr> m_jobs;
protected:
    Person_ptr generateNextPerson(const QString &p_ethnic = "", const QString &p_lifeStage = "", const QString p_sex = "");
    void generateFamilyMember(Objects::Person::LifeStage p_lifeStage = Objects::Person::Elder);
    Generator::Race generateRaceByEthnic(std::shared_ptr<Objects::Person> p_person);
    int generateAgeByRace(Person_ptr p_person);
    void setupStarters();
    int getEnumByString(QMetaEnum p_enum, const QString &p_enumValue);
};

#endif // PERSONSGENERATOR_H
