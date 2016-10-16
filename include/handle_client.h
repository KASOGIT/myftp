/*
** handle_client.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Wed May  4 14:43:11 2016 
** Last update Sun May 15 17:57:00 2016 
*/

#ifndef HANDLE_CLIENT_H_
#define HANDLE_CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "socket.h"
#include "commands.h"
#include "utils.h"

typedef enum		e_data_mode
  {
    NONE,
    PASV,
    ACTV
  }			t_data_mode;

typedef struct		s_data_sock
{
  t_data_mode		_data_mode;
  t_socket		*_sock_data;
  int			_port;
  char			*_ip;
  struct sockaddr_in	_s_in;
  int			_fd;
}			t_data_sock;

typedef struct		s_handle_client
{
  t_data_sock		_data;
  struct sockaddr_in	_s_in;
  int			_fd;
  char			*_wdir;
  char			*_ip;
  char			*_cmd;
  char			**_args;
  int			_fmt;
  
  void	(*handle_client_read_cmd)(struct s_handle_client *this);
  void	(*handle_client_wait_auth)(struct s_handle_client *this);
  void	(*handle_client_send_msg)(struct s_handle_client *this,
				  const char *msg);
  void	(*handle_client_send_msg_data)(struct s_handle_client *this,
				       const char *msg);
  void	(*handle_client_routine)(struct s_handle_client *this);
  void	(*handle_client_check_fmt)(struct s_handle_client *this,
				   char **cmd);
  int	(*handle_client_sock_data_create)(struct s_handle_client *this);
  int	(*handle_client_sock_data_close)(struct s_handle_client *this);
  int	(*handle_client_sock_data_connect)(struct s_handle_client *this);
}			t_handle_client;

void	handle_client_init(t_handle_client *this, char *wdir);
void	handle_client_error(t_handle_client *this,
			    const char *err_msg);
void	handle_client_set_methods(t_handle_client *this);
void	handle_client_destroy(t_handle_client *this);
void	handle_client_read_cmd(t_handle_client *this);
void	handle_client_send_msg(t_handle_client *this,
			       const char *msg);
void	handle_client_send_msg_data(t_handle_client *this,
				    const char *msg);
void	handle_client_wait_auth(t_handle_client *this);
void	handle_client_routine(t_handle_client *this);
void	handle_client_check_fmt(t_handle_client *this, char **cmd);
int	handle_client_sock_data_create(t_handle_client *this);
int	handle_client_sock_data_close(t_handle_client *this);
int	handle_client_sock_data_connect(t_handle_client *this);

#endif /* !HANDLE_CLIENT_H_ */
