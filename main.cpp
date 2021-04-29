#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <iostream>
using namespace std;

//size_t noAllocations = 0; 

template<class T>
class OwnAllocator {
    public:
        OwnAllocator() = default;
        ~OwnAllocator() = default;

        using value_type = T;  // alias for the value type T
        using pointer = T*;    // alias for a pointer to my type T
        using size_type = size_t;

        /*
         * The method which is used to allocate memory.
         * - it should return my pointer 
        */
        pointer allocate(size_type countedObj) {
            noAllocations += countedObj;
            return static_cast<pointer>(operator new(sizeof(T) * countedObj));
        }

        /*
         * The method which is used to deallocate memory
        */
        void deallocate(pointer p, size_type countedObj) {
            operator delete(p);
        }

        size_t get_allocations() const {
            return noAllocations;
        }
    
    private: 
        static size_t noAllocations;
};

template <class T>
typename OwnAllocator<T>::size_type OwnAllocator<T>::noAllocations = 0;

/*
 * Typename - instructs the compiler to treat the subsequent statement
 *            as a declaration
*/

class Object {
    int data[2];
    template <class T>
    static OwnAllocator<T> allocator;
    static void *operator new(size_t size) {
    }
};

int main() {

    vector<int, OwnAllocator<int>> vec;
    int *p;
    int arraySize = 10;
    p = vec.get_allocator().allocate(arraySize);
    cout << "size(p) = " << sizeof(p) << "\n";
    cout << "We have to allocate " << arraySize << " objects" << "\n";

    for(int i = 0; i < arraySize; i++) {
        vec.push_back(i);
    }

    cout<< vec.size();

    cout << "The vector has elements: \n";
    for(int i = 0; i < arraySize; i++) {
        cout << p[i] << " ";
    }

    cout<<vec.get_allocator().get_allocations()<<"\n";

    return 0;
}
