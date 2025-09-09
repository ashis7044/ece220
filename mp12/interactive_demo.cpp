#include<iostream>
#include "shape.hpp"

using namespace std;

void demonstrateShapeOperations() {
    cout << "\n" << string(80, '=') << endl;
    cout << "               INTERACTIVE SHAPE OPERATIONS DEMO" << endl;
    cout << string(80, '=') << endl;
    
    cout << "\nThis demo shows how operator overloading makes geometric operations intuitive!" << endl;
    
    // Rectangle operations
    cout << "\n1. RECTANGLE OPERATIONS:" << endl;
    cout << string(40, '-') << endl;
    
    Rectangle<double> room1(12.0, 15.0);  // Living room
    Rectangle<double> room2(8.0, 10.0);   // Bedroom
    
    cout << "Living Room: " << room1.getWidth() << "ft × " << room1.getLength() 
         << "ft (Area: " << room1.getArea() << " sq ft)" << endl;
    cout << "Bedroom: " << room2.getWidth() << "ft × " << room2.getLength() 
         << "ft (Area: " << room2.getArea() << " sq ft)" << endl;
    
    Rectangle<double> combinedSpace = room1 + room2;
    cout << "\nIf we 'add' these rooms (imagine extending dimensions):" << endl;
    cout << "Combined: " << combinedSpace.getWidth() << "ft × " << combinedSpace.getLength() 
         << "ft (Area: " << combinedSpace.getArea() << " sq ft)" << endl;
    
    Rectangle<double> difference = room1 - room2;
    cout << "\nIf we 'subtract' bedroom from living room:" << endl;
    cout << "Difference: " << difference.getWidth() << "ft × " << difference.getLength() 
         << "ft (Area: " << difference.getArea() << " sq ft)" << endl;
    
    // Circle operations
    cout << "\n2. CIRCLE OPERATIONS (Pizza Example!):" << endl;
    cout << string(40, '-') << endl;
    
    Circle pizza1(8.0);   // Large pizza (8 inch radius)
    Circle pizza2(6.0);   // Medium pizza (6 inch radius)
    
    cout << "Large Pizza: radius " << pizza1.getRadius() 
         << " inches (Area: " << pizza1.getArea() << " sq in)" << endl;
    cout << "Medium Pizza: radius " << pizza2.getRadius() 
         << " inches (Area: " << pizza2.getArea() << " sq in)" << endl;
    
    Circle megaPizza = pizza1 + pizza2;
    cout << "\nIf we could 'combine' pizzas into one mega-pizza:" << endl;
    cout << "Mega Pizza: radius " << megaPizza.getRadius() 
         << " inches (Area: " << megaPizza.getArea() << " sq in)" << endl;
    cout << "That's " << (megaPizza.getArea() / pizza1.getArea()) 
         << " times larger than the original large pizza!" << endl;
    
    // Sphere operations
    cout << "\n3. SPHERE OPERATIONS (Balloon Example!):" << endl;
    cout << string(40, '-') << endl;
    
    Sphere balloon1(5.0);  // Birthday balloon
    Sphere balloon2(3.0);  // Small balloon
    
    cout << "Birthday Balloon: radius " << balloon1.getRadius() 
         << " cm (Volume: " << balloon1.getVolume() << " cubic cm)" << endl;
    cout << "Small Balloon: radius " << balloon2.getRadius() 
         << " cm (Volume: " << balloon2.getVolume() << " cubic cm)" << endl;
    
    Sphere giantBalloon = balloon1 + balloon2;
    cout << "\nIf we could merge balloons:" << endl;
    cout << "Giant Balloon: radius " << giantBalloon.getRadius() 
         << " cm (Volume: " << giantBalloon.getVolume() << " cubic cm)" << endl;
    cout << "Volume ratio: " << (giantBalloon.getVolume() / balloon1.getVolume()) 
         << " times the original!" << endl;
    
    // Practical application
    cout << "\n4. PRACTICAL APPLICATION - Building Materials:" << endl;
    cout << string(50, '-') << endl;
    
    RectPrism concrete1(10.0, 5.0, 2.0);  // Foundation section
    RectPrism concrete2(8.0, 4.0, 1.5);   // Additional section
    
    cout << "Foundation Section: " << concrete1.getWidth() << "m × " 
         << concrete1.getLength() << "m × " << concrete1.getHeight() 
         << "m (Volume: " << concrete1.getVolume() << " cubic meters)" << endl;
    cout << "Additional Section: " << concrete2.getWidth() << "m × " 
         << concrete2.getLength() << "m × " << concrete2.getHeight() 
         << "m (Volume: " << concrete2.getVolume() << " cubic meters)" << endl;
    
    RectPrism totalConcrete = concrete1 + concrete2;
    cout << "\nTotal material if combined dimensions:" << endl;
    cout << "Combined: " << totalConcrete.getWidth() << "m × " 
         << totalConcrete.getLength() << "m × " << totalConcrete.getHeight() 
         << "m (Volume: " << totalConcrete.getVolume() << " cubic meters)" << endl;
    
    double costPerCubicMeter = 150.0;  // $150 per cubic meter
    cout << "\nCost calculation:" << endl;
    cout << "Individual sections: $" << (concrete1.getVolume() + concrete2.getVolume()) * costPerCubicMeter << endl;
    cout << "Combined section: $" << totalConcrete.getVolume() * costPerCubicMeter << endl;
    
    cout << "\n" << string(80, '=') << endl;
    cout << "WHY IS THIS SIGNIFICANT?" << endl;
    cout << string(80, '=') << endl;
    
    cout << "\n✨ OPERATOR OVERLOADING BENEFITS:" << endl;
    cout << "• Makes code more intuitive and readable" << endl;
    cout << "• '+' and '-' operations feel natural for geometric shapes" << endl;
    cout << "• Reduces learning curve for developers" << endl;
    cout << "• Enables mathematical notation in programming" << endl;
    
    cout << "\n🔧 TEMPLATE PROGRAMMING BENEFITS:" << endl;
    cout << "• Rectangle<double> vs Rectangle<int> - same code, different precision" << endl;
    cout << "• Compile-time optimization" << endl;
    cout << "• Type safety without runtime overhead" << endl;
    
    cout << "\n🏗️ POLYMORPHISM BENEFITS:" << endl;
    cout << "• Same interface (getArea, getVolume) for all shapes" << endl;
    cout << "• Easy to add new shapes without changing existing code" << endl;
    cout << "• Runtime method dispatch through virtual functions" << endl;
    
    cout << "\n🌍 REAL-WORLD APPLICATIONS:" << endl;
    cout << "• CAD software: combining/subtracting geometric primitives" << endl;
    cout << "• Game engines: collision detection and physics" << endl;
    cout << "• Architecture: space planning and material estimation" << endl;
    cout << "• Manufacturing: volume calculations for cost estimation" << endl;
    
    cout << "\n" << string(80, '=') << endl;
}

int main() {
    demonstrateShapeOperations();
    return 0;
}
