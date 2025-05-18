#include "enumssingleton.h"

Enums &Enums::instance()
{
    static Enums enms;
    return enms;
}

Enums::Enums(QObject *parent)
    : QObject{parent}
{}
