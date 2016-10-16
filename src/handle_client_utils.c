/*
** handle_client_utils.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp/src
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sun May 15 11:04:46 2016 
** Last update Sun May 15 23:07:23 2016 
*/

#include "handle_client.h"

void		handle_client_send_msg(t_handle_client *this,
				       const char *msg)
{
  ssize_t	ret;

  ret = write(this->_fd, msg, strlen(msg));
  if (ret == -1)
    handle_client_error(this, "write");
}

void		handle_client_send_msg_data(t_handle_client *this,
					    const char *msg)
{
  ssize_t	ret;

  if (this->_data._data_mode == ACTV)
    {
      ret = write(this->_data._sock_data->_fd, msg, strlen(msg));
      if (ret == -1)
	handle_client_error(this, "write");
    }
  else if (this->_data._data_mode == PASV)
    {
      ret = write(this->_data._fd, msg, strlen(msg));
      if (ret == -1)
	handle_client_error(this, "write");
    }
}

void	handle_client_check_fmt(t_handle_client *this, char **cmd)
{
  int	i;

  i = 0;
  while ((*cmd)[i] && (*cmd)[i] != '\r' && (*cmd)[i] != '\n')
    {
      i++;
    }
  if ((*cmd)[i] && strlen((*cmd) + i) == 2
      && strncmp("\r\n", (*cmd) + i, 2) == 0)
    {
      this->_fmt = 1;
    }
  else
    {
      this->_fmt = 0;
    }
  (*cmd)[i] = '\0';
}

void		handle_client_read_cmd(t_handle_client *this)
{
  char		read_cmd[256];
  char		*cmd;
  ssize_t	nb;
  char		**pars;

  memset(read_cmd, 0, 256);
  nb = read(this->_fd, read_cmd, 256);
  if (nb == -1)
    handle_client_error(this, "read");
  if (strlen(read_cmd) > 2)
    {
      cmd = strdup(read_cmd);
      this->handle_client_check_fmt(this, &cmd);
      pars = str_to_wordtab(cmd);
      if (pars == NULL)
	handle_client_error(this, "str_to_wordtab");
      this->_cmd = pars[0];
      this->_args = pars + 1;
      free(cmd);
    }
  else
    {
      this->_cmd = NULL;
      this->_args = NULL;
    }
}
