build:
	g++ main.cpp -o outAllocator
	g++ test.cpp -o outMalloc

test:
	@echo "--------BEGIN - Testing allocation--------"
	@echo " "
	@echo "noBlocks: 100.000.000"
	time ./outAllocator 8 100000000
	@echo "--------------------------"
	time ./outMalloc 100000000
	@echo "--------------------------"
	@echo "noBlocks: 200.000.000"
	time ./outAllocator 8 200000000
	@echo "--------------------------"
	time ./outMalloc 200000000	
	@echo "--------------------------"
	@echo "noBlocks: 300.000.000"
	time ./outAllocator 8 300000000
	@echo "--------------------------"
	time ./outMalloc 300000000
	@echo " "
	@echo "--------END - Testing allocation--------"
	

clean:
	rm outAllocator
	rm outMalloc