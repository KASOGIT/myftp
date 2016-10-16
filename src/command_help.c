/*
** command_help.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by Adam soto
** Login   soto_a<adam.soto@epitech.net>
** 
** Started on  Sun May 15 12:53:04 2016 
** Last update Sun May 15 14:25:34 2016 
*/

#include "commands.h"

static void	fill_help_cmd(t_handle_client *this,
			      char **buff_msg)
{
  int		i;

  i = 0;
  sprintf(*buff_msg, "214 ");
  while (i < 14)
    {
      *buff_msg = strcat(strcat(*buff_msg, g_cmd[i].cmd), " ");
      i++;
    }
  *buff_msg = strcat(*buff_msg, "\r\n\0");
  this->handle_client_send_msg(this, *buff_msg);
}

static void	fill_help_info(t_handle_client *this,
			       char **buff_msg)
{
  int		i;

  i = 0;
  while (i < 14)
    {
      if (strncmp(this->_args[0],
		  g_cmd[i].cmd,
		  strlen(g_cmd[i].cmd)) == 0)
	{
	  *buff_msg = strcat(strcat(*buff_msg,
				    g_cmd[i].info), "\r\n\0");
	  this->handle_client_send_msg(this, *buff_msg);
	  i = 15;
	}
      i++;
    }
  if (i == 14)
    this->handle_client_send_msg(this,
    "504 cmd not implemented for that param\r\n");
}

void	help(t_handle_client *this,
	     __attribute__((unused))const char *msg)
{
  int	st;
  char	*buff_msg;

  st = size_wordtab(this->_args);
  buff_msg = malloc(sizeof(char) * 4096);
  memset(buff_msg, 0, 4096);
  if (st == 0)
    fill_help_cmd(this, &buff_msg);
  else if (st == 1)
    fill_help_info(this, &buff_msg);
  else
    this->handle_client_send_msg(this, "500 help\r\n");
  free(buff_msg);
}
