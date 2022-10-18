#include "minishell.h"

/* Тут идея через не учёт pipe и выполнение команд по очереди, но есть момент, что 
редиректы имеет бОльший приоритет, но это никак не учитывается - они обрабатываются только 
в самом начале и в самом конце - надо как-то имплементировать этот момент в алгоритм.
В чём идея? В том, чтобы сначала делать пайп, потом, если есть, делать редирект.
Непонятно пока в чём идея, если редиректы есть - как будет испольняться следующая группа?
Ну, если рассудить, то ввод и вывод у нас либо терминал, либо pipe, либо файл.

Моделируем ситуацию: выводим в трубу, но новый ввод не из трубы, а из файла. 
Остаётся в трубе?

Как будем реализовывать хождение по группам? 
Хорошей идеей кажется через односвязный список, причём есть мысль без восприятия пайпа -
без его маллока и чего-то такого. Но вот как? 

[22.08.] Вроде так сделал - попробую оттестить с этим, по результатам понять что нет

[ Важно помнить про комбинацию для ввод и вывода с pipe:
  ввод: dup2 + pipe;
  вывод: pipe + dup2 ]
*/

/* Для тестов:
pwd | ls
cat e | pwd | ls
cat a | wc -l
ls | wc -l
pwd | export 
cat a | grep test
test 

ls > a | wc -l > b
*/

//                                   2) номер логической группы
void pipe_close_maza_faka(t_info  *data, int n_child, t_cmd   *tmp)
{
// exec->qtt_cmd - общее количество команд
// exec->n_child - номер ребенка, тоже с нуля счёт
    
    int	i = 0;  // пока не пройдемся по всем пайпам (счет с нуля)
	int	j;
// (data->num_elems - 1) - это сколько всего пайпов

printf("pipe_close_maza_faka: cmd = %s, num_child = %d\n", tmp->cmd, n_child);
	while (i != (data->num_elems - 1))
	{
		j = 0; // проходмся по двум файловым дескрипторам, поэтому такое условие
		while (j != 2)
		{
/* первое условие - номер команды и ребенка не совпадают, чтобы не закрыть его дескрипторы
второе условие - */
			if (n_child != i && n_child - 1 != i) // было &&
			{
printf("ft_pipe_closure: i = %d, j = %d, close = %d, n_child = %d\n", \
	i, j, data->pipe_fd[i][j], n_child);
                close (data->pipe_fd[i][j]);
			}
			j++;
		}
		i++;
    }
}

void pipe_action(t_info  *data)
{
    t_cmd   *tmp = data->cmd;
    int tmpin = dup(0);
    int tmpout = dup(1);

// Малочим трубы
    int counter = data->num_elems - 1;
    int i = 0;
    data->pipe_fd = malloc(sizeof(int *) * counter); // проверить маллоки
    if (data->pipe_fd == NULL)
        ft_error("malloc error\n", data);
    while (counter != 0)
    {
        data->pipe_fd[i] = malloc(sizeof(int) * 2);
        if (data->pipe_fd[i] == NULL)
            ft_error("malloc error\n", data);
        if (pipe(data->pipe_fd[i]) == -1)
            ft_error("pipe error\n", data);
// printf("TRUBI. in = %d, out = %d\n", tmp->redir->infile, tmp->redir->outfile); //del
        i++;
        counter--;
    }
    
// [НАЧАЛО ЦИКЛА]
    int num_elems_flag;
    int ret; // fork

    num_elems_flag = data->num_elems;
    counter = data->num_elems - 1;
// printf("num_elems_flag = %d, counter = %d \n",
//     num_elems_flag, counter);
    
    i = 0; // номер логической группы
    int red_final;
    while (num_elems_flag != 0)     
    {
//
        int p = 0;
        if (data->stroka)
        {
            while(data->stroka[p])
            {
                free(data->stroka[p]);
                p++;
            }
            free(data->stroka);
            data->stroka = NULL;
        }
        data->stroka = ft_split(tmp->cmd, '/');
//
        ret = fork();
        if (ret == -1)
            ft_perror_exit_child("", 1);
        if (ret == 0)
        {
printf("num_elems = %d, cmd = %s\n", num_elems_flag, tmp->cmd); //del
           
            red_final = redirect_enumeration(tmp, tmpin);  // перебор всех редиректов
            
            if (num_elems_flag == counter + 1)
            {   printf("first entry\n");
                close(data->pipe_fd[i][0]);
                pipe_close_maza_faka(data, i, tmp);

                if (tmp->redir[red_final].outfile == 1) // если редиректа нет - труба
                {
                    if (dup2(data->pipe_fd[i][1], 1) == -1) // пока не уверен
                        ft_perror_exit_child("Inside child dup error", 1);
                }
                close(data->pipe_fd[i][1]);
            }

// 3. last entry 
            else if (num_elems_flag == 1)
            {   printf("last entry\n");
                close(data->pipe_fd[i - 1][1]);
                pipe_close_maza_faka(data, i, tmp);

                if (tmp->redir[red_final].infile == 0) // если редиректа нет - труба
                {
                    if (dup2(data->pipe_fd[i - 1][0], 0) == -1) // пока не уверен
                        ft_perror_exit_child("Inside child dup error", 1);
                }
                close(data->pipe_fd[i - 1][0]);
            }

// 2. рутина
            else if (num_elems_flag != 1)
            {   printf("рутина\n");
                close(data->pipe_fd[i - 1][1]); // предыдуший вывод
                close(data->pipe_fd[i][0]);
                pipe_close_maza_faka(data, i, tmp);

                if (tmp->redir[red_final].infile == 0) // если редиректа нет - труба
                {
                    if (dup2(data->pipe_fd[i - 1][0], 0) == -1) // пока не уверен
                        ft_perror_exit_child("Inside child dup error", 1);
                }
                if (tmp->redir[red_final].outfile == 1) // если редиректа нет - труба
                {
                    if (dup2(data->pipe_fd[i][1], 1) == -1) // пока не уверен
                        ft_perror_exit_child("Inside child dup error", 1);
                }
                close(data->pipe_fd[i - 1][0]); // предыдуший ввод // ?!
                close(data->pipe_fd[i][1]);
            }

// Фишка в том, что если попадаются для пайпа билтыны исключения, то мы выходим ими здесь
            if (only_parent(data) == 1)
            {   printf("сработал only_parent и exit\n");
                exit(0);
            }
            else if (check_builtins(data, data->stroka) == 100) // [!?]
                execve_action_many_cmd(data, tmp); // [!?]
        }
        tmp = tmp->next;
        num_elems_flag--;
        i++;
    }
// [КОНЕЦ ЦИКЛА]

// актуальная концовка
/*
    int status = 0;
    counter = data->num_elems;
    while (--counter >= 0)
    { // yes | head
        printf("waitpid num = %d\n", counter);
        waitpid(-1, &status, 0); // WUNTRACED
    }

    if (dup2 (tmpin, 0) == -1)
		ft_perror_exit_child("Inside child dup error", 1);
    if (dup2 (tmpout, 1) == -1)
		ft_perror_exit_child("Inside child dup error", 1);
    close (tmpin);
    close (tmpout);


    i = 0; // ?
    while (counter != 0)
    {
// printf("cmd = %s, cnt = %d, i = %d in = %d, out = %d\n", 
//     tmp->cmd, counter, i, data->pipe_fd[i][0], data->pipe_fd[i][1]); //del
    printf("cmd = %s, cnt = %d, i = %d\n", 
    tmp->cmd, counter, i); //del

        close(data->pipe_fd[i][0]);
        close(data->pipe_fd[i][1]);
        tmp = tmp->next;
        i++;
        counter--;
    }
*/

// старая концовка
    dup2(tmpin,0);
    dup2(tmpout,1);
    close(tmpin);
    close(tmpout);

    i = 0; // ?
    // counter++;
    while (counter != 0)
    {
// printf("cmd = %s, cnt = %d, i = %d in = %d, out = %d\n", 
//     tmp->cmd, counter, i, data->pipe_fd[i][0], data->pipe_fd[i][1]); //del
    printf("cmd = %s, cnt = %d, i = %d\n", 
    tmp->cmd, counter, i); //del

        close(data->pipe_fd[i][0]);
        close(data->pipe_fd[i][1]);
        tmp = tmp->next;
        i++;
        counter--;
    }

    int status = 0;
    while (data->num_elems-- >= 0)
    { // yes | head
        printf("waitpid num = %d\n", data->num_elems);
        waitpid(-1, &status, 0); // WUNTRACED
    }

printf("\n KONEZ\n"); //del
}

/*

ls | pwd
pwd | ls

*/