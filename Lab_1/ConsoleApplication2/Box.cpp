#include "Box.h"
#include <algorithm>

namespace MyNamespace {
    using namespace std;


    ostream& operator<<(ostream& os, const Box& box) {
        os << "Длина: " << box.length << " см, Ширина: " << box.width << " см, "
            << "Высота: " << box.height << " см, Вес: " << box.weight << " кг, "
            << "Стоимость: " << box.value << " коп.";
        return os;
    }

    istream& operator>>(istream& is, Box& box) {
        is >> box.length >> box.width >> box.height >> box.weight >> box.value;
        return is;
    }

   
    int totalValue(const vector<Box>& boxes) {
        int total = 0;
        for (const auto& box : boxes) {
            total += box.getValue();
        }
        return total;
    }

    bool checkTotalDimensions(const vector<Box>& boxes, int maxSum) {
        int sum = 0;
        for (const auto& box : boxes) {
            sum += box.getLength() + box.getWidth() + box.getHeight();
        }
        return sum <= maxSum;
    }

    
    double maxWeightUnderVolume(const vector<Box>& boxes, int maxV) {
        double maxWeight = 0.0;
        for (const auto& box : boxes) {
            int volume = box.getLength() * box.getWidth() * box.getHeight();
            if (volume <= maxV && box.getWeight() > maxWeight) {
                maxWeight = box.getWeight();
            }
        }
        return maxWeight;
    }

    bool canNestAllBoxes(const vector<Box>& boxes) {
        auto sortedBoxes = boxes;
        sort(sortedBoxes.begin(), sortedBoxes.end(), [](const Box& a, const Box& b) {
            return a.getLength() < b.getLength() && a.getWidth() < b.getWidth() && a.getHeight() < b.getHeight();
            });

        for (size_t i = 1; i < sortedBoxes.size(); ++i) {
            if (sortedBoxes[i].getLength() <= sortedBoxes[i - 1].getLength() ||
                sortedBoxes[i].getWidth() <= sortedBoxes[i - 1].getWidth() ||
                sortedBoxes[i].getHeight() <= sortedBoxes[i - 1].getHeight()) {
                return false;
            }
        }
        return true;
    }

}