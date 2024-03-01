# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/01 13:03:35 by fporciel          #+#    #+#              #
#    Updated: 2024/03/01 15:45:27 by fporciel         ###   ########.fr        #
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
# This is the Makefile to build the program.
#

.PHONY: all clean fclean re memtest threadtest remem rethread autogit
.DEFAULT_GOAL: all
NAME := philo
DIR := $(shell pwd)
MAIN := philosophers.c
HEADER := philo.h
SRCS := $(filter-out $(MAIN), $(wildcard philo*.c))
OBJS := $(patsubst %.c, %.o, $(SRCS))
AOBJS := $(patsubst %.c, %.a, $(SRCS))
TOBJS := $(patsubst %.c, %.t, $(SRCS))
MAXTHREADS := $(shell cat /proc/sys/kernel/threads-max)
MAXPHILOS := $(shell expr $(MAXTHREADS) - 3)
CC := gcc
CSTD := -std=c17 -pedantic-errors
CFLAGS := -Wall -Wextra -Werror
AFLAGS := -fsanitize=address -fno-omit-frame-pointer
TFLAGS := -fsanitize=thread
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
	@$(CC) $(CSTD) $(CFLAGS) $(COPT) $(INCLUDE) $(DMAXPHILOS) \
		$(HEADER) $(SRCS) -c

memtest: $(AOBJS)
	@$(CC) $(CSTD) $(CFLAGS) $(COPT) $(INCLUDE) $(DMAXPHILOS) $(AFLAGS) \
		$(HEADER) $(MAIN) $(AOBJS) $(LFLAGS) $(LAFLAGS) -o $(NAME)

$(AOBJS): $(SRCS)
	@$(CC) $(CSTD) $(CFLAGS) $(COPT) $(INCLUDE) $(DMAXPHILOS) $(AFLAGS) \
		$(HEADER) $(SRCS) -c

threadtest: $(TOBJS)
	@$(CC) $(CSTD) $(CFLAGS) $(COPT) $(INCLUDE) $(DMAXPHILOS) $(TFLAGS) \
		$(HEADER) $(MAIN) $(TOBJS) $(LFLAGS) $(LTFLAGS) -o $(NAME)

$(TOBJS): $(SRCS)
	@$(CC) $(CSTD) $(CFLAGS) $(COPT) $(INCLUDE) $(DMAXPHILOS) $(TFLAGS) \
		$(HEADER) $(SRCS) -c

clean:
	@rm -f $(OBJS) $(AOBJS) $(TOBJS)
	@rm -f $(HEADER).gch

fclean: clean
	@rm -f $(NAME)

re: fclean all

remem: fclean memtest

rethread: fclean threadtest

autogit: fclean
	@git status
	@git add *
	@git status
	@echo "\nEnter commit:"
	@read commit; git commit -m "$$commit"
	@git status
	@git push
