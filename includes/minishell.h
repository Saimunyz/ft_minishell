/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:10:37 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/16 14:15:51 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "stdio.h"
# include "term.h"
# include "termios.h"
# include "libft.h"
# include "errno.h"
# include "string.h"

# define BUFF_SIZE 10

# define GET_DATA_ERR 1

typedef struct s_term
{
	struct termios	current;
	struct termios	basic;
}				t_term;

void	ft_check_errno(void);
void	ft_change_term_mode(t_term *term);
int		ft_get_term_info(void);
int		ft_parse(char *line, int len);
void	ft_pwd(void);

#endif
