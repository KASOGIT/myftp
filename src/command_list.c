/*
** command_list.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sun May 15 13:43:30 2016 
** Last update Sun May 15 17:58:22 2016 
*/

#include "commands.h"

static void	fill_list_result(t_handle_client *this,
				 char *cmd)
{
  FILE		*in;
  char		buff[512];
  char		*result;

  result = malloc(sizeof(char) * 4096);
  result[0] = '\0';
  in = popen(cmd, "r");
  if (in)
    {
      while (fgets(buff, sizeof(buff), in) != NULL)
	result = strcat(result, buff);
    }
  this->handle_client_send_msg_data(this, result);
  free(result);
  pclose(in);
  this->handle_client_sock_data_close(this);
  this->handle_client_send_msg(this,
			       "226 Closing data connection.\r\n");
}

void	list(t_handle_client *this,
	     __attribute__((unused))const char *msg)
{
  char	cmd[256];

  if (this->_data._data_mode == NONE)
    {
      this->handle_client_send_msg(this,
				   "425 use PORT or PASV first\r\n");
      return ;
    }
  if (size_wordtab(this->_args) == 0)
    sprintf(cmd, "ls -l %s", this->_wdir);
  else if (size_wordtab(this->_args) == 1)
    sprintf(cmd, "ls -l %s", this->_args[0]);
  else
    {
      this->handle_client_send_msg(this, "500 list\r\n");
      return ;
    }
  this->handle_client_send_msg(this,
  "150 File status okay; about to open data connection.\r\n");
  this->handle_client_sock_data_connect(this);
  fill_list_result(this, cmd);
}
