#!/bin/bash
#/* Copyright (C) 2014 Carlos Aguilar Melchor, Joris Barrier, Marc-Olivier Killijian
# * This file is part of XPIR.
# *
# *  XPIR is free software: you can redistribute it and/or modify
# *	it under the terms of the GNU General Public License as published by
# *  the Free Software Foundation, either version 3 of the License, or
# *  (at your option) any later version.
# *
# *  XPIR is distributed in the hope that it will be useful,
# *  but WITHOUT ANY WARRANTY; without even the implied warranty of
# *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# *  GNU General Public License for more details.
# *
# *  You should have received a copy of the GNU General Public License
# *  along with XPIR.  If not, see <http://www.gnu.org/licenses/>.
#*/


if [[ ! -d db ]]; then
	mkdir db;
	touch db/foo
fi
/bin/rm -f db/*
for ((  i = 0 ;  i < $2 ; i++  ))
	do
		dd if=/dev/urandom of=db/$i count=$1 bs=1
		#dd if=/dev/zero of=db/test$i count=$1 bs=1024
	done
