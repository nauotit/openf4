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
    
    
    /* Constructor */
    
    template <typename Element>
    Matrix<Element>::Matrix():_matrix(0), _height(0), _width(0), _nbPiv(0), _tau(0), _sigma(0), _startTail(0), _endCol(0)
    {
    }
    
    template <typename Element>
    Matrix<Element>::Matrix(int height, int width): _height(height), _width(width), _nbPiv(0), _tau(0), _sigma(0), _startTail(0), _endCol(0)
    {
        _matrix=new Element*[_height];
        for(int i=0; i< _height; i++)
        {
            _matrix[i]=new Element[_width];
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
                for(int i=0; i< _height; i++)
                {
                    _matrix[i]=new Element[_width];
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
        for(int i=0; i< _height; i++)
        {
            _matrix[i]=new Element[_width];
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
            row[i].normalize();
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
    
    template <typename Element>
    void
    Matrix<Element>::swapRow(int numRow1, int numRow2)
    {
        assert((start >= 0) && (end <= _width));
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
                    /* Normalize the row in  [-MODULO+1, MODULO-1]. */
                    //normalizeRow(_matrix[ll], ll, _width);
                    for (l2 = 0; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            //_matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _startTail[ll], _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Normalize the row in  [-MODULO+1, MODULO-1]. */
                //normalizeRow(_matrix[0], 0, _width);
                
                /* Low rectangular part (under  _nbPiv) */
                for (l2 = _nbPiv; l2 < _endCol[l]; l2++)
                {
                    for (ll = l; ll >= 0; ll--)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            //_matrix[l2][ll].modulo();
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
                    /* Normalize the row in  [-MODULO+1, MODULO-1]. */
                    //normalizeRow(_matrix[ll], ll, _width);
                    for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            //_matrix[l2][ll].modulo();
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
                            //_matrix[l2][ll].modulo();
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
                            //_matrix[l2][ll].modulo();
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
                    //_matrix[i][ca].modulo();
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
                //piv.normalize();
                inv = piv.inverse();
                
                /* Normalize the row */
                multRow (_matrix[l], inv, ca + 1, _width);      
                _matrix[l][l].setOne();
                
                /* Suppress the elements under the pivot */
                for (l2 = l + 1; l2 < _height; l2++)
                {
                    /* Normalize in  [-MODULO/2, MODULO/2]. */
                    //_matrix[l2][l].modulo();
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
                    /* Normalize the row in  [-MODULO+1, MODULO-1]. */
                    //normalizeRow(_matrix[ll], ll, _width);
                    for (l2 = _nbPiv; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            //_matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Normalize the row in  [-MODULO+1, MODULO-1]. */
                //normalizeRow(_matrix[_nbPiv], _nbPiv, _width);
                
                max_endcol = _endCol[l];
                min_endcol = _endCol[_nbPiv];
                /* Upper rectangular part */
                for (l2 = 0; l2 < min_endcol; l2++)
                {
                    for (ll = l; ll >= _nbPiv; ll--)
                    {
                        /* Normalize in  [-MODULO/2, MODULO/2]. */
                        //_matrix[l2][ll].modulo();
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
                        //_matrix[l2][ll].modulo();
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
                    /* Normalize the row in  [-MODULO+1, MODULO-1]. */
                    //normalizeRow(_matrix[ll], ll, _width);
                    for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                    {
                        if (!isZero(l2,ll) )
                        {
                            /* Normalize in  [-MODULO/2, MODULO/2]. */
                            //_matrix[l2][ll].modulo();
                            if (!isZero(l2,ll) )
                            {
                                addMultRow (_matrix[l2], _matrix[ll], -_matrix[l2][ll], _height, _width);
                                _matrix[l2][ll].setZero();
                            }
                        }
                    }
                }
                /* Normalize the row in  [-MODULO+1, MODULO-1]. */
                //normalizeRow(_matrix[l - TRANCHE + 1], l - TRANCHE + 1, _width);
                
                /* Upper rectangular part */
                max_endcol = _endCol[l];
                min_endcol = _endCol[l - TRANCHE + 1];
                for (l2 = 0; l2 < min_endcol; l2++)
                {
                    for (ll = l; ll > l - TRANCHE; ll--)
                    {
                        /* Normalize in  [-MODULO/2, MODULO/2]. */
                        //_matrix[l2][ll].modulo();
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
                        //_matrix[l2][ll].modulo();
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
                            //_matrix[l2][ll].modulo();
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
        //for (i = 0; i < _height; i++)
        //{
            //for (l = 0; l < _width; l++)
            //{
                //_matrix[i][l].normalize();
            //}
        //}

        if (VERBOSE > 1)
        {
            printf ("%.1f + %.1f + %.1f ms = %.1f CPU \n\n", tmp_ech_g, tmp_ech_db, tmp_ech_dh, tmp_ech_g + tmp_ech_db + tmp_ech_dh);
        }
        return _height;
    }
    
    
    /* Operator overload */
    
    template <typename Element>
    Matrix<Element> &
    Matrix<Element>::operator=(Matrix<Element> const & matrix)
    {
        _height(matrix._height);
        _width(matrix._width);
        int j;
        _matrix=new Element*[_height];
        for(int i=0; i< _height; i++)
        {
            _matrix[i]=new Element[_width];
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
