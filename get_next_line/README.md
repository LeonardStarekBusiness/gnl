_This project has been created as part of the 42 curriculum by lstarek_

	DESCRIPTION
The goal is to read content line by line. Whether it's a file or stdin. The only argument is the file descriptor, the function remembers where you are in the file, using a static variable. Different buffer sizes are supported.

	INSTRUCTIONS
There is no Makefile
You have to compile either
cc -Wall -Wextra Werror get_next_line.c get_next_line_utils.c
or
cc -Wall -Wextra Werror get_next_line_bonus.c get_next_line_utils_bonus.c
depending on whether you are testing mandatory or bonus.
To quickly test different buffer sizes use this flag on cc: -D BUFFER_SIZE=n

	RESOURCES
Friends told me about the general idea, such as having a stash, buffer, and readbuffer.
Francinette was used to test & find edge cases.


	ALGORITHM USED
BUFFER_SIZE bytes are read into the readbuffer. if EOF is not reached or no newline is contained, read() is called again and readbuffer and buffer are joined, until this condition is reached.
The function then returns everything up to the newline and remembers everything after the newline in the stash.
In the bonus, the stash is simply a char[][] instead of a char[]. Not much changes at all.
