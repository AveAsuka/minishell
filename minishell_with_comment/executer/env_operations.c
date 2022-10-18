#include "minishell.h"

void env_reverse_convert(t_info *struktura)
{
    int i;
    t_env *current;

    i = 0;
    current = struktura->envp_list;
    if (current)
    {
        while (struktura->envp[i] != NULL)
        {
            free(struktura->envp[i]);
            current = current->next;
            i++;
        }

        // free(struktura->envp[i]); // ?

        free(struktura->envp);
        struktura->envp = NULL;
    }

    // current = struktura->envp_list;
    i = ft_lstsize_mod(current);
    // printf("i = %d\n", i);
    struktura->envp = (char **) malloc((i + 1) * sizeof(struktura->envp));
    if (struktura->envp == NULL)
        return ;
    i = 0;
    // int j = 0;
    while(current)
    {
        // j = j + ft_strlen(current->key) + ft_strlen(current->value);

        struktura->envp[i] = ft_strjoin(current->key, "=");
        struktura->envp[i] = ft_strjoin(struktura->envp[i], current->value);
        // printf("a[i] = %s\n", a[i]);

        i++;
        current = current->next;
    }
    struktura->envp[i] = NULL;
    struktura->envp_f = 1;
    
    // printf("[!] i = %d, j = %d\n", i, j);
    // i = 0;
    // printf("\nНАШ:\n");
    // while(struktura->envp[i])
    // {
    //     printf("%s\n", struktura->envp[i]);
    //     i++;
    // }
}

void free_old_export(t_info *struktura)
{
    t_env *tmp;

    tmp = struktura->export_list_head;
    // int i = 0;
    while (tmp)
    {
// printf("Проверка, что по факту чистим: %s %s\n",
//     tmp->key, tmp->value);

        free(tmp->key);
        tmp->key = NULL;
        free(tmp->value); 
        tmp->value = NULL;

        free(tmp);

        tmp = tmp->next;
        // i++;
    }

    // ?
    // printf("1\n");
    // if (tmp)
    // {
    //     printf("1\n");
    //     free(tmp->key);
    //     printf("1\n");
    //     tmp->key = NULL;
    // }
    // printf("2\n");
    // if (tmp)
    // {   printf("2\n");
    //     free(tmp->value); 
    //     printf("2\n");
    //     tmp->value = NULL;
    // }
    // printf("3\n");
    // ?

// printf("i = %d\n", i);
    free(tmp);
    tmp = NULL;
}

void  copy_in_export(t_info *struktura, t_env *envp_struct)
{
    t_env *new;

    t_env *tmp;
    tmp = NULL;

    if (struktura->export_list_head) // ?
    {
printf("\n\nзаходим чистим: free_old_export\n\n");
        free_old_export(struktura);
    }

    new = (t_env *)malloc(sizeof(t_env));
// printf("Проверка, что по факту: %s %p \n", new);
    if (new == NULL)
        ft_error("malloc error\n", struktura);
    new->key = copy_char(envp_struct->key);    
    new->value = copy_char(envp_struct->value);
    new->num = 0;
    new->next = NULL;
    struktura->export_list_head = new;

    // int i = 1;
    envp_struct = envp_struct->next;
    while (envp_struct) // edit
    {
        tmp = (t_env *)malloc(sizeof(t_env));
// printf("Проверка, что по факту: %s %p \n", tmp);

        if (tmp == NULL)
            return ;
        tmp->key = copy_char(envp_struct->key);    
        tmp->value = copy_char(envp_struct->value);
        tmp->num = 0;
        tmp->next = NULL;

        new->next = tmp;
        while (new)
        {
            if (!new->next)
                break ;
            new = new->next;
        }
// printf("Проверка, что должно: %s %s\n", env_struct->key, env_struct->value);
// printf("Проверка, что по факту: %s %p | %s %p \n",
//     new->key, new->key, new->value, new->value);

        envp_struct = envp_struct->next;
        // i++; // del
    }
}




/* Тут задача перевести текущую переменную окружения, которая нам даётся через параметр 
'char **env' в main-е */
// void env_convert(t_info  *data, char **env)
// {
//     t_env *env_list; // название возможно поменяю
//     t_env *tmp;
//     int i;
   
//     tmp = NULL;
//     env_list = NULL;
//     i = 0;
//     while (&*env[i])
//     {
//         if (!env_list)
//         {
//             env_list = ft_lstnew_mod(&*env[i]);
//             data->envp_list = env_list;
// // printf("Проверка: key = %s value = %s\n", (env_list)->key, (env_list)->value);
//         }
//         else
//         {
//             tmp = ft_lstnew_mod(&*env[i]);
// // printf("Проверка: key = %s value = %s\n", tmp->key, tmp->value);
//             ft_lstadd_back_mod(env_list, tmp);
//         }
//         i++;
// // printf("Проверка: key = %s value = %s\n", (env_list)->key, (env_list)->value);
//     }
// }


/*
int *get_envp_list(t_info *shell)
{
 t_env *env;
 char *key;
 char *value;
 int  i;

 i = 0;
 while (shell->envp[i]) - бегу по массиву энвп
 {
  if (make_key_value(shell->envp[i], &key, &value, 0) != 0) - тут делю по первому равно на ключ и значение
   exit(-1);
  env = init_env(key, value); - тут создаю элемент
  list_add_back(&shell->envp_list, env); - тут заношу в список
  i++;
 }
 // print_envp_list(shell); // Just for checking
 return (0);
}
*/




































/*
int perebor(char **a, t_list **stack_a, t_num *check)
{
    int l;
    int d;
    t_list *tmp;

    l = 0;
    d = 0;
    if (a == NULL || (*a) == NULL)
        return (empty_error(a, *stack_a, l));
    while(&*a[l])
    {
        d = fatoi(&*a[l], check);
        if (check->flag == 0)
            return (flag_error(a, *stack_a, l));
        else
        {
            if(!stack_a)
                (*stack_a) = ft_lstnew(d);
            else
            {
                tmp = ft_lstnew(d);
                ft_lstadd_back(stack_a, tmp);
            }
        }
        mem_free(a[l]);
        l++;
    }
    return(1);
}
*/