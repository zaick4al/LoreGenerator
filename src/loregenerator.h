#ifndef LOREGENERATOR_H
#define LOREGENERATOR_H

#include <QObject>
#include <objects/person.h>
#include <generation/personsgenerator.h>
#include <generation/settlementgenerator.h>

#ifndef LOREGEN
#define LOREGEN LoreGenerator::instance()
#endif

class LoreGenerator : public QObject
{
    Q_OBJECT
public:

    static LoreGenerator &instance();

    PersonsGenerator *personGenerator();
    SettlementGenerator *settlementGenerator();

protected:
    Generator *m_generator = &Generator::instance();
    PersonsGenerator m_personGenerator;
    SettlementGenerator m_settlementGenerator;
    explicit LoreGenerator(QObject *parent = nullptr);
};

#endif // LOREGENERATOR_H
