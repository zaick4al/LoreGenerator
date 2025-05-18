#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QRandomGenerator>
#include <QLoggingCategory>
#include <enumssingleton.h>
#include <QMetaEnum>

#define generateBounded QRandomGenerator::global()->bounded

Q_DECLARE_LOGGING_CATEGORY(GeneratorLog)
class Generator : public QObject
{
    Q_OBJECT
public:
    static Generator &instance();

    int sexAmount() const;
    int ethnicAmount() const;
    int typeAmount() const;
public slots:
    QString generateName(Enums::Race p_race, Enums::Sex p_sex);
    QString generateSettlementName(Enums::Ethnic p_ethnic);
    QString generateSurname(Enums::Race p_race);
    QString generateTitle();
protected:
    QStringList getNames(Enums::Race p_race, Enums::Sex p_sex);
    QPair<QStringList, QStringList> getSettlementNames(Enums::Ethnic p_ethnic);
    QStringList getSurnames(Enums::Race p_race);
    QStringList getTitles();
public:
    QStringList getData(const QString &p_fileName);
private:
    QMetaEnum m_ethnicEnum = QMetaEnum::fromType<Enums::Ethnic>();
    QMetaEnum m_sexEnum = QMetaEnum::fromType<Enums::Sex>();
    QMetaEnum m_typeEnum = QMetaEnum::fromType<Enums::GenerateType>();
    explicit Generator(QObject *parent = nullptr);
};

#endif // GENERATOR_H
