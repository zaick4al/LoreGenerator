#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <generation/generator.h>
#include <job.h>
#include <QMetaEnum>

namespace Objects {
#define Job_ptr std::shared_ptr<Job>
class Person : public QObject
{
    Q_OBJECT
public:
    enum Race {
        GoldenDwarf = 0,
        GrayrockDwarf,
        BlackoreDwarf,
        WhitemountDwarf,
        StormveilDwarf,
        QuariteHuman,
        ViteanHuman,
        NortkinHuman,
        IrvisianHuman,
        TaikonianHuman,
        BeinianHuman,
        QualtianHuman,
        WoodElf,
        JadeElf,
        SandElf,
        IceElf,
        Halfling,
        Fishman,
        Tiefling,
        Demon,
        Deuna,
        Vampire,
        Halforc
    };
    enum LifeStage {
        Kid,
        Teen,
        Adult,
        Elder
    };
    Q_ENUM(Race);
    Q_ENUM(LifeStage);
    explicit Person(QObject *parent = nullptr);
    ~Person();

    QString name() const;
    void setName(const QString &p_name);

    QString surname() const;
    void setSurname(const QString &p_surname);

    Generator::Ethnic ethnic() const;
    void setEthnic(const Generator::Ethnic &p_ethnic);

    Race race() const;
    void setRace(Race p_race);

    quint16 age() const;
    void setAge(quint16 p_age);

    QString raceString();

    LifeStage lifeStage() const;
    void setLifeStage(const LifeStage &p_lifeStage);

    QString lifeStageString() const;

    QString ethnicString() const;

    std::shared_ptr<Job> job() const;
    void setJob(const std::shared_ptr<Job> &p_job);

    QMetaEnum getRacesEnum() const;

    QMetaEnum getLifeStagesEnum() const;


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
    Generator::Ethnic m_ethnic;
    Race m_race;
    LifeStage m_lifeStage;
    quint16 m_age;
    Job_ptr m_job;
};

} // namespace Objects

#endif // PERSON_H
