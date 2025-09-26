#include "Container.h"

namespace MyNamespace {
    using namespace std;

    int Container::addBox(const Box& box) {
        if (getTotalWeight() + box.getWeight() > maxWeight) {
            throw WeightExceededException();
        }
        boxes.push_back(box);
        return boxes.size() - 1;
    }

    void Container::removeBox(int index) {
        boxes.erase(boxes.begin() + index);
    }

    double Container::getTotalWeight() const {
        double total = 0.0;
        for (const auto& box : boxes) {
            total += box.getWeight();
        }
        return total;
    }

    int Container::getTotalValue() const {
        int total = 0;
        for (const auto& box : boxes) {
            total += box.getValue();
        }
        return total;
    }

    ostream& operator<<(ostream& os, const Container& container) {
        os << "Размеры: " << container.length << "x" << container.width << "x" << container.height << " см\n";
        os << "Максимальный вес: " << container.maxWeight << " кг\n";
        os << "Коробки внутри:\n";
        for (const auto& box : container.boxes) {
            os << box << "\n";
        }
        return os;
    }

    istream& operator>>(istream& is, Container& container) {
        is >> container.length >> container.width >> container.height >> container.maxWeight;
        return is;
    }

} 