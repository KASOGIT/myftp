/*
** handle_client_auth.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp/src
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sun May 15 11:11:43 2016 
** Last update Sun May 15 23:22:38 2016 
*/

#include "handle_client.h"

static char	*step_id(t_handle_client *this)
{
  while (1)
    {
      this->handle_client_read_cmd(this);
      if (this->_cmd)
	{
	  if (this->_fmt
	      && size_wordtab(this->_args) == 1
	      && strncmp(this->_cmd, g_cmd[0].cmd,
			 strlen(g_cmd[0].cmd)) == 0)
	    {
	      this->handle_client_send_msg(this, g_cmd[0].msg);
	      return (this->_args[0]);
	    }
	  else
	    this->handle_client_send_msg(this,
	    "530 Please login with USER AND PASS\r\n");
	}
    }
}

static int	step_passwd(t_handle_client *this)
{
  this->handle_client_read_cmd(this);
  if (this->_cmd)
    {
      if (this->_fmt
	  && size_wordtab(this->_args) == 0
	  && strncmp(this->_cmd, g_cmd[1].cmd,
		     strlen(g_cmd[1].cmd)) == 0)
	{
	  return (1);
	}
    }
  return (-1);
}

void	handle_client_wait_auth(t_handle_client *this)
{
  char	*id;
  int	ret;

  id = step_id(this);
  ret = step_passwd(this);
  if (strcmp(id, "Anonymous") == 0 && ret == 1)
    this->handle_client_send_msg(this, g_cmd[1].msg);
  else
    {
      this->handle_client_send_msg(this, "530 bad cmd auth\r\n");
      handle_client_wait_auth(this);
    }
}
