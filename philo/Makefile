# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 17:11:21 by fporciel          #+#    #+#              #
#    Updated: 2024/02/16 12:51:33 by fporciel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# This is the Makefile used to compile the Philosophers program.
# Copyright (C) 2024  Federico Porciello
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
# https://github.com/fporciel2
#

# In this Makefile, all the variables are statically named.
#
# Let's set up the phony rules, the default goal and the name of the final
# program. 'all' simply executes the default goal, 'clean' removes the object
# files and the library, 'fclean' removes the executable and 're' executes
# 'clean', 'fclean' and 'all'. The default goal will be the program's name.
# Since this program involves memory allocation and threading, there are four
# extra phony rules: one to compile using 'libasan', one to compile using
# 'libtsan', one to execute the 'memcheck' Valgrind's tool, and one to execute
# the 'helgrind' Valgrind's tool.
.PHONY: all clean fclean re asan tsan memcheck helgrind
NAME := philo
.DEFAULT_GOAL: $(NAME)
# Another useful variable is the current directory, that will be an important
# reference.
CURDIR := $(shell pwd)
# Here is the variable used to establish the maximum value allowed as an input
# for the argument 'Number of philosophers'. See the 'philo_input_check.c' file
# for more details.
MAXTHREADS := $(shell cat /proc/sys/kernel/threads-max)
# Here is the variable used to store the definition of the max number of
# philosophers allowed by the program. See the 'philo_input_check.c' file for
# more details.
MAXPHILOS := -DMAXTHREADS=$(MAXTHREADS / 2 + 1)
# Since there are no external headers to include, the only header to take into
# account is the main Philosopher's header. Here there are the variable for the
# compiler's inclusion option and the naming of the header.
INCLUDE := -I$(CURDIR)
HEADER := $(wildcard philo*.h)
# Here we will name the source files and the object files. Since the main
# function is in the 'philosophers.c' file, it will not be used as a source
# file, and will be not objectified. It will be directly compiled against the
# object files when is time to link them with the standard libraries.
SRCS := $(filter-out philosophers.c, $(wildcard philo*.c))
OBJS := $(patsubst %.c, %.o, $(SRCS))
# Finally, we will name the compiler invocation, the flags to pass to the
# compiler, the options to pass to the compiler in order to check the validity
# of the input and to locate the header, and the libraries to include. It is
# important to note that the linking of the 'pthread' library requires the
# inclusion of the 'pthread.h' header into the header and the definition of the
# default source. Please note that the standard applied is C11 due to the need
# to use 'usleep', that is not allowed by C17. 
CC := gcc
CFLAGS := -std=c11 -pedantic-errors -Wall -Wextra -Werror -O3 -march=native -g
OPT := $(MAXPHILOS) $(INCLUDE) $(HEADER)
LDFLAGS := -lc -lpthread
# For readability, I will merge the variables.
COMPILEPROGRAM := $(CC) $(CFLAGS) $(OPT) philosophers.c $(OBJS) $(LDFLAGS)

# The first rule is the default goal. It requires the compilation of the source
# files.
$(NAME): $(OBJS)
	$(COMPILEPROGRAM) -o $@

# Then, the 'all' rule simply executes the default goal.
all: $(NAME)

# The objects are created using a rule that explicitly names the source files.
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(OPT) -c $^

# The 'clean' rule removes only the object files.
clean:
	rm -f $(OBJS)

# The 'fclean' rule removes the executable file and requires that object files
# are already removed.
fclean: clean
	rm -f $(NAME)

# Finally, the 're' rule executes the default goal after cleaning both the
# object files and the executable file.
re: clean fclean

