# Usage:
# make			# compile binary
# make clean	# remove binary and all objects

.PHONY: all clean

CC 		 = gcc								# compiler to use
INCLUDES = -I .								# directory for header files
OBJS 	 = main.o display.o parse.o util.o	# list of objects to be built
BIN 	 = asfparse							# name of target binary

all: $(BIN)

$(BIN): $(OBJS)
	@echo Linking $@
	$(CC) $(INCLUDES) $^ -o $@

%.o: %.c
	@echo Creating $@
	$(CC) -c $< -o $@

clean:
	@rm -f *.o asfparse