 CC_OPT=-Wall -Wextra -Werror
 PROJ="my_printf"
 
 all:
 	gcc ${CC_OPT} my_printf.c -o ${PROJ}
