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
    enum Sex {Male = 0, Female = 1};
    enum Ethnic {Arabic = 0, Breton = 1, Germanic = 2, Dwarven = 4, Elven = 5};
    enum Type {Name = 0, Surname = 1, Title = 2, SettlementFirst = 3, SettlementSecond = 4};
    Q_ENUM(Sex);
    Q_ENUM(Ethnic);
    Q_ENUM(Type);
    int sexAmount() const;
    int ethnicAmount() const;
    int typeAmount() const;
public slots:
    QString generateName(Ethnic p_ethnic, Sex p_sex);
    QString generateSettlementName(Ethnic p_ethnic);
    QString generateSurname(Ethnic p_ethnic);
    QString generateTitle();
protected:
    QStringList getNames(Ethnic p_ethnic, Sex p_sex);
    QPair<QStringList, QStringList> getSettlementNames(Ethnic p_ethnic);
    QStringList getSurnames(Ethnic p_ethnic);
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
