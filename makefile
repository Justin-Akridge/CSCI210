make :
	clear && g++ -pedantic-errors -g ./*.cpp -o main && ./main
clean :
	rm main
