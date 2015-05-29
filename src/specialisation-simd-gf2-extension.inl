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
  * \file specialisation-simd-gf2-extension.inl
  * \brief Specialisation of addMultRow method with vectorisation for ElementGF2Extension type.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_SPECIALISATION_SIMD_GF2_EXTENSION_INL
#define F4_SPECIALISATION_SIMD_GF2_EXTENSION_INL
    
using namespace std;

namespace F4
{
    #if defined(__SSE2__) && defined(__x86_64__)
    
    #define BITBLOCKS 16
    #define NBBITBLOCKS_SHORT 4
    #define NBBITBLOCKS_INT 8
    #define NBBITBLOCKS_LONG 16
    #define BITMASK 0xf
    #define BITDECAL 4
    
    /* 16 bits integer -> up to GF(2^15) */
    template <>
    void
    Matrix<ElementGF2Extension<uint16_t>>::doubleAddMultRowGF2Extension(ElementGF2Extension<uint16_t> * dest1, ElementGF2Extension<uint16_t> * dest2, ElementGF2Extension<uint16_t> mult1, ElementGF2Extension<uint16_t> mult2, ElementGF2Extension<uint16_t> * vec, int start, int end)
    {
        uint16_t b;
        int i,j;
        uint16_t modulo = ElementGF2Extension<uint16_t>::getModulo();
        uint16_t maskBit = ElementGF2Extension<uint16_t>::getMaskBit();

        __m128i pow,amuls[BITBLOCKS*NBBITBLOCKS_SHORT],extmod,ssetmp;
        /* pow = [mult1, mult2, 0, 0, 0, 0, 0, 0] */
        pow=_mm_set_epi16(0,0,0,0,0,0,mult2.getElement(),mult1.getElement());
        /* pow = [modulo, modulo, modulo, modulo, modulo, modulo, modulo, modulo] */
        extmod=_mm_set_epi16(modulo,modulo,modulo,modulo,modulo,modulo,modulo,modulo);
        for(j=0;j<NBBITBLOCKS_SHORT;j++) 
        {
            amuls[BITBLOCKS*j]=_mm_xor_si128(pow,pow);
            amuls[BITBLOCKS*j+1]=pow;
            /* pow = [pow[0]*2, pow[1]*2, pow[2]*2, pow[3]*2, pow[4]*2, pow[5]*2, pow[6]*2, pow[7]*2] */
            pow=_mm_slli_epi16(pow,1);
            /* Arithmetic shift that sign bit into all the bits */
            ssetmp=_mm_srai_epi16(pow,maskBit);
            /* ssetmp = [modulo & ssetmp[0], modulo & ssetmp[1], modulo & ssetmp[2], modulo & ssetmp[3], modulo & ssetmp[4], modulo & ssetmp[5], modulo & ssetmp[6], modulo & ssetmp[7]] */
            ssetmp=_mm_and_si128(ssetmp,extmod);
            /* Apply modulo if required */
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<2;i++)
            {
                amuls[BITBLOCKS*j+i+2]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi16(pow,1);
            ssetmp=_mm_srai_epi16(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<4;i++)
            {
                amuls[BITBLOCKS*j+i+4]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi16(pow,1);
            ssetmp=_mm_srai_epi16(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<8;i++)
            {
                amuls[BITBLOCKS*j+i+8]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi16(pow,1);
            ssetmp=_mm_srai_epi16(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
        }

        for (i=start;i<end;i++) 
        {
            b=vec[i].getElement();
            /* ssetmp = [dest1[i], dest2[i], 0, 0, 0, 0, 0, 0] */
            ssetmp=_mm_set_epi16(0,0,0,0,0,0,dest2[i].getElement(),dest1[i].getElement());
            for(j=0;j<NBBITBLOCKS_SHORT;j++) 
            {
                ssetmp=_mm_xor_si128(ssetmp,amuls[((BITBLOCKS*j)+(b&BITMASK))]);
                b>>=BITDECAL;
            }
        
            dest1[i]=_mm_extract_epi16 (ssetmp, 0); 
            dest2[i]=_mm_extract_epi16 (ssetmp, 1);
        }
    }
    
    template <>
    void
    Matrix<ElementGF2Extension<uint16_t>>::tripleAddMultRowGF2Extension(ElementGF2Extension<uint16_t> * dest1, ElementGF2Extension<uint16_t> * dest2, ElementGF2Extension<uint16_t> * dest3, ElementGF2Extension<uint16_t> mult1, ElementGF2Extension<uint16_t> mult2, ElementGF2Extension<uint16_t> mult3, ElementGF2Extension<uint16_t> * vec, int start, int end)
    {
        uint16_t b;
        int i,j;
        uint16_t modulo = ElementGF2Extension<uint16_t>::getModulo();
        uint16_t maskBit = ElementGF2Extension<uint16_t>::getMaskBit();

        __m128i pow,amuls[BITBLOCKS*NBBITBLOCKS_SHORT],extmod,ssetmp;
        /* pow = [mult1, mult2, mult3, 0, 0, 0, 0, 0] */
        pow=_mm_set_epi16(0,0,0,0,0,mult3.getElement(),mult2.getElement(),mult1.getElement());
        /* pow = [modulo, modulo, modulo, modulo, modulo, modulo, modulo, modulo] */
        extmod=_mm_set_epi16(modulo,modulo,modulo,modulo,modulo,modulo,modulo,modulo);
        for(j=0;j<NBBITBLOCKS_SHORT;j++) 
        {
            amuls[BITBLOCKS*j]=_mm_xor_si128(pow,pow);
            amuls[BITBLOCKS*j+1]=pow;
            /* pow = [pow[0]*2, pow[1]*2, pow[2]*2, pow[3]*2, pow[4]*2, pow[5]*2, pow[6]*2, pow[7]*2] */
            pow=_mm_slli_epi16(pow,1);
            /* Arithmetic shift that sign bit into all the bits */
            ssetmp=_mm_srai_epi16(pow,maskBit);
            /* ssetmp = [modulo & ssetmp[0], modulo & ssetmp[1], modulo & ssetmp[2], modulo & ssetmp[3], modulo & ssetmp[4], modulo & ssetmp[5], modulo & ssetmp[6], modulo & ssetmp[7]] */
            ssetmp=_mm_and_si128(ssetmp,extmod);
            /* Apply modulo if required */
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<2;i++)
            {
                amuls[BITBLOCKS*j+i+2]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi16(pow,1);
            ssetmp=_mm_srai_epi16(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<4;i++)
            {
                amuls[BITBLOCKS*j+i+4]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi16(pow,1);
            ssetmp=_mm_srai_epi16(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<8;i++)
            {
                amuls[BITBLOCKS*j+i+8]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi16(pow,1);
            ssetmp=_mm_srai_epi16(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
        }

        for (i=start;i<end;i++) 
        {
            b=vec[i].getElement();
            /* ssetmp = [dest1[i], dest2[i], dest3[i], 0, 0, 0, 0, 0] */
            ssetmp=_mm_set_epi16(0,0,0,0,0,dest3[i].getElement(),dest2[i].getElement(),dest1[i].getElement());
            for(j=0;j<NBBITBLOCKS_SHORT;j++) 
            {
                ssetmp=_mm_xor_si128(ssetmp,amuls[((BITBLOCKS*j)+(b&BITMASK))]);
                b>>=BITDECAL;
            }
        
            dest1[i]=_mm_extract_epi16 (ssetmp, 0); 
            dest2[i]=_mm_extract_epi16 (ssetmp, 1);
            dest3[i]=_mm_extract_epi16 (ssetmp, 2);
        }
    }
    
    template <>
    void
    Matrix<ElementGF2Extension<uint16_t>>::quadAddMultRowGF2Extension(ElementGF2Extension<uint16_t> * dest1, ElementGF2Extension<uint16_t> * dest2, ElementGF2Extension<uint16_t> * dest3, ElementGF2Extension<uint16_t> * dest4, ElementGF2Extension<uint16_t> mult1, ElementGF2Extension<uint16_t> mult2, ElementGF2Extension<uint16_t> mult3, ElementGF2Extension<uint16_t> mult4, ElementGF2Extension<uint16_t> * vec, int start, int end)
    {
        uint16_t b;
        int i,j;
        uint16_t modulo = ElementGF2Extension<uint16_t>::getModulo();
        uint16_t maskBit = ElementGF2Extension<uint16_t>::getMaskBit();

        __m128i pow,amuls[BITBLOCKS*NBBITBLOCKS_SHORT],extmod,ssetmp;
        /* pow = [mult1, mult2, mult3, mult4, 0, 0, 0, 0] */
        pow=_mm_set_epi16(0,0,0,0,mult4.getElement(),mult3.getElement(),mult2.getElement(),mult1.getElement());
        /* pow = [modulo, modulo, modulo, modulo, modulo, modulo, modulo, modulo] */
        extmod=_mm_set_epi16(modulo,modulo,modulo,modulo,modulo,modulo,modulo,modulo);
        for(j=0;j<NBBITBLOCKS_SHORT;j++) 
        {
            amuls[BITBLOCKS*j]=_mm_xor_si128(pow,pow);
            amuls[BITBLOCKS*j+1]=pow;
            /* pow = [pow[0]*2, pow[1]*2, pow[2]*2, pow[3]*2, pow[4]*2, pow[5]*2, pow[6]*2, pow[7]*2] */
            pow=_mm_slli_epi16(pow,1);
            /* Arithmetic shift that sign bit into all the bits */
            ssetmp=_mm_srai_epi16(pow,maskBit);
            /* ssetmp = [modulo & ssetmp[0], modulo & ssetmp[1], modulo & ssetmp[2], modulo & ssetmp[3], modulo & ssetmp[4], modulo & ssetmp[5], modulo & ssetmp[6], modulo & ssetmp[7]] */
            ssetmp=_mm_and_si128(ssetmp,extmod);
            /* Apply modulo if required */
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<2;i++)
            {
                amuls[BITBLOCKS*j+i+2]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi16(pow,1);
            ssetmp=_mm_srai_epi16(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<4;i++)
            {
                amuls[BITBLOCKS*j+i+4]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi16(pow,1);
            ssetmp=_mm_srai_epi16(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<8;i++)
            {
                amuls[BITBLOCKS*j+i+8]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi16(pow,1);
            ssetmp=_mm_srai_epi16(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
        }

        for (i=start;i<end;i++) 
        {
            b=vec[i].getElement();
            /* ssetmp = [dest1[i], dest2[i], dest3[i], dest4[i], 0, 0, 0, 0] */
            ssetmp=_mm_set_epi16(0,0,0,0,dest4[i].getElement(),dest3[i].getElement(),dest2[i].getElement(),dest1[i].getElement());
            for(j=0;j<NBBITBLOCKS_SHORT;j++) 
            {
                ssetmp=_mm_xor_si128(ssetmp,amuls[((BITBLOCKS*j)+(b&BITMASK))]);
                b>>=BITDECAL;
            }
        
            dest1[i]=_mm_extract_epi16 (ssetmp, 0); 
            dest2[i]=_mm_extract_epi16 (ssetmp, 1);
            dest3[i]=_mm_extract_epi16 (ssetmp, 2);
            dest4[i]=_mm_extract_epi16 (ssetmp, 3);
        }
    }
    
    template <>
    void
    Matrix<ElementGF2Extension<uint16_t>>::octAddMultRowGF2Extension(ElementGF2Extension<uint16_t> * dest1, ElementGF2Extension<uint16_t> * dest2, ElementGF2Extension<uint16_t> * dest3, ElementGF2Extension<uint16_t> * dest4, ElementGF2Extension<uint16_t> * dest5, ElementGF2Extension<uint16_t> * dest6, ElementGF2Extension<uint16_t> * dest7, ElementGF2Extension<uint16_t> * dest8, ElementGF2Extension<uint16_t> mult1, ElementGF2Extension<uint16_t> mult2, ElementGF2Extension<uint16_t> mult3, ElementGF2Extension<uint16_t> mult4, ElementGF2Extension<uint16_t> mult5, ElementGF2Extension<uint16_t> mult6, ElementGF2Extension<uint16_t> mult7, ElementGF2Extension<uint16_t> mult8, ElementGF2Extension<uint16_t> * vec, int start, int end)
    {
        uint16_t b;
        int i,j;
        uint16_t modulo = ElementGF2Extension<uint16_t>::getModulo();
        uint16_t maskBit = ElementGF2Extension<uint16_t>::getMaskBit();

        __m128i pow,amuls[BITBLOCKS*NBBITBLOCKS_SHORT],extmod,ssetmp;
        /* pow = [mult1, mult2, mult3, mult4, mult5, mult6, mult7, mult8] */
        pow=_mm_set_epi16(mult8.getElement(),mult7.getElement(),mult6.getElement(),mult5.getElement(),mult4.getElement(),mult3.getElement(),mult2.getElement(),mult1.getElement());
        /* pow = [modulo, modulo, modulo, modulo, modulo, modulo, modulo, modulo] */
        extmod=_mm_set_epi16(modulo,modulo,modulo,modulo,modulo,modulo,modulo,modulo);
        for(j=0;j<NBBITBLOCKS_SHORT;j++) 
        {
            amuls[BITBLOCKS*j]=_mm_xor_si128(pow,pow);
            amuls[BITBLOCKS*j+1]=pow;
            /* pow = [pow[0]*2, pow[1]*2, pow[2]*2, pow[3]*2, pow[4]*2, pow[5]*2, pow[6]*2, pow[7]*2] */
            pow=_mm_slli_epi16(pow,1);
            /* Arithmetic shift that sign bit into all the bits */
            ssetmp=_mm_srai_epi16(pow,maskBit);
            /* ssetmp = [modulo & ssetmp[0], modulo & ssetmp[1], modulo & ssetmp[2], modulo & ssetmp[3], modulo & ssetmp[4], modulo & ssetmp[5], modulo & ssetmp[6], modulo & ssetmp[7]] */
            ssetmp=_mm_and_si128(ssetmp,extmod);
            /* Apply modulo if required */
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<2;i++)
            {
                amuls[BITBLOCKS*j+i+2]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi16(pow,1);
            ssetmp=_mm_srai_epi16(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<4;i++)
            {
                amuls[BITBLOCKS*j+i+4]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi16(pow,1);
            ssetmp=_mm_srai_epi16(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<8;i++)
            {
                amuls[BITBLOCKS*j+i+8]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi16(pow,1);
            ssetmp=_mm_srai_epi16(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
        }

        for (i=start;i<end;i++) 
        {
            b=vec[i].getElement();
            /* ssetmp = [dest1[i], dest2[i], dest3[i], dest4[i], dest5[i], dest6[i], dest7[i], dest8[i]] */
            ssetmp=_mm_set_epi16(dest8[i].getElement(),dest7[i].getElement(),dest6[i].getElement(),dest5[i].getElement(),dest4[i].getElement(),dest3[i].getElement(),dest2[i].getElement(),dest1[i].getElement());
            for(j=0;j<NBBITBLOCKS_SHORT;j++) 
            {
                ssetmp=_mm_xor_si128(ssetmp,amuls[((BITBLOCKS*j)+(b&BITMASK))]);
                b>>=BITDECAL;
            }
        
            dest1[i]=_mm_extract_epi16 (ssetmp, 0); 
            dest2[i]=_mm_extract_epi16 (ssetmp, 1);
            dest3[i]=_mm_extract_epi16 (ssetmp, 2);
            dest4[i]=_mm_extract_epi16 (ssetmp, 3);
            dest5[i]=_mm_extract_epi16 (ssetmp, 4); 
            dest6[i]=_mm_extract_epi16 (ssetmp, 5);
            dest7[i]=_mm_extract_epi16 (ssetmp, 6);
            dest8[i]=_mm_extract_epi16 (ssetmp, 7);
        }
    }
    
    /* 32 bits integer -> up to GF(2^31) */
    template <>
    void
    Matrix<ElementGF2Extension<uint32_t>>::doubleAddMultRowGF2Extension(ElementGF2Extension<uint32_t> * dest1, ElementGF2Extension<uint32_t> * dest2, ElementGF2Extension<uint32_t> mult1, ElementGF2Extension<uint32_t> mult2, ElementGF2Extension<uint32_t> * vec, int start, int end)
    {
        uint32_t b;
        int i,j;
        uint32_t modulo = ElementGF2Extension<uint32_t>::getModulo();
        uint32_t maskBit = ElementGF2Extension<uint32_t>::getMaskBit();

        __m128i pow,amuls[BITBLOCKS*NBBITBLOCKS_INT],extmod,ssetmp;
        /* pow = [mult1, mult2, 0, 0] */
        pow=_mm_set_epi32(0,0,mult2.getElement(),mult1.getElement());
        /* pow = [modulo, modulo, modulo, modulo] */
        extmod=_mm_set_epi32(modulo,modulo,modulo,modulo);
        for(j=0;j<NBBITBLOCKS_INT;j++) 
        {
            amuls[BITBLOCKS*j]=_mm_xor_si128(pow,pow);
            amuls[BITBLOCKS*j+1]=pow;
            /* pow = [pow[0]*2, pow[1]*2, pow[2]*2, pow[3]*2] */
            pow=_mm_slli_epi32(pow,1);
            /* Arithmetic shift that sign bit into all the bits */
            ssetmp=_mm_srai_epi32(pow,maskBit);
            /* ssetmp = [modulo & ssetmp[0], modulo & ssetmp[1], modulo & ssetmp[2], modulo & ssetmp[3]] */
            ssetmp=_mm_and_si128(ssetmp,extmod);
            /* Apply modulo if required */
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<2;i++)
            {
                amuls[BITBLOCKS*j+i+2]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi32(pow,1);
            ssetmp=_mm_srai_epi32(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<4;i++)
            {
                amuls[BITBLOCKS*j+i+4]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi32(pow,1);
            ssetmp=_mm_srai_epi32(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<8;i++)
            {
                amuls[BITBLOCKS*j+i+8]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi32(pow,1);
            ssetmp=_mm_srai_epi32(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
        }

        for (i=start;i<end;i++) 
        {
            b=vec[i].getElement();
            /* ssetmp = [dest1[i], dest2[i], 0, 0] */
            ssetmp=_mm_set_epi32(0,0,dest2[i].getElement(),dest1[i].getElement());
            for(j=0;j<NBBITBLOCKS_INT;j++) 
            {
                ssetmp=_mm_xor_si128(ssetmp,amuls[((BITBLOCKS*j)+(b&BITMASK))]);
                b>>=BITDECAL;
            }
            
            #ifdef __SSE4_1__
            dest1[i]=_mm_extract_epi32 (ssetmp, 0);
            dest2[i]=_mm_extract_epi32 (ssetmp, 1);
            #else
            dest1[i]=(_mm_extract_epi16 (ssetmp, 0)) | (_mm_extract_epi16 (ssetmp, 1) << 16);
            dest2[i]=(_mm_extract_epi16 (ssetmp, 2)) | (_mm_extract_epi16 (ssetmp, 3) << 16);
            #endif
        }
    }
    
    template <>
    void
    Matrix<ElementGF2Extension<uint32_t>>::tripleAddMultRowGF2Extension(ElementGF2Extension<uint32_t> * dest1, ElementGF2Extension<uint32_t> * dest2, ElementGF2Extension<uint32_t> * dest3, ElementGF2Extension<uint32_t> mult1, ElementGF2Extension<uint32_t> mult2, ElementGF2Extension<uint32_t> mult3, ElementGF2Extension<uint32_t> * vec, int start, int end)
    {
        uint32_t b;
        int i,j;
        uint32_t modulo = ElementGF2Extension<uint32_t>::getModulo();
        uint32_t maskBit = ElementGF2Extension<uint32_t>::getMaskBit();

        __m128i pow,amuls[BITBLOCKS*NBBITBLOCKS_INT],extmod,ssetmp;
        /* pow = [mult1, mult2, mult3, 0] */
        pow=_mm_set_epi32(0,mult3.getElement(),mult2.getElement(),mult1.getElement());
        /* pow = [modulo, modulo, modulo, modulo] */
        extmod=_mm_set_epi32(modulo,modulo,modulo,modulo);
        for(j=0;j<NBBITBLOCKS_INT;j++) 
        {
            amuls[BITBLOCKS*j]=_mm_xor_si128(pow,pow);
            amuls[BITBLOCKS*j+1]=pow;
            /* pow = [pow[0]*2, pow[1]*2, pow[2]*2, pow[3]*2] */
            pow=_mm_slli_epi32(pow,1);
            /* Arithmetic shift that sign bit into all the bits */
            ssetmp=_mm_srai_epi32(pow,maskBit);
            /* ssetmp = [modulo & ssetmp[0], modulo & ssetmp[1], modulo & ssetmp[2], modulo & ssetmp[3]] */
            ssetmp=_mm_and_si128(ssetmp,extmod);
            /* Apply modulo if required */
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<2;i++)
            {
                amuls[BITBLOCKS*j+i+2]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi32(pow,1);
            ssetmp=_mm_srai_epi32(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<4;i++)
            {
                amuls[BITBLOCKS*j+i+4]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi32(pow,1);
            ssetmp=_mm_srai_epi32(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<8;i++)
            {
                amuls[BITBLOCKS*j+i+8]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi32(pow,1);
            ssetmp=_mm_srai_epi32(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
        }

        for (i=start;i<end;i++) 
        {
            b=vec[i].getElement();
            /* ssetmp = [dest1[i], dest2[i], dest3[i], 0] */
            ssetmp=_mm_set_epi32(0,dest3[i].getElement(),dest2[i].getElement(),dest1[i].getElement());
            for(j=0;j<NBBITBLOCKS_INT;j++) 
            {
                ssetmp=_mm_xor_si128(ssetmp,amuls[((BITBLOCKS*j)+(b&BITMASK))]);
                b>>=BITDECAL;
            }
            
            #ifdef __SSE4_1__
            dest1[i]=_mm_extract_epi32 (ssetmp, 0);
            dest2[i]=_mm_extract_epi32 (ssetmp, 1);
            dest3[i]=_mm_extract_epi32 (ssetmp, 2);
            #else
            dest1[i]=(_mm_extract_epi16 (ssetmp, 0)) | (_mm_extract_epi16 (ssetmp, 1) << 16);
            dest2[i]=(_mm_extract_epi16 (ssetmp, 2)) | (_mm_extract_epi16 (ssetmp, 3) << 16);
            dest3[i]=(_mm_extract_epi16 (ssetmp, 4)) | (_mm_extract_epi16 (ssetmp, 5) << 16);
            #endif
        }
    }
    
    template <>
    void
    Matrix<ElementGF2Extension<uint32_t>>::quadAddMultRowGF2Extension(ElementGF2Extension<uint32_t> * dest1, ElementGF2Extension<uint32_t> * dest2, ElementGF2Extension<uint32_t> * dest3, ElementGF2Extension<uint32_t> * dest4, ElementGF2Extension<uint32_t> mult1, ElementGF2Extension<uint32_t> mult2, ElementGF2Extension<uint32_t> mult3, ElementGF2Extension<uint32_t> mult4, ElementGF2Extension<uint32_t> * vec, int start, int end)
    {
        uint32_t b;
        int i,j;
        uint32_t modulo = ElementGF2Extension<uint32_t>::getModulo();
        uint32_t maskBit = ElementGF2Extension<uint32_t>::getMaskBit();

        __m128i pow,amuls[BITBLOCKS*NBBITBLOCKS_INT],extmod,ssetmp;
        /* pow = [mult1, mult2, mult3, mult4] */
        pow=_mm_set_epi32(mult4.getElement(),mult3.getElement(),mult2.getElement(),mult1.getElement());
        /* pow = [modulo, modulo, modulo, modulo] */
        extmod=_mm_set_epi32(modulo,modulo,modulo,modulo);
        for(j=0;j<NBBITBLOCKS_INT;j++) 
        {
            amuls[BITBLOCKS*j]=_mm_xor_si128(pow,pow);
            amuls[BITBLOCKS*j+1]=pow;
            /* pow = [pow[0]*2, pow[1]*2, pow[2]*2, pow[3]*2] */
            pow=_mm_slli_epi32(pow,1);
            /* Arithmetic shift that sign bit into all the bits */
            ssetmp=_mm_srai_epi32(pow,maskBit);
            /* ssetmp = [modulo & ssetmp[0], modulo & ssetmp[1], modulo & ssetmp[2], modulo & ssetmp[3]] */
            ssetmp=_mm_and_si128(ssetmp,extmod);
            /* Apply modulo if required */
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<2;i++)
            {
                amuls[BITBLOCKS*j+i+2]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi32(pow,1);
            ssetmp=_mm_srai_epi32(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<4;i++)
            {
                amuls[BITBLOCKS*j+i+4]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi32(pow,1);
            ssetmp=_mm_srai_epi32(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<8;i++)
            {
                amuls[BITBLOCKS*j+i+8]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi32(pow,1);
            ssetmp=_mm_srai_epi32(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
        }

        for (i=start;i<end;i++) 
        {
            b=vec[i].getElement();
            /* ssetmp = [dest1[i], dest2[i], dest3[i], dest4[i]] */
            ssetmp=_mm_set_epi32(dest4[i].getElement(),dest3[i].getElement(),dest2[i].getElement(),dest1[i].getElement());
            for(j=0;j<NBBITBLOCKS_INT;j++) 
            {
                ssetmp=_mm_xor_si128(ssetmp,amuls[((BITBLOCKS*j)+(b&BITMASK))]);
                b>>=BITDECAL;
            }
            
            #ifdef __SSE4_1__
            dest1[i]=_mm_extract_epi32 (ssetmp, 0);
            dest2[i]=_mm_extract_epi32 (ssetmp, 1);
            dest3[i]=_mm_extract_epi32 (ssetmp, 2);
            dest4[i]=_mm_extract_epi32 (ssetmp, 3);
            #else
            dest1[i]=(_mm_extract_epi16 (ssetmp, 0)) | (_mm_extract_epi16 (ssetmp, 1) << 16);
            dest2[i]=(_mm_extract_epi16 (ssetmp, 2)) | (_mm_extract_epi16 (ssetmp, 3) << 16);
            dest3[i]=(_mm_extract_epi16 (ssetmp, 4)) | (_mm_extract_epi16 (ssetmp, 5) << 16);
            dest4[i]=(_mm_extract_epi16 (ssetmp, 6)) | (_mm_extract_epi16 (ssetmp, 7) << 16);
            #endif
        }
    }
    
    template <>
    void
    Matrix<ElementGF2Extension<uint32_t>>::octAddMultRowGF2Extension(ElementGF2Extension<uint32_t> * dest1, ElementGF2Extension<uint32_t> * dest2, ElementGF2Extension<uint32_t> * dest3, ElementGF2Extension<uint32_t> * dest4, ElementGF2Extension<uint32_t> * dest5, ElementGF2Extension<uint32_t> * dest6, ElementGF2Extension<uint32_t> * dest7, ElementGF2Extension<uint32_t> * dest8, ElementGF2Extension<uint32_t> mult1, ElementGF2Extension<uint32_t> mult2, ElementGF2Extension<uint32_t> mult3, ElementGF2Extension<uint32_t> mult4, ElementGF2Extension<uint32_t> mult5, ElementGF2Extension<uint32_t> mult6, ElementGF2Extension<uint32_t> mult7, ElementGF2Extension<uint32_t> mult8, ElementGF2Extension<uint32_t> * vec, int start, int end)
    {
        uint32_t b;
        int i,j;
        uint32_t modulo = ElementGF2Extension<uint32_t>::getModulo();
        uint32_t maskBit = ElementGF2Extension<uint32_t>::getMaskBit();

        __m128i pow,amuls[2*BITBLOCKS*NBBITBLOCKS_INT],extmod,ssetmp, ssetmp1, ssetmp2;
        /* pow = [mult1, mult2, mult3, mult4] */
        pow=_mm_set_epi32(mult4.getElement(),mult3.getElement(),mult2.getElement(),mult1.getElement());
        /* pow = [modulo, modulo, modulo, modulo] */
        extmod=_mm_set_epi32(modulo,modulo,modulo,modulo);
        
        /* Even cases */
        for(j=0;j<NBBITBLOCKS_INT;j++) 
        {
            amuls[2*(BITBLOCKS*j)]=_mm_xor_si128(pow,pow);
            amuls[2*(BITBLOCKS*j+1)]=pow;
            /* pow = [pow[0]*2, pow[1]*2, pow[2]*2, pow[3]*2] */
            pow=_mm_slli_epi32(pow,1);
            /* Arithmetic shift that sign bit into all the bits */
            ssetmp=_mm_srai_epi32(pow,maskBit);
            /* ssetmp = [modulo & ssetmp[0], modulo & ssetmp[1], modulo & ssetmp[2], modulo & ssetmp[3]] */
            ssetmp=_mm_and_si128(ssetmp,extmod);
            /* Apply modulo if required */
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<2;i++)
            {
                amuls[2*(BITBLOCKS*j+i+2)]=_mm_xor_si128(amuls[2*(BITBLOCKS*j+i)],pow);
            }
            pow=_mm_slli_epi32(pow,1);
            ssetmp=_mm_srai_epi32(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<4;i++)
            {
                amuls[2*(BITBLOCKS*j+i+4)]=_mm_xor_si128(amuls[2*(BITBLOCKS*j+i)],pow);
            }
            pow=_mm_slli_epi32(pow,1);
            ssetmp=_mm_srai_epi32(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<8;i++)
            {
                amuls[2*(BITBLOCKS*j+i+8)]=_mm_xor_si128(amuls[2*(BITBLOCKS*j+i)],pow);
            }
            pow=_mm_slli_epi32(pow,1);
            ssetmp=_mm_srai_epi32(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
        }
        
        /* pow = [mult5, mult6, mult7, mult8] */
        pow=_mm_set_epi32(mult8.getElement(),mult7.getElement(),mult6.getElement(),mult5.getElement());
        
        /* Odd cases */
        for(j=0;j<NBBITBLOCKS_INT;j++) 
        {
            amuls[2*(BITBLOCKS*j)+1]=_mm_xor_si128(pow,pow);
            amuls[2*(BITBLOCKS*j+1)+1]=pow;
            /* pow = [pow[0]*2, pow[1]*2, pow[2]*2, pow[3]*2] */
            pow=_mm_slli_epi32(pow,1);
            /* Arithmetic shift that sign bit into all the bits */
            ssetmp=_mm_srai_epi32(pow,maskBit);
            /* ssetmp = [modulo & ssetmp[0], modulo & ssetmp[1], modulo & ssetmp[2], modulo & ssetmp[3]] */
            ssetmp=_mm_and_si128(ssetmp,extmod);
            /* Apply modulo if required */
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<2;i++)
            {
                amuls[2*(BITBLOCKS*j+i+2)+1]=_mm_xor_si128(amuls[2*(BITBLOCKS*j+i)+1],pow);
            }
            pow=_mm_slli_epi32(pow,1);
            ssetmp=_mm_srai_epi32(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<4;i++)
            {
                amuls[2*(BITBLOCKS*j+i+4)+1]=_mm_xor_si128(amuls[2*(BITBLOCKS*j+i)+1],pow);
            }
            pow=_mm_slli_epi32(pow,1);
            ssetmp=_mm_srai_epi32(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<8;i++)
            {
                amuls[2*(BITBLOCKS*j+i+8)+1]=_mm_xor_si128(amuls[2*(BITBLOCKS*j+i)+1],pow);
            }
            pow=_mm_slli_epi32(pow,1);
            ssetmp=_mm_srai_epi32(pow,maskBit);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
        }

        for (i=start;i<end;i++) 
        {
            b=vec[i].getElement();
            /* ssetmp = [dest1[i], dest2[i], dest3[i], dest4[i]] */
            ssetmp1=_mm_set_epi32(dest4[i].getElement(),dest3[i].getElement(),dest2[i].getElement(),dest1[i].getElement());
            ssetmp2=_mm_set_epi32(dest8[i].getElement(),dest7[i].getElement(),dest6[i].getElement(),dest5[i].getElement());
            for(j=0;j<NBBITBLOCKS_INT;j++) 
            {
                ssetmp1=_mm_xor_si128(ssetmp1,amuls[2*((BITBLOCKS*j)+(b&BITMASK))]);
                ssetmp2=_mm_xor_si128(ssetmp2,amuls[2*((BITBLOCKS*j)+(b&BITMASK))+1]);
                b>>=BITDECAL;
            } 
            
            #ifdef __SSE4_1__
            dest1[i]=_mm_extract_epi32 (ssetmp1, 0);
            dest2[i]=_mm_extract_epi32 (ssetmp1, 1);
            dest3[i]=_mm_extract_epi32 (ssetmp1, 2);
            dest4[i]=_mm_extract_epi32 (ssetmp1, 3);
            dest5[i]=_mm_extract_epi32 (ssetmp2, 0);
            dest6[i]=_mm_extract_epi32 (ssetmp2, 1);
            dest7[i]=_mm_extract_epi32 (ssetmp2, 2);
            dest8[i]=_mm_extract_epi32 (ssetmp2, 3);
            #else
            dest1[i]=(_mm_extract_epi16 (ssetmp1, 0)) | (_mm_extract_epi16 (ssetmp1, 1) << 16);
            dest2[i]=(_mm_extract_epi16 (ssetmp1, 2)) | (_mm_extract_epi16 (ssetmp1, 3) << 16);
            dest3[i]=(_mm_extract_epi16 (ssetmp1, 4)) | (_mm_extract_epi16 (ssetmp1, 5) << 16);
            dest4[i]=(_mm_extract_epi16 (ssetmp1, 6)) | (_mm_extract_epi16 (ssetmp1, 7) << 16);
            dest5[i]=(_mm_extract_epi16 (ssetmp2, 0)) | (_mm_extract_epi16 (ssetmp2, 1) << 16);
            dest6[i]=(_mm_extract_epi16 (ssetmp2, 2)) | (_mm_extract_epi16 (ssetmp2, 3) << 16);
            dest7[i]=(_mm_extract_epi16 (ssetmp2, 4)) | (_mm_extract_epi16 (ssetmp2, 5) << 16);
            dest8[i]=(_mm_extract_epi16 (ssetmp2, 6)) | (_mm_extract_epi16 (ssetmp2, 7) << 16);
            #endif
        }
    }
    
    
    /* 64 bits integer -> up to GF(2^63) */
    #ifdef __SSE4_1__
    template <>
    void
    Matrix<ElementGF2Extension<uint64_t>>::doubleAddMultRowGF2Extension(ElementGF2Extension<uint64_t> * dest1, ElementGF2Extension<uint64_t> * dest2, ElementGF2Extension<uint64_t> mult1, ElementGF2Extension<uint64_t> mult2, ElementGF2Extension<uint64_t> * vec, int start, int end)
    {
        uint64_t b;
        int i,j;
        uint64_t modulo = ElementGF2Extension<uint64_t>::getModulo();

        __m128i pow,amuls[BITBLOCKS*NBBITBLOCKS_LONG],extmod,ssetmp;
        /* pow = [mult1, mult2] */
        pow=_mm_set_epi64((__m64)(mult2.getElement()),(__m64)(mult1.getElement()));
        /* pow = [modulo, modulo] */
        extmod=_mm_set_epi64((__m64)modulo,(__m64)modulo);
        for(j=0;j<NBBITBLOCKS_LONG;j++) 
        {
            amuls[BITBLOCKS*j]=_mm_xor_si128(pow,pow);
            amuls[BITBLOCKS*j+1]=pow;
            /* pow = [pow[0]*2, pow[1]*2] */
            pow=_mm_slli_epi64(pow,1);
            /* Arithmetic shift that sign bit into all the bits; replaced here by a comparison (_mm_srai_epi64 does not exist) */
            ssetmp=_mm_cmpgt_epi64(pow,extmod);
            /* ssetmp = [modulo & ssetmp[0], modulo & ssetmp[1]] */
            ssetmp=_mm_and_si128(ssetmp,extmod);
            /* Apply modulo if required */
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<2;i++)
            {
                amuls[BITBLOCKS*j+i+2]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi64(pow,1);
            ssetmp=_mm_cmpgt_epi64(pow,extmod);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<4;i++)
            {
                amuls[BITBLOCKS*j+i+4]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi64(pow,1);
            ssetmp=_mm_cmpgt_epi64(pow,extmod);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
            for(i=0;i<8;i++)
            {
                amuls[BITBLOCKS*j+i+8]=_mm_xor_si128(amuls[BITBLOCKS*j+i],pow);
            }
            pow=_mm_slli_epi64(pow,1);
            ssetmp=_mm_cmpgt_epi64(pow,extmod);
            ssetmp=_mm_and_si128(ssetmp,extmod);
            pow=_mm_xor_si128(ssetmp,pow);
        }

        for (i=start;i<end;i++) 
        {
            b=vec[i].getElement();
            /* ssetmp = [dest1[i], dest2[i]] */
            ssetmp=_mm_set_epi64((__m64)(dest2[i].getElement()),(__m64)(dest1[i].getElement()));
            for(j=0;j<NBBITBLOCKS_LONG;j++) 
            {
                ssetmp=_mm_xor_si128(ssetmp,amuls[((BITBLOCKS*j)+(b&BITMASK))]);
                b>>=BITDECAL;
            }
            
            dest1[i]=_mm_extract_epi64 (ssetmp, 0);
            dest2[i]=_mm_extract_epi64 (ssetmp, 1);
        }
    }
    #endif // __SSE4_1__
    #endif // __SSE2__
}

#endif // F4_SPECIALISATION_SIMD_GF2_EXTENSION_INL
