/*
** commands_mode.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sun May 15 12:24:13 2016 
** Last update Sun May 15 12:44:44 2016 
*/

#include "commands.h"

static void	pasv_set_data(t_handle_client *this,
			      char **buff_msg,
			      char **buff_port,
			      char **tmp)
{
  srand(time(NULL));
  this->_data._ip = inet_ntoa(this->_s_in.sin_addr);
  this->_data._port = rand() % 3000 + 1024;
  this->_data._data_mode = PASV;
  *buff_msg = malloc(sizeof(char) * 256);
  *buff_port = malloc(sizeof(char) * 256);
  *tmp = strdup(this->_data._ip);
  sprintf(*buff_msg, "227 Entering Passive Mode (");
}

static void	pasv_get_split_ip(char **buff_msg, char **tmp)
{
  char		*get;
  int		i;

  i = 0;
  while ((get = strsep(tmp, ".")) != NULL && i < 4)
    {
      if (i < 3)
	*buff_msg = strcat(strcat(*buff_msg, get), ",");
      else
	*buff_msg = strcat(*buff_msg, get);
      i++;
    }
}

void	pasv(t_handle_client *this,
	     __attribute__((unused))const char *msg)
{
  char	*buff_msg;
  char	*tmp;
  char	*buff_port;

  if (size_wordtab(this->_args) == 0)
    {
      pasv_set_data(this, &buff_msg, &buff_port, &tmp);
      pasv_get_split_ip(&buff_msg, &tmp);
      sprintf(buff_port, ",%d,%d).\r\n",
	      this->_data._port / 256, this->_data._port % 256);
      buff_msg = strcat(buff_msg, buff_port);
      this->handle_client_send_msg(this, buff_msg);
      free(tmp);
      free(buff_msg);
      free(buff_port);
      this->handle_client_sock_data_create(this);
    }
  else
    this->handle_client_send_msg(this, "500 pasv\r\n");
}

void	port(t_handle_client *this, const char *msg)
{
  if (size_wordtab(this->_args) == 1)
    {
      if (get_ip_port(this->_args[0],
		      &this->_data._ip, &this->_data._port) == -1)
	{
	  this->handle_client_send_msg(this, "500 port\r\n");
	}
      else
	{
	  this->_data._data_mode = ACTV;
	  this->handle_client_send_msg(this, msg);
	  this->handle_client_sock_data_create(this);
	}
    }
  else
    this->handle_client_send_msg(this, "500 port\r\n");
}
