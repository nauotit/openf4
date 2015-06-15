# -*- coding: utf-8 -*-
r"""
Groebner basis computation in finite fields using F4 algorithm.

AUTHORS:

- Vanessa VITSE (2015)

- Antoine JOUX (2015)

- Titouan COLADON (2015)

EXAMPLES:

We compute a Groebner basis for some given ideal. The type returned by
the ``groebner_basis`` method is ``PolynomialSequence``, i.e. it is not a
:class:`MPolynomialIdeal`::

    sage: R.<x1,x2,x3,x4,x5,x6,x7,x8> = Zmod(65521)[]
    sage: I = sage.rings.ideal.Cyclic(R,8)
    sage: time B=groebner_basis_f4(I)
    sage: type(B)
    <class 'sage.rings.polynomial.multi_polynomial_sequence.PolynomialSequence_generic'>

TESTS::

    sage: from sage.rings.polynomial.groebner_basis_f4 import groebner_basis_f4
    sage: R.<a,b,c,d,e,f> = Zmod(65521)[]
    sage: I = sage.rings.ideal.Cyclic(R,6)
    sage: time B=groebner_basis_f4(I)
    
    sage: from sage.rings.polynomial.groebner_basis_f4 import groebner_basis_f4
    sage: F.<t>=GF(2)[]
    sage: K.<t>=GF(2^31, name='t', modulus=t^31+t^3+1)
    sage: R.<x0,x1,x2,x3,x4,x5> = K[]
    sage: I = ideal((t+t^3)*x0+(t+t^3)*x1+(t+t^3)*x2+(t+t^3)*x3+(t+t^3)*x4+(t+t^3)*x5, (t+t^3)*x0*x1+(t+t^3)*x1*x2+(t+t^3)*x2*x3+(t+t^3)*x3*x4+(t+t^3)*x0*x5+(t+t^3)*x4*x5, (t+t^3)*x0*x1*x2+(t+t^3)*x1*x2*x3+(t+t^3)*x2*x3*x4+(t+t^3)*x0*x1*x5+(t+t^3)*x0*x4*x5+(t+t^3)*x3*x4*x5, (t+t^3)*x0*x1*x2*x3+(t+t^3)*x1*x2*x3*x4+(t+t^3)*x0*x1*x2*x5+(t+t^3)*x0*x1*x4*x5+(t+t^3)*x0*x3*x4*x5+(t+t^3)*x2*x3*x4*x5, (t+t^3)*x0*x1*x2*x3*x4+(t+t^3)*x0*x1*x2*x3*x5+(t+t^3)*x0*x1*x2*x4*x5+(t+t^3)*x0*x1*x3*x4*x5+(t+t^3)*x0*x2*x3*x4*x5+(t+t^3)*x1*x2*x3*x4*x5, (t+t^3)*x0*x1*x2*x3*x4*x5-1)
    sage: time B=groebner_basis_f4(I)


.. NOTE::

    Compute a grevlex groebner basis of the ideal.

"""


#*****************************************************************************
#
#                               Sage
#
#       Copyright (C) 2015 Antoine Joux and Vanessa Vitse 
#       Copyright (C) 2015 Titouan COLADON 
#
#  Distributed under the terms of the GNU General Public License (GPL)
#
#    This code is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    General Public License for more details.
#
#  The full text of the GPL is available at:
#
#                  http://www.gnu.org/licenses/
#*****************************************************************************


#include <Python.h>

from libcpp.string cimport string
from libcpp.vector cimport vector

from libc.stdint cimport int64_t

include "sage/ext/interrupt.pxi"


cdef extern from "libf4.h":
    cdef vector[string] groebnerBasisF4(int64_t modulo, int nbVariable, vector[string] variableName, vector[string] polynomialList, int nbThread, int verbose) 
    cdef vector[string] groebnerBasisGF2F4(int nbVariable, vector[string] variableName, vector[string] polynomialList, int nbThread, int verbose) 
#    cdef vector[string] groebnerBasisGivaroIntegerF4(string modulo, int degree, int nbVariable, vector[string] variableName, vector[string] polynomialList, int nbThread, int verbose)
    cdef vector[string] groebnerBasisGF2ExtensionF4(string modulo, int nbVariable, vector[string] variableName, string polyVarName, vector[string] polynomialList, int nbThread, int verbose)

def groebner_basis_f4(self, degree = 10, verbose = 0, nb_thread = 1):
        """
        Computes a Groebner Basis for this ideal using F4

        INPUT:

        EXAMPLES::

            sage: R.<x1,x2,x3,x4,x5,x6> = Zmod(65521)[]
            sage: I = sage.rings.ideal.Cyclic(R,6)
            sage: time B=I.groebner_basis_f4()
            sage: len(B)
            45
        """
        R = self.ring()
        polynomial_list = self.gens()
        cdef vector[string] variable_name = [str(v) for v in R.gens()]
        cdef vector[string] polynomial_list_cpp = [str(poly).replace(" ", "") for poly in polynomial_list]
        cdef vector[string] basis;
        cdef int nb_variable = R.ngens()
        cdef int modulo_int
        cdef string modulo_str
        cdef string poly_var_name = str(self.base_ring().gen())
        
        # Prime field 
        if self.base_ring().is_prime_field():
            if R.characteristic() == 2:
                sig_on()
                basis = groebnerBasisGF2F4(nb_variable, variable_name, polynomial_list_cpp, nb_thread, verbose);
                sig_off()
            elif R.characteristic() < 2**32:
                modulo_int = R.characteristic()
                sig_on()
                basis = groebnerBasisF4(modulo_int, nb_variable, variable_name, polynomial_list_cpp, nb_thread, verbose);
                sig_off()
            else:
                # not handled gmp and givaro version in sage are too old
                print "Prime field with characteristic > 2^32 are not handled in sage for the moment"
#                modulo_str = str(R.characteristic())
#                sig_on()
#                basis = groebnerBasisGivaroIntegerF4(modulo_str, degree, nb_variable, variable_name, polynomial_list_cpp, nb_thread, verbose);
#                sig_off()

        if not self.base_ring().is_prime_field():
            if R.characteristic() != 2:
                # not handled 
                print "Non prime field with characteristic != 2 are not handled by F4"
            elif self.base_ring().modulus().degree() > 63:
                # not handled 
                print "GF(2^n) field with n > 63 are not handled by F4"
            else:
                modulo_str =str(self.base_ring().modulus()).replace("x", str(self.base_ring().gen()))
                sig_on()
                basis = groebnerBasisGF2ExtensionF4(modulo_str, nb_variable, variable_name, poly_var_name, polynomial_list_cpp, nb_thread, verbose);
                sig_off()
        
        from sage.rings.polynomial.multi_polynomial_sequence import PolynomialSequence
        return PolynomialSequence([R(e) for e in basis], R, immutable=True)




