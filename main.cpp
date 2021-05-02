#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <iostream>
using namespace std;

class MemoryPool {
    private: 
        unsigned int noBlocks;          // number of blocks
        unsigned int sizeOfBlock;       // size of each block

        unsigned int noInitBlocks;      // number of initialized blocks
        unsigned int noFreeBlocks;      // number of free remaining blocks

        unsigned int *startPoint;       // beginning of memory 
        unsigned int *nextPoint;        // next free block
    
    public:
        MemoryPool() {
            noBlocks = 0;
            sizeOfBlock = 0;
            noInitBlocks = 0;
            noFreeBlocks = 0;
            startPoint = NULL;
            nextPoint = 0;
        }

        void createPool(size_t sizeOfBlock, unsigned int noBlocks) {
            this->sizeOfBlock = sizeOfBlock;
            this->noBlocks = noBlocks;
            startPoint = new unsigned int[sizeOfBlock * noBlocks];
            //cout << "sizeOfBlock * noBlocks = " << sizeOfBlock * noBlocks << "\n";
            noFreeBlocks = noBlocks;
            nextPoint = startPoint;     // initially, the next free block is the startPoint
        }

        void deletePool() {
            delete[] startPoint;
            startPoint = NULL;
        }

        /*
         * Generate the address (knowing the index)
         */
        unsigned int* addrFromIndex(unsigned int index) {
            return startPoint + (index * sizeOfBlock);
        }

        /*
         * Generate the index (knowing the adress)
         */
        unsigned int indexFromAddr(unsigned int *p) {
            return ((p - startPoint) / sizeOfBlock);
        }

        
        void* allocate() {
            if(noInitBlocks < noBlocks) {
                unsigned int *p = addrFromIndex(noInitBlocks);
               // cout << "p_init = " << p << "\n";
                *p = noInitBlocks + 1;
                noInitBlocks++;
               // cout << "noInitBlk = " << noInitBlocks << " | noFreeBlk = " << noFreeBlocks << "\n";
            }

            void *retAdr = NULL;
            if(noFreeBlocks > 0) {
                retAdr = (void*)nextPoint;
               /* cout << "ret = " << retAdr << "\n";
                  cout << "nextPoint = " << nextPoint << "\n";
                */
                --noFreeBlocks;
                //cout << "noInitBlk = " << noInitBlocks << " | noFreeBlk = " << noFreeBlocks << "\n";
                if(noFreeBlocks != 0) {
                    //cout << "*nextPoint = " << *nextPoint << "\n";
                    nextPoint = addrFromIndex(*nextPoint);
                } else {
                    nextPoint = NULL;
                }
            } else {
                cout << "No free blocks!" << "\n";
            }

            return retAdr;
        }

        void deallocate(void *p) {
            if(nextPoint != NULL) {
                (*(unsigned int*)p) = indexFromAddr(nextPoint);
                nextPoint = (unsigned int*)p;
            } else {
                *((unsigned int*)p) = noBlocks;
                nextPoint = (unsigned int*)p;
            }
            ++noFreeBlocks;
        }

    
};

int main(int argc, char *argv[]) {
    
    if(argc < 1) {
        cout << "Size error!\n";
    }

    int sizeOfBlock = atoi(argv[1]);
    double noBlocks = atoi(argv[2]);

    MemoryPool MP;
    
    MP.createPool(sizeOfBlock, noBlocks);
    for(double i = 0; i < noBlocks; i++) {
        //cout << "----------------------\n";
        //cout << "Iter: " << i << "\n";
        MP.allocate();
    }

    //cout << "uint = " << sizeof(unsigned int) << " | uchar = " << sizeof(unsigned char) << "\n";

    return 0;
}