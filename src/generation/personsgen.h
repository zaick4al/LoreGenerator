#ifndef PERSONSGEN_H
#define PERSONSGEN_H

#include <QObject>
#include <person.h>

#define Person_ptr std::shared_ptr<Objects::Person>
#define Job_ptr std::shared_ptr<Objects::Job>
class PersonsGen : public QObject
{
    Q_OBJECT
public:
    explicit PersonsGen(QObject *parent = nullptr);
    void generatePersons(int p_amount);

signals:

protected:
    Generator *m_generator = &Generator::instance();
    QHash<Objects::Person::Race, int> m_raceLife;
    QList<Person_ptr> m_persons;
    QList<Job_ptr> m_jobs;
protected:
    void generateNextPerson();
    Objects::Person::Race generateRaceByEthnic(std::shared_ptr<Objects::Person> p_person);
    int generateAgeByRace(Person_ptr p_person);
    void setupStarters();
};

#endif // PERSONSGEN_H
