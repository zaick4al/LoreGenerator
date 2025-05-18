#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include <QObject>
#include <job.h>
#include <family.h>

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
    enum SettlementType{
        HugeCity,
        LargeCity,
        MediumCity,
        SmallTown,
        Castle,
        Village,
        Outpost
    };
    Q_ENUM(SettlementType);
    static QPair<int, int> housingMinMax(SettlementType p_type);
    static QPair<int, int> guardsMinMax(SettlementType p_type);
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

    Generator::Ethnic mainEthnic() const;
    void setMainEthnic(const Generator::Ethnic &p_mainEthnic);

    QString settlementName() const;
    void setSettlementName(const QString &p_settlementName);

    int population() const;
    int area() const;
    QHash<QString, int> culturePercentages();

signals:

protected:
    int m_housingAmount;
    int m_smallHouses;
    int m_mediumHouses;
    int m_largeHouses;
    QList<Family_ptr> m_citizen;
    QString m_settlementName;
    Generator::Ethnic m_mainEthnic;
};

} // namespace Objects

#endif // SETTLEMENT_H
