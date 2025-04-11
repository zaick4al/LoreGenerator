#include <QCoreApplication>
#include <QObject>
#include <loregenerator.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    LoreGenerator loreGen;
    return a.exec();
};
