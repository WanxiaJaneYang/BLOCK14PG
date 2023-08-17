CC = g++
CFLAGS = -std=c++11 -Wall
INCLUDE_DIRS = -Icores -Iglobals -Iinput -Ioutput

OBJ = cores/Block.o cores/Cuboid.o cores/SafeInputTasks.o cores/SafeOutputTasks.o \
      globals/globals.o \
      input/main.o input/readInput.o \
      output/output.o

output_program: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o output_program

cores/%.o: cores/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

globals/%.o: globals/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

input/%.o: input/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

output/%.o: output/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -f cores/*.o globals/*.o input/*.o output/*.o output_program
