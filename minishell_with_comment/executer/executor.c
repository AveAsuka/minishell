#include "minishell.h"

int check_builtins(t_info *data, char **stroka)
{
	// char **a;
	// a = data->cmd->arg;
// printf("a[0] = %s, a[1] = %s\n", a[0], a[1]);

	if (ft_strncmp_mod("echo", stroka[0], 4) || ft_strncmp_mod("ECHO", stroka[0], 4))
		built_echo(data, data->cmd->arg);
	else if (ft_strncmp_mod("pwd", stroka[0], 3) || ft_strncmp_mod("PWD", stroka[0], 3))
	{
		printf("залез в pwd, %s \n", stroka[0]);
		built_pwd(data);
	}
	else if (ft_strncmp_mod("env", stroka[0], 3) || ft_strncmp_mod("ENV", stroka[0], 3))
	{
		built_env(data);
	}
	else
		return (100); // не нашли билтын
    return (1);      // нашли билтын
}

// Если нету пайпов и только одна команда - не делаю форк
int only_parent(t_info  *data)
{
	// char **a;
	// a = data->cmd->arg;
// printf("a[0] = %s, a[1] = %s\n", a[0], a[1]);

	if (ft_strncmp_mod("export", data->stroka[0], 6) || ft_strncmp_mod("EXPORT", data->stroka[0], 6))
	{
		printf("сработал export\n");
		built_export(data, data->cmd->arg);
		// free(data->stroka[0]); // no
	}
	else if (ft_strncmp_mod("unset", data->stroka[0], 5) || ft_strncmp_mod("UNSET", data->stroka[0], 5))
		data = built_unset(data, data->cmd->arg);
    else if (ft_strncmp_mod("cd", data->stroka[0], 2) || ft_strncmp_mod("CD", data->stroka[0], 2))
		built_cd(data, data->cmd->arg);   // ?
    else if (ft_strncmp_mod("exit", data->stroka[0], 4) || ft_strncmp_mod("EXIT", data->stroka[0], 4))
		built_exit(data);
	else
	{
		// printf("[!!!] 0\n");
		return (0);
	}
	// printf("[!!!] 1\n");
	return (1);
}

// Работа с отдельной группой
void	 one_cmd(t_info  *data)
{
	int tmpin;
    int tmpout;

	tmpin = dup(0);
	tmpout = dup(1);

/* 2. Теперь принимание в расчёт редиректов. 
Они выше по приоритеты, нежели пайпы, поэтому ими можно изменить 
ввод и вывод дескрипторов, уже потенциально изменённых пайпом. */
	redirect_enumeration(data->cmd, tmpin);

/* 0.2. Тут кейс когда есть только определенные команды
(в том числе и с редиректами): она выполняется сразу в родителе */
	int check = 1;
	// sleep(5);

	check = only_parent(data);

	if (check == 0)
	{ /* 1. Теперь непосредственно работа с командами: их исполнение
	Тут идея сразу тут открыть форк, коли команда точно есть */
		// printf("after only parent\n");
		data->group_head = (t_cmd *)malloc(sizeof(t_cmd));
		if (data->group_head == NULL)
			ft_error("malloc error\n", data);
		// data->group_head = NULL; // no

		signal(2, SIG_IGN);
	    signal(3, SIG_IGN);
        data->command_result = 0;

		data->group_head->pid = fork();
		if (data->group_head->pid == -1)
			ft_perror_exit_child("", 1);
		
		if (data->group_head->pid == 0)
		{
			signal(2, SIG_DFL);
	    	signal(3, SIG_DFL);

// printf("type: %s, file: %s\n", data->cmd->redir->type, data->cmd->redir->file);
// printf("Before execve_action: 1. pid == %d\n", data->group_head->pid);
			if (check_builtins(data, data->stroka) == 0)
				execve_action(data);// [!?]
		}
	}
	free(data->group_head); // !!!
	
	if (dup2 (tmpin, 0) == -1)
		ft_perror_exit_child("Inside child dup error", 1);
    if (dup2 (tmpout, 1) == -1)
		ft_perror_exit_child("Inside child dup error", 1);
    close (tmpin);
    close (tmpout);

	if (check == 0 && waitpid (-1, NULL, 0) == -1)
	{
		printf("waitpid error\n");
		ft_perror_exit_child("", 1);
	}

	int	status;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
		{
			data->command_result = 131;
			ft_putstr_fd("Quit: 3\n", 1);
		}
		else if (WTERMSIG(status) == 2)
		{
			data->command_result = 132;
			ft_putstr_fd("\n", 1);
		}
	}
}

/* Сюда идет на реализацию вся строка, но в ней может быть несколько
логических групп, поэтому тут мы это разбиваем и в дальнейшую работу
выносим только одну группу */
void	executor(t_info  *data)
{ /* Тут принимаем в расчёт pipe: думаю правильно это делать здесь,
нежели внутри функции логической группы. Как раз делаем в родители
ДО форка. */

/* [ПРОБЛЕМА] Парсится какая-то грязь - разобраться почему
	env_convert(data, env);
    env_reverse_convert(data);
    data->envp_f = 1; */
		

/* 0.1. Надо сначала скопировать наш envp в односвязный список, 
который потом мы отсортируем в алфавитном порядке */

	copy_in_export(data, data->envp_list);


	data->stroka = ft_split(data->cmd->cmd, '/');
	// printf("data->stroka: %p, %s\n", data->stroka, data->stroka[0], data->cmd->cmd, data->cmd->cmd);

	// t_cmd   *tmp = data->cmd;
	// int i = 0;
// printf("\n Предварительная информация: \n 
// 		Кол-во групп = %d; pipe = %s\n\n", 
// 		data->num_elems, data->cmd->pipe);
// 	while (i < data->num_elems)
// 	{
// printf("command = %s, arg = %s\n", tmp->cmd, *(tmp->arg));
// 		tmp = tmp->next; i++;
// 	}

	if (data->cmd->pipe)
	{
		printf("Зашли в pipe_action:\n\n");
		pipe_action(data); // условная функция
	}
	else // Если пайпов нет, то идём по сценарию "одна команда"
	{
		printf("Зашли в one_cmd\n");
		one_cmd(data);
	}

	free_and_new_start(data);
}
// echo $USER
// echo $SHLVL

/* Список косяков:
Егор: 
1) для реализации $? нужно - записать результат execve в int, до
этого в парсере привязать запрос (решили делать в конце);
Арина: */

/* Надо понять когда форкаем, в какой момент - до реализации пайпов и редиректов, 
или после? 
Мы знаем что работа исключительно с родителем - это частный случай, и мы делаем 'child' 
во всех остальных. Пайп находится вне 'child', как я понял.
То есть надо убедиться, что 'child' необходим, потом делать его, потом в нём уже всё остальное
(смену редиректа, команду и прочее). 
Но не совсем понятны мне манипуляции с пайпом - он должен, как я понял, быть связью между двумя 
процессами, в нашем случае подпроцессами - 'child-ами'. То есть результат работы предыдущей логической 
группы должен быть как-то зафиксирован для передачи в работу для следующей.
Pipe делаем до форка. */

/* Размышления: 
1. Сначала точно работаю с ГРУППОЙ;
2. В этой группе мы сначала ищем РЕДИРЕКТЫ, и принимаем их в расчёт;
3. С учётом присутствие или отсутствия последних мы реализуем КОМАНДЫ 
- либо БИЛТЫНЫ, либо ПРОЧИЕ;
4. Разумным представляется пока проработать и реализовать простой сценарий:
1 группа, без редиректов, только команда; */