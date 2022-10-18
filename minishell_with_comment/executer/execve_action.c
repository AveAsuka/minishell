#include "minishell.h"

void execve_action_many_cmd(t_info *struktura, t_cmd   *tmp)
{
/*  
    struktura->command_result = execve(ex, tmp->arg, struktura->envp);
    ft_putstr_fd("Execve command_result 2.: ", 2);
    ft_putstr_fd(ft_itoa(struktura->command_result), 2);
    ft_putstr_fd("\n", 2);

    if (struktura->command_result == -1)
        return (0); // Не срабатывает, если execve успешно работает!
    return (1);
*/
    env_reverse_convert(struktura);
    char   *ex;
    if (struktura->cmd->path == NULL)
        ex = ft_strdup(tmp->cmd);
    else
        ex = ft_strjoin(tmp->path, tmp->cmd);
    
// printf("[execve_action] ex: %s| arg: %s\n", ex, *(tmp->arg));
printf("\n[Action] %s %s\n", struktura->stroka[0], *(tmp->arg));
// printf("Action in / out: %d, %d \n\n", tmp->redir->infile, tmp->redir->outfile);

    struktura->command_result = execve(ex, tmp->arg, struktura->envp);

    // ft_putstr_fd("Execve command_result 2: ", 2);
    // ft_putstr_fd(ft_itoa(struktura->command_result), 2);
    // ft_putstr_fd("\n", 2);

    struktura->command_result = 0;
    ft_perror_exit_child("Inside last child execve error execve_action_many_cmd", 1);
}

void execve_action(t_info *struktura)
{
    char   *ex;

// 1. Перенесим env в двойной массив
    // if (struktura->envp_f == 0) // надо ли обновлять?
    env_reverse_convert(struktura);

    if (struktura->cmd->path == NULL)
        ex = ft_strdup(struktura->cmd->cmd);
    else
        ex = ft_strjoin(struktura->cmd->path, struktura->cmd->cmd);

// printf("[execve_action] ex: %s| arg: %s\n", ex, *(struktura->cmd->arg));
// printf("\n[Action] \n\n");

    struktura->command_result = execve(ex, struktura->cmd->arg, struktura->envp);

// Не срабатывает, если execve успешно работает!
    struktura->command_result = 0;
    ft_perror_exit_child("Inside last child execve error execve_action", 1);
}


/* 28.07. Ситуация в следующем: мы вбиваем нестандартную команду в readline,
она анализируется и исполняется. 
В этом действе точно участвуют три элемента:
1) access - удостоверится, что путь правильный;
2) execve - выполнение программы;
3) fork - выполнение программы в отдельном процессе.
Это пока то, что я понял, что-то упустил, провожу дальнейший анализ */

/* Думаю над мыслью оптимизировать весь алгоритм в том смысле, чтобы он лишний
раз не проигрывался, но пока остановился только на шаге 1. Взять во внимание. */

/* Варианты что делать, если execve плохо срабатывает:
1) Использование функции fflush();
2) Вывести значение errno, расшифровать код ошибки;
3) (-) "Скорее всего у тебя последним элементом в argv не ноль. А срабатывает иногда, 
потому что попадает в память с нулем и останавливает чтение";
4) Передача и использование неинициализированных переменных. */

/*  Мой вариант реализации функции execve_action
// ================
// 2. Находим path и копируем в массив
    t_env *current;
    current = struktura->envp_list;
    while (current)
    {
        if (ft_strncmp_mod("PATH", current->key, 4))
            break;
        current = current->next;
    }
    int     i = ft_strlen(current->value);
    char    *path = copy_char_two(current->value, i); // скопирую в него путь, указанный в PATH в env

// 3. Переносим массив в двойной массив, и бьем по ":", после чего ищем правильный путь
    char    **path_two;
    int     check;
    char **stroka;
    stroka = ft_split(struktura->cmd->cmd, ' ');
    stroka[0] = ft_strjoin("/", stroka[0]); // мне не нравится цифра ноль
    path_two = ft_split(path, ':');
    i = 0;
    while (path_two[i])
    {
        path_two[i] = ft_strjoin(path_two[i], stroka[0]);
        check = access(path_two[i], F_OK);
        if (check != -1)
            break;
        else
            i++;
    }
    free(stroka);
    stroka = ft_split(struktura->cmd->cmd, ' ');
// ================

// 3. Переносим массив в двойной массив, и бьем по ":", после чего ищем правильный путь
    // int i = 0;
    // int check;
    // while (struktura->cmd->arg[i])
    // {
    //     check = access(struktura->cmd->arg[i], F_OK);
    //     if (check != -1)
    //         break;
    //     else
    //         i++;
    // }

// 4. Запускаем всё эту тему
    char    *pat;
    pat = ft_strjoin("/", struktura->cmd->cmd); // мне не нравится цифра ноль
    printf("\nstruktura->cmd->path = %s, struktura->cmd->cmd = %s\n", struktura->cmd->arg[0], pat);
    printf("path_two[i] = %s, stroka[0] = %s\n", path_two[i], stroka[0]); // новое, проверка
// должно: "path_two[i] = /bin/ls, stroka[0] = /ls"
// выводит: "struktura->cmd->path = /bin/ls, struktura->cmd->cmd = /ls"
    // if (execve(struktura->cmd->arg[i], struktura->cmd->arg, struktura->envp) == -1)
    if (execve(path_two[i], stroka, struktura->envp) == -1) // новое, проверка
    {
        printf("%s: %s: No such file or directory\n", struktura->cmd->cmd, struktura->cmd->arg[i+1]);
        printf("errno = %d\n", errno);
    }
// не зависит от envp, от cheсk-a, от arg-ов - блуждающая ошибка
// errno == 14, у меня тоже самое
// дело с фактурой, которую обрабатываем раньше, любопытно
// 14 По УМОЛЧАНИЮ Неверный адрес. Система обнаружила недопустимый адрес при
// попытке использовать аргумент вызова.
*/
