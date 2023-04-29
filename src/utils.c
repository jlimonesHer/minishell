/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlimones <jlimones@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:19:13 by jlimones          #+#    #+#             */
/*   Updated: 2023/04/29 13:19:17 by jlimones         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/**
 * @brief la funcion sale si el parametro pasado es exit
 * 
 * @param cmd string del comando pasado desde shell
 */
void	ft_exit(t_command *cmds)
{
	ft_free_struct(cmds);
}

void	free_quotes(t_expand *e)
{
	free(e->var);
	free(e->env);
	free(e->line);
	free(e->sub);
	e->var = NULL;
	e->env = NULL;
	e->line = NULL;
	e->sub = NULL;
}

void	free_first_quotes(t_expand *e)
{
	free(e->var);
	free(e->env);
	e->var = NULL;
	e->env = NULL;
}

void	ft_change_va_report(char ***env, char ***va_export, int b)
{
	char	*b2;
	char	*itoa;

	itoa = ft_itoa(b);
	b2 = ft_strjoin("?=", itoa);
	free(itoa);
	free((*env)[0]);
	(*env)[0] = ft_strdup(b2);
	free((*va_export)[0]);
	(*va_export)[0] = ft_strdup(b2);
	free(b2);
}
