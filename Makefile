es20-11: cryptoRC4.o
	gcc -o es20-11 cryptoRC4.o 
cryptoRC4.o : cryptoRC4.c
	gcc -c cryptoRC4.c -std=c11 -Wall
