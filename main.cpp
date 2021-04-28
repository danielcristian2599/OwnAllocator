#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <iostream>
using namespace std;

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

int main() {

    vector<int, OwnAllocator<int>> vec(3);
    cout<<vec.get_allocator().get_allocations()<<"\n";
    cout<<"\n";
    return 0;
}
