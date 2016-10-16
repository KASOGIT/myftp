/*
** socket_manage.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sun May 15 10:32:58 2016 
** Last update Sun May 15 14:45:38 2016 
*/

#include "socket.h"

void	socket_error(t_socket *this, const char *err_msg)
{
  fprintf(stderr,
	  "[%d] Socket error on func: %s\n",
	  (int)getpid(), err_msg);
  socket_destroy(this);
  exit(EXIT_FAILURE);
}

void	socket_destroy(t_socket *this)
{
  if (this->_fd)
    {
      if (close(this->_fd) == -1)
	fprintf(stderr,
		"[%d] Socket error on func: close\n",
		getpid());
    }
}

static void	socket_init_attr(t_socket *this, int port)
{
  int		pr;

  pr = 1;
  socket_set_methods(this);
  this->_port = port;
  this->_pe = getprotobyname("TCP");
  if (this->_pe == NULL)
    socket_error(this, "getprotobyname");
  this->_fd = socket(AF_INET, SOCK_STREAM, this->_pe->p_proto);
  setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
	     &pr, sizeof(int));
  if (this->_fd == -1)
    socket_error(this, "socket");
  this->s_in.sin_family = AF_INET;
  this->s_in.sin_port = htons(this->_port);
}

void			socket_init(t_socket *this, int port, char *addr)
{
  struct in_addr	s_in_data;

  socket_init_attr(this, port);
  if (addr == NULL)
    {
      this->s_in.sin_addr.s_addr = INADDR_ANY;
      this->socket_bind(this);
    }
  else
    {
      if (inet_aton(addr, &s_in_data) == 0)
	socket_error(this, "inet_aton");
      this->s_in.sin_addr = s_in_data;
    }
}
