##
## Makefile for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_philo
## 
## Made by adam soto
## Login   <soto_a@epitech.net>
## 
## Started on  Wed Mar  2 12:54:44 2016 
## Last update Sun Oct 16 22:47:40 2016 
##

NAME	= server

CFLAGS	= -I./include -O2 -pipe
#LDFLAGS	= 

CC	= gcc

SRC	= main.c \
	  server.c \
	  server_manage.c \
	  socket.c \
	  socket_manage.c \
	  handle_client.c \
	  handle_client_manage.c \
	  handle_client_utils.c \
	  handle_client_auth.c \
	  handle_client_data.c \
	  utils.c \
	  commands.c \
	  commands_mode.c \
	  command_help.c \
	  command_retr.c \
	  command_stor.c \
	  command_list.c \
	  command_move.c \

OBJ	= $(addprefix src/, $(SRC:.c=.o))

$(NAME):	$(OBJ)
		$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

all:	$(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

