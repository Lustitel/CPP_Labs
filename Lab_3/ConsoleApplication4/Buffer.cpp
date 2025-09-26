#include <iostream>
#include <stdexcept>

using namespace std;

class CircularBuffer {
private:
    int* storage;
    size_t maxSize;
    size_t startIdx;
    size_t endIdx;
    size_t elemCount;

public:
    CircularBuffer(size_t len) : maxSize(len), startIdx(0), endIdx(0), elemCount(0) {
        storage = new int[maxSize];
    }

    ~CircularBuffer() { delete[] storage; }

    void push_back(int val) {
        if (elemCount == maxSize) throw overflow_error("Буфер переполнен");
        storage[endIdx] = val;
        endIdx = (endIdx + 1) % maxSize;
        elemCount++;
    }

    int pop_front() {
        if (isEmpty()) throw underflow_error("Буфер пуст");
        int val = storage[startIdx];
        startIdx = (startIdx + 1) % maxSize;
        elemCount--;
        return val;
    }

    int front() const {
        if (isEmpty()) throw underflow_error("Буфер пуст");
        return storage[startIdx];
    }

    size_t size() const { return elemCount; }

    void clear() { startIdx = endIdx = elemCount = 0; }

    bool isEmpty() const { return elemCount == 0; }

    class Iterator {
    private:
        CircularBuffer& bufRef;
        size_t curIdx;
        size_t stepCnt;

    public:
        Iterator(CircularBuffer& buf) : bufRef(buf), curIdx(buf.startIdx), stepCnt(0) {}

        void start() { curIdx = bufRef.startIdx; stepCnt = 0; }

        void next() {
            if (stepCnt >= bufRef.elemCount) throw out_of_range("Итератор вышел за границы");
            curIdx = (curIdx + 1) % bufRef.maxSize;
            stepCnt++;
        }

        bool finish() const { return stepCnt >= bufRef.elemCount; }

        int getValue() const {
            if (stepCnt >= bufRef.elemCount) throw out_of_range("Итератор вышел за границы");
            return bufRef.storage[curIdx];
        }
    };

    Iterator getIterator() { return Iterator(*this); }
};

int main() {
    try {
        setlocale(LC_ALL, "Rus");
        CircularBuffer buf(5);

        buf.push_back(10);
        buf.push_back(20);
        buf.push_back(30);
        buf.push_back(40);
        buf.push_back(50);

        CircularBuffer::Iterator it = buf.getIterator();
        cout << "Содержимое буфера: ";
        for (it.start(); !it.finish(); it.next()) cout << it.getValue() << " ";
        cout << endl;

        cout << "Первый элемент: " << buf.front() << endl;

        cout << "Извлечено: " << buf.pop_front() << endl;
        cout << "Извлечено: " << buf.pop_front() << endl;

        buf.push_back(60);
        buf.push_back(70);

        cout << "Содержимое буфера после изменений: ";
        for (it.start(); !it.finish(); it.next()) cout << it.getValue() << " ";
        cout << endl;

        buf.clear();
        cout << "Размер буфера после очистки: " << buf.size() << endl;

    }
    catch (const exception& ex) {cerr << "Ошибка: " << ex.what() << endl;}

    return 0;
}
