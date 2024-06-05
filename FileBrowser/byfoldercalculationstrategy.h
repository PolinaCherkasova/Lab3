#ifndef BYFOLDERCALCULATIONSTRATEGY_H
#define BYFOLDERCALCULATIONSTRATEGY_H
#include "calculationstrategy.h"
#include <QFileInfo> //предоставляет информацию об имени файла, размере, пути, позиции в файловой системе
#include <QDir> //обеспечивает доступ к структурам каталогов(папок) и их содержимомму

class ByFolderCalculationStrategy : public CalculationStrategy
{
public:
    QMap<QString, int> calculate(const QString& path, int level) { //метод для вычисления общего размера файлов, сгруппированных по папкам,
        // на вход которого передается ссылка path - путь к текущей папке и уровень вложенности level в файловой системе
        QMap<QString, int> map; // Создаем словарь для хранения имени папки и ее размера в Кб
        QFileInfo file(path); // Создаем объект типа QFileInfo для проверки информации о его текущей позиции в файловой системе

        if (file.isDir()) {// Проверка, является ли текущий файл директорией(папкой), с помощью метода isDir()
            QDir dir(path); // Создаем объект типа QDir, передавая в него текущий путь, для работы с директориями
            QFileInfoList listInfo = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks); // Создаем объект типа QFileInfoList и
            //получаем список файлов и информацию о них с помощью метода entryInfoList() для текущей директории с учетом флагов:
            // Files - включаются только файлы (а не директории) в список-результат, Hidden - включаются скрытые файлы
            //(начинающиеся с точки), NoSymLinks - исключаются символьные ссылки

            int dirSize = 0; // Переменная для хранения общего размера файлов в текущей директории (передается на выход)
            for (const QFileInfo& fileInfo : listInfo) { // Проходимся по каждому файлу из списка
                dirSize += fileInfo.size(); // Добавляем размер текущего файла к общему размеру директории
            }
            map.insert(path, dirSize); // Добавляем путь и размер текущей директории в словарь

            QStringList listDir = dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs); // Создаем список строк и получаем список поддиректорий
            //(папок внутри текущей директории), исключая символы . и ..
            for (const QString& subDirName : listDir) { // Проходимся по каждой поддиректории
                QString subDirPath = path + "/" + subDirName; // Формируем полный путь к поддиректории
                QMap<QString, int> subDirMap = this->calculate(subDirPath, level + 1); // Рекурсивно вызываем метод calculate для поддиректории,
                // увеличивая уровень вложенности на 1
                for (auto it = subDirMap.constBegin(); it != subDirMap.constEnd(); ++it) {
                    map.insert(it.key(), it.value()); // Добавляем данные из рекурсивного вызова в словарь-результат
                }
            }
        }
        return map;
    }
};

#endif // BYFOLDERCALCULATIONSTRATEGY_H
