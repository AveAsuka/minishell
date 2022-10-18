#include "minishell.h"

/* Если подаются комбинации:
1) больше одного аргумента - написание ошибки и не выход из терминала;
2) если этого точно нет - символа или числа -  написание "exit" и выход из нашей программы/

control+d = "exitell" и выход из нашей программы 
комбинация control+c и control+d = "exit" и выход из нашей программы 

Подается наша контрольная структура и наша строка в терминале,
любопытно - она не записывается в структуру, а тащиться через всю программу -
возможно это можно как-то оптимизировать. 
Это, как выяснилось, как раз оптимизация, чтобы не тащить долгую структуру в 
функцию. */
int check_ex_arg(char *stroka)
{ // тут проверку на цифры и на буквы
	int	res;
	int	i;

	i = 0;
	res = 1;
	if (stroka[i] == '-' || stroka[i] == '+')
		i++;
	while (stroka[i])
	{
		if (!ft_isdigit(stroka[i]))
			res = -1;
		i++;
    }

    if (i == 20)
        res = -1;

    return (res);
}

void built_exit(t_info *struktura)
{       
    int		i;
	char	c;

    if (struktura->stroka[1] == NULL)
	{
		struktura->command_result = 0;
        exit(struktura->command_result); // момент для будущей работы
	}
    else if (struktura->stroka[2] != NULL)
        ft_putstr_fd(": exit: too many arguments\n", 2);
    else if (struktura->stroka[1] != NULL)
    {
        if (check_ex_arg(struktura->stroka[1]) == -1)
        {
            ft_putstr_fd(": exit: ", 2);
		    ft_putstr_fd(struktura->stroka[1], 2);
		    ft_putstr_fd(": numeric argument required\n", 2);
			struktura->command_result = 1;
            exit(255);
        }

		i = ft_atoi(struktura->stroka[1]);
		c = i;
		ft_putstr_fd("exit\n", 1);
		struktura->command_result = 0;
		exit(c);
    }
}
