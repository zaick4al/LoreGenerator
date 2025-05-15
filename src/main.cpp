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
    LoreGenerator loreGen;
    WRITER;
    for (int i = 0; i < 25; i++) {
        auto family = loreGen.personGenerator()->generateFamily();
        WRITER.writeFamily(family);
    }

    return a.exec();
};
