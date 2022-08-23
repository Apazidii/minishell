#ifndef BUILTIN_H
#define BUILTIN_H

int valid_env(char *s);
void sort_list(t_list *start);
void print_env(void *content);
int	add_env(char *s, t_base *base);

#endif
