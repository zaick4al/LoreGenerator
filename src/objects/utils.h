#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QMetaEnum>
#include <person.h>

#ifndef U_INS
#define U_INS Utils::instance()
#endif

class Utils : public QObject
{
    Q_OBJECT
public:
    static Utils &instance();
    QString raceString(Enums::Race p_race) const;

protected:
    QHash<Enums::Race, QString> m_raceString;
private:
    explicit Utils(QObject *parent = nullptr);
};

#endif // UTILS_H
