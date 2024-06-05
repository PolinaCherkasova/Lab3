#ifndef BYTYPECALCULATIONSTRATEGY_H
#define BYTYPECALCULATIONSTRATEGY_H
#include "calculationstrategy.h"
#include <QFileInfo>

class ByTypeCalculationStrategy : public CalculationStrategy
{
public:
    QMap<QString, int> calculate(const QString& path, int level);
};

#endif // BYTYPECALCULATIONSTRATEGY_H
