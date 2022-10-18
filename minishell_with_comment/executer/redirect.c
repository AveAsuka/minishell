#include "minishell.h"

/* 2) Перенаправление вывода - COMMAND_OUTPUT, " > "
1. если нет файла - создать (через open);
2. если есть - перезаписать  */
void redirect_output(char *file_name, char *type, t_redir *redir_str)
{	
// 1. В любом случае создаётся создается файл 
    if (ft_strncmp_mod(">", type, 1)) // значит имеем дело с ">"
    {
		redir_str->outfile = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);  
        if (redir_str->outfile == -1) // если он уже есть, тогда...
			printf("Error!\n");
    }
    else // значит имеем дело с ">>"
    {
		redir_str->outfile = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
        if (redir_str->outfile == -1)
			printf("Error!\n");
    }

// 2. Меняем fd-ник
printf("[!!!] Outfile = %d\n", redir_str->outfile);
	if (dup2(redir_str->outfile, 1) == -1) // меняем вывод в терминал (1) на файл
		ft_perror_exit_child("Inside child dup error", 1);
	close (redir_str->outfile);
}

// Перенаправление ввода - redirecting input, " < "
void redirect_input(char *file_name, t_redir *redir_str)
{
// printf("Input check\n");`
   
    redir_str->infile = open(file_name, O_RDONLY);
printf("Infile = %d\n", redir_str->infile);
    if (redir_str->infile == -1)
		printf("%s: No such file or directory\n", file_name);

	if (dup2(redir_str->infile, 0) == -1) // меняем ввод c терминал (0) на c файла
		ft_perror_exit_child("Inside child dup error", 1);
	close (redir_str->infile);
}

/* Cтоп-слово, "<<". Надо чтобы документ очищался в конце работы программы! */
void	stop_word(char *limiter, t_redir *redir_str, int tmpin) 
{ // << b << a pwd > c
	char	*buff;
	char	*tmp;
	int t_outfile; // Временный вывод, на временный документ

	t_outfile = 1;
	buff = NULL;
	tmp = NULL;

	if (redir_str->infile != 0)
	{
		redir_str->infile = 0;
		if (dup2 (tmpin, 0) == -1)
			ft_perror_exit_child("Inside child dup error", 1);
	}

// Создаём временный файл, в котором копим то, что введено с терминала
// open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);  
	t_outfile = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (t_outfile == -1)
		printf("Error!\n");
printf("before tmp = %s\n", tmp);
	tmp = readline("> "); // Запускаем новый ридлайн под ввод
printf("after tmp = %s\n", tmp);

// Крутим вечный цикл до ввода стоп-слова: пока существует ридлайн
// и пока сравнение конечного результата совпадет со стоп-словом
// int a = ft_strncmp(tmp, limiter, ft_strlen(limiter));
	while (tmp && ft_strncmp(tmp, limiter, ft_strlen(limiter)))
	{
/* Мне не совсем понятно смысл использовать отдельный бафф -
чтобы корректно завершать строку, или нельзя отправлять во
write readline? Будет ли добавляться "> "? */
		buff = ft_strjoin(tmp, "\n\0");
		
// Мне пока не совсем понятно по какой логике это работает
		write(t_outfile, buff, ft_strlen(buff));
		free(buff);

// [!] Этот момент возможно не на своём месте, учесть!
        free(tmp);
		tmp = readline("> ");
	}
	free(tmp);
	close(t_outfile);  // Закончили запись во временный файл

/* По сути вариант: "команда + <<что-то" работает штатно, теперь
сложность главная с 'перекачкой' из .here_doc в док посредством cat. 
Новая часть, делаем перенаправление ввода. */
    redir_str->infile = open(".here_doc", O_RDONLY);
    if (redir_str->infile == -1)
		printf("%s: No such file or directory\n", ".here_doc");
	if (dup2(redir_str->infile, 0) == -1) // меняем ввод c терминала (0) на файл
		ft_perror_exit_child("Inside child dup error", 1);
	close (redir_str->infile);
}

void redirect_action(char *type, char *file, t_redir *redir_str, int tmpin)
{
	if (ft_strncmp_mod(">", type, 1) || ft_strncmp_mod(">>", type, 2)) // 
		redirect_output( file, type, redir_str); // data,
	else if (ft_strncmp_mod("<", type, 1))
		redirect_input( file, redir_str); // data,
	else if (ft_strncmp_mod("<<", type, 2))
		stop_word(file, redir_str, tmpin);
}

int redirect_enumeration(t_cmd   *tmp, int tmpin)
{
	int i;

	i = 0;
	if (tmp->redir->type && tmp->redir->file)
    {
        while (tmp->redir[i].type)
        { 
// printf("before redirect_action: infile = %d, outfile = %d\n", 
//     tmp->redir[i].infile, tmp->redir[i].outfile);

            redirect_action(tmp->redir[i].type, tmp->redir[i].file,
                tmp->redir, tmpin);
            i++;

// printf("After redirect_action in pipe: infile = %d, outfile = %d\n", 
//     tmp->redir[i].infile, tmp->redir[i].outfile);
            }
        }
// printf("END. After redirect_action in pipe: infile = %d, outfile = %d\n", 
//     tmp->redir->infile, tmp->redir->outfile);

	return (i);
}


























/* Временная функция, удалить 
int	main()
{
	char	*line;
	char	**a;

	t_redir	*redir_str;
	redir_str = (t_redir *)malloc(sizeof(t_redir));
	redir_str->infile = 0;	// < ввод, ОТКУДА считываем, по умолчанию 0
	redir_str->outfile = 1;	// > вывод, КУДА считываем,по умолчанию 1

	while (1)
	{
		line = readline("minishell>> ");
		a = ft_split(line, ' ');
		redirect_action(a[0], a[1], redir_str);
		free(a);
	}
}
*/

/*  Общая информация: 

	I. Функция:
int dup2(int old_handle, int new_handle)
Функция dup2() дублирует old_handle как new_handle. Если имеется файл, который был связан с new_handle
до вызова dup2(), то он будет закрыт. В случае успеха возвращается 0, а в случае ошибки —1. 
При ошибке errno устанавливается в одно из следующих значений:
EMFILE	Открыто слишком много файлов
EBADF	Недействительный дескриптор файла

	II. Чужой алгоритм: 
1) dup_fd: fd = dup(1); dup2(file, 1); close не делал!
// Сохранение терминального дескриптора и смена его на файловый

2) fd = dup_cmd

3) execution (перемычка)

4) redup_cmd(fd, data): // структура
dup2(fd, 1); close(fd);
// Обратная смена терминального дескриптора и его закрытие

	III. Логика редиректов:
1) в логической группе их может быть сколько угодно, НО команда всегда одна;
2) команда в логической группе может находится где угодно, это не принципиально; 
3) правее редиректа ВСЕГДА стоит название файла: если такого файла не существует, 
то при перенаправлении вывода он создаётся, при вводе это ошибка;
4) в частном случае "<<" не название файла, а стоп-слово;
5)[!] важный момент с очередностью (кстати, она УЖЕ установлена):
	1. после чего делаем / выполнения какого условия? (при редиректе "<<");
	2. откуда делаем? (по умолчанию из терминала ИЛИ редирект "<" ИЛИ временный файл "<");
	3. куда делаем? (по умолчанию в терминал ИЛИ редиректы ">" и ">>");
	4. что делаем? (команда).
	Команда и редиректы же, как уже понятно, уточняют контекст события. 
6)[!] перенаправление ввода может не оказать влияния на некоторые команды, так как
они не имеют входа (например "ls" или "pwd");
7) тонкий момент с перенаправлением ввода - на некоторых командах он и не нужен -
они "берут" файл сами по умолчанию;
8)[!] если перенаправление ввода/вывода делаем многократно, то команда работать
будет только с ПОСЛЕДНЕЙ введённой, причём можно повторять названия файлов,
НО у "<<" есть свои свойства:
- срабатывают все стоп-слова поочередно, причём сохраняется интервал только между
двумя последними стоп-словами;
- считать это надо отдельным документом, поэтому он "конфликтует" с "<" по
следующей логике - в работу идёт только последний упомянутый в строке 
(либо "<", "<<").
*/

/* Ненужная функция
	// Возвращение файлового дескриптора на исходное.
void	return_redirect(t_redir	*redir_str, int fd)
{	
	// printf("[!] %d\n", redir_str->outfile);

	if (redir_str->outfile != 1)
	{
		if (dup2(fd, redir_str->outfile) == -1)
			ft_perror_exit_child("Inside child dup error", 0);
	}
	if (redir_str->infile != 0)
	{
		if (dup2(fd, redir_str->infile) == -1)
			ft_perror_exit_child("Inside child dup error", 0);
	} // код ошибки 2-ым параметром возможно неправильный

// Закрытие текущего дескриптора происходит позже
}
*/