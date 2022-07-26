/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:36:54 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/29 16:54:11 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

int	find_rav(char *s)
{
	while (*s)
	{
		if (*s == '=')
			return (1);
		s++;
	}
	return (0);
}

t_dict	*create_new_dict(char *key, char *value)
{
	t_dict	*c;

	c = ft_calloc(sizeof(t_dict), 1);
	if (c == NULL)
	{
		perror("export");
		errno = 0;
		return (NULL);
	}
	c->key = ft_strdup(key);
	c->value = ft_strdup(value);
	if ((c->key == NULL && key != NULL) || (c->value == NULL && value != NULL))
	{
		if (c->key != NULL && key != NULL)
			free(c->key);
		if (c->value != NULL && value != NULL)
			free(c->value);
		free(c);
		perror("export");
		errno = 0;
		return (NULL);
	}
	return (c);
}

int	without_key(char *s, t_list *env)
{
	t_dict	*c;
	t_dict	*d;

	d = find_dict_in_env(env, s);
	if (d != NULL)
		return (SUCCES);
	c = create_new_dict(s, NULL);
	if (c == NULL)
		return (MALLOC_ERROR);
	ft_lstadd_back(&env, ft_lstnew(c));
	if (errno != 0)
	{
		perror("export");
		errno = 0;
		return (MALLOC_ERROR);
	}
	return (SUCCES);
}

int	with_key(char *s, t_list *env)
{
	t_dict	*c;
	t_dict	*d;

	d = parse_line_envp(s);
	if (d == NULL)
		return (MALLOC_ERROR);
	c = find_dict_in_env(env, d->key);
	if (c == NULL)
	{
		ft_lstadd_back(&env, ft_lstnew(d));
		if (errno != 0)
		{
			perror("export");
			errno = 0;
			return (MALLOC_ERROR);
		}
		return (SUCCES);
	}
	free(c->key);
	c->key = d->key;
	free(c->value);
	c->value = d->value;
	free(d);
	return (SUCCES);
}

int	add_env(char *s, t_base *base)
{
	if (valid_env(s))
	{
		ft_putstr_fd("minishell: export: \'", 2);
		ft_putstr_fd(s, 2);
		ft_putendl_fd("\': not a valid identifier", 2);
		return (SUCCES);
	}
	if (find_rav(s) == 0)
		return (without_key(s, base->env_lst));
	return (with_key(s, base->env_lst));
}
