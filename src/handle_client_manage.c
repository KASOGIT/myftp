/*
** handle_client_manage.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sun May 15 10:48:51 2016 
** Last update Sun May 15 10:50:05 2016 
*/

#include "handle_client.h"

void	handle_client_error(t_handle_client *this, const char *err_msg)
{
  fprintf(stderr,
	  "[%d] Handle client error on func: %s\n",
	  (int)getpid(), err_msg);
  handle_client_destroy(this);
  exit(EXIT_FAILURE);
}

void	handle_client_init(t_handle_client *this, char *wdir)
{
  handle_client_set_methods(this);
  this->_wdir = realpath(wdir, NULL);
  this->_data._data_mode = NONE;
  this->_data._port = 0;
  this->_data._ip = malloc(sizeof(char) * 256);
}

void	handle_client_destroy(t_handle_client *this)
{
  if (close(this->_fd) == -1)
    {
      fprintf(stderr,
	      "[%d] Handle client error on func: close\n",
	      (int)getpid());
      exit(EXIT_FAILURE);
    }
}
