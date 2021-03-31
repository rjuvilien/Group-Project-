/*

Rejy Juvilien 

volumeCalculator.cpp

Menu-driven program that allows users to calculate and display the volume of different figures using different formulas.

Input:

Processing:

Output:
*/



#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

int main() {
  cout << "\nVolume Calculator ... \n\n";
  string script = "Calculate the volume of a ";
  cout << "1. " << script << "Rectangular Prism.\n" << "2. " << script << "Triangular Prism.\n" 
  << "3. " << script << "Cylinder.\n" << "4. " << script << "Pyramid.\n"
  << "5. " << script << "Cone.\n" << "6. Quit.\n\n";
  double volume, height, length, width, base, radius;
  int choice;
  cout << "Enter your choice (1-6): ";
  cin >> choice;
  if (choice >= 1 && choice <= 6) {
  } else {
    cout << "Error ... Invalid choice. Try Again. ";
    }
  
  switch (choice) {

    case 1:
    cout << "\n\n\nRectangular Prism ... \n\n"; 
    cout << "Enter the length, width and height (respectively): ";
    cin >> length >> width >> height;
    if (length > 0 && width > 0 && height > 0) {
    volume = length * width * height;
    cout << "The volume is " << fixed << setprecision(5) << volume << " units. ";
    break;
    } else {
      cout << "Error ... Invalid length/width/height. Try Again. ";
      break;
      }

    case 2:
    cout << "\n\n\nTriangular Prism ... \n\n";
    cout << "Enter the base, height, and length (respectively): ";
    cin >> base >> height >> length;
    if (base > 0 && height > 0 && length > 0) {
    volume = (base * height * length)/2;
    cout << "The volume is " << fixed << setprecision(5) << volume << " units. ";
    break;
    } else {
      cout << "Error ... Invalid base/height/length. Try Again. ";
      break;
      }

    case 3: 
    cout << "\n\n\nCylinder ... \n\n";
    cout << "Enter the radius and height (respectively): ";
    cin >> radius >> height;
    if (radius > 0 && height > 0) {
    volume = M_PI * pow (radius, 2) * height;
    cout << "The volume is " << fixed << setprecision(5) << volume << " units. ";
    break;
    } else {
      cout << "Error ... Invalid radius/height. Try Again. ";
      break;
      } 

    case 4:
    cout << "\n\n\nPyramid ... \n\n";
    cout << "Enter the length, width and height (respectively): ";
    cin >> length >> width >> height;
    if (length > 0 && width > 0 && height > 0) {
    volume = (length * width * height)/3;
    cout << "The volume is " << fixed << setprecision(5) << volume << " units. ";
    break;
    } else {
      cout << "Error ... Invalid length/width/height. Try Again. ";
      break;
      }

    case 5: 
    cout << "\n\n\nCone ... \n\n";
    cout << "Enter the radius and height (respectively): ";
    cin >> radius >> height;
    if (radius > 0 && height > 0) {
    volume = (M_PI * pow (radius, 2) * height)/3;
    cout << "The volume is " << fixed << setprecision(5) << volume << " units. ";
    break;
    } else {
      cout << "Error ... Invalid radius/height. Try Again. ";
      break;
      } 

    default:
    cout << "\n\n\nEnd. \n\n"; 
    break;
  }
}