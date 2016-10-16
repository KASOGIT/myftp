/*
** utils.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp/src
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu May  5 17:04:20 2016 
** Last update Tue May 10 20:08:13 2016 
*/

#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char	**str_to_wordtab(char *str);
int	size_wordtab(char **tab);
void	free_wordtab(char **tab);
void	show_wordtab(char **tab);
int	get_ip(char *arg, char **ip);
int	get_ip_port(char *arg, char **ip, int *port);

#endif /* !UTILS_H_ */
