/*
** exceptions.c for  in /home/penava_b/perso/test
** 
** Made by bastien penavayre
** Login   <penava_b@epitech.net>
** 
** Started on  Tue Jul 28 23:26:37 2015 bastien penavayre
** Last update Sun Aug 30 04:44:40 2015 bastien penavayre
*/

#include	<stdlib.h>
#include	<string.h>
#include	"exceptions.h"

static jmp_buf	env;
static t_list	*list;
static t_node	*last;

__attribute__((constructor))
static void    	init_list(void)
{
  list = CREATE_LIST();
}

__attribute__((destructor))
static void	end_list(void)
{
  delete_list(list);
}

t_list		*get_list(void)
{
  return list;
}

void		__throw_func(char *type, size_t size, void *arg)
{
  __push_type(type, size, list, arg);
  longjmp(env, -1);
}


jmp_buf		*__get_jump()
{
  return &env;
}

char		__catch_func(char *type)
{
  t_node	*tmp;

  if (type == NULL || *type == '\0')
    return 42;
  tmp = list->start;
  while (tmp != NULL)
    {
      if (strcmp(type, tmp->type) == 0)
	{
	  last = tmp;
	  return 42;
	}
    }
  return 0;
}

void		fill_exception(void *arg)
{
  pop_if_same(arg, last, list);
}
