#ifndef SETTLEMENTGENERATOR_H
#define SETTLEMENTGENERATOR_H

#include <QObject>
#include <settlement.h>
#include <generation/generator.h>

class SettlementGenerator : public QObject
{
    Q_OBJECT
public:
    explicit SettlementGenerator(QObject *parent = nullptr);

    void setupStarters();

    Settlement_ptr generateSettlement(Enums::SettlementType p_type, Enums::Ethnic p_ethnic);

signals:

protected:
    QHash<Enums::SettlementType, QList<Job_ptr>> m_jobsBySettlementType;
    QHash<Enums::JobSpecialization, QList<Job_ptr>> m_jobsBySpecialization;
};

#endif // SETTLEMENTGENERATOR_H
