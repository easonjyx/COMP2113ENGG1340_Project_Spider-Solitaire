CC = g++
CFLAGS = -pedantic-errors -std=c++11
TARGET = spider

# Objective files
OBJS = main.o \
       GameController.o \
       DeckManager.o \
       eliminate_card.o \
       Movecard.o \
       MoveRule.o \
       GameHistory.o \
       SaveLoad.o \
       Print_introduction.o

# exefile
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)


# compile rules
main.o: main.cpp GameController.h Print_introduction.h SaveLoad.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o

GameController.o: GameController.cpp GameController.h DeckManager.h GameHistory.h Movecard.h eliminate_card.h SaveLoad.h cards.h
	$(CC) $(CFLAGS) -c GameController.cpp -o GameController.o

DeckManager.o: DeckManager.cpp DeckManager.h GameHistory.h MoveRule.h cards.h
	$(CC) $(CFLAGS) -c DeckManager.cpp -o DeckManager.o

eliminate_card.o: eliminate_card.cpp eliminate_card.h DeckManager.h MoveRule.h cards.h
	$(CC) $(CFLAGS) -c eliminate_card.cpp -o eliminate_card.o

Movecard.o: Movecard.cpp Movecard.h MoveRule.h cards.h
	$(CC) $(CFLAGS) -c Movecard.cpp -o Movecard.o

MoveRule.o: MoveRule.cpp MoveRule.h cards.h
	$(CC) $(CFLAGS) -c MoveRule.cpp -o MoveRule.o

GameHistory.o: GameHistory.cpp GameHistory.h DeckManager.h cards.h
	$(CC) $(CFLAGS) -c GameHistory.cpp -o GameHistory.o

SaveLoad.o: SaveLoad.cpp SaveLoad.h DeckManager.h GameController.h cards.h
	$(CC) $(CFLAGS) -c SaveLoad.cpp -o SaveLoad.o

Print_introduction.o: Print_introduction.cpp Print_introduction.h
	$(CC) $(CFLAGS) -c Print_introduction.cpp -o Print_introduction.o

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
