#ifndef FAMILY_H
#define FAMILY_H

#include <QObject>
#include <objects/person.h>

#ifndef Family_weak
#define Family_weak std::weak_ptr<Objects::Family>
#endif
#ifndef Family_ptr
#define Family_ptr std::shared_ptr<Objects::Family>
#endif

namespace Objects {
class Family : public QObject
{
    Q_OBJECT
public:
    explicit Family(QObject *parent = nullptr);

    QList<std::shared_ptr<Objects::Person> > persons() const;
    void setPersons(const QList<std::shared_ptr<Objects::Person> > &p_persons);
    void addPerson(Person_ptr p_person);
    void removePerson(Person_ptr p_person);
    int familyCount();
signals:

protected:
    QList<Person_ptr> m_persons;
};
}
#endif // FAMILY_H
