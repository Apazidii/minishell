/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:25:11 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/29 16:54:10 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

char	*skip_spaces(char *s);
int		check_qutes(char *s);
int		is_metachar(char c);
int		is_space(char c);

int		pipe_or_lexer(char **command, t_list **lexer);
int		redirect_lexer(char **command, t_list **lexer);
int		reverse_redirect_lexer(char **command, t_list **lexer);
int		str_lexer(char **command, t_list **lexer);
int		quote_lexer(char **command, t_list **lexer);

int		add_to_lst_lexer(t_token *token, t_list **lexer);

#endif
