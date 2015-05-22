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
  * \file matrix.inl
  * \brief Definition of Matrix methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_MATRIX_INL
#define F4_MATRIX_INL

using namespace std;

namespace F4
{
    /* Global variables */
    
    extern int VERBOSE;
    
    extern int NB_THREAD;
    
    
    /* Constructor */
    
    template <typename Element>
    Matrix<Element>::Matrix():_matrix(0), _height(0), _width(0), _nbPiv(0), _tau(0), _sigma(0), _startTail(0), _endCol(0)
    {
    }
    
    template <typename Element>
    Matrix<Element>::Matrix(int height, int width): _height(height), _width(width), _nbPiv(0), _tau(0), _sigma(0), _startTail(0), _endCol(0)
    {
        _matrix=new Element*[_height];
        int allocWidth = 16 * ((_width + 16 - 1) / 16);
        for(int i=0; i< _height; i++)
        {
            _matrix[i]=new Element[allocWidth]();
        }
    }
    
    template <typename Element>
    Matrix<Element>::Matrix(string const & filename)
    {
        ifstream file(filename);
        if(file)
        {
            size_t pos;
            int i;
            int row=0;
            string string1="Matrix of size:";
            string string2="Number of pivots:";
            string string3="*";
            string string4="sigma:";
            string string5="tau:";
            string string6="start_tail:";
            string string7="end_col:";
            string string8="matrix:";
            string tmp;
            string line;
            
            getline(file, line);
            if (line.find(string1)!=string::npos)
            {
                /* Get height */
                pos=string1.size();
                tmp=line.substr(pos);
                _height=stoul(tmp);
                
                /* Get width */
                pos=line.find(string3, pos);
                tmp=line.substr(pos + string3.size());
                _width=stoul(tmp);
                cout << "height: " << _height << ", width: " << _width << endl;
                _matrix=new Element*[_height];
                int allocWidth = 16 * ((_width + 16 - 1) / 16);
                for(int i=0; i< _height; i++)
                {
                    _matrix[i]=new Element[allocWidth]();
                }
                _sigma=new int[_width];
                _tau=new int[_width];
                _startTail=new int[_height];
                _endCol=new int[_width];
            }
            getline(file, line);
            if (line.find(string2)!=string::npos)
            {
                /* Get nbPiv */
                pos=string2.size();
                tmp=line.substr(pos);
                _nbPiv=stoul(tmp);
                cout << "nbPiv: " << _nbPiv << endl;
            }
            getline(file, line);
            if (line.find(string4)!=string::npos)
            {
                /* Skip one line */
                getline(file, line);
                
                /* Get sigma */
                i = 0;
                stringstream ssin(line);
                while (ssin.good() && i < _width)
                {
                    ssin >> tmp;
                    _sigma[i]=stoi(tmp);
                    ++i;
                }
            }
            getline(file, line);
            if (line.find(string5)!=string::npos)
            {
                /* Skip one line */
                getline(file, line);
                
                // Get tau
                i = 0;
                stringstream ssin(line);
                while (ssin.good() && i < _width)
                {
                    ssin >> tmp;
                    _tau[i]=stoi(tmp);
                    ++i;
                }
            }
            getline(file, line);
            if (line.find(string6)!=string::npos)
            {
                // skip one line
                getline(file, line);
                
                // Get startTail
                i = 0;
                stringstream ssin(line);
                while (ssin.good() && i < _height)
                {
                    ssin >> tmp;
                    _startTail[i]=stoi(tmp);
                    ++i;
                }
            }
            getline(file, line);
            if (line.find(string7)!=string::npos)
            {
                /* Skip one line */
                getline(file, line);
                
                /* Get endCol */
                i = 0;
                stringstream ssin(line);
                while (ssin.good() && i < _width)
                {
                    ssin >> tmp;
                    _endCol[i]=stoi(tmp);
                    ++i;
                }
            }
            getline(file, line);
            if (line.find(string8)!=string::npos)
            {
                /* Get matrix */
                while(getline(file, line) && row <_height)
                {
                    i = 0;
                    stringstream ssin(line);
                    while (ssin.good() && i < _width)
                    {
                        ssin >> tmp;
                        getRow(row)[i]=stoul(tmp);
                        ++i;
                    }
                    row++;
                }
            }
            file.close();
        }
        else
        {
            cout << "Matrix::Matrix(string filename): Failed " << endl;
        }
    }
    
    template <typename Element>
    Matrix<Element>::Matrix(Matrix const & matrix): _height(matrix._height), _width(matrix._width), _nbPiv(matrix._nbPiv), _tau(matrix._tau), _sigma(matrix._sigma), _startTail(matrix._startTail), _endCol(matrix._endCol)
    {
        int j;
        _matrix=new Element*[_height];
        int allocWidth = 16 * ((_width + 16 - 1) / 16);
        for(int i=0; i< _height; i++)
        {
            _matrix[i]=new Element[allocWidth]();
            for(j=0; j<_width; j++)
            {
                _matrix[i][j]=matrix._matrix[i][j];
            }
        }
    }
            
    template <typename Element>
    Matrix<Element>::Matrix(Matrix && matrix)
    {
        if(_matrix!=0)
        {
            for(int i=0; i< _height; i++)
            {
                delete[] _matrix[i];
                _matrix[i]=0;
            } 
            delete[] _matrix;
        }
        _matrix=matrix._matrix;
        matrix._matrix=0;
        _height=matrix._height;
        matrix._height=0;
        _width=matrix._width;
        matrix._width=0;
        _nbPiv=matrix._nbPiv;
        matrix._nbPiv=0;
        _tau=matrix._tau;
        matrix._tau=0;
        _sigma=matrix._sigma;
        matrix._sigma=0;
        _startTail=matrix._startTail; 
        matrix._startTail=0;
        _endCol=matrix._endCol;
        matrix._endCol=0;
    }
    
    
    /* Destructor */ 
    
    template <typename Element>
    Matrix<Element>::~Matrix()
    {
        if(_matrix!=0)
        {
            for(int i=0; i< _height; i++)
            {
                delete[] _matrix[i];
                _matrix[i]=0;
            } 
            delete[] _matrix;
            _matrix=0;
        }
    }
    
    
    /* Get / Set */
    
    template <typename Element>
    inline Element & 
    Matrix<Element>::operator() (int row, int col) 
    { 
        assert(row < _height && col < _width); 
        return _matrix[row][col]; 
    } 
    
    template <typename Element>
    inline Element 
    Matrix<Element>::operator() (int row, int col) const 
    { 
        assert(row < _height && col < _width);
        return _matrix[row][col]; 
    }
    
    template <typename Element>
    inline Element 
    Matrix<Element>::getElement(int row, int col) const
    {
        assert(row < _height && col < _width); 
        return _matrix[row][col]; 
    }
    
    template <typename Element>
    inline void 
    Matrix<Element>::setElement (int row, int col, Element const & element)
    {
        assert(row < _height && col < _width); 
        _matrix[row][col]=element; 
    }
    
    template <typename Element>
    Element *
    Matrix<Element>::getRow (int row) 
    { 
        assert(row < _height);
        return _matrix[row]; 
    }
    
    template <typename Element>
    int
    Matrix<Element>::getHeight() const
    {
        return _height;
    }
    
    template <typename Element>
    int
    Matrix<Element>::getWidth() const
    {
        return _width;
    }
    
    template <typename Element>
    void 
    Matrix<Element>::setNbPiv(int nbPiv)
    {
        _nbPiv=nbPiv;
    }
    
    template <typename Element>
    int
    Matrix<Element>::getNbPiv() const
    {
        return _nbPiv;
    }
    
    template <typename Element>
    void
    Matrix<Element>::setTau(int * tau)
    {
        _tau=tau;
    }
    
    template <typename Element>
    int * 
    Matrix<Element>::getTau()
    {
        return _tau;
    }
    
    template <typename Element>
    void
    Matrix<Element>::setSigma(int * sigma)
    {
        _sigma=sigma;
    }
    
    template <typename Element>
    int *
    Matrix<Element>::getSigma()
    {
        return _sigma;
    }
    
    template <typename Element>
    void 
    Matrix<Element>::setStartTail(int * startTail)
    {
        _startTail=startTail;
    }
    
    template <typename Element>
    int * 
    Matrix<Element>::getStartTail()
    {
        return _startTail;
    }
    
    template <typename Element>
    void
    Matrix<Element>::setEndCol(int * endCol)
    {
        _endCol=endCol;
    }
    
    template <typename Element>
    int * 
    Matrix<Element>::getEndCol()
    {
        return _endCol;
    }
    
    template <typename Element>
    void
    Matrix<Element>::setInfo(int nbPiv, int *tau, int *sigma, int * startTail, int * endCol)
    {
         _nbPiv=nbPiv;
         _tau=tau;
         _sigma=sigma;
         _startTail=startTail;
         _endCol=endCol;
    }
    
    /* Miscellaneous */
    
    template <typename Element>
    void
    Matrix<Element>::printMatrix (std::ostream & stream) const
    {
        for (int i=0; i<_height; i++)
        {
            for(int j=0; j<_width; j++)
            {
                stream << " " << _matrix[i][j] << " "; 
            }
            stream << endl;
        }
    }
    
    template <typename Element>
    void
    Matrix<Element>::printMatrix (string const & filename) const
    {
        ofstream file(filename);
        if (file)
        {
            file << "P3" << endl << _width << " " << _height << endl << 1 << endl;
            int i, j;
            for (i = 0; i < _height; i++)
            {
                for (j = 0; j < _width; j++)
                {
                    if (!isZero(i,j))
                    {
                        file << " 0 0 0 ";
                    }
                    else
                    {
                        file << " 1 1 1 ";
                    }
                }
                file << endl;
            }
            file.close();
        }
    }
    
    template <typename Element>
    void
    Matrix<Element>::printMatrixTxt (string const & filename) const
    {
        ofstream file(filename);
        if (file)
        {
            file << "Matrix of size: " << _height << " * " << _width << " " << endl;
            file << "Number of pivots: " << _nbPiv << " " << endl;
            int i, j;

            //Affichage de _sigma
            file <<  "sigma:" << endl;
            for (i = 0; i < _width; i++)
            {
                file << " " << _sigma[i] << " ";
            }
            file << endl;
            
            //Affichage de _tau
            file << "tau:" << endl;
            for (i = 0; i < _width; i++)
            {
                file << " " << _tau[i] << " ";
            }
            file << endl;

            //Affichage de _startTail
            file << "start_tail:" << endl;
            for (i = 0; i < _height; i++)
            {
                file << " " << _startTail[i] << " ";
            }
            file << endl;

            //Affichage de _endCol
            file << "end_col:" << endl;
            for (i = 0; i < _width; i++)
            {
                file << " " << _endCol[i] << " ";
            }
            file << endl;
            
            // Affichage de la matrice
            file << "matrix:" << endl;
            for (i = 0; i < _height; i++)
            {
                for (j = 0; j < _width; j++)
                {
                    file << " " << _matrix[i][j] << " ";
                }
                file << endl;
            }
            file << endl;
            file.close();
        }
    }
    
    //template <typename Element>
    //void
    //Matrix<Element>::printMatrixTxt (string const & filename) const
    //{
        //ofstream file(filename);
        //if (file)
        //{
            //file << _height << endl << _width << endl;
            
            //for (int i = 0; i < _height; i++)
            //{
                //for (int j = 0; j < _width; j++)
                //{
                    //file << " " << _matrix[i][j] << " ";
                //}
                //file << endl;
            //}
            //file << endl;
            //file.close();
        //}
    //}
    
    //template <typename Element>
    //void
    //Matrix<Element>::printMatrixTxt (string const & filename) const
    //{
        //ofstream file(filename);
        //if (file)
        //{
            //file << "A=Matrix(GF(65521), [" ;
            //for (int i = 0; i < _height; i++)
            //{
                //file << "[";
                //for (int j = 0; j < _width; j++)
                //{
                    //if(j==_width-1)
                    //{
                        //file << _matrix[i][j];
                    //}
                    //else
                    //{
                        //file << _matrix[i][j] << ",";
                    //}
                //}
                //file << "]," << endl;
            //}
            //file << "])" << endl;
            //file.close();
        //}
    //}
    
    template <typename Element>
    bool
    Matrix<Element>::isZero(int row, int col) const
    {
        return (_matrix[row][col]).isZero(); 
    }
    
    template <typename Element>
    void
    Matrix<Element>::normalizeRow(Element * row, int start, int end)
    {
        assert((start >= 0) && (end <= _width));
        for(int i=start; i<end; ++i)
        {
            row[i].modulo();
        }
    }
    
    template <typename Element>
    void
    Matrix<Element>::multRow(Element * row, Element const & element, int start, int end)
    {
        assert((start >= 0) && (end <= _width));
        for(int i=start; i<end; ++i)
        {
            row[i]*=element;
        }
    }
    
    template <typename Element>
    inline void
    Matrix<Element>::addMultRow(Element * row1, Element * row2, Element element, int start, int end)
    {
        assert((start >= 0) && (end <= _width));
        element.modulo();
        for(int i=start; i<end; ++i)
        {
            row1[i].addMult(row2[i], element);
        }
    }
    
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
    
    template <typename Element>
    void
    Matrix<Element>::swapRow(int numRow1, int numRow2)
    {
        Element * tmp = _matrix[numRow1];
        _matrix[numRow1] = _matrix[numRow2];
        _matrix[numRow2] = tmp;
    }
    
    template <typename Element>
    void
    Matrix<Element>::swapCol(int numCol1, int numCol2, int start, int end)
    {
        assert((start >= 0) && (end <= _height));
        for(int i=start; i<end; i++)
        {
            swap(_matrix[i][numCol1], _matrix[i][numCol2]);
        }
    }
    
    template <typename Element>
    int
    Matrix<Element>::echelonizeRight (chrono::duration<int,milli> & tmp_ech_db, chrono::duration<int,milli> & tmp_ech_dh)
    {
        chrono::steady_clock::time_point startc;
        typedef chrono::duration<int,milli> millisecs_t;
        typedef Givaro::ModularBalanced<double> Field;
        Field F(Element::getModulo());
        typename Field::Element * matrixRight = FFLAS::fflas_new (F,_height,_width-_nbPiv);
        typename Field::Element one, minusOne;
        size_t *P = new size_t[_height-_nbPiv]();
        size_t *Q = new size_t[_width-_nbPiv]();
        int ld=_width-_nbPiv;
        F.init(one,1);
        F.init(minusOne,-1);
        
        /* Convert left slice into FFLAS-FFPACK matrix */
        startc=chrono::steady_clock::now();
        for(int i=0; i<_height; i++)
        {
            for(int j=0; j<ld; j++)
            {
                F.init(matrixRight[i*ld+j], _matrix[i][_nbPiv+j].getElement());
            }
        }
        cout << "Time conversion 1: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-startc).count() << " ms" << endl;
        
        typename Field::Element * B=matrixRight;
        typename Field::Element * D=matrixRight+_nbPiv*ld;
        
        startc=chrono::steady_clock::now();
        /* PLUQ(D) */
        int rank = (int)FFPACK::PLUQ (F, FFLAS::FflasUnit, (_height-_nbPiv), (_width-_nbPiv), D, ld, P, Q);
        /* D2 = D1^(-1) * D2 */
        FFLAS::ftrsm (F, FFLAS::FflasLeft, FFLAS::FflasUpper, FFLAS::FflasNoTrans, FFLAS::FflasUnit, rank, (_width-_nbPiv)-rank, one, D, ld, D+rank, ld);
        /* Suppress zero rows */
        //FFLAS::fzero(F, (_height-_nbPiv)-rank, (_width-_nbPiv), D+rank*ld, ld);
        /* Suppress L */
        FFLAS::fidentity (F, rank, rank, D, ld);
        /* B = B * Q^T */
        FFPACK::applyP(F, FFLAS::FflasRight, FFLAS::FflasTrans, _nbPiv, 0, (_width-_nbPiv), B, ld, Q);
        /* Carry the column swap over */
        int exc=0;
        for(int i=0; i<ld; i++)
        {
            int l = _nbPiv+i;
            int ca = _nbPiv+Q[i];
            _tau[_sigma[l]] = ca;
            _tau[_sigma[ca]] = l;
            exc = _sigma[l];
            _sigma[l] = _sigma[ca];
            _sigma[ca] = exc;
            exc = _endCol[l];
            _endCol[l] = _endCol[ca];
            _endCol[ca] = exc;
        }
        
        tmp_ech_db=chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-startc);
        startc=chrono::steady_clock::now();
        /* B2 = B2 - B1 * D2 */
        FFLAS::fgemm(F, FFLAS::FflasNoTrans, FFLAS::FflasNoTrans, _nbPiv, (_width-_nbPiv)-rank, rank, minusOne, B , ld, D+rank, ld, one, B+rank, ld);
        /* B1 = 0 */
        FFLAS::fzero(F, _nbPiv, rank, B, ld);
        tmp_ech_dh=chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-startc);
        
        /* Convert the FFLAS-FFPACK matrix into integer matrix */
        startc=chrono::steady_clock::now();
        for(int i=0; i<_height; i++)
        {
            for(int j=0; j<ld; j++)
            {
                _matrix[i][_nbPiv+j] = (int32_t)matrixRight[i*ld+j];
            }
        }
        cout << "Time conversion 2: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-startc).count() << " ms" << endl;
        delete[] P;
        delete[] Q;
        FFLAS::fflas_delete(matrixRight);
        return _nbPiv+rank;
    }
    
    #define PARALLEL
    #define FFLAS_FFPACK
    #ifndef PARALLEL
    #ifndef FFLAS_FFPACK
    template <typename Element>
    int
    Matrix<Element>::echelonize ()
    {
        clock_t start;
        double tmp_ech_g, tmp_ech_db, tmp_ech_dh;
        int ca = 0;
        int i, l, l2, ll;
        i = 0;
        l = 0;
        Element piv, inv;
        int exc;

        if (VERBOSE > 1)
        {
            printf ("Echelonization time: ");
        }

    #define TRANCHE 64
    
        /* Echelonize the left part of the matrix */
        start = clock ();
        for (l = _nbPiv - 1; l >= 0; l -= TRANCHE)
        {
            /* 1st slice */
            if (l < TRANCHE)
            {
                /* Triangular part */
                for (ll = l; ll > 0; ll--)
                {
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[ll], ll, _width);
                    for (l2 = 0; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                normalizeRow(_matrix[0], 0, _width);
                
                /* Low rectangular part (under  _nbPiv) */
                for (l2 = _nbPiv; l2 < _endCol[l]; l2++)
                {
                    for (ll = l; ll >= 0; ll--)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
            }
            /* Other slices */
            else
            {
                /* Triangular part */
                for (ll = l; ll > l - TRANCHE; ll--)
                {
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[ll], ll, _width);
                    for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Hight rectangular part */
                for (l2 = 0; l2 <= l - TRANCHE; l2++)
                {
                    for (ll = l; ll > l - TRANCHE; ll--)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Low rectangular part (under  _nbPiv) */
                for (l2 = _nbPiv; l2 < _endCol[l]; l2++)
                {
                    for (ll = l; ll > l - TRANCHE; ll--)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
            }
        }
        tmp_ech_g = (((double)clock () - start) * 1000) / CLOCKS_PER_SEC;
        
        /* Echelonize the low right part of the matrix */
        start = clock ();
        ca = _nbPiv;
        l = _nbPiv;
        while (l < _height)
        {
            for (; ca < _width; ca++)
            {
                /* Search a pivot in column ca */
                for (i = l; i < _height; i++)
                {
                    /* Normalize in  [-MODULO/2, MODULO/2]. */
                    _matrix[i][ca].modulo();
                    if (!isZero(i,ca) )
                    {
                        break;
                    }
                }
                if (i < _height)
                {
                    /* Pivot found in column ca */
                    break;          
                }
            }
            if (ca == _width)
            {
                /* All the rows under the l-th row are zeros */ 
                for(l2=l; l2<_height; l2++)
                {
                    delete[] _matrix[l2];
                }
                /* Forget all the zeros rows */
                _height = l;
            }
            else
            {
                /* Swap with the row containing the pivot */
                swapRow(l,i);
                if (ca != l)
                {
                    /* Column swap */
                    ll = (_endCol[l] > _endCol[ca] ? _endCol[l] : _endCol[ca]);
                    swapCol(l,ca,0, ll);
                    swapCol(l, ca, _nbPiv, _height);
                    /* Carry the column swap over */
                    _tau[_sigma[l]] = ca;
                    _tau[_sigma[ca]] = l;
                    exc = _sigma[l];
                    _sigma[l] = _sigma[ca];
                    _sigma[ca] = exc;
                    exc = _endCol[l];
                    _endCol[l] = _endCol[ca];
                    _endCol[ca] = exc;
                }
                piv = _matrix[l][l];
                inv = piv.inverse();
                
                /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                multRow (_matrix[l], inv, ca + 1, _width);      
                _matrix[l][l].setOne();
                
                /* Suppress the elements under the pivot */
                for (l2 = l + 1; l2 < _height; l2++)
                {
                    /* Normalize in  [-MODULO/2, MODULO/2]. */
                    _matrix[l2][l].modulo();
                    if (!isZero(l2,l) )
                    {
                        addMultRow (_matrix[l2], _matrix[l], -_matrix[l2][l], ca, _width);
                        _matrix[l2][l].setZero();
                    }
                }
                l++;
                ca++;
            }
        }
        tmp_ech_db = (((double)clock () - start) * 1000) / CLOCKS_PER_SEC;

        /* Echelonize the hight right part of the matrix */
        start = clock ();

        /* Check _endCol */
        for (l = _nbPiv; l < _height - 1; l++)
        {
            if (_endCol[l + 1] < _endCol[l])
            {
                fprintf (stderr, "_endCol hypothesis voided: please report\n");
                exit (1);
            }
        }

        int min_endcol, max_endcol;
        for (l = _height - 1; l >= _nbPiv; l -= TRANCHE)
        {
            if (l < (_nbPiv + TRANCHE))
            {
                /* 1st slice */
                /* Triangular part */
                for (ll = l; ll > _nbPiv; ll--)
                {
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[ll], ll, _width);
                    for (l2 = _nbPiv; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                normalizeRow(_matrix[_nbPiv], _nbPiv, _width);
                
                max_endcol = _endCol[l];
                min_endcol = _endCol[_nbPiv];
                /* Upper rectangular part */
                for (l2 = 0; l2 < min_endcol; l2++)
                {
                    for (ll = l; ll >= _nbPiv; ll--)
                    {
                        /* Normalize in  [-MODULO/2, MODULO/2]. */
                        _matrix[l2][ll].modulo();
                        if (!isZero(l2,ll) )
                        {
                            addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                            _matrix[l2][ll].setZero();
                        }
                    }
                }
                for (l2 = min_endcol; l2 < max_endcol; l2++)
                {
                    for (ll = l; _endCol[ll] > l2; ll--)
                    {
                        /* Normalize in  [-MODULO/2, MODULO/2]. */
                        _matrix[l2][ll].modulo();
                        if (!isZero(l2,ll))
                        {
                            addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                            _matrix[l2][ll].setZero();
                        }
                    }
                }
            }
            else
            {
                /* Triangular part */
                for (ll = l; ll > l - TRANCHE + 1; ll--)
                {
                   /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[ll], ll, _width);
                    for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                normalizeRow(_matrix[l - TRANCHE + 1], l - TRANCHE + 1, _width);
                
                /* Upper rectangular part */
                max_endcol = _endCol[l];
                min_endcol = _endCol[l - TRANCHE + 1];
                for (l2 = 0; l2 < min_endcol; l2++)
                {
                    for (ll = l; ll > l - TRANCHE; ll--)
                    {
                        /* Normalize in  [-MODULO/2, MODULO/2]. */
                        _matrix[l2][ll].modulo();
                        if (!isZero(l2,ll) )
                        {
                            addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                            _matrix[l2][ll].setZero();
                        }
                    }
                }
                for (l2 = min_endcol; l2 < max_endcol; l2++)
                {
                    for (ll = l; _endCol[ll] > l2; ll--)
                    {
                        /* Normalize in  [-MODULO/2, MODULO/2]. */
                        _matrix[l2][ll].modulo();
                        if (!isZero(l2,ll) )
                        {
                            addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                            _matrix[l2][ll].setZero();
                        }
                    }
                }
                for (l2 = _nbPiv; l2 <= l - TRANCHE; l2++)
                {
                    for (ll = l; ll > l - TRANCHE; ll--)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
            }
        }
        tmp_ech_dh = (((double)clock () - start) * 1000) / CLOCKS_PER_SEC;
        
        /* Normalize the matrix */
        for (i = 0; i < _height; i++)
        {
            for (l = 0; l < _width; l++)
            {
                _matrix[i][l].modulo();
            }
        }

        if (VERBOSE > 1)
        {
            printf ("%.1f + %.1f + %.1f ms = %.1f CPU \n\n", tmp_ech_g, tmp_ech_db, tmp_ech_dh, tmp_ech_g + tmp_ech_db + tmp_ech_dh);
        }
        return _height;
    }
    #endif // FFLAS_FFPACK
    #endif // PARALLEL
    
    #ifdef FFLAS_FFPACK
    template <typename Element>
    int
    Matrix<Element>::echelonize ()
    {
        chrono::steady_clock::time_point start;
        typedef chrono::duration<int,milli> millisecs_t;
        millisecs_t tmp_ech_g, tmp_ech_db, tmp_ech_dh;
        int i, l, l2, ll;
        i = 0;
        l = 0;
        
        /* Thread parameters */
        omp_set_num_threads(NB_THREAD);
        int chunk = 1;

        if (VERBOSE > 1)
        {
            printf ("Echelonization time: ");
        }

    #define TRANCHE 64
    
        /* Echelonize the left part of the matrix */
        start = chrono::steady_clock::now();
        for (l = _nbPiv - 1; l >= 0; l -= TRANCHE)
        {
            /* 1st slice */
            if (l < TRANCHE)
            {
                /* Triangular part */
                for (ll = l; ll > 0; ll--)
                {
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[ll], ll, _width);
                    #pragma omp parallel for schedule(dynamic,chunk)
                    for (l2 = 0; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                normalizeRow(_matrix[0], 0, _width);
                
                /* Low rectangular part (under  _nbPiv) */
                #pragma omp parallel for private(ll) schedule(dynamic,chunk)
                for (l2 = _nbPiv; l2 < _endCol[l]; l2++)
                {
                    for (ll = l; ll >= 0; ll--)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
            }
            /* Other slices */
            else
            {
                /* Triangular part */
                for (ll = l; ll > l - TRANCHE; ll--)
                {
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[ll], ll, _width);
                    #pragma omp parallel for schedule(dynamic,chunk)
                    for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Hight rectangular part */
                #pragma omp parallel 
                {
                    #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                    for (l2 = 0; l2 <= l - TRANCHE; l2++)
                    {
                        for (ll = l; ll > l - TRANCHE; ll--)
                        {
                            if (!isZero(l2,ll) )
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                    }
                    /* Low rectangular part (under  _nbPiv) */
                    #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                    for (l2 = _nbPiv; l2 < _endCol[l]; l2++)
                    {
                        for (ll = l; ll > l - TRANCHE; ll--)
                        {
                            if (!isZero(l2,ll) )
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                    }
                }
            }
        }
        tmp_ech_g = chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start);
        
        /* Echelonize the right part of the matrix */
        
        #define SEUIL_FFLAS_FFPACK 1000000
        
        if((_width-_nbPiv)*(_height-_nbPiv) > SEUIL_FFLAS_FFPACK)
        {
            int rank=echelonizeRight(tmp_ech_db, tmp_ech_dh);
            /* All the rows under the l-th row are zeros */ 
            for(l2=rank; l2<_height; l2++)
            {
                delete[] _matrix[l2];
            }
            _height=rank;
        }
        else
        {
            int ca = 0;
            int exc;
            Element inv, piv;
            
            /* Echelonize the low right part of the matrix */
            start = chrono::steady_clock::now();
            ca = _nbPiv;
            l = _nbPiv;
            while (l < _height)
            {
                for (; ca < _width; ca++)
                {
                    /* Search a pivot in column ca */
                    for (i = l; i < _height; i++)
                    {
                        /* Normalize in  [-MODULO/2, MODULO/2]. */
                        _matrix[i][ca].modulo();
                        if (!isZero(i,ca) )
                        {
                            break;
                        }
                    }
                    if (i < _height)
                    {
                        /* Pivot found in column ca */
                        break;          
                    }
                }
                if (ca == _width)
                {
                    /* All the rows under the l-th row are zeros */ 
                    for(l2=l; l2<_height; l2++)
                    {
                        delete[] _matrix[l2];
                    }
                    /* Forget all the zeros rows */
                    _height = l;
                }
                else
                {
                    /* Swap with the row containing the pivot */
                    swapRow(l,i);
                    if (ca != l)
                    {
                        /* Column swap */
                        ll = (_endCol[l] > _endCol[ca] ? _endCol[l] : _endCol[ca]);
                        swapCol(l,ca,0, ll);
                        swapCol(l, ca, _nbPiv, _height);
                        /* Carry the column swap over */
                        _tau[_sigma[l]] = ca;
                        _tau[_sigma[ca]] = l;
                        exc = _sigma[l];
                        _sigma[l] = _sigma[ca];
                        _sigma[ca] = exc;
                        exc = _endCol[l];
                        _endCol[l] = _endCol[ca];
                        _endCol[ca] = exc;
                    }
                    piv = _matrix[l][l];
                    inv = piv.inverse();
                    
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    multRow (_matrix[l], inv, ca + 1, _width);      
                    _matrix[l][l].setOne();
                    
                    /* Suppress the elements under the pivot */
                    #pragma omp parallel for schedule(dynamic,chunk)
                    for (l2 = l + 1; l2 < _height; l2++)
                    {
                        /* Normalize in  [-MODULO/2, MODULO/2]. */
                        _matrix[l2][l].modulo();
                        if (!isZero(l2,l) )
                        {
                            addMultRow (_matrix[l2], _matrix[l], -_matrix[l2][l], ca, _width);
                            _matrix[l2][l].setZero();
                        }
                    }
                    l++;
                    ca++;
                }
            }
            tmp_ech_db = chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start);

            /* Echelonize the hight right part of the matrix */
            start = chrono::steady_clock::now();

            /* Check _endCol */
            for (l = _nbPiv; l < _height - 1; l++)
            {
                if (_endCol[l + 1] < _endCol[l])
                {
                    fprintf (stderr, "_endCol hypothesis voided: please report\n");
                    exit (1);
                }
            }

            int min_endcol, max_endcol;
            for (l = _height - 1; l >= _nbPiv; l -= TRANCHE)
            {
                if (l < (_nbPiv + TRANCHE))
                {
                    /* 1st slice */
                    /* Triangular part */
                    for (ll = l; ll > _nbPiv; ll--)
                    {
                        /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                        normalizeRow(_matrix[ll], ll, _width);
                        #pragma omp parallel for schedule(dynamic,chunk)
                        for (l2 = _nbPiv; l2 < ll; l2++)
                        {
                            if (!isZero(l2,ll) )
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                    }
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[_nbPiv], _nbPiv, _width);
                    
                    max_endcol = _endCol[l];
                    min_endcol = _endCol[_nbPiv];
                    /* Upper rectangular part */
                    #pragma omp parallel
                    {
                        #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                        for (l2 = 0; l2 < min_endcol; l2++)
                        {
                            for (ll = l; ll >= _nbPiv; ll--)
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                        #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                        for (l2 = min_endcol; l2 < max_endcol; l2++)
                        {
                            for (ll = l; _endCol[ll] > l2; ll--)
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll))
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                    }
                }
                else
                {
                    /* Triangular part */
                    for (ll = l; ll > l - TRANCHE + 1; ll--)
                    {
                       /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                        normalizeRow(_matrix[ll], ll, _width);
                        #pragma omp parallel for schedule(dynamic,chunk)
                        for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                        {
                            if (!isZero(l2,ll) )
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                    }
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[l - TRANCHE + 1], l - TRANCHE + 1, _width);
                    
                    /* Upper rectangular part */
                    max_endcol = _endCol[l];
                    min_endcol = _endCol[l - TRANCHE + 1];
                    #pragma omp parallel
                    {
                        #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                        for (l2 = 0; l2 < min_endcol; l2++)
                        {
                            for (ll = l; ll > l - TRANCHE; ll--)
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                        #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                        for (l2 = min_endcol; l2 < max_endcol; l2++)
                        {
                            for (ll = l; _endCol[ll] > l2; ll--)
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                        #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                        for (l2 = _nbPiv; l2 <= l - TRANCHE; l2++)
                        {
                            for (ll = l; ll > l - TRANCHE; ll--)
                            {
                                if (!isZero(l2,ll) )
                                {
                                    /* Normalize in  [-MODULO/2, MODULO/2]. */
                                    _matrix[l2][ll].modulo();
                                    if (!isZero(l2,ll) )
                                    {
                                        addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                        _matrix[l2][ll].setZero();
                                    }
                                }
                            }
                        }
                    }
                }
            }
            tmp_ech_dh = chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start);
        }
            
        /* Normalize the matrix */
        #pragma omp parallel for private(l) schedule(dynamic,chunk)
        for (i = 0; i < _height; i++)
        {
            for (l = i; l < _width; l++)
            {
                _matrix[i][l].modulo();
            }
        }

        if (VERBOSE > 1)
        {
            cout << tmp_ech_g.count() << " + " << tmp_ech_db.count() << " + " << tmp_ech_dh.count() << " = " << (tmp_ech_g + tmp_ech_db + tmp_ech_dh).count() << " ms" << endl << endl;
        }
        return _height;
    }
    #endif // FFLAS_FFPACK
    
    
    #ifdef PARALLEL
    #ifndef FFLAS_FFPACK
    template <typename Element>
    int
    Matrix<Element>::echelonize ()
    {
        chrono::steady_clock::time_point start;
        typedef chrono::duration<int,milli> millisecs_t;
        millisecs_t tmp_ech_g, tmp_ech_db, tmp_ech_dh;
        int ca = 0;
        int i, l, l2, ll;
        i = 0;
        l = 0;
        Element piv, inv;
        int exc;
        
        /* Thread parameters */
        omp_set_num_threads(NB_THREAD);
        int chunk = 1;

        if (VERBOSE > 1)
        {
            printf ("Echelonization time: ");
        }

    #define TRANCHE 64
    
        /* Echelonize the left part of the matrix */
        start = chrono::steady_clock::now();
        for (l = _nbPiv - 1; l >= 0; l -= TRANCHE)
        {
            /* 1st slice */
            if (l < TRANCHE)
            {
                /* Triangular part */
                for (ll = l; ll > 0; ll--)
                {
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[ll], ll, _width);
                    #pragma omp parallel for schedule(dynamic,chunk)
                    for (l2 = 0; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                normalizeRow(_matrix[0], 0, _width);
                
                /* Low rectangular part (under  _nbPiv) */
                #pragma omp parallel for private(ll) schedule(dynamic,chunk)
                for (l2 = _nbPiv; l2 < _endCol[l]; l2++)
                {
                    for (ll = l; ll >= 0; ll--)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
            }
            /* Other slices */
            else
            {
                /* Triangular part */
                for (ll = l; ll > l - TRANCHE; ll--)
                {
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[ll], ll, _width);
                    #pragma omp parallel for schedule(dynamic,chunk)
                    for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Hight rectangular part */
                #pragma omp parallel 
                {
                    #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                    for (l2 = 0; l2 <= l - TRANCHE; l2++)
                    {
                        for (ll = l; ll > l - TRANCHE; ll--)
                        {
                            if (!isZero(l2,ll) )
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                    }
                    /* Low rectangular part (under  _nbPiv) */
                    #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                    for (l2 = _nbPiv; l2 < _endCol[l]; l2++)
                    {
                        for (ll = l; ll > l - TRANCHE; ll--)
                        {
                            if (!isZero(l2,ll) )
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                    }
                }
            }
        }
        tmp_ech_g = chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start);
        
        /* Echelonize the low right part of the matrix */
        start = chrono::steady_clock::now();
        ca = _nbPiv;
        l = _nbPiv;
        while (l < _height)
        {
            for (; ca < _width; ca++)
            {
                /* Search a pivot in column ca */
                for (i = l; i < _height; i++)
                {
                    /* Normalize in  [-MODULO/2, MODULO/2]. */
                    _matrix[i][ca].modulo();
                    if (!isZero(i,ca) )
                    {
                        break;
                    }
                }
                if (i < _height)
                {
                    /* Pivot found in column ca */
                    break;          
                }
            }
            if (ca == _width)
            {
                /* All the rows under the l-th row are zeros */ 
                for(l2=l; l2<_height; l2++)
                {
                    delete[] _matrix[l2];
                }
                /* Forget all the zeros rows */
                _height = l;
            }
            else
            {
                /* Swap with the row containing the pivot */
                swapRow(l,i);
                if (ca != l)
                {
                    /* Column swap */
                    ll = (_endCol[l] > _endCol[ca] ? _endCol[l] : _endCol[ca]);
                    swapCol(l,ca,0, ll);
                    swapCol(l, ca, _nbPiv, _height);
                    /* Carry the column swap over */
                    _tau[_sigma[l]] = ca;
                    _tau[_sigma[ca]] = l;
                    exc = _sigma[l];
                    _sigma[l] = _sigma[ca];
                    _sigma[ca] = exc;
                    exc = _endCol[l];
                    _endCol[l] = _endCol[ca];
                    _endCol[ca] = exc;
                }
                piv = _matrix[l][l];
                inv = piv.inverse();
                
                /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                multRow (_matrix[l], inv, ca + 1, _width);      
                _matrix[l][l].setOne();
                
                /* Suppress the elements under the pivot */
                #pragma omp parallel for schedule(dynamic,chunk)
                for (l2 = l + 1; l2 < _height; l2++)
                {
                    /* Normalize in  [-MODULO/2, MODULO/2]. */
                    _matrix[l2][l].modulo();
                    if (!isZero(l2,l) )
                    {
                        addMultRow (_matrix[l2], _matrix[l], -_matrix[l2][l], ca, _width);
                        _matrix[l2][l].setZero();
                    }
                }
                l++;
                ca++;
            }
        }
        tmp_ech_db = chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start);

        /* Echelonize the hight right part of the matrix */
        start = chrono::steady_clock::now();

        /* Check _endCol */
        for (l = _nbPiv; l < _height - 1; l++)
        {
            if (_endCol[l + 1] < _endCol[l])
            {
                fprintf (stderr, "_endCol hypothesis voided: please report\n");
                exit (1);
            }
        }

        int min_endcol, max_endcol;
        for (l = _height - 1; l >= _nbPiv; l -= TRANCHE)
        {
            if (l < (_nbPiv + TRANCHE))
            {
                /* 1st slice */
                /* Triangular part */
                for (ll = l; ll > _nbPiv; ll--)
                {
                    /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[ll], ll, _width);
                    #pragma omp parallel for schedule(dynamic,chunk)
                    for (l2 = _nbPiv; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                normalizeRow(_matrix[_nbPiv], _nbPiv, _width);
                
                max_endcol = _endCol[l];
                min_endcol = _endCol[_nbPiv];
                /* Upper rectangular part */
                #pragma omp parallel
                {
                    #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                    for (l2 = 0; l2 < min_endcol; l2++)
                    {
                        for (ll = l; ll >= _nbPiv; ll--)
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                    #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                    for (l2 = min_endcol; l2 < max_endcol; l2++)
                    {
                        for (ll = l; _endCol[ll] > l2; ll--)
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll))
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
            }
            else
            {
                /* Triangular part */
                for (ll = l; ll > l - TRANCHE + 1; ll--)
                {
                   /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                    normalizeRow(_matrix[ll], ll, _width);
                    #pragma omp parallel for schedule(dynamic,chunk)
                    for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Normalize the row in  [-MODULO/2, MODULO/2]. */
                normalizeRow(_matrix[l - TRANCHE + 1], l - TRANCHE + 1, _width);
                
                /* Upper rectangular part */
                max_endcol = _endCol[l];
                min_endcol = _endCol[l - TRANCHE + 1];
                #pragma omp parallel
                {
                    #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                    for (l2 = 0; l2 < min_endcol; l2++)
                    {
                        for (ll = l; ll > l - TRANCHE; ll--)
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                    #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                    for (l2 = min_endcol; l2 < max_endcol; l2++)
                    {
                        for (ll = l; _endCol[ll] > l2; ll--)
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            _matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                    #pragma omp for private(ll) nowait schedule(dynamic,chunk)
                    for (l2 = _nbPiv; l2 <= l - TRANCHE; l2++)
                    {
                        for (ll = l; ll > l - TRANCHE; ll--)
                        {
                            if (!isZero(l2,ll) )
                            {
                                /* Normalize in  [-MODULO/2, MODULO/2]. */
                                _matrix[l2][ll].modulo();
                                if (!isZero(l2,ll) )
                                {
                                    addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                    _matrix[l2][ll].setZero();
                                }
                            }
                        }
                    }
                }
            }
        }
        tmp_ech_dh = chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start);
        
        /* Normalize the matrix */
        #pragma omp parallel for private(l) schedule(dynamic,chunk)
        for (i = 0; i < _height; i++)
        {
            for (l = i; l < _width; l++)
            {
                _matrix[i][l].modulo();
            }
        }

        if (VERBOSE > 1)
        {
            cout << tmp_ech_g.count() << " + " << tmp_ech_db.count() << " + " << tmp_ech_dh.count() << " = " << (tmp_ech_g + tmp_ech_db + tmp_ech_dh).count() << " ms" << endl << endl;
        }
        return _height;
    }
    #endif // FFLAS_FFPACK
    #endif // PARALLEL
    
    
    /* Operator overload */
    
    template <typename Element>
    Matrix<Element> &
    Matrix<Element>::operator=(Matrix<Element> const & matrix)
    {
        _height(matrix._height);
        _width(matrix._width);
        int j;
        _matrix=new Element*[_height];
        int allocWidth = 16 * ((_width + 16 - 1) / 16);
        for(int i=0; i< _height; i++)
        {
            _matrix[i]=new Element[allocWidth]();
            for(j=0; j<_width; j++)
            {
                _matrix[i][j]=matrix._matrix[i][j];
            }
        }
        _nbPiv=matrix._nbPiv;
        _tau=matrix._tau;
        _sigma=matrix._sigma;
        _startTail=matrix._startTail; 
        _endCol=matrix._endCol;
        return * this;
    }
    
    template <typename Element>
    Matrix<Element> &
    Matrix<Element>::operator=(Matrix<Element> && matrix)
    {
        if(this != &matrix)
        {
            for(int i=0; i< _height; i++)
            {
                delete[] _matrix[i];
                _matrix[i]=0;
            } 
            delete[] _matrix;
            
            _matrix=move(matrix._matrix);
            matrix._matrix=0;
            _height=matrix._height;
            matrix._height=0;
            _width=matrix._width;
            matrix._width=0;
            _nbPiv=matrix._nbPiv;
            matrix._nbPiv=0;
            _tau=matrix._tau;
            matrix._tau=0;
            _sigma=matrix._sigma;
            matrix._sigma=0;
            _startTail=matrix._startTail; 
            matrix._startTail=0;
            _endCol=matrix._endCol;
            matrix._endCol=0;
        }
        return * this;
    }
    
    template <typename Element>
    ostream & operator<<(ostream & stream, Matrix<Element> const & matrix)
    {
        matrix.printMatrix(stream);
        return stream;
    }

}

#endif // F4_MATRIX_INL
