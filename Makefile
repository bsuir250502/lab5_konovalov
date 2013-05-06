OBJ = lab5.o optlib.o service.o
CFLAGS = -Wall -std=c89 -pedantic
BINARY = lab5
all: $(BINARY)

$(BINARY): $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(BINARY)

%.o : %.c
	gcc $(CFLAGS) -c $<

clean:
	rm $(BINARY) $(OBJ)
