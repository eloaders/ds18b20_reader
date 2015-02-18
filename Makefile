SRC_DIR = src
INC_DIR = $(SRC_DIR)
OBJ_DIR = obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
CFLAGS = -O3 -Wall -Wextra -Werror -std=c1x -I$(INC_DIR)
LDFLAGS = -O3 -Wall -Wextra -Werror -std=c1x

all: ds18b20_reader 

ds18b20_reader: $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f ds18b20_reader
