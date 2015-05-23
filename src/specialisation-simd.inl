/* 
 * Copyright (C) 2010 Antoine Joux and Vanessa Vitse 

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 */

  /**
  * \file specialisation-simd.inl
  * \brief Specialisation of addMultRow method with vectorisation.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_SPECIALISATION_SIMD_INL
#define F4_SPECIALISATION_SIMD_INL
    
using namespace std;

namespace F4
{
    #if defined(__SSE2__) && defined(__x86_64__)
    #ifndef __SSE4_1__
    template <typename T>
    string __m128i_toString(const __m128i var) 
    {
        stringstream sstr;
        const T* values = (const T*) &var;
        if (sizeof(T) == 1) 
        {
            for (unsigned int i = 0; i < sizeof(__m128i); i++) 
            {
                sstr << (int) values[i] << " ";
            }
        } 
        else 
        {
            for (unsigned int i = 0; i < sizeof(__m128i) / sizeof(T); i++) 
            {
                sstr << values[i] << " ";
            }
        }
        return sstr.str();
    }
    
    template <>
    inline void
    Matrix<ElementPrime<int16_t>>::addMultRow(ElementPrime<int16_t> * row1, ElementPrime<int16_t> * row2, ElementPrime<int16_t> mult, int start, int end)
    {
        int i;
        static int16_t hibound = 0;
        static int16_t modulo = 0;
        static int16_t reduct = 0;
        static __m128i ssehibound;
        static __m128i sselobound;
        static __m128i ssereduct;

        if (modulo != ElementPrime<int16_t>::getModulo())
        {
            modulo = ElementPrime<int16_t>::getModulo();
            reduct = modulo*(modulo / 2);
            hibound = ElementPrime<int16_t>::getMax();
            /* ssehibound = [hibound,hibound,hibound,hibound,hibound,hibound,hibound,hibound] */
            ssehibound = _mm_setr_epi16 (hibound,hibound,hibound,hibound,hibound,hibound,hibound,hibound);
            sselobound = _mm_setr_epi16 (-hibound,-hibound,-hibound,-hibound,-hibound,-hibound,-hibound,-hibound);
            ssereduct = _mm_setr_epi16 (reduct,reduct,reduct,reduct,reduct,reduct,reduct,reduct);
        }
        
        int8_t mul=(int8_t)mult.modulo();
        __m128i ssemult = _mm_setzero_si128 ();
        __m128i *sserow2, *ssedst;
        sserow2 = reinterpret_cast<__m128i *>(row2);
        ssedst = reinterpret_cast<__m128i *>(row1);
        /* ssemult = [mul,mul,mul,mul,mul,mul,mul,mul] */
        ssemult = _mm_setr_epi16(mul,mul,mul,mul,mul,mul,mul,mul);

        for (i = (start / 8); i < (end + 7) / 8; i++)
        {
            __m128i sse0, sse1;
            
            /* Multiply row2 by mult */
            
            /* sse0 = ssemult * ssein_0 [15:0] */
            sse0 = _mm_mullo_epi16 (ssemult, sserow2[i]);
            
            
            /* Test if row1 > hibound */
            
            /* sse1 = (ssedst[i] > ssehibound) ? 0xffff : 0x0 for the 8 integers */
            sse1 = _mm_cmpgt_epi16 (ssedst[i], ssehibound);
            
            /* sse1 = ssereduct^sse1 */
            sse1 = _mm_and_si128 (ssereduct, sse1);
            
            /* ssedst[i] = [ssedst[i][0]-sse1[0], ssedst[i][1]-sse1[1], ssedst[i][2]-sse1[2], ssedst[i][3]-sse1[3], ssedst[i][4]-sse1[4], ssedst[i][5]-sse1[5], ssedst[i][6]-sse1[6], ssedst[i][7]-sse1[7]] */
            ssedst[i] = _mm_sub_epi16 (ssedst[i], sse1);
            
            
            /* Test if row1 < -hibound */
            
            /* sse1 = (ssedst[i] < sselobound) ? 0xffff : 0x0 for the 8 integers */
            sse1 = _mm_cmplt_epi16 (ssedst[i], sselobound);
            
            /* sse1 = ssereduct^sse1 */
            sse1 = _mm_and_si128 (ssereduct, sse1);
            
            /*  ssedst[i] = [ssedst[i][0]+sse1[0], ssedst[i][1]+sse1[1], ssedst[i][2]+sse1[2], ssedst[i][3]+sse1[3], ssedst[i][4]+sse1[4], ssedst[i][5]+sse1[5], ssedst[i][6]+sse1[6], ssedst[i][7]+sse1[7]] */
            ssedst[i] = _mm_add_epi16 (ssedst[i], sse1);
        
            
            /* Add row1 with row2 * mult */

            /* ssedst[i] = [sse0[0]+ssedst[i][0], sse0[1]+ssedst[i][1], sse0[2]+ssedst[i][2], sse0[3]+ssedst[i][3], sse0[4]+ssedst[i][4], sse0[5]+ssedst[i][5], sse0[6]+ssedst[i][6], sse0[7]+ssedst[i][7]] */
            ssedst[i] = _mm_add_epi16 (sse0, ssedst[i]);
        }
    }
    
    template <>
    inline void
    Matrix<ElementPrime<int32_t>>::addMultRow(ElementPrime<int32_t> * row1, ElementPrime<int32_t> * row2, ElementPrime<int32_t> mult, int start, int end)
    {
        int i;
        static int32_t hibound = 0;
        static int32_t modulo = 0;
        static int32_t reduct = 0;
        static __m128i ssehibound;
        static __m128i sselobound;
        static __m128i ssereduct;

        if (modulo != ElementPrime<int32_t>::getModulo())
        {
            modulo = ElementPrime<int32_t>::getModulo();
            reduct = modulo*(modulo / 2);
            hibound = ElementPrime<int32_t>::getMax();
            /* ssehibound = [hibound,hibound,hibound,hibound] */
            ssehibound = _mm_setr_epi32 (hibound,hibound,hibound,hibound);
            sselobound = _mm_setr_epi32 (-hibound,-hibound,-hibound,-hibound);
            ssereduct = _mm_setr_epi32 (reduct,reduct,reduct,reduct);
        }
        int16_t mul=(int16_t)mult.modulo();

        /* Version by group of 16 */
        __m128i ssemult = _mm_setzero_si128 ();
        __m128i *sserow2, *ssedst;

        sserow2 = reinterpret_cast<__m128i *>(row2);
        ssedst = reinterpret_cast<__m128i *>(row1);
        
        /* ssemult = [mul,mul,mul,mul,mul,mul,mul,mul] */
        ssemult = _mm_setr_epi16(mul,mul,mul,mul,mul,mul,mul,mul);

        for (i = (start / 16); i < (end + 15) / 16; i++)
        {
            __m128i ssein_0, ssein_1, sse0, sse1, sse2, sse3, sse4, sse5, sse6,sse7, sse8, sse9, sseA, sseB;
            
            /* ssein_0 = [row2[0],row2[1],row2[2],row2[3],row2[4],row2[5],row2[6],row2[7]] */
            ssein_0 = _mm_packs_epi32 (sserow2[4 * i], sserow2[4 * i + 1]);
            /* ssein_1 = [row2[8],row2[9],row2[10],row2[11],row2[12],row2[13],row2[14],row2[15]] */
            ssein_1 = _mm_packs_epi32 (sserow2[4 * i + 2], sserow2[4 * i + 3]);
            
            
            /* Multiply row2 by mult */
            
            /* sse0 = ssemult * ssein_0 [15:0] */
            sse0 = _mm_mullo_epi16 (ssemult, ssein_0);
            /* sse1 = ssemult * ssein_0 [31:16] */
            sse1 = _mm_mulhi_epi16 (ssemult, ssein_0);
            /* sse2 = ssemult * ssein_1 [15:0] */
            sse2 = _mm_mullo_epi16 (ssemult, ssein_1);
            /* sse3 = ssemult * ssein_1 [31:16] */
            sse3 = _mm_mulhi_epi16 (ssemult, ssein_1);
            
            /* sse4 = [sse0[0],sse1[0], sse0[1],sse1[1], sse0[2],sse1[2], sse0[3],sse1[3]] = [mul*row2[0], mul*row2[1], mul*row2[2], mul*row2[3]] */
            sse4 = _mm_unpacklo_epi16 (sse0, sse1);
            /* sse5 = [sse0[4],sse1[4], sse0[5],sse1[5], sse0[6],sse1[6], sse0[7],sse1[7]] = [mul*row2[4], mul*row2[5], mul*row2[6], mul*row2[7]] */
            sse5 = _mm_unpackhi_epi16 (sse0, sse1);
            /* sse6 = [sse2[0],sse3[0], sse2[1],sse3[1], sse2[2],sse3[2], sse2[3],sse3[3]] = [mul*row2[8], mul*row2[9], mul*row2[10], mul*row2[11]] */
            sse6 = _mm_unpacklo_epi16 (sse2, sse3);
            /* sse7 = [sse2[4],sse3[4], sse2[5],sse3[5], sse2[6],sse3[6], sse2[7],sse3[7]] = [mul*row2[12], mul*row2[13], mul*row2[14], mul*row2[15]] */
            sse7 = _mm_unpackhi_epi16 (sse2, sse3);
            
            
            /* Test if row1 > hibound */
            
            /* sse8 = (ssedst[4 * i] > ssehibound) ? 0xffff : 0x0 for the 4 integers */
            sse8 = _mm_cmpgt_epi32 (ssedst[4 * i], ssehibound);
            /* sse9 = (ssedst[4 * i + 1] > ssehibound) ? 0xffff : 0x0 for the 4 integers */
            sse9 = _mm_cmpgt_epi32 (ssedst[4 * i + 1], ssehibound);
            /* sseA = (ssedst[4 * i + 2] > ssehibound) ? 0xffff : 0x0 for the 4 integers */
            sseA = _mm_cmpgt_epi32 (ssedst[4 * i + 2], ssehibound);
            /* sseB = (ssedst[4 * i + 3] > ssehibound) ? 0xffff : 0x0 for the 4 integers */
            sseB = _mm_cmpgt_epi32 (ssedst[4 * i + 3], ssehibound);
            
            /* sse8 = ssereduct^sse8 */
            sse8 = _mm_and_si128 (ssereduct, sse8);
            /* sse9 = ssereduct^sse9 */
            sse9 = _mm_and_si128 (ssereduct, sse9);
            /* sseA = ssereduct^sseA */
            sseA = _mm_and_si128 (ssereduct, sseA);
            /* sseB = ssereduct^sseB */
            sseB = _mm_and_si128 (ssereduct, sseB);
            
            /* ssedst[4*i] = [ssedst[4*i][0]-sse8[0], ssedst[4*i][1]-sse8[1], ssedst[4*i][2]-sse8[2], ssedst[4*i][3]-sse8[3]] */
            ssedst[4 * i] = _mm_sub_epi32 (ssedst[4 * i], sse8);
            /* ssedst[4*i+1] = [ssedst[4*i+1][0]-sse9[0], ssedst[4*i+1][1]-sse9[1], ssedst[4*i+1][2]-sse9[2], ssedst[4*i+1][3]-sse9[3]] */
            ssedst[4 * i + 1] = _mm_sub_epi32 (ssedst[4 * i + 1], sse9);
            /* ssedst[4*i+2] = [ssedst[4*i+2] [0]-sseA[0], ssedst[4*i+2] [1]-sseA[1], ssedst[4*i+2] [2]-sseA[2], ssedst[4*i+2] [3]-sseA[3]] */
            ssedst[4 * i + 2] = _mm_sub_epi32 (ssedst[4 * i + 2], sseA);
            /* ssedst[4*i+3] = [ssedst[4*i+3][0]-sseB[0], ssedst[4*i+3][1]-sseB[1], ssedst[4*i+3][2]-sseB[2], ssedst[4*i+3][3]-sseB[3]] */
            ssedst[4 * i + 3] = _mm_sub_epi32 (ssedst[4 * i + 3], sseB);
            
            
            /* Test if row1 < -hibound */
            
            /* sse8 = (ssedst[4 * i] < sselobound) ? 0xffff : 0x0 for the 4 integers */
            sse8 = _mm_cmplt_epi32 (ssedst[4 * i], sselobound);
            /* sse9 = (ssedst[4 * i + 1] < sselobound) ? 0xffff : 0x0 for the 4 integers */
            sse9 = _mm_cmplt_epi32 (ssedst[4 * i + 1], sselobound);
            /* sseA = (ssedst[4 * i + 2] < sselobound) ? 0xffff : 0x0 for the 4 integers */
            sseA = _mm_cmplt_epi32 (ssedst[4 * i + 2], sselobound);
            /* sseB = (ssedst[4 * i + 3] < sselobound) ? 0xffff : 0x0 for the 4 integers */
            sseB = _mm_cmplt_epi32 (ssedst[4 * i + 3], sselobound);
            
            /* sse8 = ssereduct^sse8 */
            sse8 = _mm_and_si128 (ssereduct, sse8);
            /* sse9 = ssereduct^sse9 */
            sse9 = _mm_and_si128 (ssereduct, sse9);
            /* sseA = ssereduct^sseA */
            sseA = _mm_and_si128 (ssereduct, sseA);
            /* sseB = ssereduct^sseB */
            sseB = _mm_and_si128 (ssereduct, sseB);
            
            /* ssedst[4*i] = [ssedst[4*i][0]+sse8[0], ssedst[4*i][1]+sse8[1], ssedst[4*i][2]+sse8[2], ssedst[4*i][3]+sse8[3]] */
            ssedst[4 * i] = _mm_add_epi32 (ssedst[4 * i], sse8);
            /* ssedst[4*i+1] = [ssedst[4*i+1][0]+sse9[0], ssedst[4*i+1][1]+sse9[1], ssedst[4*i+1][2]+sse9[2], ssedst[4*i+1][3]+sse9[3]] */
            ssedst[4 * i + 1] = _mm_add_epi32 (ssedst[4 * i + 1], sse9);
            /* ssedst[4*i+2] = [ssedst[4*i+2][0]+sseA[0], ssedst[4*i+2][1]+sseA[1], ssedst[4*i+2][2]+sseA[2], ssedst[4*i+2][3]+sseA[3]] */
            ssedst[4 * i + 2] = _mm_add_epi32 (ssedst[4 * i + 2], sseA);
            /* ssedst[4*i+3] = [ssedst[4*i+3][0]+sseB[0], ssedst[4*i+3][1]+sseB[1], ssedst[4*i+3][2]+sseB[2], ssedst[4*i+3][3]+sseB[3]] */
            ssedst[4 * i + 3] = _mm_add_epi32 (ssedst[4 * i + 3], sseB);
            
            
            /* Add row1 with row2 * mult */

            /* ssedst[4*i] = [sse40[0]+row1[0], sse4[1]+row1[1], sse4[2]+row1[2], sse4[3]+row1[3]] */
            ssedst[4 * i] = _mm_add_epi32 (sse4, ssedst[4 * i]);
            /* ssedst[4*i+1] = [sse5[0]+row1[4], sse5[1]+row1[5], sse5[2]+row1[6], sse5[3]+row1[7]] */
            ssedst[4 * i + 1] = _mm_add_epi32 (sse5, ssedst[4 * i + 1]);
            /* ssedst[4*i+2] = [sse6[0]+row1[8], sse6[1]+row1[9], sse6[2]+row1[10], sse6[3]+row1[11]] */
            ssedst[4 * i + 2] = _mm_add_epi32 (sse6, ssedst[4 * i + 2]);
            /* ssedst[4*i+3] = [sse7[0]+row1[12], sse7[1]+row1[13], sse7[2]+row1[14], sse7[3]+row1[15]] */
            ssedst[4 * i + 3] = _mm_add_epi32 (sse7, ssedst[4 * i + 3]);
        }
    }
    
    template <>
    inline void
    Matrix<ElementPrime<double>>::addMultRow(ElementPrime<double> * row1, ElementPrime<double> * row2, ElementPrime<double> mult, int start, int end)
    {
        int i;
        static double hibound = 0;
        static double modulo = 0;
        static double reduct = 0;
        static __m128d ssehibound;
        static __m128d sselobound;
        static __m128d ssereduct;

        if (modulo != ElementPrime<double>::getModulo())
        {
            modulo = ElementPrime<double>::getModulo();
            reduct = modulo*((int)modulo / 2);
            hibound = ElementPrime<double>::getMax();
            /* ssehibound = [hibound,hibound] */
            ssehibound = _mm_setr_pd (hibound,hibound);
            sselobound = _mm_setr_pd (-hibound,-hibound);
            ssereduct = _mm_setr_pd (reduct, reduct);
        }
        double mul=(double)mult.modulo();

        /* Version by group of 2 */
        __m128d ssemult =  _mm_setzero_pd ();
        __m128d *sserow2, *ssedst;

        sserow2 = reinterpret_cast<__m128d *>(row2);
        ssedst = reinterpret_cast<__m128d *>(row1);
        
        /* ssemult = [mul,mul] */
        ssemult = _mm_setr_pd(mul, mul);

        for (i = (start / 2); i < (end + 1) / 2; i++)
        {
            __m128d sse0, sse1;
            
            /* Multiply row2 by mult */
            
            /* sse0 = ssemult * sserow2[i] */
            sse0 = _mm_mul_pd (ssemult, sserow2[i]);
            
            /* Test if row1 > hibound */
            
            /* sse1 = (ssedst[i] > ssehibound) ? 0xffff : 0x0 for the 2 integers */
            sse1 = _mm_cmpgt_pd (ssedst[i], ssehibound);
            
            /* sse1 = ssereduct^sse1 */
            sse1 = _mm_and_pd (ssereduct, sse1);
            
            /* ssedst[i] = [ssedst[i][0]-sse1[0], ssedst[i][1]-sse1[1] */
            ssedst[i] = _mm_sub_pd (ssedst[i], sse1);
            
            
            /* Test if row1 < -hibound */
            
            /* sse1 = (sselobound > ssedst[i]) ? 0xffff : 0x0 for the 2 integers */
            sse1 = _mm_cmpgt_pd (sselobound, ssedst[i]);
            
            /* sse1 = ssereduct^sse1 */
            sse1 = _mm_and_pd (ssereduct, sse1);
            
            /*  ssedst[i] = [ssedst[i][0]+sse1[0], ssedst[i][1]+sse1[1] */
            ssedst[i] = _mm_add_pd (ssedst[i], sse1);
        
            
            /* Add row1 with row2 * mult */

            /* ssedst[i] = [sse0[0]+ssedst[i][0], sse0[1]+ssedst[i][1]] */
            ssedst[i] = _mm_add_pd (sse0, ssedst[i]);
        }
    }
    
    #endif // __SSE2__
    #endif // __SSE4_1__
    
    #if defined(__SSE4_1__) && defined(__x86_64__)
    template <>
    inline void
    Matrix<ElementPrime<int16_t>>::addMultRow(ElementPrime<int16_t> * row1, ElementPrime<int16_t> * row2, ElementPrime<int16_t> mult, int start, int end)
    {
        int i;
        static int16_t hibound = 0;
        static int16_t modulo = 0;
        static int16_t reduct = 0;
        static __m128i ssehibound;
        static __m128i ssereduct;

        if (modulo != ElementPrime<int16_t>::getModulo())
        {
            modulo = ElementPrime<int16_t>::getModulo();
            reduct = modulo*(modulo / 2);
            hibound = ElementPrime<int16_t>::getMax();
            /* ssehibound = [hibound,hibound,hibound,hibound,hibound,hibound,hibound,hibound] */
            ssehibound = _mm_setr_epi16 (hibound,hibound,hibound,hibound,hibound,hibound,hibound,hibound);
            ssereduct = _mm_setr_epi16 (reduct,reduct,reduct,reduct,reduct,reduct,reduct,reduct);
        }
        int8_t mul=(int8_t)mult.modulo();

        /* Version by group of 8 */
        __m128i ssemult = _mm_setzero_si128 ();
        __m128i *sserow2, *ssedst;

        sserow2 = reinterpret_cast<__m128i *>(row2);
        ssedst = reinterpret_cast<__m128i *>(row1);
        
        /* ssemult = [mul,mul,mul,mul,mul,mul,mul,mul] */
        ssemult = _mm_setr_epi16(mul,mul,mul,mul,mul,mul,mul,mul);

        for (i = (start / 8); i < (end + 7) / 8; i++)
        {
            __m128i sse0, sse1, sse2;
            
            /* Multiply row2 by mult */
            
            /* sse0 = ssemult * ssein_0 [15:0] */
            sse0 = _mm_mullo_epi16 (ssemult, sserow2[i]);
            
            
            /* Test if row1 > hibound or if row1 < -hibound  */
            
            /* sse1 = (ssedst[i] < 0) ? -ssedst[i] : ssedst[i] */
            sse1 = _mm_sign_epi16 (ssedst[i], ssedst[i]);
            
            /* sse2 = (sse1 > ssehibound) ? 0xffff : 0x0 for the 8 integers */
            sse2 = _mm_cmpgt_epi16 (sse1, ssehibound);
            
            /* sse2 = ssereduct^sse2 */
            sse2 = _mm_and_si128 (ssereduct, sse2);
            
            /* sse1 = [sse1[0]-sse2[0], sse1[1]-sse2[1], sse1[2]-sse2[2], sse1[3]-sse2[3], sse1[4]-sse2[4], sse1[5]-sse2[5], sse1[6]-sse2[6], sse1[7]-sse2[7]] */
            sse1 = _mm_sub_epi16 (sse1, sse2);
            
            /* sse1 = (ssedst[i] < 0) ? -sse1 : sse1 */
            sse1 = _mm_sign_epi16 (sse1, ssedst[i]);
            
            
            /* Add row1 with row2 * mult */

            /* ssedst[i] = [sse0[0]+sse1[0], sse0[1]+sse1[1], sse0[2]+sse1[2], sse0[3]+sse1[3], sse0[4]+sse1[4], sse0[5]+sse1[5], sse0[6]+sse1[6], sse0[7]+sse1[7]] */
            ssedst[i] = _mm_add_epi16 (sse0, sse1);
        }
    }

    template <>
    inline void
    Matrix<ElementPrime<int32_t>>::addMultRow(ElementPrime<int32_t> * row1, ElementPrime<int32_t> * row2, ElementPrime<int32_t> mult, int start, int end)
    {
        int i;
        static int32_t hibound = 0;
        static int32_t modulo = 0;
        static int32_t reduct = 0;
        static __m128i ssehibound;
        static __m128i ssereduct;

        if (modulo != ElementPrime<int32_t>::getModulo())
        {
            modulo = ElementPrime<int32_t>::getModulo();
            reduct = modulo*(modulo / 2);
            hibound = ElementPrime<int32_t>::getMax();
            /* ssehibound = [hibound,hibound,hibound,hibound] */
            ssehibound = _mm_setr_epi32 (hibound,hibound,hibound,hibound);
            ssereduct = _mm_setr_epi32 (reduct,reduct,reduct,reduct);
        }
        int16_t mul=(int16_t)mult.modulo();

        /* Version by group of 4 */
        __m128i ssemult = _mm_setzero_si128 ();
        __m128i *sserow2, *ssedst;

        sserow2 = reinterpret_cast<__m128i *>(row2);
        ssedst = reinterpret_cast<__m128i *>(row1);
        
        /* ssemult = [mul,mul,mul,mul] */
        ssemult = _mm_setr_epi32(mul,mul,mul,mul);

        for (i = (start / 4); i < (end + 3) / 4; i++)
        {
            __m128i sse0, sse1, sse2;
            
            /* Multiply row2 by mult */
            
            /* sse0 = ssemult * ssein_0 [31:0] */
            sse0 = _mm_mullo_epi32 (ssemult, sserow2[i]);
            
            
            /* Test if row1 > hibound or if row1 < -hibound  */
            
            /* sse1 = (ssedst[i] < 0) ? -ssedst[i] : ssedst[i] */
            sse1 = _mm_sign_epi32 (ssedst[i], ssedst[i]);
            
            /* sse2 = (sse1 > ssehibound) ? 0xffff : 0x0 for the 4 integers */
            sse2 = _mm_cmpgt_epi32 (sse1, ssehibound);
            
            /* sse2 = ssereduct^sse2 */
            sse2 = _mm_and_si128 (ssereduct, sse2);
            
            /* sse1 = [sse1[0]-sse2[0], sse1[1]-sse2[1], sse1[2]-sse2[2], sse1[3]-sse2[3]] */
            sse1 = _mm_sub_epi32 (sse1, sse2);
            
            /* sse1 = (ssedst[i] < 0) ? -sse1 : sse1 */
            sse1 = _mm_sign_epi32 (sse1, ssedst[i]);
            
            
            /* Add row1 with row2 * mult */

            /* ssedst[i] = [sse0[0]+sse1[0], sse0[1]+sse1[1], sse0[2]+sse1[2], sse0[3]+sse1[3]] */
            ssedst[i] = _mm_add_epi32 (sse0, sse1);
        }
    }
    
    template <>
    inline void
    Matrix<ElementPrime<int64_t>>::addMultRow(ElementPrime<int64_t> * row1, ElementPrime<int64_t> * row2, ElementPrime<int64_t> mult, int start, int end)
    {
        int i;
        static int64_t hibound = 0;
        static int64_t modulo = 0;
        static int64_t reduct = 0;
        static __m128i ssehibound;
        static __m128i sselobound;
        static __m128i ssereduct;

        if (modulo != ElementPrime<int64_t>::getModulo())
        {
            modulo = ElementPrime<int64_t>::getModulo();
            reduct = modulo*(modulo / 2);
            hibound = ElementPrime<int64_t>::getMax();
            /* ssehibound = [hibound,hibound] */
            ssehibound = _mm_setr_epi64 ((__m64)hibound,(__m64)hibound);
            sselobound = _mm_setr_epi64 ((__m64)(-hibound),(__m64)(-hibound));
            ssereduct = _mm_setr_epi64 ((__m64)reduct,(__m64)reduct);
        }
        int32_t mul=(int32_t)mult.modulo();

        /* Version by group of 2 */
        __m128i ssemult = _mm_setzero_si128 ();
        __m128i *sserow2, *ssedst;

        sserow2 = reinterpret_cast<__m128i *>(row2);
        ssedst = reinterpret_cast<__m128i *>(row1);
        
        /* ssemult = [mul,mul] */
        ssemult = _mm_setr_epi32(mul, 0, mul, 0);

        for (i = (start / 2); i < (end + 1) / 2; i++)
        {
            __m128i sse0, sse1;
            
            /* Multiply row2 by mult */
            
            /* sse0 = ssemult * sserow2[i] */
            sse0 = _mm_mul_epi32 (ssemult, sserow2[i]);
            
            /* Test if row1 > hibound */
            
            /* sse1 = (ssedst[i] > ssehibound) ? 0xffff : 0x0 for the 2 integers */
            sse1 = _mm_cmpgt_epi64 (ssedst[i], ssehibound);
            
            /* sse1 = ssereduct^sse1 */
            sse1 = _mm_and_si128 (ssereduct, sse1);
            
            /* ssedst[i] = [ssedst[i][0]-sse1[0], ssedst[i][1]-sse1[1] */
            ssedst[i] = _mm_sub_epi64 (ssedst[i], sse1);
            
            
            /* Test if row1 < -hibound */
            
            /* sse1 = (sselobound > ssedst[i]) ? 0xffff : 0x0 for the 2 integers */
            sse1 = _mm_cmpgt_epi64 (sselobound, ssedst[i]);
            
            /* sse1 = ssereduct^sse1 */
            sse1 = _mm_and_si128 (ssereduct, sse1);
            
            /*  ssedst[i] = [ssedst[i][0]+sse1[0], ssedst[i][1]+sse1[1] */
            ssedst[i] = _mm_add_epi64 (ssedst[i], sse1);
        
            
            /* Add row1 with row2 * mult */

            /* ssedst[i] = [sse0[0]+ssedst[i][0], sse0[1]+ssedst[i][1]] */
            ssedst[i] = _mm_add_epi64 (sse0, ssedst[i]);
        }
    }
    #endif // __SSE4_1__
}

#endif //F4_SPECIALISATION_SIMD_INL
