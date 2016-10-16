/*
** commands.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp/src
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu May  5 17:24:51 2016 
** Last update Sun May 15 14:07:03 2016 
*/

#include "commands.h"

void	quit(t_handle_client *this, const char *msg)
{
  if (size_wordtab(this->_args) == 0)
    {
      this->handle_client_send_msg(this, msg);
      handle_client_destroy(this);
      exit(EXIT_SUCCESS);
    }
  this->handle_client_send_msg(this, "500 quit\r\n");
}

void	dele(t_handle_client *this, const char *msg)
{
  if (size_wordtab(this->_args) == 1)
    {
      if (remove(this->_args[0]) != 0)
	this->handle_client_send_msg(this, "500 dele\r\n");
      else
	this->handle_client_send_msg(this, msg);
    }
  else
    this->handle_client_send_msg(this, "500 dele\r\n");
}

void	pwd(t_handle_client *this, __attribute__((unused))const char *msg)
{
  char	buff_msg[4096];

  if (size_wordtab(this->_args) == 0)
    {
      sprintf(buff_msg, "257 %s created.\r\n", this->_wdir);
      this->handle_client_send_msg(this, buff_msg);
      return ;
    }
  this->handle_client_send_msg(this, "500 pwd\r\n");
}

void	noop(t_handle_client *this, const char *msg)
{
  if (size_wordtab(this->_args) == 0)
    {
      this->handle_client_send_msg(this, msg);
    }
  else
    this->handle_client_send_msg(this, "500 noop\r\n");
}
