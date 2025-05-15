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

    Settlement_ptr generateSettlement(Objects::Settlement::SettlementType p_type, Generator::Ethnic p_ethnic);

signals:

protected:
    QHash<Objects::Settlement::SettlementType, QList<Job_ptr>> m_jobs;
};

#endif // SETTLEMENTGENERATOR_H
