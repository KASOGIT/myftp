/*
** command_stor.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sun May 15 13:12:40 2016 
** Last update Sun May 15 18:01:14 2016 
*/

#include "commands.h"

static void	write_file(t_handle_client *this)
{
  int		fd;
  int		br;
  char		buff_data[4096];
  FILE		*fw;

  fd = this->_data._data_mode == ACTV ?
    this->_data._sock_data->_fd : this->_data._fd;
  fw = fopen(this->_args[0], "w+");
  if (fw == NULL)
    {
      this->handle_client_send_msg(this, "500 stor\r\n");
      return ;
    }
  while ((br = read(fd, buff_data, 4096)))
    {
      buff_data[br] = '\0';
      fwrite(buff_data, br, 1, fw);
    }
  fclose(fw);
  this->handle_client_sock_data_close(this);
  this->handle_client_send_msg(this,
			       "226 Closing data connection.\r\n");
}

void	stor(t_handle_client *this,
	     __attribute__((unused))const char *msg)
{
  if (this->_data._data_mode == NONE)
    {
      this->handle_client_send_msg(this, "425 use PORT or PASV first\r\n");
      return ;
    }
  if (size_wordtab(this->_args) == 1)
    {
      this->handle_client_send_msg(this,
      "150 File status okay; about to open data connection.\r\n");
      this->handle_client_sock_data_connect(this);
      write_file(this);
    }
  else
    this->handle_client_send_msg(this, "500 stor\r\n");
}
