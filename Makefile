
CC = c++
CFLAGS = -lraylib -Wall -Werror -Wextra -g -ldl
ASAN =  -fsanitize=address -fsanitize=leak -fsanitize=undefined -fno-omit-frame-pointer 
SRCS = main.cpp
NAME = arcade
SHARED = shared.cpp

%.o: %.c
	@$(CC) $(HOTRELOEAD) $(CFLAGS)  -c $< -o $@

all : shared
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

asan: shared
	@$(CC) $(CFLAGS) $(ASAN) $(SRCS) -o $(NAME)
clean:
	rm -fr *.o

fclean : clean
	rm -fr $(NAME)

shared :
	@c++ -shared -fPIC $(SHARED) -o shared.so -g

re: fclean all

.PHONY: all clean fclean re shared




