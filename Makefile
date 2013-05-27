SRC = players.c ui.c gameEngine.c score.c dice.c highscore.c nojYatzy.c rules.c
OBJ = $(SRC:.c=.o)

PROG = nojyatzy
CC = gcc

$(PROG): $(OBJ)
	$(CC) $(OBJ) -o $(PROG) -DHIGHSCOREPATH=${HIGHSCOREPATH}

$(OBJ): $(SRC)

install: $(PROG)
	@install -Dm755 ${PROG} ${DESTDIR}${PREFIX}/bin/${PROG}

clean:
	rm $(PROG)

debug:
	$(CC) -g $(OBJ) -o $(PROG)
	gdb $(PROG)
