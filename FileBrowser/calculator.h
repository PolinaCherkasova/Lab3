#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QString>
#include <QList>
#include <QPair>
#include "calculationstrategy.h"

class Calculator //Этот класс - контекст, который ссылается на стратегию, делегируя ей выполнение вычислений
{
public:
    Calculator(CalculationStrategy* st) : strategy(st) {} //В конструктор передается указатель на стратегию
    void setStrategy(CalculationStrategy* str) { //сеттер для установки стратегии вычислений и возможности ее смены
        this->strategy = str; //т.е. мы указателю на стратегию присваиваем выбранную стратегию
    }
    QList<QPair<QString, QPair<int, int>>> calculate(QString path) //метод для передачи вычислений объекту-стратегии
    {
       return strategy->calculate(path); //вызов метода для конкретной стратегии, в который передается путь к папке
    }

private:
    CalculationStrategy* strategy; //ссылка на объект-стратегию
};

#endif // CALCULATOR_H
