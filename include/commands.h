/*
** commands.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu May  5 17:17:32 2016 
** Last update Sun May 15 14:00:47 2016 
*/

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "handle_client.h"

typedef struct s_handle_client	t_handle_client;

typedef struct	s_cmd
{
  char		*cmd;
  char		*msg;
  char		*info;
  void		(*func_cmd)(t_handle_client *this,
			    const char *msg);
}		t_cmd;

extern struct s_cmd	g_cmd[14];

void	cwd(t_handle_client *this, const char *msg);
void	cdup(t_handle_client *this, const char *msg);
void	quit(t_handle_client *this, const char *msg);
void	dele(t_handle_client *this, const char *msg);
void	pwd(t_handle_client *this, const char *msg);
void	pasv(t_handle_client *this, const char *msg);
void	port(t_handle_client *this, const char *msg);
void	help(t_handle_client *this, const char *msg);
void	noop(t_handle_client *this, const char *msg);
void	retr(t_handle_client *this, const char *msg);
void	stor(t_handle_client *this, const char *msg);
void	list(t_handle_client *this, const char *msg);

#endif /* !COMMANDS_H_ */
