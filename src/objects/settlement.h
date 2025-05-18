#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include <QObject>
#include <job.h>
#include <family.h>

#include <enumssingleton.h>
#include <enumssingleton.h>

#ifndef Settlement_weak
#define Settlement_weak std::weak_ptr<Objects::Settlement>
#endif
#ifndef Settlement_ptr
#define Settlement_ptr std::shared_ptr<Objects::Settlement>
#endif

namespace Objects {

class Settlement : public QObject
{
    Q_OBJECT
public:

    static QPair<int, int> housingMinMax(Enums::SettlementType p_type);
    static QPair<int, int> guardsMinMax(Enums::SettlementType p_type);
    explicit Settlement(QObject *parent = nullptr);

    int housingAmount() const;
    void setHousingAmount(int p_housingAmount);

    QList<std::shared_ptr<Objects::Family>> citizen() const;
    void setCitizen(const QList<std::shared_ptr<Objects::Family> > &p_citizen);
    void addFamily(const Family_ptr &p_family);
    void addCitizen(const std::shared_ptr<Objects::Person> &p_citizen);

    int smallHouses() const;
    void setSmallHouses(int p_smallHouses);

    int mediumHouses() const;
    void setMediumHouses(int p_mediumHouses);

    int largeHouses() const;
    void setLargeHouses(int p_largeHouses);

    Enums::Ethnic mainEthnic() const;
    void setMainEthnic(const Enums::Ethnic &p_mainEthnic);

    QString settlementName() const;
    void setSettlementName(const QString &p_settlementName);

    int population() const;
    int area() const;
    QHash<QString, int> culturePercentages();

    QHash<Enums::JobSpecialization, qreal> specialisations() const;
    void setSpecialisations(const QHash<Enums::JobSpecialization, qreal> &p_specialisations);

signals:

protected:
    int m_housingAmount;
    int m_smallHouses;
    int m_mediumHouses;
    int m_largeHouses;
    QList<Family_ptr> m_citizen;
    QString m_settlementName;
    Enums::Ethnic m_mainEthnic;
    QHash<Enums::JobSpecialization, qreal> m_specialisations;
};

} // namespace Objects

#endif // SETTLEMENT_H
