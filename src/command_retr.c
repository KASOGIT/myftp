/*
** command_retr.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sun May 15 13:04:40 2016 
** Last update Sun May 15 18:00:55 2016 
*/

#include "commands.h"

static void	send_file(t_handle_client *this)
{
  FILE		*fr;
  char		*data;
  long		s;

  fr = fopen(this->_args[0], "r");
  if (fr == NULL)
    {
      this->handle_client_send_msg(this, "500 retr\r\n");
      return ;
    }
  fseek(fr, 0, SEEK_END);
  s = ftell(fr);
  fseek(fr, 0, SEEK_SET);
  data = malloc(sizeof(char) * (s + 1));
  if (fread(data, s, 1, fr) != 0)
    {
      data[s] = '\0';
      this->handle_client_send_msg_data(this, data);
      free(data);
      this->handle_client_sock_data_close(this);
      this->handle_client_send_msg(this,
				   "226 Closing data connection.\r\n");
    }
  fclose(fr);
}

void	retr(t_handle_client *this, __attribute__((unused))const char *msg)
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
      send_file(this);
    }
  else
    this->handle_client_send_msg(this, "500 retr\r\n");
}
