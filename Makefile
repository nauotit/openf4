
# Copyright (C) 2010 Antoine Joux and Vanessa Vitse 

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>. 

CXX=g++
CFLAGS= -O3 -g -Wall 
LDFLAGS=
#LDFLAGS= -lblas -llapack -lgivaro -lgmpxx -lgmp -lmpfr -llinbox
OBJ = obj/monomial.o obj/polynomial.o obj/taggeg-polynomial.o obj/critical-pair.o obj/matrix.o obj/ideal.o
EXEC = example

# common files

obj/%.o: src/%.inl include/%.h 
	$(CXX) $(CFLAGS) -D -o $@ -c $<

# Specific files:

# Regression tests
obj/test-monomial.o: example/test-monomial.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

bin/test-monomial: obj/monomial.o obj/test-monomial.o 
	$(CXX) -o $@ $^ $(LDFLAGS)


# Intermediate rules

example: test-monomial

all: $(EXEC)

# systematically rebuild dependencies
.PHONY: clean distclean

clean:
	rm -f obj/*.o bin/* 

# require the indent program (GNU indent)
indent: 
	indent -nbad -bap -nbc -bbo -bl -bli0 -bls -ncdb -nce -cp1 -ncs -di2 -ndj -nfc1 -nfca -hnl -i4 -ip4 -lp -pcs -nprs -psl -saf -sai -saw -nsc -nsob -nut src/*.inl
	indent -nbad -bap -nbc -bbo -bl -bli0 -bls -ncdb -nce -cp1 -ncs -di2 -ndj -nfc1 -nfca -hnl -i4 -ip4 -lp -pcs -nprs -psl -saf -sai -saw -nsc -nsob -nut include/*.h
# -nut: not use tab
# -i4: indent to 4 spaces
# -bli0: braces on the same column than if
# -ncs: no space between the cast operator and the object
# -nbc: no newline after each comma in a declaration.
