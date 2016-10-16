/*
** server.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Wed May  4 13:03:19 2016 
** Last update Sun May 15 10:45:46 2016 
*/

#include "server.h"

static void	server_listen(t_server *this);
static void	server_accept(t_server *this, t_handle_client *client);
static void	server_handle_client(t_server *this);

void	server_set_methods(t_server *this)
{
  this->server_listen = &server_listen;
  this->server_accept = &server_accept;
  this->server_handle_client = &server_handle_client;
}

static void	server_listen(t_server *this)
{
  this->_sock->socket_listen(this->_sock);
}

static void	server_accept(t_server *this, t_handle_client *client)
{
  socklen_t	len;

  len = sizeof(client->_s_in);
  client->_fd = accept(this->_sock->_fd,
		       (struct sockaddr *)&client->_s_in,
		       &len);
  if (client->_fd == -1)
    server_error(this, "accept");
}

static void		server_handle_client(t_server *this)
{
  t_handle_client	client;

  this->server_listen(this);
  while (1)
    {
      handle_client_init(&client, this->_wdir);
      this->server_accept(this, &client);
      if (fork() == 0)
	{
	  if (close(this->_sock->_fd) == -1)
	    server_error(this, "close");
	  client.handle_client_routine(&client);
	}
      else
	{
	  if (close(client._fd) == -1)
	    server_error(this, "close");
	}
    }
}
