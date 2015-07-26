dnl Copyright (C) 2015 Antoine Joux, Vanessa Vitse and Titouan Coladon
 
dnl This file is part of openf4.

dnl openf4 is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.

dnl openf4 is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.

dnl You should have received a copy of the GNU General Public License
dnl along with openf4.  If not, see <http://www.gnu.org/licenses/>.


dnl OPENF4_ENABLE_VECTORISATION

dnl Tests SSE2 SSE4.1 and SSE4.2 for and define HAVE_SSE2 HAVE_SSE4_1 HAVE_SSE4_2


AC_DEFUN([OPENF4_ENABLE_VECTORISATION],
         [AC_ARG_ENABLE([vectorisation],
                        [AC_HELP_STRING([--enable-vectorisation],
                        [Use SSE vectorisation (-msse2 -msse4.1 -msse4.2),
                         default=yes])],
                        [with_vectorisation=$enable_vectorisation],
                        [with_vectorisation=yes])
          AC_MSG_CHECKING(for Vectorisation)
          AS_IF([ test "x$with_vectorisation" != "xno" ],
          [
                BACKUP_CXXFLAGS=${CXXFLAGS}
                SSE2FLAGS="-msse2"
                CXXFLAGS="${BACKUP_CXXFLAGS} ${SSE2FLAGS}"
                AC_TRY_RUN([
                    #include <emmintrin.h>
                    int main() 
                    {
                        __m128d P ;
                        double p = 1;
                        P   = _mm_set1_pd(p);
                        P = _mm_add_pd(P,P);
                        return 0;
                    }
                    ],
                    [ sse2_found="yes" ],
                    [ sse2_found="no" ],
                    [
                    echo "cross compiling...disabling"
                    sse2_found="no"
                    ])
                
                SSE4_1FLAGS="-msse4.1"
                CXXFLAGS="${BACKUP_CXXFLAGS} ${SSE4_1FLAGS}"
                AC_TRY_RUN([
                    #include <smmintrin.h>
                    int main() 
                    {
                        __m128d P ;
                        double p = 1;
                        P   = _mm_set1_pd(p);
                        P = _mm_add_pd(P,P);
                        P = _mm_floor_pd(P);
                        return 0;
                    }
                    ],
                    [ sse4_1_found="yes" ],
                    [ sse4_1_found="no" ],
                    [
                    echo "cross compiling...disabling"
                    sse4_1_found="no"
                    ])
                
                SSE4_2FLAGS="-msse4.2"
                CXXFLAGS="${BACKUP_CXXFLAGS} ${SSE4_2FLAGS}"
                AC_TRY_RUN([
                    #include <nmmintrin.h>
                    int main ()
                    {
                        __m128i res = _mm_cmpgt_epi64(_mm_setzero_si128 (), _mm_setzero_si128 ());
                        return 0;
                    }
                    ],
                    [ sse4_2_found="yes" ],
                    [ sse4_2_found="no" ],
                    [
                    echo "cross compiling...disabling"
                    sse4_2_found="no"
                    ])
                
                AS_IF([ test "x$sse4_2_found" = "xyes" ],
                      [
                          AC_DEFINE(HAVE_SSE4_2,1,[Define if SSE4.2 is available])
                          AC_DEFINE(HAVE_SSE4_1,1,[Define if SSE4.1 is available])
                          AC_DEFINE(HAVE_SSE2,1,[Define if SSE2 is available])
                          VECTORISATION_FLAGS="-msse4.2"
                          AC_MSG_RESULT(yes (SSE4.2))
                      ],
                      [
                        AS_IF([ test "x$sse4_1_found" = "xyes" ],
                              [
                                  AC_DEFINE(HAVE_SSE4_1,1,[Define if SSE4.1 is available])
                                  AC_DEFINE(HAVE_SSE2,1,[Define if SSE2 is available])
                                  VECTORISATION_FLAGS="-msse4.1"
                                  AC_MSG_RESULT(yes (SSE4.1))
                              ],
                              [
                                AS_IF([ test "x$sse2_found" = "xyes" ],
                                      [
                                          AC_DEFINE(HAVE_SSE2,1,[Define if SSE2 is available])
                                          VECTORISATION_FLAGS="-msse2"
                                          AC_MSG_RESULT(yes (SSE2))
                                      ],
                                      [
                                        VECTORISATION_FLAGS=""
                                        AC_MSG_RESULT(no)
                                      ]
                                    )
                              ]
                            )
                      ]
                    )
                 CXXFLAGS="${BACKUP_CXXFLAGS}"
                 AC_SUBST(VECTORISATION_FLAGS)
            ])
         ]
)

