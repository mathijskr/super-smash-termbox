CC=tcc 
IN=main.c player.c ../termbox/src/termbox.c ../termbox/src/utf8.c
OUT=main
INCLUDE=../termbox/src/

make:
	$(CC) -I $(INCLUDE) $(IN) -o $(OUT)

.Phony: run

run:
	./main

clean:
	rm main
