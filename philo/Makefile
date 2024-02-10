# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 17:11:21 by fporciel          #+#    #+#              #
#    Updated: 2024/02/10 17:21:32 by fporciel         ###   ########.fr        #
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

# Here is the variable used to establish the maximum value allowed as an input
# for the argument 'Number of philosophers'. See the 'philo_input_check.c' file
# for more details.
MAXTHREADS := $(shell cat /proc/sys/kernel/threads-max)
# Here is the variable used to store the definition of the max number of
# philosophers allowed by the program. See the 'philo_input_check.c' file for
# more details.
MAXPHILOS := -DMAXPHILO=$(MAXTHREADS)
