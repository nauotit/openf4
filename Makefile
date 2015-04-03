
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

#CXX=clang++
CXX=g++-4.9
#std=c++11 required by forward_list
CFLAGS= -O3 -Wall -funroll-loops -ftree-vectorize -std=c++11 -DNDEBUG -Wno-strict-overflow 
#CFLAGS= -O3 -g -Wall -std=c++11 -Wno-strict-overflow
#CFLAGS= -g -Wall -std=c++11 
#LDFLAGS= -lblas -llapack -lgivaro -lgmpxx -lgmp -lmpfr -llinbox
LDFLAGS= 

EXEC = example benchmark

# Regression tests
obj/test-monomial.o: example/test-monomial.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/test-monomial: obj/test-monomial.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-monomial-array.o: example/test-monomial-array.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/test-monomial-array: obj/test-monomial-array.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-memory-monomial.o: example/test-memory-monomial.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/test-memory-monomial: obj/test-memory-monomial.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-term.o: example/test-term.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/test-term: obj/test-term.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-single-list.o: example/test-single-list.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/test-single-list: obj/test-single-list.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-polynomial.o: example/test-polynomial.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/test-polynomial: obj/test-polynomial.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-tagged-polynomial.o: example/test-tagged-polynomial.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/test-tagged-polynomial: obj/test-tagged-polynomial.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-critical-pair.o: example/test-critical-pair.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/test-critical-pair: obj/test-critical-pair.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-matrix.o: example/test-matrix.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/test-matrix: obj/test-matrix.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-element-prime.o: example/test-element-prime.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/test-element-prime: obj/test-element-prime.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-ideal.o: example/test-ideal.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/test-ideal: obj/test-ideal.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-dynamic-array.o: example/test-dynamic-array.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/test-dynamic-array: obj/test-dynamic-array.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-avl-monomial.o: example/test-avl-monomial.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/test-avl-monomial: obj/test-avl-monomial.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-avl-polynomial.o: example/test-avl-polynomial.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/test-avl-polynomial: obj/test-avl-polynomial.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-avl-critical-pair.o: example/test-avl-critical-pair.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/test-avl-critical-pair: obj/test-avl-critical-pair.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/test-avl-pointer-critical-pair.o: example/test-avl-pointer-critical-pair.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/test-avl-pointer-critical-pair: obj/test-avl-pointer-critical-pair.o 
	$(CXX) -o $@ $^ $(LDFLAGS)


# Benchmark 
obj/benchmark-int.o: benchmark/benchmark-int.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/benchmark-int: obj/benchmark-int.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/benchmark-long.o: benchmark/benchmark-long.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/benchmark-long: obj/benchmark-long.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/benchmark-semaev.o: benchmark/benchmark-semaev.cpp 
	$(CXX) $(CFLAGS) -o $@ -c $<

bin/benchmark-semaev: obj/benchmark-semaev.o 
	$(CXX) -o $@ $^ $(LDFLAGS)


# Intermediate rules

example: bin/test-ideal bin/test-avl-pointer-critical-pair bin/test-single-list bin/test-polynomial bin/test-tagged-polynomial bin/test-monomial bin/test-monomial-array bin/test-critical-pair bin/test-avl-critical-pair  bin/test-avl-polynomial bin/test-avl-monomial bin/test-dynamic-array bin/test-matrix bin/test-element-prime
# bin/test-term
benchmark: bin/benchmark-int bin/benchmark-long bin/benchmark-semaev

all: $(EXEC)

# systematically rebuild dependencies
.PHONY: clean distclean

clean:
	rm -f obj/*.o bin/* data/*.pgm

# require the indent program (GNU indent)
#indent: 
	#indent -nbad -bap -nbc -bbo -bl -bli0 -bls -ncdb -nce -cp1 -ncs -di2 -ndj -nfc1 -nfca -hnl -i4 -ip4 -lp -pcs -nprs -psl -saf -sai -saw -nsc -nsob -nut src/*.inl
	#indent -nbad -bap -nbc -bbo -bl -bli0 -bls -ncdb -nce -cp1 -ncs -di2 -ndj -nfc1 -nfca -hnl -i4 -ip4 -lp -pcs -nprs -psl -saf -sai -saw -nsc -nsob -nut include/*.h
# -nut: not use tab
# -i4: indent to 4 spaces
# -bli0: braces on the same column than if
# -ncs: no space between the cast operator and the object
# -nbc: no newline after each comma in a declaration.
