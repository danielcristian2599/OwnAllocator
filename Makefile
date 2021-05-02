build:
	g++ main.cpp -o out
	g++ test.cpp -o outTest 
clean:
	rm out
	rm outTest