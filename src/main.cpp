#include "writer/latexwriter.h"
#include <QCoreApplication>
#include <QObject>
#include <loregenerator.h>
#include <QProcess>
#include <QDir>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    WRITER;
    for (int i = 0; i < 2; i++) {
        auto eth = i == 0 ? Generator::Ethnic::Dwarven : Generator::Ethnic::Germanic;
        auto type = i == 0 ? Objects::Settlement::HugeCity : Objects::Settlement::MediumCity;
        auto settlement = LOREGEN.settlementGenerator()->generateSettlement(type, eth);
        WRITER.writeSettlement(settlement);
    }

    return a.exec();
};
