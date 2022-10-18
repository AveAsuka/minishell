/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:14:36 by lbrianna          #+#    #+#             */
/*   Updated: 2022/09/13 18:01:35 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Записываю переменные окружения из массива envp
в связанный список. Зачем и то и другое так и не поняла
Но со списком будет проще работать, массив пусть будет, дальше решим
нужен или нет
*/

t_env	*init_env(char	*key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
}

int	make_key_value(char *env, char **key, char **value, int i)
{
	int	j;

	j = -1;
	while (env[i + 1] != '=')
		i++;
	*key = malloc(sizeof(char) * (i + 2));
	if (!key)
		return (-1);
	while (env[(++j) + 1] != '=')
		(*key)[j] = env[j];
	(*key)[j] = env[j];
	(*key)[++j] = '\0';
	i++;
	j = i;
	while (env[i])
		i++;
	*value = malloc(sizeof(char) * (i - j));
	if (!value)
		return (-1);
	i = -1;
	while (env[(++j)])
		(*value)[++i] = env[j];
	(*value)[++i] = '\0';
	return (0);
}

int	*get_envp_list(t_info *shell)
{
	t_env	*env;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (shell->envp[i])
	{
		if (make_key_value(shell->envp[i], &key, &value, 0) != 0)
			exit(-1);
		env = init_env(key, value);
		list_add_back(&shell->envp_list, env);
		i++;
	}
	return (0);
}
