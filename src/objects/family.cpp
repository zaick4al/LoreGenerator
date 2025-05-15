#include "family.h"
namespace Objects {
Family::Family(QObject *parent)
    : QObject{parent}
{}

QList<std::shared_ptr<Person> > Family::persons() const
{
    return m_persons;
}

void Family::setPersons(const QList<std::shared_ptr<Objects::Person> > &p_persons)
{
    m_persons = p_persons;
}

void Family::removePerson(std::shared_ptr<Person> p_person)
{
    m_persons.removeAll(p_person);
}

void Family::addPerson(std::shared_ptr<Person> p_person)
{
    m_persons << p_person;
}

int Family::familyCount()
{
    return m_persons.count();
}
}
