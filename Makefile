CC = g++
CFLAGS = -std=c++11
LFLAGS = -lwiringPi -ltft_st7735
HEADERS = -I./headers

SOURCEDIR = ./src/

OBJECTS = main.o Input.o GameObject.o Scene.o SceneManager.o Button.o
all: clear tetrisPi
	@echo Done

tetrisPi: $(OBJECTS)
	$(CC) $(CFLAGS) $(HEADERS) $(OBJECTS) $(LFLAGS) -o tetrisPi

%.o: $(SOURCEDIR)%.cpp
	$(CC) $(CFLAGS) $(HEADERS) $(LFLAGS) -MMD -c $< -o $@

-include ./*.d

clear:
	clear

clean:
	rm -f *.o *~ *.d
