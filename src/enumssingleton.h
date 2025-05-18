#ifndef ENUMSSINGLETON_H
#define ENUMSSINGLETON_H

#include <QObject>

class Enums : public QObject
{
    Q_OBJECT
public:
    static Enums &instance();
    enum SettlementType {
        HugeCity,
        LargeCity,
        MediumCity,
        SmallTown,
        Village,
        Castle,
        Outpost,
        Port,
        Monastery,
        Capital
    };
    enum LifeStage {
        Kid,
        Teen,
        Adult,
        Elder
    };
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
        IceElf,
        SandElf,
        Halfling,
        Fishman,
        Tiefling,
        Demon,
        Deuna,
        Vampire,
        Halforc
    };
    enum Sex {Male = 0,
              Female
             };
    enum Ethnic {Arabic = 0,
                 Breton,
                 Germanic,
                 Dwarven,
                 Elven,
                 Infernal
                };
    enum GenerateType {Name = 0,
                       Surname,
                       Title,
                       SettlementFirst,
                       SettlementSecond
                      };
    enum JobSpecialization {Military = 0,
                            Chivalry,
                            Royal,
                            Siege,
                            Agricultural,
                            Trade,
                            Finance,
                            Religious,
                            Underworld,
                            Academic,
                            Alchemy,
                            Magic,
                            Craft,
                            Medical,
                            Culinary,
                            Art,
                            Law,
                            Service,
                            Fishery,
                            Mining,
                            Hunter,
                            Adventurer,
                            Guild,
                            Hospitality
                           };
    Q_ENUM(SettlementType);
    Q_ENUM(LifeStage);
    Q_ENUM(Race);
    Q_ENUM(Sex);
    Q_ENUM(Ethnic);
    Q_ENUM(GenerateType);
    Q_ENUM(JobSpecialization);


signals:

protected:
    explicit Enums(QObject *parent = nullptr);
};

#endif // ENUMSSINGLETON_H
