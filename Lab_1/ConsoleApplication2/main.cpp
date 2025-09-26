#include <iostream>
#include "Box.h"
#include "Container.h"

int main() {
    using namespace MyNamespace;
    using namespace std;

    Box box1(10, 20, 30, 5.0, 1000);
    Box box2(15, 25, 35, 7.5, 1500);
    Box box3(20, 30, 40, 10.0, 2000);

    vector<Box> boxes = { box1, box2, box3 };

    setlocale(LC_ALL, "RU");

    cout << "Общая стоимость: " << totalValue(boxes) << " коп.\n";
    cout << "Проверка размеров: " << (checkTotalDimensions(boxes, 300) ? "Успешно" : "Неудача") << "\n";
    cout << "Максимальный вес при объеме <= 30000 см³: " << maxWeightUnderVolume(boxes, 30000) << " кг\n";
    cout << "Можно ли вложить все коробки друг в друга: " << (canNestAllBoxes(boxes) ? "Да" : "Нет") << "\n";



    Container container(100, 100, 100, 50.0);
    container.addBox(box1);
    container.addBox(box2);

    cout << container;

    return 0;
}