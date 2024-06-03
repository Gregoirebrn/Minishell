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
				format_utils_3.c

EXEC		:=	builtins.c			\
				builtins_utils.c	\
				builtins_utils2.c	\
				piping.c			\
				piping_utils.c		\
				piping_utils2.c		\
				piping_utils3.c		\
				export_no_args.c	\
				built_exit.c

VALGRIND	:=	valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all\
				--track-fds=yes --show-mismatched-frees=yes --read-var-info=yes -s --trace-children=yes

IGN_LEAK	:=	valgrind_ignore_leaks.txt

$(IGN_LEAK)		:
				@echo "{"                                > $(IGN_LEAK)
				@echo "    leak readline"                    >> $(IGN_LEAK)
				@echo "        Memcheck:Leak"                >> $(IGN_LEAK)
				@echo "        ..."                        >> $(IGN_LEAK)
				@echo "        fun:readline"                 >> $(IGN_LEAK)
				@echo "}"                                >> $(IGN_LEAK)
				@echo "{"                                >> $(IGN_LEAK)
				@echo "    leak add_history"                >> $(IGN_LEAK)
				@echo "        Memcheck:Leak"                >> $(IGN_LEAK)
				@echo "        ..."                        >> $(IGN_LEAK)
				@echo "        fun:add_history"            >> $(IGN_LEAK)
				@echo "}"                                >> $(IGN_LEAK)
				@echo "{"                                >> $(IGN_LEAK)
				@echo "    leak readline_internal_char"    >> $(IGN_LEAK)
				@echo "        Memcheck:Leak"                >> $(IGN_LEAK)
				@echo "        ..."                        >> $(IGN_LEAK)
				@echo "        fun:readline_internal_char"    >> $(IGN_LEAK)
				@echo "}"                                >> $(IGN_LEAK)

SRCS_D		:=	srcs/

OBJS_D		:=	objs/

EXEC_D		:=	exec/

OBJS		:=	$(SRCS:%.c=$(OBJS_D)%.o)\

OBJS_E		:=	$(EXEC:%.c=$(OBJS_D)%.o)\

HEAD		:=	includes/minishell.h	\
				includes/parser.h		\
				includes/builtins.h

HEAD_D		:=	.

ifeq ($(shell uname), Darwin)
READLINE_DIR	=	$(shell brew --prefix readline)
endif
READLINE_LIB	=	-lreadline -lhistory -L $(READLINE_DIR)/lib

CFLAGS		:=	-Wall -Wextra -Werror -g3 -I$(READLINE_DIR)/include

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

leaks		:	all $(IGN_LEAK)
				$(VALGRIND) ./$(NAME)

$(NAME)		:	$(OBJS_D) $(OBJS) $(OBJS_E) $(LIB_A) $(HEAD)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(OBJS_E) $(LIB_A) -lm ${READLINE_LIB}

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD) $(LIB_H)
				$(CC) $(CFLAGS) -Isuper_libft -c $< -o $@

$(OBJS_E)	:	$(OBJS_D)%.o: $(EXEC_D)%.c $(HEAD) $(LIB_H)
				$(CC) $(CFLAGS) -Isuper_libft -c $< -o $@

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
