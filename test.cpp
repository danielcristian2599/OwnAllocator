#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <iostream>
#include <string.h>
using namespace std;

class TestClass {
    private: 
        int real;
        int imag;
    
    public:
        TestClass() {

        }

        TestClass(int real, int imag) {
            this->real = real;
            this->imag = imag;
        }

        int getReal() {
            return real;
        }

        int getImag() {
            return imag;
        }

        
    
};

int main(int argc, char *argv[]) {
    
    if(argc < 1) {
        cout << "Dimension!\n";
    }
    double size = atoi(argv[1]);

    TestClass obj(1,2);
    cout << sizeof(obj) * size;
    cout << "\n" << " Sizeof(double) = " << sizeof(double) << "\n";

    double *a;
    

    for(double i = 0; i < size; i++) {
        a = (double*)malloc(sizeof(double));
    }
    

    
    return 0;
}