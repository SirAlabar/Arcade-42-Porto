
CC = c++
CFLAGS = -lraylib -Wall -Werror -Wextra -g -ldl
ASAN =  -fsanitize=address -fsanitize=leak -fsanitize=undefined -fno-omit-frame-pointer 
SRCS = main.cpp
NAME = arcade
HOTRELOAD =

%.o: %.c
	@$(CC) $(HOTRELOEAD) $(CFLAGS)  -c $< -o $@

all :
	@c++ -shared -fPIC hotreload.cpp -o hotreload.so
	@$(CC) $(HOTRELOEAD) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -fr *.o

fclean : clean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re




