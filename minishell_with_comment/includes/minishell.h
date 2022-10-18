/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:08:26 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/22 17:46:20 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h> 
# include <string.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	int				num;
}	t_env;

typedef struct s_redir
{
	char	*type;
	char	*file;
	int		outfile;
	int		infile;
}	t_redir;

typedef struct s_cmd
{
	pid_t			pid;
	char			*pipe;
	char			*cmd;
	char			*path;
	char			**arg;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	struct s_redir	*redir;
}	t_cmd;

typedef struct s_info
{
	char		**envp;
	t_env		*envp_list;
	char		envp_f;
	char		*cmd_line;
	t_cmd		*cmd;
	int			exit_f;
	int			num_elems;
	int			**pipe_fd;
	t_cmd		*group_head;
	t_env		*export_list_head;
	int			command_result;
	int			pipe;
	char		**stroka;
}	t_info;

// ФУНКЦИИ АРИНЫ:

// Запуск и инициализация
int		main(int argc, char **argv, char **envp);
int		init(t_info *shell, char **envp, int i);
void	handler_ctrlc(int sig);
char	*ft_readline(const char *prompt);

// Переменные окружения
int		*get_envp_list(t_info *shell);
int		make_key_value(char *env, char **key, char **value, int i);
t_env	*init_env(char	*key, char *value);

// Модифицированные функции либы чисто для энвп списка
t_env	*list_last(t_env *lst);
void	list_add_front(t_env **lst, t_env *new);
void	list_add_back(t_env **lst, t_env *new);

// Сам минишелл
int		minishell(t_info *shell);
int		search_pipe(char *str, int *f);
void	print_env_list(t_info *shell);
void	find_current_shlvl(t_info *struktura);

// Функция ридлайна, иначе не работает
void	rl_replace_line(const char *text, int clear_undo);

// ПАРСЕР-ЛЕКСЕР ЕПТЕТЬ
int		space(char c);
int		is_space(t_info *shell);
int		check_unclosed_quotes(char *line, t_info *shell);
int		check_wrong_redirect(char *line, int *redir);
int		first_check(t_info *shell);
int		parser(t_info *shell);
char	**join_double(char **line, char *str);
int		quotes(int *flag, char c);
int		check_redirect(char c, int flag);
void	*free_single(void **line);
void	*free_double(void **line);
char	**create_command(char *line);
char	*create_command_2(char **line, int *flag);
int		create_command_3(char	**line);
char	*join_symbol(char **line, char c);
char	**d_duplicate(char **line);
int		build_cmd(char **cmd, t_info *shell);
int		add_elem(t_cmd *cmd, t_info *shell);
t_cmd	*init_elem(char *cmd, t_info *shell);
t_redir	*make_redir(char **cmd);
int		make_redir_2(t_redir **temp, char **cmd, int *i);
int		get_redir_type(char *line);
char	*get_elem(char **cmd, int *i);
t_redir	*build_redirect(t_redir **temp, char *redir, char *file);
char	*take_redirect(int type, int *i, char **cmd);
int		size_redir(t_redir *str);
char	*make_cmd(char **cmd);
char	*make_path(char **cmd);
char	*make_env_path(char *cmd, t_info *shell);
char	**get_path(t_info *shell);
char	*make_pipe(char **cmd);
char	**make_arg(char	**cmd, t_cmd *temp);
char	**concat_arg(char	**temp, char **str);

// Продолжение - раскрытие кавычек
int		check_all_quotes(t_cmd *cmd, t_info *shell);
int		erase_quotes(char **str);
void	erase_2(char **str, int i);
int		check_command(char **cmd, t_info *shell);
char	*get_new_arg(char *cmd, int i, t_info *shell);
char	*get_key(char *cmd, int *i);
void	change_arg(char **cmd, char *arg, int i);
int		check_argument(char **arg, t_info *shell);
int		check_redir_quotes(t_redir *red, t_info *shell);

// ФУНКЦИИ ЕГОРА:
// executor
void	executor(t_info *data);
int		only_parent(t_info *data);

// env operations
void	copy_in_export(t_info *struktura, t_env *env_struct);
void	env_convert(t_info *data, char **env);
void	env_reverse_convert(t_info *struktura);

// Обновленные манипуляции с листами
t_env	*ft_lstlast_mod(t_env *lst);
t_env	*ft_lstnew_mod(char *content);
t_env	*ft_lstnew_mod_two(char *content);
void	ft_lstadd_back_mod(t_env *lst, t_env *new);
int		ft_lstsize_mod(t_env *lst);

// Билтыны
int		check_builtins(t_info *data, char **stroka);
void	built_echo(t_info *struktura, char **stroka);
void	built_pwd(t_info *struktura);
void	built_env(t_info *struktura);
void	built_cd(t_info *struktura, char **stroka);
void	built_exit(t_info *struktura);

// Билтын: export
void	built_export(t_info *struktura, char **stroka);
void	export_alph_find(t_env *ex_l);
void	export_alph_print(t_env *ex_l);
void	export_analiz(t_info *struktura, char **stroka);
int		export_analiz_word(t_info *struktura, char *str);
void	check_env_or_export(t_env *something);
void	export_error(char *stroka, t_info *struktura);
int		find_duplicate(t_info *struktura, char *a, int k, char *str);

// Билтын: unset
t_info	*built_unset(t_info *struktura, char **stroka);

// execve_action
void	execve_action(t_info *struktura);
void	execve_action_many_cmd(t_info *struktura, t_cmd *tmp);

// utils
char	*copy_char(char *a);
char	*copy_char_two(char *a, int j);
void	find_key(char *content, t_env *d);
void	find_key_value(char *content, t_env *d);
void	add_new_elem_key(t_env *something, char *str);
void	add_new_elem_key_value(t_env *something, char *str);
int		ft_strncmp_mod(const char *s1, const char *s2, size_t n);
void	ft_perror_exit_child(char *str, int error);

// Функции под редиректы:
void	redirect_action(char *type, char *file, t_redir *redir_str, int tmpin);
int		redirect_enumeration(t_cmd *tmp, int tmpin);

// Пайпы:
void	pipe_action(t_info *data);

// Error and free
void	ft_error(char	*error_message, t_info	*data);
void	ft_perror_exit_child(char	*str, int error);
void	free_and_new_start(t_info	*data);

// Прочее:
void	find_current_shlvl(t_info *struktura);

// Проверка пайпов
int		check_first_pipe(t_info *shell);
void	check_last_pipe(t_info *shell);
int		search_pipe(char *str, int *f);
int		find_double_pipe(t_info *shell);
void	print_error(int flag, char *cmd, int code, t_info *shell);
int		redir_check(t_info *shell, char *line);
void	redir_change(t_info *shell, char *line);
int		syntax_check(t_info *shell, char *line);
char	*question_mark(char *cmd, t_info *shell);
void	handler_two(int sig);

#endif
