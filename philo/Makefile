NAME = philo

SRCS	=	./philo.c\
./create_philo.c\
./init_philo.c\
./free.c\
./actions.c\
./time.c\
./monitor.c\
./utils.c\
./routine.c\
./destroy.c\
./create_thread.c\
./manage_state.c\


OBJS	=	${SRCS:%.c=${OBJ_D}%.o}

SRC_D =	src/

OBJ_D = objs/

CC = cc

CFLAGS = -Wall -Wextra -Werror

HEADER = philo.h

all		:
	@make --no-print-directory ${NAME}

${OBJS}	:	${OBJ_D}%.o: ${SRC_D}%.c headers/philo.h
	${CC}	${CFLAGS} -c $< -o $@

${NAME}	:	${OBJ_D} ${OBJS} Makefile headers/philo.h
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

${OBJ_D}:
	@mkdir -p ${OBJ_D}

clean	:
	rm -rf ${OBJ_D}

fclean	:	clean
	rm -f ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re%   