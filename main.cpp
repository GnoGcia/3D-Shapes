#include <iostream>
#include <cmath>

using namespace std;

// Abstract Class for 3D Shapes
class ThreeDimensionalShape {
    protected:
        // PI Constant
        const double pi = 2 * acos(0.0);
        // Input Attributes
        int shapeType;
        double shapeSize;
        double depth;
        // Calculated Attributes
        double area;
        double surfaceArea;
        double volume;
        // Internal Helper Methods
        virtual void checkAttributes() {
            if(shapeSize <= 0.0) {
                shapeSize = 1.0;
            }
            if(depth <= 0.0) {
                depth = 1.0;
            }
        };
        virtual double calcArea() = 0;
        virtual double calcSurfaceArea() = 0;
        virtual double calcVolume() = 0;
        void calcAttributes() {
            checkAttributes();
            area = calcArea();
            surfaceArea = calcSurfaceArea();
            volume = calcVolume();
        }
    public:
        // Parameterized Constructor
        ThreeDimensionalShape(int shapeType, double shapeSize, double depth) {
            this->shapeType = shapeType;
            this->shapeSize = shapeSize;
            this->depth = depth;
        }
        // Input Attribute Setters
        void setShapeType(int shapeType) {
            this->shapeType = shapeType;
            calcAttributes();
        }
        void setShapeSize(double shapeSize) {
            this->shapeSize = shapeSize;
            calcAttributes();
        }
        void setDepth(double depth) {
            this->depth = depth;
            calcAttributes();
        }
        // Input Attribute Getters
        int getShapeType() {
            return shapeType;
        }
        double getShapeSize() {
            return shapeSize;
        }
        double getDepth() {
            return depth;
        }
        // Calculated Attribute Getters
        double getArea() {
            return area;
        }
        double getSurfaceArea() {
            return surfaceArea;
        }
        double getVolume() {
            return volume;
        }
};
// Class for Regular Prisms
class AnglePrism : public ThreeDimensionalShape {
    private:
        // Calculated Attributes
        double apothem;
        // Internal Helper Methods
        void checkAttributes() override {
            // Default to Triangle
            if(shapeType < 3) {
                shapeType = 3;
            }
            ThreeDimensionalShape::checkAttributes();
        }
        double calcApothem() {
            return shapeSize / (2 * tan(pi / shapeType));
        }
        double calcArea() override {
            return (0.5 * (apothem * shapeSize)) * shapeType;
        }
        double calcSurfaceArea() override {
            return (area * 2) + ((depth * shapeSize) * shapeType);
        }
        double calcVolume() override {
            return area * depth;
        }
        void calcAttributes() {
            apothem = calcApothem();
            ThreeDimensionalShape::calcAttributes();
        }
    public:
        // Parameterized Constructor
        AnglePrism(int shapeType, double shapeSize, double depth)
            : ThreeDimensionalShape(shapeType, shapeSize, depth) {
            calcAttributes();
        }
        // Setters
        double getApothem() {
            return apothem;
        }
};
// Class for Round Solids
class CurvePrism : public ThreeDimensionalShape {
    private:
        // Internal Helper Methods
        void checkAttributes() override {
            // Default to Cone
            if(shapeType < 0) {
                shapeType = 0;
            }
            // Default to Cylinder
            else if(shapeType > 2) {
                shapeType = 2;
            }
            ThreeDimensionalShape::checkAttributes();
        }
        double calcArea() override {
            return pi * pow(shapeSize, 2);
        }
        double calcSurfaceArea() override {
            // Sphere
            if(shapeType == 0) {
                return 4 * area;
            }
            // Cone
            if(shapeType == 1) {
                return (pi * shapeSize) * (shapeSize + sqrt(pow(depth, 2) + pow(shapeSize, 2)));
            }
            // Cylinder
            return (2 * pi * shapeSize * depth) + (2 * area);
        }
        double calcVolume() override {
            // Sphere
            if(shapeType == 0) {
                return (4.0 / 3.0) * (area * shapeSize);
            }
            // Cone
            if(shapeType == 1) {
                return area * (depth / 3);
            }
            // Cylinder
            return area * depth;
        }
    public:
        // Parameterized Constructor
        CurvePrism(int shapeType, double shapeSize, double depth)
            : ThreeDimensionalShape(shapeType, shapeSize, depth) {
            calcAttributes();
        }
};
// Driver Code
int main()
{
    // Initialize CurvePrism Objects

    CurvePrism sphere1 = CurvePrism(-2, 4, 0);
    CurvePrism sphere2 = CurvePrism(0, 5, 0);
    CurvePrism cone1 = CurvePrism(1, 4, 2.5);
    CurvePrism cone2 = CurvePrism(1, 6.25, -1.75);
    CurvePrism cylinder1 = CurvePrism(2, 2.4, 3);
    CurvePrism cylinder2 = CurvePrism(5, -1, 7);

    // Initialize AnglePrism Objects

    AnglePrism trigon = AnglePrism(3, 4, 2);
    AnglePrism tetragon = AnglePrism(4, 2, 6);
    AnglePrism pentagon = AnglePrism(5, 3.33, 0.5);
    AnglePrism hexagon = AnglePrism(6, 1, 4);

    // Output Calculated Attributes of Each ThreeDimensionalShape Object

    cout << "Sphere 1" << endl;
    cout << " A - " << sphere1.getArea() << endl;
    cout << "SA - " << sphere1.getSurfaceArea() << endl;
    cout << " V - " << sphere1.getVolume() << endl << endl;

    cout << "Sphere 2" << endl;
    cout << " A - " << sphere2.getArea() << endl;
    cout << "SA - " << sphere2.getSurfaceArea() << endl;
    cout << " V - " << sphere2.getVolume() << endl << endl;

    cout << "Cone 1" << endl;
    cout << " A - " << cone1.getArea() << endl;
    cout << "SA - " << cone1.getSurfaceArea() << endl;
    cout << " V - " << cone1.getVolume() << endl << endl;

    cout << "Cone 2" << endl;
    cout << " A - " << cone2.getArea() << endl;
    cout << "SA - " << cone2.getSurfaceArea() << endl;
    cout << " V - " << cone2.getVolume() << endl << endl;

    cout << "Cylinder 1" << endl;
    cout << " A - " << cylinder1.getArea() << endl;
    cout << "SA - " << cylinder1.getSurfaceArea() << endl;
    cout << " V - " << cylinder1.getVolume() << endl << endl;

    cout << "Cylinder 2" << endl;
    cout << " A - " << cylinder2.getArea() << endl;
    cout << "SA - " << cylinder2.getSurfaceArea() << endl;
    cout << " V - " << cylinder2.getVolume() << endl << endl;

    cout << "Trigon" << endl;
    cout << "AP - " << trigon.getApothem() << endl;
    cout << " A - " << trigon.getArea() << endl;
    cout << "SA - " << trigon.getSurfaceArea() << endl;
    cout << " V - " << trigon.getVolume() << endl << endl;

    cout << "Tetragon" << endl;
    cout << "AP - " << tetragon.getApothem() << endl;
    cout << " A - " << tetragon.getArea() << endl;
    cout << "SA - " << tetragon.getSurfaceArea() << endl;
    cout << " V - " << tetragon.getVolume() << endl << endl;

    cout << "Pentagon" << endl;
    cout << "AP - " << pentagon.getApothem() << endl;
    cout << " A - " << pentagon.getArea() << endl;
    cout << "SA - " << pentagon.getSurfaceArea() << endl;
    cout << " V - " << pentagon.getVolume() << endl << endl;

    cout << "Hexagon" << endl;
    cout << "AP - " << hexagon.getApothem() << endl;
    cout << " A - " << hexagon.getArea() << endl;
    cout << "SA - " << hexagon.getSurfaceArea() << endl;
    cout << " V - " << hexagon.getVolume() << endl << endl;

    return 0;
}
