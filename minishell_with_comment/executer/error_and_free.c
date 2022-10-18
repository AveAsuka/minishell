#include "minishell.h"

void free_and_new_start(t_info  *data)
{
    // (void)data;
   
/*
    t_cmd *cmd = data->cmd;
    int i;
    while (cmd)
    {
        if (cmd->pipe)
        {
            free(cmd->pipe);
            cmd->pipe = NULL;
        }
        if (cmd->path)
        {
            free(cmd->path);
            cmd->path = NULL;
        }
        if (cmd->cmd)
        {
            free(cmd->cmd);
            cmd->cmd = NULL;
        }
    
        if (cmd->arg) // не пойму где тут ошибка
        {
            i = 0;
            while(cmd->arg[i])
            {
                free(cmd->arg[i]);
                i++;
            }
            free(cmd->arg);
            cmd->arg = NULL;
        }
        free(cmd); // ?
        // cmd = NULL; // ???
        cmd = cmd->next;
    }
*/

    int i = 0;
    if (data->stroka)
	{
		while(data->stroka[i])
		{
			free(data->stroka[i]);
			i++;
		}
		free(data->stroka);
		data->stroka = NULL;
	}

    // unlink(".here_doc");
}

void ft_error(char *error_message, t_info  *data)
{
    ft_putstr_fd(error_message, 2);
    data->command_result = 1;

    exit(0);
}

void	ft_perror_exit_child(char *str, int error)
{
    // возможно надо подавать структуру дату
	if (str != NULL)
		perror(str);
	exit(error);
}

/*
void command_result_processing (t_info *struktura)
{ // перезаписываю - иногда выдаёт 1 иногда 0 
// 0 - когда успешно
// 1 - когда неуспешно
    if (struktura->command_result != -1)
        struktura->command_result = 1;
//
    else
        struktura->command_result = 0;

// 127 - команда не найдена 
}
*/
