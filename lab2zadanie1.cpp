#include <iostream>
#include <vector>
#include <typeinfo>

class Class1 {
public:
    virtual ~Class1() = default;
};

class Class2 : public Class1 {
public:
    ~Class2() override = default; // ������������ ����������, ������� �������������� ����������� ���������� �������� ������
};

void my_copy(const std::vector<Class1*>& src, std::vector<Class1*>& dest) { // ������� my_copy �������� ������� �� ������ ������� src � ������ ������ dest
    for (const auto& obj : src) {
        if (auto casted_obj = dynamic_cast<Class2*>(obj)) { //dynamic_cast, ��������� ��������� ���������� ����� �� ����� ���������� ���������. ����� �������� ��������� �� obj (������� ������) � ���� Class2
            dest.push_back(new Class2(*casted_obj));        //���� ���������� ����� �������, �� ��������� �� ������ Class2 ����������� � ���������� casted_obj � ������������ ��� �������� ������ ������� Class2 (� ����������� � ������ dest)
        }
        else {                                              //����� ��������� ����� ������ Class1 (� ����������� � ������ dest)
            dest.push_back(new Class1(*obj));
        }
    }
}

int main() {
    Class1 obj1;
    Class2 obj2;
    std::vector<Class1*> src = { &obj1, &obj2 }; // ������� ������ ���������� �� ������� Class1, ������� obj1 � obj2
    std::vector<Class1*> database; // ������� ������ ������ ���������� �� ������� Class1

    my_copy(src, database); // �������� ������� �� ������� src � ������ database

    for (const auto& obj : database) { // ����������� �� �������� � ������� database
        std::cout << typeid(*obj).name() << std::endl;
        delete obj;
    }

    return 0;
}