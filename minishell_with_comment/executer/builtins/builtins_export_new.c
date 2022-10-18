#include "minishell.h"

void edit_value(t_env *tmp, char *a)
{
    int i;
    int j;
    int r;
    int l;
   
    i = 0;
    j = 0;
    r = 0;
    l = ft_strlen(a);
    free(tmp->value);

    while (a[i] != '=')
        i++;
// printf("i = %d, l = %d\n", i, l);

// не исключен проёб, если подано нихуя, надо учесть
    tmp->value = (char *) malloc((l - i) * sizeof(char));
    if (tmp->value == NULL)
        return ;
    if (!tmp->value)
    {
        tmp->value = NULL;
        return ;
    }
    while (l > j)
    {
        if (j > i)
        {
            tmp->value[r] = a[j];
            r++;
        }
        j++;
    }
}

/* Если 'равно' нет, то пофигу вообще, ничего менять не надо
а если есть, то перезаписываем.
1 - , 2 - key, 3 - есть ли "=", 4 - и "key" и "value" */
int find_duplicate(t_info *struktura, char *a, int k, char *str)
{
    int i = ft_strlen(a);
    int j = 0;
    t_env *tmp;

// printf("key = %s, равно = %d, строка = %s\n", a, k, str);
    tmp = struktura->envp_list;
    while (tmp)
    {
// как выяснилось в процессе мысль передавать есть ли 'равно' и 'строку' оказалось удачной
        if (ft_strncmp_mod(a, tmp->key, i) && k == 1)
        {
            edit_value(tmp, str);
            j = 1;
            break;
        }
        tmp = tmp->next;    
    }
    
    tmp = struktura->export_list_head;
    while (tmp)
    {
        if (ft_strncmp_mod(a, tmp->key, i) && k == 1)
        {
            edit_value(tmp, str);
            j = j + 2;
            break;
        }
        tmp = tmp->next;
    }

    free(a);
    return (j);
}

int export_analiz_word(t_info *struktura, char *str)
{
// printf("str = %s\n", str);
    int i = 0;
    int find_equally = 0;
    char *a = NULL;

    while (str[i])
    {
        if (i == 0 && str[i] >= '0' && str[i] <= '9')
			return (2);

        if (str[0] == '=')
            return (2);

		if ((str[i] >= '!' && str[i] <= '-') || \
				(str[i] >= ';' && str[i] <= '<') || \
					(str[i] >= '>' && str[i] <= '@') || \
						(str[i] >= '[' && str[i] <= '^') || \
							(str[i] >= '{' && str[i] <= '~'))
            return (2);
// printf("str[%d] = %c\n", i, str[i]);
        if (str[i] == '=')
        {
            find_equally = 1;
            a = copy_char_two(str, i);
        }
        i++;
    }
// тут проблема - список без 'равно' не обновляется...
    if (find_equally == 0)
        a = copy_char_two(str, i);

    i = find_duplicate(struktura, a, find_equally, str);
// printf("i = %d, find_equally = %d \n", i, find_equally);

    if (i == 2 && find_equally == 1)
        return (3); // знак равно есть, но дубликат найден только в export, 
                    // значит добавить надо только в env

// допустим нашли дубликат - разберемся с экспортом - дубликат есть и есть "="
    if (i != 0 && find_equally == 1)
        return (4); // равно есть - мы всё подредачили, ничего делать не надо

// дубликаты не найдены и есть знак равно
    if (i == 0 && find_equally == 1)
        return (1); // новое: и в export list и в env

// дубликаты не найдены и нет знака равно
// если всё остальное не подходит, то вернем код 0 (только в export list)
// это мне кажется интуитивно верным, но могу и ошибаться
    return (0); 
}

void export_error(char *stroka, t_info *struktura)
{
    ft_putstr_fd("export: `", 2);
    ft_putstr_fd(stroka, 2);
    ft_putstr_fd("': not a valid identifier\n", 2);

    struktura->command_result = 1;

    exit(0); // ?
}

void export_analiz(t_info *struktura, char **stroka)
{
    int i;
    int code;

    i = 1;
    code = 0;
    
    while(stroka[i])
    { // я не предусмотрел наличие дубликаты
        code = export_analiz_word(struktura, stroka[i]);

        if (code == 0) // только в export list
        {
            add_new_elem_key(struktura->export_list_head, stroka[i]);
// printf("\nТОЛЬКО EXPORT:\n\n");
// check_env_or_export(struktura->export_list_head);
        }
        else if (code == 1) // и в export list и в env
        {
            add_new_elem_key_value(struktura->export_list_head, stroka[i]);
            add_new_elem_key_value(struktura->envp_list, stroka[i]);
            struktura->envp_f = 0;
// printf("\nОБА:\nenv:\n");
// check_env_or_export(struktura->envp_list);
// printf("\nexport:\n");
// check_env_or_export(struktura->export_list_head);
        }
        else if (code == 3) // и в export list и в env
        {
            add_new_elem_key_value(struktura->envp_list, stroka[i]);
            struktura->envp_f = 0;
// printf("\nenv:\n");
// check_env_or_export(struktura->envp_list);
        }
        else if (code == 2) // ошибка
            export_error (stroka[i], struktura);
//  code == 4 - ничего делать не надо
        i++;
    }
}
