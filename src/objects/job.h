#ifndef JOB_H
#define JOB_H

#include <QObject>
#include <QDebug>
#include <enumssingleton.h>

#ifndef Job_weak
#define Job_weak std::weak_ptr<Objects::Job>
#endif
#ifndef Job_ptr
#define Job_ptr std::shared_ptr<Objects::Job>
#endif

namespace Objects {
class Job : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged
               FINAL)
    Q_PROPERTY(StatsAdjustment statsAdjustments READ statsAdjustments WRITE setStatsAdjustments NOTIFY
               statsAdjustmentsChanged FINAL)
public:
    static std::shared_ptr<Job> fromString(const QString &p_data, QObject *p_parent = nullptr);
    struct StatsAdjustment {
        qint8 strength = 0;
        qint8 dexterity = 0;
        qint8 intelligence = 0;
        qint8 constitution = 0;
        qint8 perception = 0;
        qint8 charisma = 0;
    };
    QString name() const;
    void setName(const QString &p_name);

    QString description() const;
    void setDescription(const QString &p_description);

    StatsAdjustment statsAdjustments() const;
    void setStatsAdjustments(const StatsAdjustment &p_statsAdjustments);

    explicit Job(QObject *p_parent = nullptr);

    QList<Enums::SettlementType> availableIn() const;
    void setAvailableIn(const QList<Enums::SettlementType> p_availableIn);
    void addAvailableIn(const Enums::SettlementType p_availableIn);
    void addAvailableIn(const QString &p_avIn);

    QList<Enums::JobSpecialization> specializations() const;
    void setSpecializations(const QList<Enums::JobSpecialization> p_specializations);
    void addSpecializations(const Enums::JobSpecialization p_specialization);
    void addSpecializations(const QString &p_spec);

signals:
    void nameChanged();

    void descriptionChanged();

    void statsAdjustmentsChanged();

private:
    StatsAdjustment m_statsAdjustments;
    QString m_description;
    QString m_name;
    QList<Enums::SettlementType> m_availableIn;
    QList<Enums::JobSpecialization> m_specializations;
};

} // namespace Objects

#endif // JOB_H
