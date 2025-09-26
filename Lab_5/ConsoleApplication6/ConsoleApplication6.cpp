#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

using namespace std;

class BinaryTree {
private:
    struct TreeNode {
        int key;
        shared_ptr<TreeNode> leftChild;
        shared_ptr<TreeNode> rightChild;

        TreeNode(int k) : key(k), leftChild(nullptr), rightChild(nullptr) {}
    };

    shared_ptr<TreeNode> rootNode;

    void printInOrder(shared_ptr<TreeNode> node) const {
        if (node) {
            printInOrder(node->leftChild);
            cout << node->key << " ";
            printInOrder(node->rightChild);
        }
    }

    int countEven(shared_ptr<TreeNode> node) const {
        if (!node) return 0;
        int add = (node->key % 2 == 0) ? 1 : 0;
        return add + countEven(node->leftChild) + countEven(node->rightChild);
    }

    bool allPositiveNodes(shared_ptr<TreeNode> node) const {
        if (!node) return true;
        if (node->key <= 0) return false;
        return allPositiveNodes(node->leftChild) && allPositiveNodes(node->rightChild);
    }

    shared_ptr<TreeNode> deleteLeaves(shared_ptr<TreeNode> node) {
        if (!node) return nullptr;
        if (!node->leftChild && !node->rightChild) return nullptr;
        node->leftChild = deleteLeaves(node->leftChild);
        node->rightChild = deleteLeaves(node->rightChild);
        return node;
    }

    pair<int, int> sumAndCount(shared_ptr<TreeNode> node) const {
        if (!node) return { 0, 0 };
        auto l = sumAndCount(node->leftChild);
        auto r = sumAndCount(node->rightChild);
        return { l.first + r.first + node->key,
                 l.second + r.second + 1 };
    }

    bool findPathHelper(shared_ptr<TreeNode> node, int target, vector<int>& path) const {
        if (!node) return false;
        if (node->key == target) return true;

        path.push_back(0);
        if (findPathHelper(node->leftChild, target, path)) return true;
        path.pop_back();

        path.push_back(1);
        if (findPathHelper(node->rightChild, target, path)) return true;
        path.pop_back();

        return false;
    }

public:
    BinaryTree() : rootNode(nullptr) {}

    BinaryTree(const BinaryTree& other) {
        rootNode = other.rootNode;
    }

    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            rootNode = other.rootNode;
        }
        return *this;
    }

    ~BinaryTree() {}

    void insert(int value, const vector<int>& directions) {
        if (directions.empty()) {
            if (!rootNode) {
                rootNode = make_shared<TreeNode>(value);
            }
            else {
                rootNode->key = value;
            }
            return;
        }

        shared_ptr<TreeNode> current = rootNode;
        for (size_t i = 0; i < directions.size() - 1; ++i) {
            if (directions[i] == 0) {
                if (!current->leftChild) {
                    throw invalid_argument("Ошибка: путь проходит через несуществующий узел");
                }
                current = current->leftChild;
            }
            else if (directions[i] == 1) {
                if (!current->rightChild) {
                    throw invalid_argument("Ошибка: путь проходит через несуществующий узел");
                }
                current = current->rightChild;
            }
            else {
                throw invalid_argument("Ошибка: неверный элемент в пути");
            }
        }

        if (directions.back() == 0) {
            if (!current->leftChild) {
                current->leftChild = make_shared<TreeNode>(value);
            }
            else {
                current->leftChild->key = value;
            }
        }
        else if (directions.back() == 1) {
            if (!current->rightChild) {
                current->rightChild = make_shared<TreeNode>(value);
            }
            else {
                current->rightChild->key = value;
            }
        }
        else {
            throw invalid_argument("Ошибка: неверный последний элемент в пути");
        }
    }

    friend ostream& operator<<(ostream& os, const BinaryTree& tree) {
        tree.printInOrder(tree.rootNode);
        return os;
    }

    int countEven() const {
        return countEven(rootNode);
    }

    bool allPositive() const {
        return allPositiveNodes(rootNode);
    }

    void removeLeaves() {
        rootNode = deleteLeaves(rootNode);
    }

    double average() const {
        if (!rootNode) return 0.0;
        auto res = sumAndCount(rootNode);
        return static_cast<double>(res.first) / res.second;
    }

    vector<int> pathTo(int target) const {
        vector<int> path;
        if (findPathHelper(rootNode, target, path)) {
            return path;
        }
        throw invalid_argument("Элемент не найден в дереве");
    }
};

int main() {
    setlocale(LC_ALL, "Rus");

    BinaryTree tree;

    tree.insert(10, {});
    tree.insert(5, { 0 });
    tree.insert(15, { 1 });
    tree.insert(3, { 0, 0 });
    tree.insert(7, { 0, 1 });
    tree.insert(12, { 1, 0 });
    tree.insert(18, { 1, 1 });

    cout << "Элементы дерева: " << tree << endl;
    cout << "Количество чётных чисел: " << tree.countEven() << endl;
    cout << "Все ли числа положительные: " << (tree.allPositive() ? "да" : "нет") << endl;
    cout << "Среднее арифметическое: " << tree.average() << endl;

    try {
        int target = 7;
        vector<int> path = tree.pathTo(target);
        cout << "Путь к элементу " << target << ": ";
        for (int dir : path) {
            cout << dir << " ";
        }
        cout << endl;
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    tree.removeLeaves();
    cout << "Элементы дерева после удаления: " << tree << endl;

    return 0;
}
