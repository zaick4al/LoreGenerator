#include "generator.h"
#include <QFile>
#include <QTextStream>

Q_LOGGING_CATEGORY(GeneratorLog, "app.generator")

QString Generator::generateName(Race p_race, Sex p_sex)
{
    auto names = getNames(p_race, p_sex);
    auto index = generateBounded(0, names.count() - 1);
    return names.at(index);
}

QString Generator::generateSettlementName(Ethnic p_ethnic)
{
    auto lists = getSettlementNames(p_ethnic);
    auto roots = lists.first;
    auto topoformants = lists.second;
    auto root = roots.at(generateBounded(roots.count() - 1));
    auto topoformant = topoformants.at(generateBounded(topoformants.count() - 1));
    auto result = root.trimmed() + topoformant.trimmed();
    return result;
}



QString Generator::generateSurname(Race p_race)
{
    auto surnames = getSurnames(p_race);
    auto index = generateBounded(0, surnames.count() - 1);
    return surnames.at(index);
}

QString Generator::generateTitle()
{
    auto titles = getTitles();
    auto index = generateBounded(titles.count() - 1);
    return titles.at(index);
}

QStringList Generator::getNames(Race p_race, Sex p_sex)
{
    auto raceEnum = QMetaEnum::fromType<Race>();
    QString raceName = raceEnum.key(p_race);
    if (raceName.contains("Dwarf"))
        raceName = "Dwarven";
    else if (raceName.contains("Elf"))
        raceName = "Elven";
    else if (raceName.contains("Human"))
        raceName = raceName.replace("Human", "");
    else if (raceName == "Demon" || raceName == "Deuna" || raceName == "Vampire")
        raceName = "Tiefling";
    else if(raceName == "HalfOrc")
        raceName = "Halforc";
    QString path = QString(":/resource/names/") + QString(m_sexEnum.key(p_sex)).toLower() + "/" +
                   raceName + ".txt";
    return getData(path);
}

QPair<QStringList, QStringList> Generator::getSettlementNames(Ethnic p_ethnic)
{
    QString rootsPath = ":/resource/settlement/roots/";
    QString topofPath = ":/resource/settlement/topoformants/";
    QMetaEnum metaEnum = QMetaEnum::fromType<Ethnic>();
    QString rootsType = p_ethnic == Breton || p_ethnic == Germanic
                        || p_ethnic == Elven ? "Latin" : m_ethnicEnum.key(p_ethnic);
    QStringList roots = getData(rootsPath + rootsType + ".txt");
    QStringList topoformants = p_ethnic == Elven ? getData(topofPath + m_ethnicEnum.key(
                                   Breton) + ".txt") : getData(topofPath + m_ethnicEnum.key(p_ethnic) + ".txt");
    return QPair<QStringList, QStringList>(roots, topoformants);
}

QStringList Generator::getSurnames(Race p_race)
{
    QString surPath = ":/resource/surnames/";
    auto raceEnum = QMetaEnum::fromType<Race>();
    QString raceName = raceEnum.key(p_race);
    if (raceName.contains("Dwarf"))
        raceName = "Dwarven";
    else if (raceName.contains("Elf"))
        raceName = "Elven";
    else if (raceName.contains("Human"))
        raceName = raceName.replace("Human", "");
    else if (raceName == "Demon" || raceName == "Deuna" || raceName == "Vampire")
        raceName = "Tiefling";
    else if(raceName == "HalfOrc")
        raceName = "Halforc";
    return getData(surPath + raceName + ".txt");
}

QStringList Generator::getTitles()
{
    return getData(":/resource/titles/Any.txt");
}

QStringList Generator::getData(const QString &p_fileName)
{
    QFile file(p_fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCCritical(GeneratorLog) << "File doesn't exist" << file.fileName();
        return QStringList();
    };
    QTextStream textStream(&file);
    QString fileData = textStream.readAll();
    file.close();
    if (fileData.isEmpty()) {
        qCCritical(GeneratorLog) << "File is empty" << file.fileName();
        return QStringList();
    }
    QStringList data = fileData.split(",");
    if (data.last() == "\n")
        data.removeLast();
    return data;
}

Generator::Generator(QObject *parent)
    : QObject{parent}
{}

Generator &Generator::instance()
{
    static Generator generator;
    return generator;
}

int Generator::sexAmount() const
{
    return m_sexEnum.keyCount();
}

int Generator::ethnicAmount() const
{
    return m_ethnicEnum.keyCount();
}

int Generator::typeAmount() const
{
    return m_typeEnum.keyCount();
}
