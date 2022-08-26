/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:36:57 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/26 14:41:48 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

void	set_pipe(t_list *group);
int		check_pipe(t_list *lexer);
int		check_parenthesis(t_list *lexer);
int		parse_redirect(t_list **lexer, t_group *group);
int		free_group(t_group *group);
int		parse_arg(t_list **lexer, t_group *group);
int		free_group_arg(t_arg *arg, int num_arg);

t_arg	*add_arg(t_arg *arg, int num_arg, t_token *token);

int		free_group_redirect(t_redirect *arg, int num_arg);

void	group_argue(t_group **gr);

#endif