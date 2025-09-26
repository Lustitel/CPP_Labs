#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual void start() = 0;
    virtual T getCurrent() const = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
    virtual void prev() = 0;
};

template <typename T>
class List {
public:
    virtual ~List() = default;
    virtual void insert(const T& val, Iterator<T>& it) = 0;
    virtual void remove(Iterator<T>& it) = 0;
    virtual Iterator<T>* findFirst(const T& val) = 0;
    virtual void clear() = 0;
    virtual bool isEmpty() const = 0;
    virtual size_t size() const = 0;
    virtual Iterator<T>* begin() = 0;
};

template <typename T>
class LinkedList : public List<T> {
private:
    struct Node {
        T elem;
        Node* prev;
        Node* next;

        Node(const T& val, Node* p = nullptr, Node* n = nullptr)
            : elem(val), prev(p), next(n) {
        }
    };

    Node* sentinel;
    size_t elemCount;

public:
    class LinkedListIterator : public Iterator<T> {
    private:
        Node* cur;
        Node* sentinel;
        bool ended;

    public:
        LinkedListIterator(Node* start, Node* s) : cur(start), sentinel(s), ended(start == s) {}

        void start() override { cur = sentinel->next; ended = (cur == sentinel); }

        T getCurrent() const override {
            if (ended || cur == sentinel) throw out_of_range("Итератор вышел за границы списка");
            return cur->elem;
        }

        void next() override {
            if (isDone()) throw out_of_range("Итератор вышел за границы списка");
            cur = cur->next;
            ended = (cur == sentinel);
        }

        void prev() override {
            if (cur == sentinel->next) ended = true;
            else { cur = cur->prev; ended = false; }
        }

        bool isDone() const override { return ended; }

        Node* getNode() const { return cur; }
    };

    LinkedList() : elemCount(0) {
        sentinel = new Node(T());
        sentinel->prev = sentinel;
        sentinel->next = sentinel;
    }

    LinkedList(const LinkedList& other) : LinkedList() {
        for (auto it = other.begin(); !it->isDone(); it->next())
            insert(it->getCurrent(), *begin());
    }

    LinkedList(LinkedList&& other) noexcept : sentinel(other.sentinel), elemCount(other.elemCount) {
        other.sentinel = nullptr;
        other.elemCount = 0;
    }

    ~LinkedList() {
        clear();
        delete sentinel;
    }

    void insert(const T& val, Iterator<T>& it) override {
        LinkedListIterator& lit = dynamic_cast<LinkedListIterator&>(it);
        Node* curNode = lit.getNode();

        Node* newNode = new Node(val, curNode->prev, curNode);
        curNode->prev->next = newNode;
        curNode->prev = newNode;

        elemCount++;
    }

    void remove(Iterator<T>& it) override {
        if (isEmpty()) throw out_of_range("Список пуст");

        LinkedListIterator& lit = dynamic_cast<LinkedListIterator&>(it);
        Node* toDel = lit.getNode();

        if (toDel == sentinel) throw out_of_range("Нельзя удалить буферный элемент");

        toDel->prev->next = toDel->next;
        toDel->next->prev = toDel->prev;

        lit.next();
        delete toDel;
        elemCount--;
    }

    Iterator<T>* findFirst(const T& val) override {
        auto it = begin();
        for (; !it->isDone(); it->next())
            if (it->getCurrent() == val) return it;
        delete it;
        return nullptr;
    }

    void clear() override {
        while (!isEmpty()) {
            auto it = begin();
            remove(*it);
            delete it;
        }
    }

    bool isEmpty() const override { return elemCount == 0; }

    size_t size() const override { return elemCount; }

    Iterator<T>* begin() override { return new LinkedListIterator(sentinel->next, sentinel); }
};

int main() {
    setlocale(LC_ALL, "Rus");
    LinkedList<int> lst;

    auto it = lst.begin();
    lst.insert(10, *it);
    lst.insert(20, *it);
    lst.insert(30, *it);

    cout << "Содержимое списка: ";
    for (auto it = lst.begin(); !it->isDone(); it->next()) cout << it->getCurrent() << " ";
    cout << endl;

    auto found = lst.findFirst(20);
    if (found) {
        cout << "Найден элемент: " << found->getCurrent() << endl;
        delete found;
    }

    it = lst.begin();
    it->next();
    lst.remove(*it);
    delete it;

    cout << "После удаления: ";
    for (auto it = lst.begin(); !it->isDone(); it->next()) cout << it->getCurrent() << " ";
    cout << endl;

    cout << "Размер списка: " << lst.size() << endl;

    lst.clear();
    cout << "После очистки, список пуст: " << boolalpha << lst.isEmpty() << endl;

    return 0;
}
