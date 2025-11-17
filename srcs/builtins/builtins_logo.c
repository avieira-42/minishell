#include "../../libs/libft/include/libft.h"

void	builtins_logo_part_1(void)
{
	ft_printf("\n\n\n\n\n");
	ft_printf("███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗");
	ft_printf("██╗     ██╗     \n");
	ft_printf("████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝");
	ft_printf("██║     ██║     \n");
	ft_printf("██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ");
	ft_printf("██║     ██║     \n");
	ft_printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ");
	ft_printf("██║     ██║     \n");
	ft_printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗");
	ft_printf("███████╗███████╗\n");
}

void	builtins_logo_part_2(void)
{
	ft_printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝");
	ft_printf("╚══════╝╚══════╝\n\n");
	ft_printf("A shell project created by Julio Cesar and Alexandre Soeiro at");
	ft_printf(" 42_Porto\n\n");
	ft_printf("Type:  ");
	ft_printf("\n");
	ft_printf("       authors   for more info about the awesome ");
	ft_printf("creators\n\n");
	ft_printf("       logo      to see this cool ");
	ft_printf("logo again\n\n");
	ft_printf("       help      to get some ");
	ft_printf("help\n\n");
}

void	builtins_logo_part_3(void)
{
	ft_printf("       man       to understand how to navigate this awesome ");
	ft_printf("shell\n\n");
	ft_printf("       credits   to get a definitely not boring text ");
	ft_printf("screen\n\n");
	ft_printf("       ???       the special command we created that is");
	ft_printf("\n");
	ft_printf("                 definitely not hidden for you to ");
	ft_printf("guess\n");
	ft_printf("\n\n\n\n\n");
}

int	builtins_logo(void)
{
	builtins_logo_part_1();
	builtins_logo_part_2();
	builtins_logo_part_3();
	return (0);
}
