main:	main.c
	gcc -o main main.c -lssl -lcrypto
clean:	
	rm main
