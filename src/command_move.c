/*
** command_move.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sun May 15 13:58:03 2016 
** Last update Sun May 15 17:44:31 2016 
*/

#include "commands.h"

void	cwd(t_handle_client *this, const char *msg)
{
  char	*rpath;

  if (size_wordtab(this->_args) == 1)
    {
      rpath = realpath(this->_args[0], NULL);
      if (rpath != NULL)
	{
	  if (chdir(rpath) == 0)
	    {
	      if (this->_wdir)
		free(this->_wdir);
	      this->_wdir = rpath;
	      this->handle_client_send_msg(this, msg);
	      return ;
	    }
	}
      else
	this->handle_client_send_msg(this,
	"550 Failed to change directory.\r\n");
    }
  else
    this->handle_client_send_msg(this, "500 cwd\r\n");
}

void	cdup(t_handle_client *this, const char *msg)
{
  char	*rpath;

  if (size_wordtab(this->_args) == 0)
    {
      rpath = realpath("..", NULL);
      if (rpath != NULL)
	{
	  if (chdir(rpath) == 0)
	    {
	      if (this->_wdir)
		free(this->_wdir);
	      this->_wdir = rpath;
	      this->handle_client_send_msg(this, msg);
	      return ;
	    }
	}
    }
  this->handle_client_send_msg(this, "500 cdup\r\n");
}
