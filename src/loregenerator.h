#ifndef LOREGENERATOR_H
#define LOREGENERATOR_H

#include <QObject>
#include <objects/person.h>
#include <generation/personsgenerator.h>

#define Person_ptr std::shared_ptr<Objects::Person>

class LoreGenerator : public QObject
{
    Q_OBJECT
public:
    explicit LoreGenerator(QObject *parent = nullptr);

    PersonsGenerator *personGenerator() const;

protected:
    Generator *m_generator = &Generator::instance();
    PersonsGenerator *m_personGenerator;
};

#endif // LOREGENERATOR_H
