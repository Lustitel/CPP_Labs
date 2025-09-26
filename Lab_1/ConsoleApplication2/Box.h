#ifndef BOX_H
#define BOX_H

#include <iostream>
#include <vector>

namespace MyNamespace {
    using namespace std;

    class Box {
    private:
        int length, width, height; 
        double weight;             
        int value;                 

    public:

        Box(int l = 0, int w = 0, int h = 0, double wt = 0.0, int v = 0)
            : length(l), width(w), height(h), weight(wt), value(v) {
        }

 
        int getLength() const {
            return length; 
        }

        int getWidth() const {
            return width; 
        }

        int getHeight() const {
            return height; 
        }

        double getWeight() const {
            return weight; 
        }

        int getValue() const {
            return value; 
        }

  
        void setLength(int l) { length = l; }
        void setWidth(int w) { width = w; }
        void setHeight(int h) { height = h; }
        void setWeight(double wt) { weight = wt; }
        void setValue(int v) { value = v; }

        
        bool operator==(const Box& other) const {
            return length == other.length && width == other.width &&
                height == other.height && weight == other.weight &&
                value == other.value;
        }

        friend ostream& operator<<(ostream& os, const Box& box);
        friend istream& operator>>(istream& is, Box& box);
    };

    int totalValue(const vector<Box>& boxes);
    bool checkTotalDimensions(const vector<Box>& boxes, int maxSum);
    double maxWeightUnderVolume(const vector<Box>& boxes, int maxV);
    bool canNestAllBoxes(const vector<Box>& boxes);

} 

#endif 
