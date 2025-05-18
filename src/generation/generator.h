#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QRandomGenerator>
#include <QLoggingCategory>
#include <QMetaEnum>

#define generateBounded QRandomGenerator::global()->bounded

Q_DECLARE_LOGGING_CATEGORY(GeneratorLog)
class Generator : public QObject
{
    Q_OBJECT
public:
    static Generator &instance();
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
    enum Sex {Male = 0, Female};
    enum Ethnic {Arabic = 0, Breton, Germanic, Dwarven, Elven, Infernal};
    enum Type {Name = 0, Surname, Title, SettlementFirst, SettlementSecond};
    Q_ENUM(Race);
    Q_ENUM(Sex);
    Q_ENUM(Ethnic);
    Q_ENUM(Type);
    int sexAmount() const;
    int ethnicAmount() const;
    int typeAmount() const;
public slots:
    QString generateName(Race p_race, Sex p_sex);
    QString generateSettlementName(Ethnic p_ethnic);
    QString generateSurname(Race p_race);
    QString generateTitle();
protected:
    QStringList getNames(Race p_race, Sex p_sex);
    QPair<QStringList, QStringList> getSettlementNames(Ethnic p_ethnic);
    QStringList getSurnames(Race p_race);
    QStringList getTitles();
public:
    QStringList getData(const QString &p_fileName);
private:
    QMetaEnum m_ethnicEnum = QMetaEnum::fromType<Ethnic>();
    QMetaEnum m_sexEnum = QMetaEnum::fromType<Sex>();
    QMetaEnum m_typeEnum = QMetaEnum::fromType<Type>();
    explicit Generator(QObject *parent = nullptr);
};

#endif // GENERATOR_H
