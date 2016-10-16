/*
** handle_client.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Wed May  4 14:49:03 2016 
** Last update Sun May 15 17:57:19 2016 
*/

#include "handle_client.h"

t_cmd	g_cmd[14] =
  {
    {"USER", "331 Anonymous okay, need password.\r\n",
     "214 Specify user for authentication", NULL},
    {"PASS", "230 User logged in, proceed.\r\n",
     "214 Specify password for authentication", NULL},
    {"CWD", "250 Requested file action okay, completed.\r\n",
     "214 Change working directory", &cwd},
    {"CDUP", "200 Command okay.\r\n",
     "214 Change working directory to parent directory", &cdup},
    {"QUIT", "221 Service closing control connection.\r\n",
     "214 Disconnection",  &quit},
    {"DELE", "250 Requested file action okay, completed.\r\n",
     "214 Delete file on the server",  &dele},
    {"PWD", "257 \"PATHNAME\" created.\r\n",
     "214 Print working directory", &pwd},
    {"PASV", "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).\r\n",
     "214 Enable \"passive\" mode for data transfer", &pasv},
    {"PORT", "200 Command okay.\r\n",
     "214 Enable \"active\" mode for data transfer", &port},
    {"HELP", "214",
     "214 List available commands", &help},
    {"NOOP", "200 Command okay.\r\n",
     "214 Do nothing", &noop},
    {"RETR", "150 File status okay; about to open data connection.\r\n",
     "214 Download file from server to client", &retr},
    {"STOR", "150 File status okay; about to open data connection.\r\n",
     "214 Upload file from client to server", &stor},
    {"LIST", "150 File status okay; about to open data connection.\r\n",
     "214 List files in the current working directory", &list}
  };

void	handle_client_set_methods(t_handle_client *this)
{
  this->handle_client_read_cmd = &handle_client_read_cmd;
  this->handle_client_wait_auth = &handle_client_wait_auth;
  this->handle_client_send_msg = &handle_client_send_msg;
  this->handle_client_send_msg_data = &handle_client_send_msg_data;
  this->handle_client_routine = &handle_client_routine;
  this->handle_client_check_fmt = &handle_client_check_fmt;
  this->handle_client_sock_data_create = &handle_client_sock_data_create;
  this->handle_client_sock_data_close = &handle_client_sock_data_close;
  this->handle_client_sock_data_connect = &handle_client_sock_data_connect;
}

static void	run_cmd(t_handle_client *this)
{
  int		i;

  i = 1;
  if (this->_cmd)
    {
      if (this->_fmt)
	{
	  while (++i < 14)
	    {
	      if (strncmp(this->_cmd, g_cmd[i].cmd,
			  strlen(g_cmd[i].cmd)) == 0)
		{
		  g_cmd[i].func_cmd(this, g_cmd[i].msg);
		  i = 14;
		}
	    }
	  if (i == 14)
	    this->handle_client_send_msg(this, "500 cmd not found\r\n");
	}
      else
	this->handle_client_send_msg(this, "500 cmd bad fmt\r\n");
    }
}

void	handle_client_routine(t_handle_client *this)
{
  this->handle_client_send_msg(this, "220 Service ready for new user\r\n");
  this->handle_client_wait_auth(this);
  while (1)
    {
      this->handle_client_read_cmd(this);
      run_cmd(this);
    }
}
