#include "writer/latexwriter.h"
#include <QCoreApplication>
#include <QObject>
#include <loregenerator.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    LoreGenerator loreGen;
    WRITER;
    for(int i = 0; i < 3; i++){
        auto family = loreGen.personGenerator()->generateFamily();
        WRITER.writeFamily(family);
        qDebug() << "writing family";
    }
    return a.exec();
};
