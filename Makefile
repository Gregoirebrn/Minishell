########################################################################################################################
#                                                       VARIABLE                                                       #
########################################################################################################################

SRCS		:=	main.c				\
				parser.c			\
				init.c				\
				init_utils.c		\
				parser_utils.c		\
				parser_utils_2.c	\
				parser_utils_3.c	\
				format.c			\
				format_utils.c		\
				format_utils_2.c	\
				format_utils_3.c	\
				rewind_lst.c

SRCS_D		:=	srcs/

OBJS_D		:=	objs/

OBJS		:=	$(SRCS:%.c=$(OBJS_D)%.o)

HEAD		:=	includes/minishell.h	\
				includes/parser.h

HEAD_D		:=	.

CFLAGS		:=	-Wall -Wextra -Werror -g3

NAME		:=	minishell

########################################################################################################################
#                                                         LIB                                                          #
########################################################################################################################

LIB			:=	libft.a

LIB_D		:=	super_libft/

LIB_I		:=	$(LIB_D)

LIB_H		:=	$(LIB_I)libft.h

LIB_A		:=	$(addprefix $(LIB_D), $(LIB))

########################################################################################################################
#                                                        RULES                                                         #
########################################################################################################################

all			:	lib
				$(MAKE) $(NAME)

lib			:
				$(MAKE) -C $(LIB_D)

$(NAME)		:	$(OBJS_D) $(OBJS) $(LIB_A) $(HEAD)
				$(CC) $(CFLAGS) -lreadline -o $(NAME) $(OBJS) $(LIB_A)

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD) $(LIB_H)
				$(CC) $(CFLAGS) -I/usr/include -Isuper_libft -c $< -o $@

$(OBJS_D)	:
				@mkdir -p $(OBJS_D)

########################################################################################################################
#                                                        COMMANDS                                                      #
########################################################################################################################

clean		:
				$(RM) -r $(OBJS) $(OBJS_D)
				$(MAKE) clean -C super_libft

fclean		:	clean
				$(RM) $(NAME) $(NAME_B)
				$(MAKE) fclean -C super_libft

re			:	fclean all

.PHONY: all clean fclean re lib