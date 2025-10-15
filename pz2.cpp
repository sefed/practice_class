#include <iostream>
#include <windows.h>

class DynamicArray {
private:
    int* data;
    int size;

public:
    // Конструктор
    DynamicArray(int arrSize) {
        if (arrSize < 0) {
            std::cout << "Ошибка: размер не может быть отрицательным" << std::endl;
            size = 0;
            data = nullptr;
            return;
        }
        size = arrSize;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0; // Инициализируем нулями вместо случайных значений
        }
    }

    // Конструктор копирования
    DynamicArray(const DynamicArray& other) {
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    // Деструктор
    ~DynamicArray() {
        delete[] data;
    }

    // Сеттер
    void setValue(int index, int value) {
        if (0 <= index && index < size) {
            if (-100 <= value && value <= 100) {
                data[index] = value;
            } else {
                std::cout << "Ошибка: значение " << value << " выходит за пределы [-100, 100]" << std::endl;
            }
        } else {
            std::cout << "Ошибка: индекс " << index << " выходит за границы массива" << std::endl;
        }
    }

    // Геттер
    int getValue(int index) {
        if (0 <= index && index < size) {
            return data[index];
        } else {
            std::cout << "Ошибка: индекс " << index << " выходит за границы массива" << std::endl;
            return 0;
        }
    }

    // Функция вывода
    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    // Добавление значения в конец
    void addValue(int value) {
        if (-100 <= value && value <= 100) {
            int* newData = new int[size + 1];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            newData[size] = value;
            delete[] data;
            data = newData;
            size++;
        } else {
            std::cout << "Ошибка: значение " << value << " выходит за пределы [-100, 100]" << std::endl;
        }
    }

    // Операция сложения массивов
    DynamicArray add(const DynamicArray& other) {
        int maxSize = (size > other.size) ? size : other.size;
        DynamicArray result(maxSize);

        for (int i = 0; i < maxSize; i++) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.size) ? other.data[i] : 0;
            result.data[i] = val1 + val2;
        }

        return result;
    }

    // Операция вычитания массивов
    DynamicArray subtract(const DynamicArray& other) {
        int maxSize = (size > other.size) ? size : other.size;
        DynamicArray result(maxSize);

        for (int i = 0; i < maxSize; i++) {
            int val1 = (i < size) ? data[i] : 0;
            int val2 = (i < other.size) ? other.data[i] : 0;
            result.data[i] = val1 - val2;
        }

        return result;
    }

    // Геттер для размера
    int getSize() const {
        return size;
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "=== Демонстрация работы DynamicArray ===" << std::endl;

    std::cout << "1) Создаём массив firstArray длиной 3 и заполняем значениями." << std::endl;
    DynamicArray firstArray(3);
    firstArray.setValue(0, 10);
    firstArray.setValue(1, 20);
    firstArray.setValue(2, 30);
    std::cout << "firstArray: ";
    firstArray.print();

    std::cout << "2) Создаём массив secondArray длиной 5 и задаём элементы." << std::endl;
    DynamicArray secondArray(5);
    secondArray.setValue(0, 5);
    secondArray.setValue(1, 15);
    secondArray.setValue(2, 25);
    secondArray.setValue(3, 35);
    secondArray.setValue(4, 45);
    std::cout << "secondArray: ";
    secondArray.print();

    std::cout << "3) Проверяем работу конструктора копирования (копируем firstArray в copyOfFirst)." << std::endl;
    DynamicArray copyOfFirst = firstArray;
    std::cout << "copyOfFirst (копия firstArray): ";
    copyOfFirst.print();

    std::cout << "4) Добавляем значение 40 в конец firstArray." << std::endl;
    firstArray.addValue(40);
    std::cout << "firstArray после добавления: ";
    firstArray.print();

    std::cout << "5) Складываем firstArray и secondArray в sumArray (поэлементно)." << std::endl;
    DynamicArray sumArray = firstArray.add(secondArray);
    std::cout << "sumArray (first + second): ";
    sumArray.print();

    std::cout << "6) Вычитаем secondArray из firstArray в diffArray (поэлементно)." << std::endl;
    DynamicArray diffArray = firstArray.subtract(secondArray);
    std::cout << "diffArray (first - second): ";
    diffArray.print();

    std::cout << "7) Демонстрация обработки ошибок (индекс и значение вне диапазона)." << std::endl;
    firstArray.setValue(10, 50);   // индекс вне границ
    firstArray.setValue(0, 150);   // значение вне [-100,100]

    std::cout << "=== Конец демонстрации ===" << std::endl;
    return 0;
}
