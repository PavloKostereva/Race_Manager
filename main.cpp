#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class Object
{
protected:
    char *name;

public:
    Object() : name(nullptr) {}
    Object(const char *n)
    {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }
    Object(const Object &obj)
    {
        name = new char[strlen(obj.name) + 1];
        strcpy(name, obj.name);
    }
    virtual ~Object()
    {
        delete[] name;
    }
    friend ostream &operator<<(ostream &os, const Object &obj)
    {
        os << obj.name;
        return os;
    }
    virtual bool operator<(const Object &obj) const
    {
        return strcmp(name, obj.name) < 0;
    }
    virtual bool operator==(const Object &obj) const
    {
        return strcmp(name, obj.name) == 0;
    }
    virtual void display() const
    {
        cout << name << endl;
    }
};

class RaceDriver : public Object
{
private:
    char *country;
    char *carBrand;

public:
    RaceDriver() : Object(), country(nullptr), carBrand(nullptr) {}
    RaceDriver(const char *n, const char *c, const char *b) : Object(n)
    {
        country = new char[strlen(c) + 1];
        strcpy(country, c);
        carBrand = new char[strlen(b) + 1];
        strcpy(carBrand, b);
    }
    RaceDriver(const RaceDriver &driver) : Object(driver)
    {
        country = new char[strlen(driver.country) + 1];
        strcpy(country, driver.country);
        carBrand = new char[strlen(driver.carBrand) + 1];
        strcpy(carBrand, driver.carBrand);
    }
    ~RaceDriver() override
    {
        delete[] country;
        delete[] carBrand;
    }
    friend ostream &operator<<(ostream &os, const RaceDriver &driver)
    {
        os << "Driver: " << static_cast<const Object &>(driver) << ", Country: " << driver.country << ", Car Brand: " << driver.carBrand;
        return os;
    }
    bool operator<(const RaceDriver &driver) const
    { // Видалено override
        return strcmp(name, driver.name) < 0;
    }
    bool operator==(const RaceDriver &driver) const
    { // Видалено override
        return strcmp(name, driver.name) == 0;
    }
    void display() const override
    {
        cout << "Driver: " << name << ", Country: " << country << ", Car Brand: " << carBrand << endl;
    }
};

class Stage
{
private:
    int number;
    char *startPoint;
    char *endPoint;
    RaceDriver winner;

public:
    Stage() : number(0), startPoint(nullptr), endPoint(nullptr) {}
    Stage(int n, const char *start, const char *end, const RaceDriver &w) : number(n), winner(w)
    {
        startPoint = new char[strlen(start) + 1];
        strcpy(startPoint, start);
        endPoint = new char[strlen(end) + 1];
        strcpy(endPoint, end);
    }
    Stage(const Stage &stage) : number(stage.number), winner(stage.winner)
    {
        startPoint = new char[strlen(stage.startPoint) + 1];
        strcpy(startPoint, stage.startPoint);
        endPoint = new char[strlen(stage.endPoint) + 1];
        strcpy(endPoint, stage.endPoint);
    }
    ~Stage()
    {
        delete[] startPoint;
        delete[] endPoint;
    }
    friend ostream &operator<<(ostream &os, const Stage &stage)
    {
        os << "Stage Number: " << stage.number << ", Start: " << stage.startPoint << ", End: " << stage.endPoint << ", Winner: " << stage.winner;
        return os;
    }
    bool operator<(const Stage &stage) const
    {
        return strcmp(endPoint, stage.endPoint) < 0;
    }
    void display() const
    {
        cout << "Stage Number: " << number << ", Start: " << startPoint << ", End: " << endPoint << ", Winner: ";
        winner.display();
    }
    const char *getEndPoint() const
    { // Доданий метод для доступу до endPoint
        return endPoint;
    }
};

int main()
{
    int numStages;
    cout << "Enter the number of stages: ";
    cin >> numStages;

    // Оголошення та ініціалізація масиву об'єктів
    Stage *stages = new Stage[numStages];

    // Введення даних про етапи
    for (int i = 0; i < numStages; ++i)
    {
        int number;
        char start[100], end[100];
        char driverName[100], country[100], carBrand[100];

        cout << "Enter Stage " << i + 1 << " details:" << endl;
        cout << "Number: ";
        cin >> number;
        cout << "Start Point: ";
        cin >> start;
        cout << "End Point: ";
        cin >> end;
        cout << "Winner Name: ";
        cin >> driverName;
        cout << "Winner Country: ";
        cin >> country;
        cout << "Winner Car Brand: ";
        cin >> carBrand;

        stages[i] = Stage(number, start, end, RaceDriver(driverName, country, carBrand));
    }

    // Сортування етапів за зростанням кінцевого пункту
    for (int i = 0; i < numStages - 1; ++i)
    {
        for (int j = 0; j < numStages - i - 1; ++j)
        {
            if (strcmp(stages[j].getEndPoint(), stages[j + 1].getEndPoint()) > 0)
            {
                swap(stages[j], stages[j + 1]);
            }
        }
    }

    // Виведення відсортованих етапів на екран
    for (int i = 0; i < numStages; ++i)
    {
        stages[i].display();
    }

    delete[] stages; // Звільнення пам'яті

    return 0;
}
