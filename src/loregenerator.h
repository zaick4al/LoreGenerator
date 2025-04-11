#ifndef LOREGENERATOR_H
#define LOREGENERATOR_H

#include <QObject>
#include <objects/person.h>
#include <generation/personsgen.h>

#define Person_ptr std::shared_ptr<Objects::Person>

class LoreGenerator : public QObject
{
    Q_OBJECT
public:
    explicit LoreGenerator(QObject *parent = nullptr);

    PersonsGen *personGenerator() const;

protected:
    Generator *m_generator = &Generator::instance();
    PersonsGen *m_personGenerator;
};

#endif // LOREGENERATOR_H
