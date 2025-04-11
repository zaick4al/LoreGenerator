#include "loregenerator.h"
#include <QElapsedTimer>

LoreGenerator::LoreGenerator(QObject *parent)
    : QObject{parent},
      m_personGenerator(new PersonsGen(this))
{
}

PersonsGen *LoreGenerator::personGenerator() const
{
    return m_personGenerator;
}
