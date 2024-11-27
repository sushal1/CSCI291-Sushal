// --- Question #3: C++ Basic Programming ---

// LIBRARIES TO INCLUDE
#include <iostream>
#include <iomanip>
#include <cstdlib> 

using namespace std; // namespace

// FUNCTION PROTOTYPES
void print_real(float number, int fieldspace, int precision); // printing numbers
template <typename T> // template
void update_scale(T&m1, T&m2, T m3 = 10); // updating numbers

// MAIN FUNCTION
int main(void) {
    float a, b; // variables for user input
    cout << "Please input two real numbers: "; 
    cin >> a >> b;	// storing user input

    // original numbers
    cout<< "Original numbers: " << endl;
    // calling print_real() on user's numbers
    print_real(a,7,3);
    print_real(b,7,3);
    
    // call the function update_scale with ONLY the actual parameters a and b
    update_scale(a,b); // using update_scale() on user's numbers

    // updated numbers
    cout << "Updated numbers: " << endl;
    // calling print_real() on the updated numbers
    print_real(a,7,3);
    print_real(b,7,3);
	
    return 0;
}

/* complete the body of the function */
void print_real(float number, int fieldspace, int precision){
    // printing real numbers with set precision (fixed - point)
    cout << fixed << setw(fieldspace) << setprecision(precision) << number << endl;
}

// add the function definition (header + body) of the template function update_scale
template <typename T>
void update_scale(T&m1, T&m2, T m3) {
    float x,y; // variables for storing calculation
    x = (m1+m2)*m3; // calculating value for new m1
    y = (m1-m2)*m3; // calculating value for new m2

    m1 = x; // updating m1
    m2 = y; // updating m2
}
