#include <unistd.h>

int main(int argc, char** argv)
{
	int ascii[255] = {0};
	int move_argc;
	int move_argv;

	if (argc == 3)
	{
		move_argc = 1;
		while (move_argc < 3)
		{
			move_argv = 0;
			while (argv[move_argc][move_argv])
			{
				if (!ascii[(unsigned char)argv[move_argc][move_argv]])
				{
					ascii[(unsigned char)argv[move_argc][move_argv]] = 1;
					write(1, &argv[move_argc][move_argv], 1);
				}
				move_argv++;
			}
			move_argc++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
