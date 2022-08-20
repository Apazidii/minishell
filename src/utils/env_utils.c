#include "minishell.h"

// âàðèàíòû:

// Name_01 				-> 		Name_01
// $Name_01 			-> 		Olga
// Hello$Name_01 		-> 		HelloOlga
// Hello$Name_01$Name_02 -> 	HelloOlgaAlex
// Hello$Name_01_klock 	-> 		Hello

char *find_in_env(t_list *env, char *key)
{
	t_dict *c;
	int 	l;

	l = ft_strlen(key);
	while (env)
	{
		c = (t_dict *)env->content;
		if (ft_strncmp(c->key, key, l) == 0)
			return (c->value);
		env = env->next;
	}
	return (NULL);
}

char *ft_alloc_mem_linepair(char *str1, char* str2, size_t *len1, size_t *len2)
{
	char *res;

	if (!str1 || !str2)
		return (NULL);
	*len1 = ft_strlen(str1);
	*len2 = ft_strlen(str2);
	res = (char *)ft_calloc(sizeof(char) , (*len1 + *len2 + 1));
	if (!res)
		return (NULL);
	return (res);
}

char *ft_strnconcat(char *dest, char *src, size_t start, size_t end)
{
	char *res;
	size_t len_dest;
	size_t len_src;
	size_t i;
	size_t j;

	if (!dest || !src)
		return (NULL);
	if (start > end || start > (size_t)ft_strlen(src) || end > (size_t)ft_strlen(src))
		return (NULL);
	res = ft_alloc_mem_linepair(dest, src, &len_dest, &len_src);
	if (!res)
		return (NULL);
	i = 0;
	while (dest[i] != '\0')
	{
		res[i] = dest[i];
		i++;
	}
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

char *get_perem(char *str, size_t start, size_t end)
{
	char *res;
	size_t i;

	if (end < start)
		return (NULL);
	res = (char *)ft_calloc(sizeof(char) ,(end - start + 1));
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
	size_t i;
	size_t start;
	char *perem;
	char *res;
	char *key;



	i = 0;


	res = (char *)ft_calloc(1, 1);

	if (!(*str))
		return (0); // (?)

	while ((*str)[i])
	{
		if ((*str)[i] == '$' && (*str)[i + 1])
		{
			i++;
			start = i;
			while (ft_isalnum((*str)[i]) || (*str)[i] == '_')
				i++;
			perem = get_perem(*str, start, i);
			key = find_in_env(env, perem);
			free(perem);
			if (key != NULL)
				res = ft_strnconcat(res, key, 0, ft_strlen(key));
		}
		else if ((*str)[i] == '$' && !(*str)[i + 1])
		{
			res = ft_strnconcat(res, (*str), i, i + 1);
			i++;
		}

		if ((*str)[i] && (*str)[i] != '$')
		{
			start = i;
			while (!((*str)[i] == '\0' || (*str)[i] == '$'))
			{
				i++;
			}
			res = ft_strnconcat(res, *str, start, i);
		}
	}

//	free(*str);
	*str = res;
	return (SUCCES);
}