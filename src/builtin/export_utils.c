#include "../../hdr/minishell.h"
#include "builtin.h"

void	print_env(void *content)
{
	t_dict	*c;

	c = (t_dict *)content;
	printf("declare -x %s", c->key);
	if (c->value == NULL)
		printf("\n");
	else
		printf("=\"%s\"\n", c->value);
}

/* function to swap data of two nodes a and b*/
void	swap(t_list *a, t_list *b)
{
	void	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

void	sort_list(t_list *start)
{
	int		swapped;
	t_list	*ptr1;
	t_list	*lptr;

	if (start == NULL)
		return ;
	lptr = NULL;
	while (1)
	{
		swapped = 0;
		ptr1 = start;
		while (ptr1->next != lptr)
		{
			if (ft_strncmp(((t_dict *)ptr1->content)->key, \
						((t_dict *)ptr1->next->content)->key,
					ft_strlen(((t_dict *)ptr1->content)->key) + 1) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
		if (!swapped)
			break ;
	}
}

int	valid_env(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalnum(*s) && *s != '_')
		return (1);
	while (s[i] != '\0')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_' && s[i] != '=')
			return (1);
		i++;
	}
	return (0);
}
