CC=tcc
IN=main.c player.c bullet.c platform.c menu.c
LIBS=-ltermbox
OUT=main
INCLUDE=-I headers/

make:
	$(CC) $(INCLUDE) $(LIBS) $(IN) -o $(OUT)

.Phony: run

run:
	./main

clean:
	rm main
