#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <generation/generator.h>
#include <job.h>
#include <QMetaEnum>
#include <enumssingleton.h>

#ifndef Person_weak
#define Person_weak std::weak_ptr<Objects::Person>
#endif
#ifndef Person_ptr
#define Person_ptr std::shared_ptr<Objects::Person>
#endif

namespace Objects {
class Person : public QObject
{
    Q_OBJECT
public:

    struct Stats {
        int *strength = new int(0);
        int *dexterity = new int(0);
        int *intelligence = new int(0);
        int *constitution = new int(0);
        int *wisdom = new int(0);
        int *charisma = new int(0);
    };
    explicit Person(QObject *parent = nullptr);
    ~Person();

    QString name() const;
    void setName(const QString &p_name);

    QString surname() const;
    void setSurname(const QString &p_surname);

    Enums::Ethnic ethnic() const;
    void setEthnic(const Enums::Ethnic &p_ethnic);

    Enums::Race race() const;
    void setRace(Enums::Race p_race);

    quint16 age() const;
    void setAge(quint16 p_age);

    QString raceString();
    QString raceRuString();

    Enums::LifeStage lifeStage() const;
    void setLifeStage(const Enums::LifeStage &p_lifeStage);

    QString lifeStageString() const;

    QString ethnicString() const;

    std::shared_ptr<Job> job() const;
    void setJob(const std::shared_ptr<Job> &p_job);

    static QMetaEnum getRacesEnum();

    static QMetaEnum getLifeStagesEnum();

    static QMetaEnum getEthnicsEnum();

    static QMetaEnum getSexEnum();

    Enums::Sex sex() const;
    void setSex(const Enums::Sex &newSex);
    QString sexString() const;

    Person *spouse() const;
    void setSpouse(Person *newSpouse);

    QList<Person *> parents() const;
    void setParents(const QList<Person *> &newParents);
    void addParent(Person *p_parent);

    QList<Person *> children() const;
    void setChildren(const QList<Person *> &newChildren);
    void addChild(Person *p_child);

    Stats &personStats();
    void setPersonStats(const Stats &p_personStats);

protected:

signals:
    void nameChanged();
    void surnameChanged();
    void ethnicChanged();
    void raceChanged();
    void lifeStageChanged();
    void ageChanged();

protected:
    QMetaEnum racesEnum;
    QMetaEnum lifeStagesEnum;
    QMetaEnum ethnicsEnum;
    QString m_name;
    QString m_surname;
    Enums::Ethnic m_ethnic;
    Enums::Sex m_sex;
    Person* m_spouse;
    QList<Person*> m_parents;
    QList<Person*> m_children;
    Enums::Race m_race;
    Enums::LifeStage m_lifeStage;
    quint16 m_age;
    Job_ptr m_job;
    Stats m_personStats;
};

} // namespace Objects

#endif // PERSON_H
