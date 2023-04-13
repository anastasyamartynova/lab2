#include <iostream>
#include <vector>
#include <typeinfo>

class Class1 {
public:
    virtual ~Class1() = default;
};

class Class2 : public Class1 {
public:
    ~Class2() override = default; // Определяется деструктор, который переопределяет виртуальный деструктор базового класса
};

void my_copy(const std::vector<Class1*>& src, std::vector<Class1*>& dest) { // Функция my_copy копирует объекты из одного вектора src в другой вектор dest
    for (const auto& obj : src) {
        if (auto casted_obj = dynamic_cast<Class2*>(obj)) { //dynamic_cast, позволяет выполнить приведение типов во время выполнения программы. Нужно привести указатель на obj (текущий объект) к типу Class2
            dest.push_back(new Class2(*casted_obj));        //Если приведение типов успешно, то указатель на объект Class2 сохраняется в переменной casted_obj и используется для создания нового объекта Class2 (и добавляется в вектор dest)
        }
        else {                                              //Иначе создается новый объект Class1 (и добавляется в вектор dest)
            dest.push_back(new Class1(*obj));
        }
    }
}

int main() {
    Class1 obj1;
    Class2 obj2;
    std::vector<Class1*> src = { &obj1, &obj2 }; // Создать вектор указателей на объекты Class1, включая obj1 и obj2
    std::vector<Class1*> database; // Создать пустой вектор указателей на объекты Class1

    my_copy(src, database); // Копирует объекты из вектора src в вектор database

    for (const auto& obj : database) { // Итерируется по объектам в векторе database
        std::cout << typeid(*obj).name() << std::endl;
        delete obj;
    }

    return 0;
}