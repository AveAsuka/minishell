#include "minishell.h"

/* Недопрописанные мною моменты:
1) когда подаем длинное имя с пробелами - не срабатывает, надо это обдумать
(minishell with comment/, а должно  minishell\ with\ comment/);
2) что-то непонятное с обновлением HOME в env (я забил);
3) какой-то ещё тип ошибки не прописан мною.

Имеем дело с перезаписью путей - есть старый, есть новый
Надо обеспечить возможность обновления и перезаписи -идея в том, что мы можем узнать,
где сейчас находимся и сравнить с уже имеющимся в env и заменить */
t_env *find_current_pwd(t_info *struktura)
{
    t_env *head;
    int i;

    head = struktura->envp_list;
    while (head)
    {
        i = ft_strlen(head->key);
        if (ft_strncmp_mod("PWD", head->key, i))
            return (head);
        head = head->next;
    } 
    return (head);
}

t_env *find_old_pwd(t_info *struktura)
{
    t_env *head;
    int i;

    head = struktura->envp_list;
    while (head)
    {
        i = ft_strlen(head->key);
        if (ft_strncmp_mod("OLDPWD", head->key, i))
            return (head);
        head = head->next;
    } 
    return (head);
}

void    edit_old_pwd(t_env *pwd_v, t_env *old_pwd)
{
    free(old_pwd->value);
    old_pwd->value = copy_char(pwd_v->value);
}

// t_info *struktura, int flag, t_env *oldpwd
void	ft_cd_error(char *arr)
{
	// free(oldpwd->value);

	// if (flag == 1)
	// {
	// 	ft_print_shell(NULL, SHELL);
	// 	ft_putstr_fd(": cd: HOME not set \n", 2);
	// }

	// else if (flag == 2)
	// {
		// ft_print_shell(NULL, SHELL);
		ft_putstr_fd(": cd: ", 2);
		ft_putstr_fd(arr, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	// }

	// data->exit_f = 1;
}

void    pwds_edit(t_env *current_pwd, t_env *old_pwd)
{
    char	tmp[1024];

    edit_old_pwd(current_pwd, old_pwd);

    free(current_pwd->value);
// неправильно - это не актуальный каталог, а залупа какая-то!
// надо думать, как перезаписать корректно

    getcwd(tmp, 1024);
    current_pwd->value = copy_char(tmp);
}

int	ft_without_argument(t_env *envp_l, char *path, t_info *struktura)
{
	t_env	*tmp;
    t_env *current_pwd;

	tmp = envp_l;
	while (tmp)
	{
		if (ft_strncmp("HOME", tmp->key, 5) == 0)
			break ;
		tmp = tmp->next;
	}

	if (tmp != NULL && ft_strncmp("HOME", tmp->key, 5) == 0)
	{
		path = tmp->value;
		chdir(path);
	}
	else // если ошибка
		return (1);

    current_pwd = find_current_pwd(struktura);
    current_pwd->value = path;

	return (0);
}

// PWD=/Users
// OLDPWD=/Users/rabderus
void    built_cd(t_info *struktura, char **stroka)
{    
    t_env *current_pwd;
    t_env *old_pwd;
    int result; // результат работы функции 'chdir'
    char *path = NULL;

// получаем ссылки на пвд и старое пвд, 
// cразу ими, как я понял, меняем список ещё ранее,
// и чтобы при редакции поменять
    current_pwd = find_current_pwd(struktura);
    old_pwd = find_old_pwd(struktura);

//  сценарий первый - подали только 'cd' - тогда pwd становится == HOME
    if (stroka[1] == NULL)
    { // надо тут обработать ошибки
        result = ft_without_argument(struktura->envp_list, path, struktura);
		// if (result == 1)
			// ft_cd_error(stroka[1]);
    }
    else // основное течение событий
    {
        result = chdir(stroka[1]);
        printf("result = %d\n", result);
        if (result == -1)
            ft_cd_error(stroka[1]);
    }

//Что делаем, если всё тип-топ? Редактируем наши пвд-шники, под текущие реалии
    if (result == 0)
        pwds_edit(current_pwd, old_pwd);
        
    struktura->command_result = 0;
}
