NAME := minishell

NAME_C := nullshell.c
HDR_DIR = .

#Libs
HLP_DIR :=	./helpers
HLP_ARC :=	$(HLP_DIR)/lib/libft.a		\
			$(HLP_DIR)/lists/lst.a		\
			$(HLP_DIR)/print/prt.a		\

SRC_DIR :=	./src
SRC_ARC :=	$(SRC_DIR)/exe/exe.a		\
			$(SRC_DIR)/arg/arg.a		\
			$(SRC_DIR)/command/cmd.a	\
			$(SRC_DIR)/data/data.a		\
			$(SRC_DIR)/env/env.a		\
			$(SRC_DIR)/parse/parse.a	\



ALL_ARC := $(SRC_ARC) $(HLP_ARC) 

ALL_C := $(foreach arc, $(ALL_ARC), $(wildcard $(dir $(arc))*.c))

#Vars
MAKEFLAGS += --no-print-directory

FLAGS := -Wall -Wextra -Werror

LINKS := -lreadline

RM := rm -f

blank :=
define NEWLINE

$(blank)
endef

COLOUR_GREEN := \033[1;32m
COLOUR_RED := \033[1;31m
COLOUR_YELLOW := \033[1;33m
COLOUR_BLUE := \033[1;34m
COLOR_WHITE := \033[0m

all: $(NAME)

$(NAME): $(ALL_ARC) $(NAME_C)
	@cc $(FLAGS) -o $@ -I$(HDR_DIR) $(NAME_C) $(ALL_ARC) -lreadline
	@echo "$(COLOUR_GREEN)Made main file$(COLOR_WHITE)"

$(ALL_ARC): $(ALL_C)
ifeq ($($?),)
	@echo "$(COLOUR_BLUE)Updating archives of $@$(COLOR_WHITE)"
	@cd $(dir $@ ) && make
	@touch $@
endif

clean:
	@echo "$(COLOUR_YELLOW)Cleaning archives$(COLOR_WHITE)"
	@$(foreach dir,$(dir $(SRC_ARC)), cd $(dir) && make fclean && echo$(NEWLINE)$(NEWLINE))
	@$(foreach dir,$(dir $(HLP_ARC)), cd $(dir) && make fclean && echo$(NEWLINE)$(NEWLINE))


fclean: 
	@echo "$(COLOUR_YELLOW)Cleaning everything$(COLOR_WHITE)"
	@$(RM) $(NAME)
	@$(foreach dir,$(dir $(SRC_ARC)), cd $(dir) && make fclean && echo$(NEWLINE)$(NEWLINE))
	@$(foreach dir,$(dir $(HLP_ARC)), cd $(dir) && make fclean && echo$(NEWLINE)$(NEWLINE))

re: re_libs all
	
re_libs:
	@echo "$(COLOUR_BLUE)Remaking everything$(COLOR_WHITE)"
	@$(foreach dir,$(dir $(SRC_ARC)), cd $(dir) && make re && echo$(NEWLINE)$(NEWLINE))
	@$(foreach dir,$(dir $(HLP_ARC)), cd $(dir) && make re && echo$(NEWLINE)$(NEWLINE))


.PHONY: all clean fclean re
