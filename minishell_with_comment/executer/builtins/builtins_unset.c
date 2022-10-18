#include "minishell.h"

/* -----
◦ 5) unset (сбросить настройки) без каких-либо опций;

Удаляет переменную среды из текущего сеанса входа в систему
Обрабатывайте переменные среды ($, за которыми следует последовательность символов), 
которые должны расширяться до их значений.

Разбираюсь с переменной среды (environment variable)
Пока кажется правильным обращаться к своей структуре, находить нужную [ПС] и удалять её, 
но есть и внештатные ситуации, мне необходимо их выявить:
1) нет ничего ИЛИ удаление чего-то базового, что забивается в самом начале через env ИЛИ
той переменной окружения, которую мы забили в процессе [МОЖНО НЕСКОЛЬКО ПОДРЯД] ИЛИ
удаление с ошибкой == ничего не происходит;
2) если чего-то нет: "unset: '2': not a valid identifier" - причём это можно будет 
в несколько строк;
3) ?

Цифры приемлимо использовать вторыми и последующими символами
Русские буквы не воспринимает

Пример:
minishell$ export MY3=456
minishell$ echo $MY3
456
minishell$ unset MY
minishell$ echo $MY
 (ничего)

[!] Удаляется что-то базовое в ДАННОМ процессе, не во всём компе
----- */

//  unset TMPDIR unset USER

/* Тут надо разобраться как мы удаляем что-то
из структуры, и это выразить */ 
t_env*  delete_knot(t_env *current_del)
{
/* По сути в частном случае с самым первым элементом подается одно и тоже.
Нам нужно назначит новую голову! но как? будем думать */
    t_env *tmp;

    tmp = current_del;
    current_del = current_del->next;

    tmp->next = NULL;
    free(tmp->key);
    free(tmp->value);
    free(tmp);
    
    // check_env_or_export(current_del);
    return (current_del);
}

// Если подали хрень какую-то
void unset_error(t_info *struktura, char *stroka)
{
// добавить какой-то шелловский утилитовский принт

    ft_putstr_fd(": unset: \'", 2);
	ft_putstr_fd(stroka, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);

    struktura->command_result = 1;

    exit(0); // ?
}

// теперь сравниваем то, что прошло валидацию, с нашим внутренним списком
t_info *find_env(t_info  *struktura, char *stroka)
{
    t_env *ex_l_current;
    t_env *env_current;
    t_env *previous; // предпоследний элемент, который мы скрепим с последующим

    int j;
    int i;

    i = ft_strlen(stroka);
// -----
    j = 0;
    env_current = struktura->envp_list;
    previous = struktura->envp_list;
    while (env_current)
    {
        if (ft_strncmp_mod(stroka, env_current->key, i))
        {
            printf("1. key = %s, stroka = %s\n", env_current->key, stroka);
            if (j == 0)
            {
// current "перескакивает" на элемент вперёд
                struktura->envp_list = delete_knot(env_current);
                env_current = struktura->envp_list;
            }
            else
                env_current = delete_knot(env_current);
// предпоследний меняем, он теперь "смотрит" на "перескачивший" current
            previous->next = env_current;
            struktura->envp_f = 0;
        }
        else
        {
            previous = env_current;
            env_current = env_current->next;
            j++;
        }
    }
// -----
    j = 0;
    ex_l_current = struktura->export_list_head;
    previous = struktura->export_list_head;
    while (ex_l_current)
    {
        if (ft_strncmp_mod(stroka, ex_l_current->key, i))
        {
            printf("2. key = %s, stroka = %s\n", ex_l_current->key, stroka);
            if (j == 0)
            {
                struktura->export_list_head = delete_knot(ex_l_current);
                ex_l_current = struktura->export_list_head;
            }
            else
                ex_l_current = delete_knot(ex_l_current);
            previous->next = ex_l_current;
        }
        else
        {
            previous = ex_l_current;
            ex_l_current = ex_l_current->next;
            j++;
        }
    }
// -----
    return (struktura);
}

/* У нас точно будет работа вестись с:
1) нашей основной структурой;
2) непосредственно структурой env (которую мы забиваем по умолчанию и дополняем в процессе);
3) строкой в терминале.

То есть ?)считывание команды на корректность; 1) поиск нужного; 2) удаление, если есть.

Если так рассуждать, то после парсера мы делаем повторную проверку, уже
на внутреннюю корректность*/
t_info *built_unset(t_info *struktura, char **stroka)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while (stroka[i])
    {
        while (stroka[i][j])
        {
/*
            if (j == 0 && ((stroka[i][j] < 'A' || stroka[i][j] > 'Z')))
                unset_error(stroka[i]);
            if (j != 0 && (stroka[i][j] < 'A' || stroka[i][j] > 'Z' ||
                stroka[i][j] < '1' || stroka[i][j] > '9'))
                    // тут надо пошаманить с числами, что их типо можно
                unset_error(stroka[i]);
             unset_error(struktura, stroka[i]);
*/
            if (j == 0 && stroka[i][j] >= '0' && stroka[i][j] <= '9')
                unset_error(struktura, stroka[i]);
			if ((stroka[i][j] >= '!' && stroka[i][j] <= '/') || \
				(stroka[i][j] >= ':' && stroka[i][j] <= '@') || \
				(stroka[i][j] >= '[' && stroka[i][j] <= '^') || \
				(stroka[i][j] >= '{' && stroka[i][j] <= '~'))
                unset_error(struktura, stroka[i]);

            j++;
        }
// элемент проверен, "чист", ищем его в листе, и, если есть, удаляем
        struktura = find_env(struktura, stroka[i]);
        i++;
        j = 0;
    }

    struktura->command_result = 0;
    return (struktura);
}
