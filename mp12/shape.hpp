//ashis pandey ashisp2 MP12
#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>    

using namespace std;

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 
  	Shape(string name) {
		name_ = name; 
	}
	
  	string getName() {
		return name_;//name of the shape, this function exists so that you can indirectly access the private variable and not let others change both at the same time.
	}
	
  virtual double getArea() const = 0; //virtual means it will allow all the functions like rect, circle, suqre, to access area and volume. 
  	virtual double getVolume() const = 0; // PVF This is an abstract class, no one can inherit from this class.
	
private:
  string name_;


};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape{ // just belongs to based class


public:
  	Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle") { // ignore T, it means u can have any data type/ : also want to call shape initialize the shape lhs means constructor and rhs is initialize add on shape function as well
 width_ = width; //accessing private variables.
 length_ = length;

	}
	
  	double getArea() const {
		return width_*length_;

	}
	
  	double getVolume() const {
		return 0;
	}
	
	Rectangle<T> operator + (const Rectangle<T>& rec) { // no return type, this is operator overload declaration, rec is object
 //printf("%d %d", this->width_+ rec.getWidth(), this->length_ + rec.getLength());//return new rectangle
 Rectangle new_rec =  Rectangle(this->width_+ rec.getWidth(), this->length_ + rec.getLength());
 return new_rec;//we can use the default constructor to instantiate an object
 /*Rectangle c;

 c.length_ = this->length_ + rec.getLength();
 c.width_ = this->width_+rec.getWidth();*/


 //return c;
	}
	
	Rectangle<T> operator - (const Rectangle<T>& rec) { //syntax for operator overload rec is object pointer pass by refernece
	return Rectangle (this->width_- rec.getWidth(), this->length_ - rec.getLength() );}
 /* Rectangle c; //or is it T c
  c.width_ = getWidth() - rec.width_;
  if(c.width_ < 0)
  {
    c.width_ = 0;
  }

  c.length_ = getLength() - rec.length_;
  if(c.length_ < 0)
  {
    c.length_ = 0;
  }

  return c;

	} */
	
	T getWidth() const { 
		return this->width_;

	}
	
	T getLength() const { 
		return this->length_;
	}
private:
  T width_; //how to make this variable accessible to the above function....  set width_ equal to width arguement, we want to amke getarea function return area value. we make this private bcz other functions like rectprisms cannot access the variable, efficient less memory less code no repitition.
    T length_;

};


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape{
public:
  	Circle(double radius):Shape("Circle") {
		  radius_ = radius;

	}
	
  	double getArea() const{
		return M_PI * pow(radius_, 2);


	}
	
 	double getVolume() const{
return 0;
	}
	
Circle operator + ( const Circle& cir){
		double radius = this->radius_ + cir.getRadius();
	return Circle(radius);


	}
	
	Circle operator - (const Circle& cir){
	double radius = fmax(0, this->radius_ - cir.getRadius()); //fmax to avoid negative
	return Circle(radius);}


	double getRadius() const { 
			return radius_;
	}
private:
	double radius_;

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape{
public:
  	Sphere(double radius):Shape("Sphere") {
		radius_ = radius;


	}

  	double getVolume() const {
		return 4.0 / 3.0 * M_PI * pow(radius_, 3);


	}	
	
  	double getArea() const {
		return 4 * M_PI * pow(radius_, 2);


	}

	Sphere operator + (const Sphere& sph) {
		double radius = this->radius_ + sph.getRadius();
	return Sphere(radius);


	}

	Sphere operator - (const Sphere& sph) {
		
 double radius = fmax(0, this->radius_ - sph.getRadius());
	return Sphere(radius);


	} 
	
	double getRadius() const {
		return radius_;
	}

private:
	double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape{
public:
  	RectPrism(double width, double length, double height):Shape("RectPrism") { 
width_ = width; //no need to define variable twice
  length_ = length;
  height_ = height;
	}
	
  	double getVolume() const {
		return length_ * width_ * height_;


	}
  	
	double getArea() const {  //why do we want to make these constant ? just for safety.
			return 2 * ((length_ * width_) + (length_ * height_) + (width_ * height_));
	}
	
	RectPrism operator + (const RectPrism& rectp){
		 double width = width_ + rectp.getWidth();
	double length = length_ + rectp.getLength();
	double height = height_ + rectp.getHeight();
	return RectPrism(width, length, height);

	}
	
	RectPrism operator - (const RectPrism& rectp){
		  double width = fmax(0, width_ - rectp.getWidth());
	double length = fmax(0, length_ - rectp.getLength());
	double height = fmax(0, height_ - rectp.getHeight());
	return RectPrism(width, length, height);


	}	
	
	double getWidth() const { 
		return width_;
	}
	
	double getLength() const { 
		return length_;
	}
	
	double getHeight() const { 
		return height_;
	}
  
private:
  	double length_;
  	double width_;
  	double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
	//@@Insert your code here
	
ifstream input_file (file_name, std::ifstream::in);

	// read in the number of shapes contained in the input file
	int num_shapes;
	input_file >> num_shapes;

	// declare return vector and temp pointer for adding shapes
	list<Shape*> newShape;

	// iterate over the input file to read in shapes
	//list <int> :: iterator it;
	//for (int it = g.begin(); it != g.end(); ++it) 
	for(int i = 0; i<num_shapes; i++) // i aminto the list, no of shapes is not a list i am already into the list
	{
		string shape_name;
		input_file >> shape_name;

		// read in the appropriate data based on the name of the shape
		if (shape_name == "Rectangle") {
			double w, l;
			input_file >> w >> l;
			Shape* shapeptr = new Rectangle <double> (w,l); //new shape list of shape pointer
			//create object and push it back into the list
            newShape.push_back(shapeptr);
			//push into list of shape pointer
		}
		else if (shape_name == "Circle") {
			double r;
			input_file >> r;
			Shape* shapeptr = new Circle(r);

			newShape.push_back(shapeptr);

		}
		else if (shape_name == "Sphere") {
			double r;
			input_file >> r;
			Shape* shapeptr = new Sphere(r);
			newShape.push_back(shapeptr);

		}
		else if (shape_name == "RectPrism") {
			double w, l, h;
			input_file >> w >> l >> h;

			Shape* shapeptr = new RectPrism(w,l,h);
			newShape.push_back(shapeptr);

		}


	}

	// close the input stream and return the vector
	input_file.close();
	return newShape;

}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;
	
	list<Shape*>::iterator it;
	for (it = shapes.begin(); it != shapes.end(); it++) {
		double current_area = (*it)->getArea();
		if (max_area < current_area){
			max_area = current_area;
		}
	}
	return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
	
	list<Shape*>::iterator it;
	for (it = shapes.begin(); it != shapes.end(); it++) {
		double current_volume = (*it)->getVolume();
		if (max_volume < current_volume){
			max_volume = current_volume;
		}
	}
	return max_volume;
}

#endif

