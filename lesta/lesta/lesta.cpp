#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

//Вопрос 1
//Оригинальный метод (с использованием операции деления)
bool isEvenModulo(int value) {
    return value % 2 == 0;
}
/*
Плюсы:
Простота и понятность кода.
Минусы :
 Использование операции деления % может быть медленнее операции побитового.
*/

//Новый метод (с использованием побитовой операции "И")
bool isEvenBitwise(int value) {
    return (value & 1) == 0;
}
/*
Плюсы:
Более эффективное использование процессорного времени, так как операция побитового "И" выполняется быстрее операции деления.
*/

//Вопрос 2.
//Реализация циклического буфера с использованием массива
class CircularBufferArray {
private:
    int* buffer;
    int size;
    int head;
    int tail;
    int count;

public:
    CircularBufferArray(int capacity) : size(capacity), head(0), tail(0), count(0) {
        buffer = new int[capacity];
    }

    ~CircularBufferArray() {
        delete[] buffer;
    }

    void enqueue(int value) {
        if (count == size) {
            std::cout << "Buffer is full. Cannot enqueue." << std::endl;
            return;
        }
        buffer[tail] = value;
        tail = (tail + 1) % size;
        count++;
    }

    int dequeue() {
        if (count == 0) {
            std::cout << "Buffer is empty. Cannot dequeue." << std::endl;
            return -1; 
        }
        int value = buffer[head];
        head = (head + 1) % size;
        count--;
        return value;
    }
};
/*
Плюсы:
Более эффективное использование памяти, так как не требуется дополнительная структура данных для хранения элементов.
Минусы:
Фиксированный размер буфера, который не может быть изменен после создания.
Необходимость управления памятью вручную для выделения и освобождения массива.
*/

// Реализация циклического буфера с использованием вектора
class CircularBufferVector {
private:
    std::vector<int> buffer;
    int size;
    int head;
    int tail;
    int count;

public:
    CircularBufferVector(int capacity) : size(capacity), head(0), tail(0), count(0) {
        buffer.reserve(capacity);
    }

    void enqueue(int value) {
        if (count == size) {
            std::cout << "Buffer is full. Cannot enqueue." << std::endl;
            return;
        }
        buffer.push_back(value);
        tail = (tail + 1) % size;
        count++;
    }

    int dequeue() {
        if (count == 0) {
            std::cout << "Buffer is empty. Cannot dequeue." << std::endl;
            return -1; // or throw an exception
        }
        int value = buffer[head];
        buffer.erase(buffer.begin());
        count--;
        return value;
    }
};
/*
Плюсы:
Динамический размер буфера, который может быть изменен по мере необходимости.
Встроенная поддержка динамического выделения и освобождения памяти.
Минусы:
Возможные фрагментации памяти при динамическом изменении размера вектора.
*/

// Вопрос 3
void fastestSort(int arr[], int size) {
    std::sort(arr, arr + size);
}
/*
Я выбрал стандартную библиотечную функцию std::sort, поскольку она реализует быстрые и эффективные алгоритмы сортировки.

Преимущества использования std::sort:

Производительность:Эффективные алгоритмы для быстрой сортировки.
Универсальность: Поддержка различных размеров и типов данных массивов.
Надежность: Широко используется в индустрии и зарекомендовала себя как надежная и эффективная функция сортировки.
*/

int main() {
    int num = 5;

    std::cout << "Using Modulo: " << isEvenModulo(num) << std::endl;
    std::cout << "Using Bitwise: " << isEvenBitwise(num) << std::endl;





    // Создание и тестирование CircularBufferArray
    CircularBufferArray arrayBuffer(5);
    arrayBuffer.enqueue(1);
    arrayBuffer.enqueue(2);
    arrayBuffer.enqueue(3);
    arrayBuffer.enqueue(4);
    arrayBuffer.enqueue(5);

    for (int i = 0; i < 6; ++i) {
        std::cout << "Dequeued from Array Buffer: " << arrayBuffer.dequeue() << std::endl;
    }

    // Создание и тестирование CircularBufferVector
    CircularBufferVector vectorBuffer(5);
    vectorBuffer.enqueue(10);
    vectorBuffer.enqueue(20);
    vectorBuffer.enqueue(30);
    vectorBuffer.enqueue(40);
    vectorBuffer.enqueue(50);

    for (int i = 0; i < 6; ++i) {
        std::cout << "Dequeued from Vector Buffer: " << vectorBuffer.dequeue() << std::endl;
    }


    const int size = 1000000;
    int* arr = new int[size];

    // Заполнение массива случайными числами
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000;
    }

    auto start = std::chrono::high_resolution_clock::now();
    fastestSort(arr, size);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken to sort array of size " << size << ": " << duration.count() << " seconds." << std::endl;

    delete[] arr;

}