#include<fstream>
#include <iomanip>    
#include "shape.hpp"
#include <vector>
#include <algorithm>

using namespace std;

// Function to display shape details in a formatted way
void displayShapeAnalysis(list<Shape*> shapes) {
    cout << "\n" << string(80, '=') << endl;
    cout << "                    SHAPE GEOMETRY ANALYSIS" << endl;
    cout << string(80, '=') << endl;
    
    // Display all shapes with their properties
    cout << "\nDetailed Shape Information:" << endl;
    cout << string(50, '-') << endl;
    
    int count = 1;
    double totalArea = 0, totalVolume = 0;
    
    for (list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++, count++) {
        Shape* shape = *it;
        double area = shape->getArea();
        double volume = shape->getVolume();
        
        totalArea += area;
        totalVolume += volume;
        
        cout << count << ". " << shape->getName() << ":" << endl;
        cout << "   Area:   " << fixed << setprecision(3) << area << " square units" << endl;
        cout << "   Volume: " << fixed << setprecision(3) << volume << " cubic units" << endl;
        
        // Add specific shape information
        if (shape->getName() == "Rectangle") {
            Rectangle<double>* rect = dynamic_cast<Rectangle<double>*>(shape);
            cout << "   Dimensions: " << rect->getWidth() << " x " << rect->getLength() << endl;
        }
        else if (shape->getName() == "Circle") {
            Circle* circle = dynamic_cast<Circle*>(shape);
            cout << "   Radius: " << circle->getRadius() << endl;
        }
        else if (shape->getName() == "Sphere") {
            Sphere* sphere = dynamic_cast<Sphere*>(shape);
            cout << "   Radius: " << sphere->getRadius() << endl;
        }
        else if (shape->getName() == "RectPrism") {
            RectPrism* prism = dynamic_cast<RectPrism*>(shape);
            cout << "   Dimensions: " << prism->getWidth() << " x " << prism->getLength() << " x " << prism->getHeight() << endl;
        }
        cout << endl;
    }
    
    // Summary statistics
    cout << string(50, '-') << endl;
    cout << "SUMMARY STATISTICS:" << endl;
    cout << "Total shapes analyzed: " << count-1 << endl;
    cout << "Total combined area: " << fixed << setprecision(3) << totalArea << " square units" << endl;
    cout << "Total combined volume: " << fixed << setprecision(3) << totalVolume << " cubic units" << endl;
    cout << "Average area per shape: " << fixed << setprecision(3) << totalArea/(count-1) << " square units" << endl;
    cout << "Average volume per shape: " << fixed << setprecision(3) << totalVolume/(count-1) << " cubic units" << endl;
    
    // Find max values
    double maxArea = MaxArea(shapes);
    double maxVolume = MaxVolume(shapes);
    
    cout << "\nMAXIMUM VALUES:" << endl;
    cout << "Largest area: " << fixed << setprecision(3) << maxArea << " square units" << endl;
    cout << "Largest volume: " << fixed << setprecision(3) << maxVolume << " cubic units" << endl;
    
    // Find which shapes have max values
    cout << "\nShapes with maximum values:" << endl;
    count = 1;
    for (list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++, count++) {
        Shape* shape = *it;
        if (abs(shape->getArea() - maxArea) < 0.001) {
            cout << "- " << shape->getName() << " #" << count << " has the maximum area" << endl;
        }
        if (abs(shape->getVolume() - maxVolume) < 0.001) {
            cout << "- " << shape->getName() << " #" << count << " has the maximum volume" << endl;
        }
    }
}

// Function to create ASCII visualization of shapes (simple representation)
void visualizeShapes(list<Shape*> shapes) {
    cout << "\n" << string(80, '=') << endl;
    cout << "                    SHAPE VISUALIZATION" << endl;
    cout << string(80, '=') << endl;
    
    int count = 1;
    for (list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++, count++) {
        Shape* shape = *it;
        cout << "\n" << count << ". " << shape->getName() << ":" << endl;
        
        if (shape->getName() == "Rectangle") {
            Rectangle<double>* rect = dynamic_cast<Rectangle<double>*>(shape);
            int w = min(10, (int)rect->getWidth());
            int l = min(5, (int)rect->getLength());
            
            for (int i = 0; i < l; i++) {
                cout << "   ";
                for (int j = 0; j < w; j++) {
                    cout << "█";
                }
                cout << endl;
            }
        }
        else if (shape->getName() == "Circle") {
            Circle* circle = dynamic_cast<Circle*>(shape);
            int r = min(5, (int)circle->getRadius());
            
            for (int i = -r; i <= r; i++) {
                cout << "   ";
                for (int j = -r; j <= r; j++) {
                    if (i*i + j*j <= r*r) {
                        cout << "●";
                    } else {
                        cout << " ";
                    }
                }
                cout << endl;
            }
        }
        else if (shape->getName() == "Sphere") {
            cout << "   3D Sphere (radius: " << dynamic_cast<Sphere*>(shape)->getRadius() << ")" << endl;
            cout << "       ●●●●●" << endl;
            cout << "     ●●●●●●●" << endl;
            cout << "    ●●●●●●●●●" << endl;
            cout << "     ●●●●●●●" << endl;
            cout << "       ●●●●●" << endl;
        }
        else if (shape->getName() == "RectPrism") {
            RectPrism* prism = dynamic_cast<RectPrism*>(shape);
            cout << "   3D Rectangular Prism (" << prism->getWidth() << "x" << prism->getLength() << "x" << prism->getHeight() << ")" << endl;
            cout << "     ┌─────────┐" << endl;
            cout << "    ╱│         │╱" << endl;
            cout << "   ╱ │         │╱" << endl;
            cout << "  ┌─────────┐ ╱" << endl;
            cout << "  │         │╱" << endl;
            cout << "  │         │" << endl;
            cout << "  └─────────┘" << endl;
        }
    }
}

// Function to demonstrate operator overloading
void demonstrateOperatorOverloading() {
    cout << "\n" << string(80, '=') << endl;
    cout << "                OPERATOR OVERLOADING DEMONSTRATION" << endl;
    cout << string(80, '=') << endl;
    
    cout << "\nDemonstrating shape addition and subtraction:" << endl;
    cout << string(50, '-') << endl;
    
    // Rectangle operations
    Rectangle<double> rect1(4.0, 5.0);
    Rectangle<double> rect2(2.0, 3.0);
    Rectangle<double> rect3 = rect1 + rect2;
    Rectangle<double> rect4 = rect1 - rect2;
    
    cout << "\nRectangle Operations:" << endl;
    cout << "Rectangle 1: " << rect1.getWidth() << " x " << rect1.getLength() << " (Area: " << rect1.getArea() << ")" << endl;
    cout << "Rectangle 2: " << rect2.getWidth() << " x " << rect2.getLength() << " (Area: " << rect2.getArea() << ")" << endl;
    cout << "Rectangle 1 + Rectangle 2 = " << rect3.getWidth() << " x " << rect3.getLength() << " (Area: " << rect3.getArea() << ")" << endl;
    cout << "Rectangle 1 - Rectangle 2 = " << rect4.getWidth() << " x " << rect4.getLength() << " (Area: " << rect4.getArea() << ")" << endl;
    
    // Circle operations
    Circle circle1(5.0);
    Circle circle2(2.0);
    Circle circle3 = circle1 + circle2;
    Circle circle4 = circle1 - circle2;
    
    cout << "\nCircle Operations:" << endl;
    cout << "Circle 1: radius " << circle1.getRadius() << " (Area: " << fixed << setprecision(2) << circle1.getArea() << ")" << endl;
    cout << "Circle 2: radius " << circle2.getRadius() << " (Area: " << circle2.getArea() << ")" << endl;
    cout << "Circle 1 + Circle 2 = radius " << circle3.getRadius() << " (Area: " << circle3.getArea() << ")" << endl;
    cout << "Circle 1 - Circle 2 = radius " << circle4.getRadius() << " (Area: " << circle4.getArea() << ")" << endl;
    
    // Sphere operations
    Sphere sphere1(3.0);
    Sphere sphere2(1.0);
    Sphere sphere3 = sphere1 + sphere2;
    Sphere sphere4 = sphere1 - sphere2;
    
    cout << "\nSphere Operations:" << endl;
    cout << "Sphere 1: radius " << sphere1.getRadius() << " (Volume: " << fixed << setprecision(2) << sphere1.getVolume() << ")" << endl;
    cout << "Sphere 2: radius " << sphere2.getRadius() << " (Volume: " << sphere2.getVolume() << ")" << endl;
    cout << "Sphere 1 + Sphere 2 = radius " << sphere3.getRadius() << " (Volume: " << sphere3.getVolume() << ")" << endl;
    cout << "Sphere 1 - Sphere 2 = radius " << sphere4.getRadius() << " (Volume: " << sphere4.getVolume() << ")" << endl;
}

// Function to explain the significance of the code
void explainSignificance() {
    cout << "\n" << string(80, '=') << endl;
    cout << "                    EDUCATIONAL SIGNIFICANCE" << endl;
    cout << string(80, '=') << endl;
    
    cout << "\nThis program demonstrates several important Computer Science concepts:" << endl;
    cout << "\n1. OBJECT-ORIENTED PROGRAMMING (OOP):" << endl;
    cout << "   • Inheritance: All shapes inherit from the base Shape class" << endl;
    cout << "   • Polymorphism: Virtual functions allow different implementations" << endl;
    cout << "   • Encapsulation: Private members with public accessors" << endl;
    cout << "   • Abstraction: Shape is an abstract base class" << endl;
    
    cout << "\n2. TEMPLATE PROGRAMMING:" << endl;
    cout << "   • Rectangle class uses templates for flexible data types" << endl;
    cout << "   • Demonstrates generic programming concepts" << endl;
    
    cout << "\n3. OPERATOR OVERLOADING:" << endl;
    cout << "   • + and - operators are overloaded for shape operations" << endl;
    cout << "   • Shows how to extend language functionality" << endl;
    
    cout << "\n4. DYNAMIC MEMORY MANAGEMENT:" << endl;
    cout << "   • Uses pointers and dynamic allocation" << endl;
    cout << "   • Demonstrates polymorphic behavior through base class pointers" << endl;
    
    cout << "\n5. FILE I/O and DATA PROCESSING:" << endl;
    cout << "   • Reads shape data from files" << endl;
    cout << "   • Processes and analyzes geometric data" << endl;
    
    cout << "\n6. STL (Standard Template Library):" << endl;
    cout << "   • Uses std::list for container management" << endl;
    cout << "   • Demonstrates iterator usage" << endl;
    
    cout << "\n7. REAL-WORLD APPLICATIONS:" << endl;
    cout << "   • Computer Graphics: Shape representation and manipulation" << endl;
    cout << "   • CAD Software: Geometric calculations and transformations" << endl;
    cout << "   • Game Development: Collision detection and object management" << endl;
    cout << "   • Architecture: Area and volume calculations for construction" << endl;
    cout << "   • Manufacturing: Material usage optimization" << endl;
}

int main(int argc, char *argv[]){
    if(argc != 2) {
        cerr << "USAGE: ./enhanced_mp12 test1.txt" << endl; 
        return -1;
    }
    
    // Load shapes from file
    list<Shape*> shape_ptrs = CreateShapes(argv[1]);
    
    if (shape_ptrs.empty()) {
        cerr << "Error: No shapes found in file or file cannot be read!" << endl;
        return -1;
    }
    
    // Display comprehensive analysis
    displayShapeAnalysis(shape_ptrs);
    
    // Show visual representations
    visualizeShapes(shape_ptrs);
    
    // Demonstrate operator overloading
    demonstrateOperatorOverloading();
    
    // Explain educational significance
    explainSignificance();
    
    cout << "\n" << string(80, '=') << endl;
    cout << "                    PROGRAM COMPLETE" << endl;
    cout << string(80, '=') << endl;
    
    // Clean up memory
    for (list<Shape*>::iterator it = shape_ptrs.begin(); it != shape_ptrs.end(); it++) {
        delete *it;
    }
    
    return 0;
}
