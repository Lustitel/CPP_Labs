#include <iostream>
#include <stdexcept>

using namespace std;

class DynamicArray {
private:
    int* buffer;
    size_t lengthValue;

public:
    DynamicArray() : buffer(new int[10]), lengthValue(10) {
        for (size_t idx = 0; idx < lengthValue; ++idx) {
            buffer[idx] = 0;
        }
    }

    explicit DynamicArray(size_t len) : buffer(new int[len]), lengthValue(len) {
        for (size_t idx = 0; idx < lengthValue; ++idx) {
            buffer[idx] = 0;
        }
    }

    DynamicArray(size_t len, int fillVal) : buffer(new int[len]), lengthValue(len) {
        for (size_t idx = 0; idx < lengthValue; ++idx) {
            buffer[idx] = fillVal;
        }
    }

    DynamicArray(const DynamicArray& src) : buffer(new int[src.lengthValue]), lengthValue(src.lengthValue) {
        for (size_t idx = 0; idx < lengthValue; ++idx) {
            buffer[idx] = src.buffer[idx];
        }
    }

    DynamicArray(DynamicArray&& src) noexcept : buffer(src.buffer), lengthValue(src.lengthValue) {
        src.buffer = nullptr;
        src.lengthValue = 0;
    }

    ~DynamicArray() {
        delete[] buffer;
    }

    DynamicArray& operator=(const DynamicArray& src) {
        if (this != &src) {
            delete[] buffer;
            lengthValue = src.lengthValue;
            buffer = new int[lengthValue];
            for (size_t idx = 0; idx < lengthValue; ++idx) {
                buffer[idx] = src.buffer[idx];
            }
        }
        return *this;
    }

    DynamicArray& operator=(DynamicArray&& src) noexcept {
        if (this != &src) {
            delete[] buffer;
            buffer = src.buffer;
            lengthValue = src.lengthValue;
            src.buffer = nullptr;
            src.lengthValue = 0;
        }
        return *this;
    }

    size_t length() const {
        return lengthValue;
    }

    int& operator[](size_t pos) {
        if (pos >= lengthValue) {
            throw out_of_range("Индекс за пределами массива");
        }
        return buffer[pos];
    }

    void resize(size_t newLen) {
        if (newLen == lengthValue) {
            return;
        }

        int* tmpBuffer = new int[newLen];
        size_t copyCount = (newLen < lengthValue) ? newLen : lengthValue;

        for (size_t idx = 0; idx < copyCount; ++idx) {
            tmpBuffer[idx] = buffer[idx];
        }

        for (size_t idx = lengthValue; idx < newLen; ++idx) {
            tmpBuffer[idx] = 0;
        }

        delete[] buffer;
        buffer = tmpBuffer;
        lengthValue = newLen;
    }

    bool operator==(const DynamicArray& other) const {
        for (size_t idx = 0; idx < lengthValue; ++idx) {
            if (buffer[idx] != other.buffer[idx]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const DynamicArray& other) const {
        return !(*this == other);
    }

    bool operator<(const DynamicArray& other) const {
        size_t minLen = (lengthValue < other.lengthValue) ? lengthValue : other.lengthValue;
        for (size_t idx = 0; idx < minLen; ++idx) {
            if (buffer[idx] < other.buffer[idx]) {
                return true;
            }
            if (buffer[idx] > other.buffer[idx]) {
                return false;
            }
        }
        return lengthValue < other.lengthValue;
    }

    bool operator<=(const DynamicArray& other) const {
        return !(other < *this);
    }

    bool operator>(const DynamicArray& other) const {
        return other < *this;
    }

    bool operator>=(const DynamicArray& other) const {
        return !(*this < other);
    }

    DynamicArray operator+(const DynamicArray& other) const {
        DynamicArray result(lengthValue + other.lengthValue);
        for (size_t idx = 0; idx < lengthValue; ++idx) {
            result.buffer[idx] = buffer[idx];
        }
        for (size_t idx = 0; idx < other.lengthValue; ++idx) {
            result.buffer[lengthValue + idx] = other.buffer[idx];
        }
        return result;
    }

    friend ostream& operator<<(ostream& os, const DynamicArray& arr) {
        os << "[";
        for (size_t idx = 0; idx < arr.lengthValue; ++idx) {
            os << arr.buffer[idx];
            if (idx != arr.lengthValue - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

    friend istream& operator>>(istream& is, DynamicArray& arr) {
        for (size_t idx = 0; idx < arr.lengthValue; ++idx) {
            is >> arr.buffer[idx];
        }
        return is;
    }
};

int main() {
    setlocale(LC_ALL, "Rus");
    cout << "Тестирование конструкторов:" << endl;
    DynamicArray obj1;
    DynamicArray obj2(5);
    DynamicArray obj3(3, 7);
    DynamicArray obj4 = obj3;
    DynamicArray obj5 = move(DynamicArray(4, 2));

    cout << "obj1 (по умолчанию): " << obj1 << endl;
    cout << "obj2 (размер 5): " << obj2 << endl;
    cout << "obj3 (3 элемента со значением 7): " << obj3 << endl;
    cout << "obj4 (копия obj3): " << obj4 << endl;
    cout << "obj5 (перемещение временного массива): " << obj5 << endl;

    cout << "\nТестирование операторов:" << endl;
    DynamicArray obj6 = obj3 + obj5;
    cout << "Результат конкатенации obj3 + obj5: " << obj6 << endl;

    obj1.resize(5);
    cout << "obj1 после изменения размера до 5: " << obj1 << endl;

    cout << "\nТестирование сравнений:" << endl;
    cout << "obj3 == obj4: " << (obj3 == obj4) << endl;
    cout << "obj3 < obj5: " << (obj3 < obj5) << endl;
    cout << "obj3 > obj5: " << (obj3 > obj5) << endl;

    return 0;
}
