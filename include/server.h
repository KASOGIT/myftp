/*
** server.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp/include
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Tue May  3 13:32:11 2016 
** Last update Sun May 15 14:01:48 2016 
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "socket.h"
#include "handle_client.h"

typedef struct	s_server
{
  char		*_wdir;
  t_socket	*_sock;
  void		(*server_listen)(struct s_server *this);
  void		(*server_accept)(struct s_server *this,
				 t_handle_client *client);
  void		(*server_handle_client)(struct s_server *this);
}		t_server;

void	server_error(t_server *this, const char *err_msg);
void	server_init(t_server *this, int port, char *wdir);
void	server_set_methods(t_server *this);
void	server_destroy(t_server *this);

#endif /* !SERVER_H_ */
