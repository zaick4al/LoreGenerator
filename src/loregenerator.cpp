#include "loregenerator.h"
#include <QElapsedTimer>

LoreGenerator::LoreGenerator(QObject *parent)
    : QObject{parent},
      m_personGenerator(&PersonsGenerator::instance())
{
}

PersonsGenerator *LoreGenerator::personGenerator() const
{
    return m_personGenerator;
}
