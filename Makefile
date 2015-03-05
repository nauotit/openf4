
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
# std=c++11 required by forward_list
#CFLAGS= -O3 -g -Wall -std=c++11
CFLAGS= -g -Wall -std=c++11
#LDFLAGS=
LDFLAGS= -lblas -llapack -lgivaro -lgmpxx -lgmp -lmpfr -llinbox
EXEC = example

# Regression tests
obj/test-monomial.o: example/test-monomial.cpp 
	$(CC) $(CFLAGS) -o $@ -c $<

bin/test-monomial: obj/test-monomial.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-memory-monomial.o: example/test-memory-monomial.cpp 
	$(CC) $(CFLAGS) -o $@ -c $<

bin/test-memory-monomial: obj/test-memory-monomial.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-term.o: example/test-term.cpp 
	$(CC) $(CFLAGS) -o $@ -c $<

bin/test-term: obj/test-term.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-polynomial.o: example/test-polynomial.cpp 
	$(CC) $(CFLAGS) -o $@ -c $<

bin/test-polynomial: obj/test-polynomial.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-tagged-polynomial.o: example/test-tagged-polynomial.cpp 
	$(CC) $(CFLAGS) -o $@ -c $<

bin/test-tagged-polynomial: obj/test-tagged-polynomial.o 
	$(CXX) -o $@ $^ $(LDFLAGS)


# Intermediate rules

example: bin/test-monomial bin/test-memory-monomial bin/test-polynomial bin/test-term bin/test-tagged-polynomial

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
