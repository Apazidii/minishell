/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olga <olga@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:39:25 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/25 18:45:12 by olga             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/minishell.h"

char	*find_in_env(t_list *env, char *key)
{
	t_dict	*c;
	size_t	len;

	len = ft_strlen(key);
	while (env)
	{
		c = (t_dict *)env->content;
		if (ft_strncmp(c->key, key, len) == 0)
			return (c->value);
		env = env->next;
	}
	return (NULL);
}

char	*ft_alloc_mem_linepair(char *str1, char *str2,
	size_t *len1, size_t *len2)
{
	char	*res;

	if (!str1 || !str2)
		return (NULL);
	*len1 = ft_strlen(str1);
	*len2 = ft_strlen(str2);
	res = (char *)ft_calloc(sizeof(char), (*len1 + *len2 + 1));
	if (!res)
		return (NULL);
	return (res);
}

char	*ft_strnconcat(char *dest, char *src, size_t start, size_t end)
{
	char	*res;
	size_t	len_dest;
	size_t	len_src;
	size_t	i;
	size_t	j;

	if (!dest || !src)
		return (NULL);
	if (start > (size_t)ft_strlen(src) || end > (size_t)ft_strlen(src))
		return (NULL);
	res = ft_alloc_mem_linepair(dest, src, &len_dest, &len_src);
	if (!res)
		return (NULL);
	copy_from_dest(dest, &res, &i);
	j = 0;
	while (j + start < end)
	{
		res[i] = src[j + start];
		i++;
		j++;
	}
	res[i] = '\0';
	free(dest);
	return (res);
}

char	*get_perem(char *str, size_t start, size_t end)
{
	char	*res;
	size_t	i;

	if (end < start)
		return (NULL);
	res = (char *)ft_calloc(sizeof(char), (end - start + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i + start < end)
	{
		res[i] = str[i + start];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	insert_var(char **str, t_list *env)
{
	size_t	i;
	size_t	start;
	char	*perem;
	char	*res;
	char	*key;

	checks_and_init(&i, &res);
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && (*str)[i + 1] && (*str)[i + 1] != '?')
		{
			perem = iterate_per_perem(&i, &start, *str);
			key = find_in_env(env, perem);
			free(perem);
			if (key != NULL)
				res = ft_strnconcat(res, key, 0, ft_strlen(key));
			// free(key);
		}
		else if ((*str)[i] == '$' && !(*str)[i + 1])
			get_last_dollar(&i, *str, &res);
		else if ((*str)[i] == '$' && (*str)[i + 1] && (*str)[i + 1] == '?')
		{
			key = find_in_env(env, "?");
			res = ft_strnconcat(res, key, 0, ft_strlen(key));
			// free(key);
			i += 2;
		}
		get_remaining_characters(&start, &i, (*str), &res);
	}
	*str = res;
	return (SUCCES);
}