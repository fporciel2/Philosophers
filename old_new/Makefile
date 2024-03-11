# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 06:01:44 by fporciel          #+#    #+#              #
#    Updated: 2024/03/11 09:45:25 by fporciel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# 'Philosophers' is a simulation of a solution to the dining philosophers
# problem.
# Copyright (C) 2024 Federico Porciello
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# For more information on how to contact me by electronic and paper mail
# please see:
# https://github.com/fporciel2/Philosophers
#

.PHONY: all clean fclean re mem memcheck helgrind thread remem rethread \
	autogit memdebug threaddebug
.DEFAULT_GOAL: all
NAME := philo
DIR := $(shell pwd)
MAIN := philosophers.c
HEADER := philo.h
SRCS := $(filter-out $(MAIN), $(wildcard philo*.c))
OBJS := $(patsubst %.c, %.o, $(SRCS))
MAXTHREADS := $(shell cat /proc/sys/kernel/threads-max)
MAXPHILOS := $(shell expr $(MAXTHREADS) / 2)
CC := gcc
CSTD := -std=c17 -pedantic-errors
CFLAGS := -Wall -Wextra -Werror
AFLAGS := -fsanitize=address -fno-omit-frame-pointer -g
TFLAGS := -fsanitize=thread -g
COPT := -O3 -march=native -g
INCLUDE := -I$(DIR)
DMAXPHILOS := -DMAXPHILOS=$(MAXPHILOS)
LFLAGS := -lc -lpthread
LAFLAGS := -lasan
LTFLAGS := -ltsan

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CSTD) $(CFLAGS) $(COPT) $(INCLUDE) $(DMAXPHILOS) $(HEADER) \
		$(MAIN) $(OBJS) $(LFLAGS) -o $@

$(OBJS): $(SRCS)
	@$(CC) $(CSTD) $(CFLAGS) $(COPT) $(INCLUDE) $(DMAXPHILOS) $(HEADER) \
		$(SRCS) -c

memcheck: all
	@echo "\nEnter parameters for Valgrind's memcheck:"
	@read parameters; valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --verbose ./$(NAME) $$parameters

mem:
	@$(CC) $(CSTD) $(CFLAGS) $(INCLUDE) $(DMAXPHILOS) $(AFLAGS) \
		$(HEADER) $(MAIN) $(SRCS) $(LFLAGS) $(LAFLAGS) -o $(NAME)

helgrind: all
	@echo "\nEnter parameters for Valgrind's helgrind:"
	@read parameters; valgrind --tool=helgrind ./$(NAME) $$parameters

thread: all
	@$(CC) $(CSTD) $(CFLAGS) $(INCLUDE) $(DMAXPHILOS) $(TFLAGS) \
		$(HEADER) $(MAIN) $(SRCS) $(LFLAGS) $(LTFLAGS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -f $(HEADER).gch

fclean: clean
	@rm -f $(NAME)

re: fclean all

remem: fclean mem

rethread: fclean thread

autogit: fclean
	@git status
	@echo "\nIs there anything to remove? [y/n]"
	@read answer; if [ $$answer = "y" ]; \
		then git rm $$(git ls-files --deleted); fi
	@git status
	@git add *
	@git status
	@git commit -m "$(shell date)"
	@git status
	@git push

memdebug: all
	@echo "\nEnter the 'n' value for '--vgdb-error=n':"
	@read n && \
		echo "Enter parameters 'p' to pass to the program:" && \
		read p && \
		tmux new-session -d -s debug_session 'valgrind --leak-check=full \
		--show-leak-kinds=all --track-origins=yes --verbose \
		--vgdb=yes --vgdb-error=$$n ./$(NAME) $$p' && \
		tmux split-window -h -t debug_session && \
		tmux send-keys -t debug_session:0.1 'echo "Use 'target remote | vgdb' \
		to connect GDB."' C-m && \
		tmux send-keys -t debug_session:0.1 'gdb ./philo' C-m && \
		tmux send-keys -t debug_session:0.1 'target remote | vgdb' C-m && \
		tmux attach-session -t debug_session

threaddebug: all
	@echo "\nEnter the 'n' value for '--vgdb-error=n':"
	@read n && \
		echo "Enter parameters 'p' to pass to the program:" && \
		read p && \
		tmux new-session -d -s debug_session 'valgrind --leak-check=full \
		--tool=helgrind --trace-children=yes \
		--track-origins=yes --verbose \
		--vgdb=yes --vgdb-error=$$n ./$(NAME) $$p' && \
		tmux split-window -h -t debug_session && \
		tmux send-keys -t debug_session:0.1 'echo "Use 'target remote | vgdb' \
		to connect GDB."' C-m && \
		tmux send-keys -t debug_session:0.1 'gdb ./philo' C-m && \
		tmux send-keys -t debug_session:0.1 'target remote | vgdb' C-m && \
		tmux attach-session -t debug_session

