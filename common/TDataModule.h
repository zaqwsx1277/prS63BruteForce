#ifndef CLASSDATAMODULE_H
#define CLASSDATAMODULE_H

#include <memory>

#include <QSettings>

/*
 * КЛАС СИНГЛТОН(ОДИНОЧКА).
 * Может существовать только в единственном экземпляре.
 *
 * При этом констуктор и диструктор закрыты от разработчика
 * (Что не позволяет плодить или уничтожать объекты этого класса).
 * Копирующий конструктор и конструктор приравнивания запрещены к созданию
 * т.к. не соответствуют концепции синглтона (требуется стандарт C++11).
 * На данный класс помжно получить ссылку вызвав метод Instance(),
 * который в свою очередь вызывает конструктор и возвращает ссылку на объект.
 *
 * В свою очередь при использовании данной концепции как DataModule, имеет смысл
 * хранить объекты данного класса в виде умного указателя (уникального), причём
 * в открытом виде (Public [агрегация]), ибо инкапсуляция данных этих классов
 * должна быть реализовывана самими этими классами.
 *
 * Первое создание/вызов имеет смысл в main.cpp после инициализации Application
 * и перед инициализацией и вызовом mainwindow.
 *
 * САМАЯ ГЛАВНАЯ ФИЧА:
 * Не требуется тащить #include "main.cpp" в каждый
 * файл, где требуется доступ к модулю данных. Это позволит избежать
 * зацикливания подключений.
 *
 * Достаточно #include "ClassDataModule.h", что позволит сразу запросить
 * ссылку на статический расположенный в памяти модуль данных.
 *
 * !!!
 * Внимание, попытка подключить #include "ClassDataModule.h" в заголовочном файле класса,
 * содержащегося в модуле данных приведёт к тому самомоу зацикливанию подключений.
 * Следовательно все глобальные типы данных\структуры и методы должны быть описаны отдельно!
 *
 * МОДУЛЬ ДАННЫХ РЕАЛИЗУЕТ ДОСТУП К ГЛОБАЛЬНЫМ КЛАССАМ ИЗ ЛЮБОЙ ТОЧКИ ПРОГРАММЫ.
 * ОН НЕ ПОМОЙКА ТИПОВ ДАННЫХ И НЕ ХРАНИЛИЩЕ МЕТОДОВ!
*/

/*!
 * \brief The TDataModule class Общий класс для хранения статических данных
 */
class TDataModule
{
public:
    std::unique_ptr <QSettings> fSettings = std::make_unique <QSettings> ("prS63.ini", QSettings::IniFormat ) ; // настройки проекта
    static TDataModule& Instance(); // Метод, возвращающий ссылку на синглтон

private:
    TDataModule(); // Скрытый конструктор по умолчанию
    ~TDataModule(); // Скрытый деструктор

    TDataModule(TDataModule const&) = delete; // Инициализация копирование запрещена
    TDataModule& operator= (TDataModule const&) = delete; // Прамое копирование запрещено
};

#endif // CLASSDATAMODULE_H
