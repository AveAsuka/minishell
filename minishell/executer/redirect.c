/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:44:49 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/21 16:46:50 by lbrianna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_output(char *file_name, char *type, t_redir *redir_str)
{	
	if (ft_strncmp_mod(">", type, 1))
	{
		redir_str->outfile = open(file_name, O_CREAT \
			| O_RDWR | O_TRUNC, 0644);
		if (redir_str->outfile == -1)
			printf("Error!\n");
	}
	else
	{
		redir_str->outfile = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (redir_str->outfile == -1)
			printf("Error!\n");
	}
	if (dup2(redir_str->outfile, 1) == -1)
		ft_perror_exit_child("Inside child dup error", 1);
	close (redir_str->outfile);
}

void	redirect_input(char *file_name, t_redir *redir_str)
{
	redir_str->infile = open(file_name, O_RDONLY);
	if (redir_str->infile == -1)
		printf("%s: No such file or directory\n", file_name);
	if (dup2(redir_str->infile, 0) == -1)
		ft_perror_exit_child("Inside child dup error", 1);
	close (redir_str->infile);
}

void	stop_word(char *limiter, t_redir *redir_str, int tmpin)
{
	if (redir_str->infile != 0)
	{
		redir_str->infile = 0;
		if (dup2 (tmpin, 0) == -1)
			ft_perror_exit_child("Inside child dup error", 1);
	}
	stop_norme(limiter);
	redir_str->infile = open(".here_doc", O_RDONLY);
	if (redir_str->infile == -1)
		printf("%s: No such file or directory\n", ".here_doc");
	if (dup2(redir_str->infile, 0) == -1)
		ft_perror_exit_child("Inside child dup error", 1);
	close (redir_str->infile);
}

void	redirect_action(char *type, char *file, t_redir *redir_str, int tmpin)
{
	if (ft_strncmp_mod(">", type, 1) || ft_strncmp_mod(">>", type, 2))
		redirect_output(file, type, redir_str);
	else if (ft_strncmp_mod("<", type, 1))
		redirect_input(file, redir_str);
	else if (ft_strncmp_mod("<<", type, 2))
		stop_word(file, redir_str, tmpin);
}

int	redirect_enumeration(t_cmd *tmp, int tmpin)
{
	int	i;

	i = 0;
	if (tmp->redir->type && tmp->redir->file)
	{
		while (tmp->redir[i].type)
		{
			redirect_action(tmp->redir[i].type, tmp->redir[i].file,
				tmp->redir, tmpin);
			i++;
		}
	}
	return (i);
}
