#ifndef CONTAINER_H
#define CONTAINER_H

#include "Box.h"
#include <vector>
#include <stdexcept>

namespace MyNamespace {
    using namespace std;

    class Container {
    private:
        vector<Box> boxes;
        int length, width, height; 
        double maxWeight;          

    public:
        Container(int l, int w, int h, double maxW)
            : length(l), width(w), height(h), maxWeight(maxW) {
        }

        int addBox(const Box& box);

        void removeBox(int index);

        int getBoxCount() const {
            return boxes.size(); 
        }

        double getTotalWeight() const;

        int getTotalValue() const;

        Box& getBox(int index) {
            return boxes.at(index); 
        }

        Box& operator[](int index) {
            return boxes.at(index); 
        }

        friend ostream& operator<<(ostream& os, const Container& container);
        friend istream& operator>>(istream& is, Container& container);
    };

    class WeightExceededException : public exception {
    public:
        const char* what() const noexcept override {
            return "Превышен лимит веса!";
        }
    };

} 

#endif 