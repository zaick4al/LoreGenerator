#include "loregenerator.h"
#include <QElapsedTimer>

LoreGenerator::LoreGenerator(QObject *parent)
    : QObject{parent}
{
}

LoreGenerator &LoreGenerator::instance()
{
    static LoreGenerator loregen;
    return loregen;
}

PersonsGenerator *LoreGenerator::personGenerator()
{
    return &m_personGenerator;
}

SettlementGenerator *LoreGenerator::settlementGenerator()
{
    return &m_settlementGenerator;
}
