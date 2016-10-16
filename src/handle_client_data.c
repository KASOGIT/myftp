/*
** handle_client_data.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp/src
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sun May 15 11:30:47 2016 
** Last update Sun May 15 18:26:16 2016 
*/

#include "handle_client.h"

int		handle_client_sock_data_connect(t_handle_client *this)
{
  socklen_t	len;

  if (this->_data._data_mode == ACTV)
    {
      this->_data._sock_data->socket_connect(this->_data._sock_data);
    }
  else if (this->_data._data_mode == PASV)
    {
      len = sizeof(this->_data._s_in);
      this->_data._fd = accept(this->_data._sock_data->_fd,
			       (struct sockaddr *)&this->_data._s_in,
			       &len);
      if (this->_data._fd == -1)
	handle_client_error(this, "accept");
    }
  return (1);
}

int		handle_client_sock_data_create(t_handle_client *this)
{
  if (this->_data._data_mode == NONE)
    return (-1);
  this->_data._sock_data = malloc(sizeof(t_socket));
  socket_init(this->_data._sock_data,
	      this->_data._port,
	      this->_data._ip);
  if (this->_data._data_mode == ACTV)
    {
    }
  else if (this->_data._data_mode == PASV)
    {
      this->_data._sock_data->socket_bind(this->_data._sock_data);
      this->_data._sock_data->socket_listen(this->_data._sock_data);
    }
  return (0);
}

int	handle_client_sock_data_close(t_handle_client *this)
{
  if (this->_data._data_mode == ACTV)
    {
      if (this->_data._sock_data)
	{
	  socket_destroy(this->_data._sock_data);
	  free(this->_data._sock_data);
	}
    }
  else if (this->_data._data_mode == PASV)
    {
      if (this->_data._sock_data)
	{
	  socket_destroy(this->_data._sock_data);
	  free(this->_data._sock_data);
	}
      if (close(this->_data._fd) == -1)
	handle_client_error(this, "close");
    }
  this->_data._data_mode = NONE;
  return (0);
}
