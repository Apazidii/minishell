/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:44:49 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/29 16:54:11 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*now;
	void	*c;

	if (!(lst && f))
		return (NULL);
	new = ft_lstnew(f(lst->content));
	now = new;
	while (lst->next)
	{
		lst = lst->next;
		c = f(lst->content);
		now->next = ft_lstnew(c);
		if (!(now->next) || c == NULL)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		now = now->next;
	}
	return (new);
}
