CC = gcc
SRC = main.c
OUT = skyasm

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT)

install:
	cp $(OUT) /usr/local/bin

clean:
	rm -f $(OUT)
