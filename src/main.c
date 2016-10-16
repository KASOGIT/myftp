/*
** main.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp/src
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Tue May  3 13:29:32 2016 
** Last update Sun May 15 14:10:58 2016 
*/

#include "server.h"

static void usage()
{
  printf("Usage : ./server port path\n");
}

int		main(int ac, char **av)
{
  t_server	*server;

  if (ac == 3)
    {
      server = malloc(sizeof(t_server));
      if (server == NULL)
	{
	  fprintf(stderr, "Main error: malloc server\n");
	  exit(EXIT_FAILURE);
	}
      server_init(server, atoi(av[1]), av[2]);
      server->server_handle_client(server);
      server_destroy(server);
      free(server);
    }
  else
    usage();
  return (0);
}
