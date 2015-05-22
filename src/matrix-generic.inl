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
  * \file matrix-generic.inl
  * \brief Definition of MatrixGeneric methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_MATRIX_GENERIC_INL
#define F4_MATRIX_GENERIC_INL

//#define BLOCK

using namespace std;

namespace F4
{
    /* Global variables */
    
    extern int VERBOSE;
    
    
    /* Constructor */
    
    #ifndef BLOCK
    template <class Field>
    MatrixGeneric<Field>::MatrixGeneric(Field & f):_matrix(0), _A(0), _B(0), _C(0), _D(0), _F(f), _height(0), _width(0), _nbPiv(0), _tau(0), _sigma(0), _startTail(0), _endCol(0)
    {
    }
    #endif // BLOCK
    
    #ifdef BLOCK
    template <class Field>
    MatrixGeneric<Field>::MatrixGeneric(Field & f):_matrix(0), _A(0), _B(0), _C(0), _D(0), _F(f), _height(0), _width(0), _nbPiv(0), _tau(0), _sigma(0), _startTail(0), _endCol(0)
    {
    }
    #endif // BLOCK
    
    #ifndef BLOCK
    template <class Field>
    MatrixGeneric<Field>::MatrixGeneric(Field & f, int height, int width):_F(f), _height(height), _width(width), _nbPiv(0), _tau(0), _sigma(0), _startTail(0), _endCol(0)
    {
        _matrix=FFLAS::fflas_new (_F,_height,_width);
        for (int i=0; i<_height; i++)
        {
            for(int j=0; j<_width; j++)
            {
                _F.init(_matrix[i*_width+j],_F.zero); 
            }
        }
    }
    #endif // BLOCK
    
    #ifndef BLOCK
    template <class Field>
    MatrixGeneric<Field>::MatrixGeneric(Field & f, string const & filename):_F(f)
    {
        ifstream file(filename);
        if(file)
        {
            size_t pos;
            int i=0;
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
                _matrix=FFLAS::fflas_new (_F,_height,_width);
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
                        _F.init(_matrix[row*_width+i],stol(tmp));
                        ++i;
                    }
                    row++;
                }
            }
            file.close();
        }
        else
        {
            cout << "MatrixGeneric::MatrixGeneric(string filename): Failed " << endl;
        }
    }
    #endif // BLOCK
    
    #ifdef BLOCK
    template <class Field>
    MatrixGeneric<Field>::MatrixGeneric(Field & f, string const & filename):_matrix(0), _F(f)
    {
        ifstream file(filename);
        if(file)
        {
            size_t pos;
            int i=0;
            int j=0;
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
                _A=FFLAS::fflas_new (_F,_nbPiv,_nbPiv);
                _B=FFLAS::fflas_new (_F,_nbPiv, _width-_nbPiv);
                _C=FFLAS::fflas_new (_F,_height-_nbPiv,_nbPiv);
                _D=FFLAS::fflas_new (_F,_height-_nbPiv,_width-_nbPiv);
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
                while(row <_nbPiv && getline(file, line))
                {
                    i = 0;
                    j = 0;
                    stringstream ssin(line);
                    while (i < _nbPiv && ssin.good())
                    {
                        ssin >> tmp;
                        _F.init(_A[row*_nbPiv+i],stol(tmp));
                        ++i;
                    }
                    while (i < _width && ssin.good())
                    {
                        ssin >> tmp;
                        _F.init(_B[row*(_width-_nbPiv)+j],stol(tmp));
                        ++i;
                        ++j;
                    }
                    row++;
                }
                row=0;
                while(row <(_height-_nbPiv) && getline(file, line))
                {
                    i = 0;
                    j = 0;
                    stringstream ssin(line);
                    while (i < _nbPiv && ssin.good())
                    {
                        ssin >> tmp;
                        _F.init(_C[row*_nbPiv+i],stol(tmp));
                        ++i;
                    }
                    while (i < _width && ssin.good())
                    {
                        ssin >> tmp;
                        _F.init(_D[row*(_width-_nbPiv)+j],stol(tmp));
                        ++i;
                        ++j;
                    }
                    row++;
                }
            }
            file.close();
        }
        else
        {
            cout << "MatrixGeneric::MatrixGeneric(string filename): Failed " << endl;
        }
    }
    #endif // BLOCK
    
    
    #ifndef BLOCK
    template <class Field>
    MatrixGeneric<Field>::MatrixGeneric(MatrixGeneric const & matrix): _A(0), _B(0), _C(0), _D(0), _F(matrix._F), _height(matrix._height), _width(matrix._width), _nbPiv(matrix._nbPiv), _tau(matrix._tau), _sigma(matrix._sigma), _startTail(matrix._startTail), _endCol(matrix._endCol)
    {
        _matrix=FFLAS::fflas_new (_F,_height,_width);
        for(int i=0; i< _height; i++)
        {
            for(int j=0; j<_width; j++)
            {
                _F.init(_matrix[i*_width+j],matrix._matrix[i*_width+j]);
            }
        }
    }
    #endif //BLOCK
    
    #ifdef BLOCK
    template <class Field>
    MatrixGeneric<Field>::MatrixGeneric(MatrixGeneric const & matrix): _matrix(0), _F(matrix._F), _height(matrix._height), _width(matrix._width), _nbPiv(matrix._nbPiv), _tau(matrix._tau), _sigma(matrix._sigma), _startTail(matrix._startTail), _endCol(matrix._endCol)
    {
        _A=FFLAS::fflas_new (_F,_nbPiv,_nbPiv);
        for(int i=0; i< _nbPiv; i++)
        {
            for(int j=0; j<_nbPiv; j++)
            {
                _F.init(_A[i*_nbPiv+j],matrix._A[i*_nbPiv+j]);
            }
        }
        _B=FFLAS::fflas_new (_F,_nbPiv,_width-_nbPiv);
        for(int i=0; i< _nbPiv; i++)
        {
            for(int j=0; j<_width-_nbPiv; j++)
            {
                _F.init(_B[i*(_width-_nbPiv)+j],matrix._B[i*(_width-_nbPiv)+j]);
            }
        }
        _C=FFLAS::fflas_new (_F,_height-_nbPiv,_nbPiv);
        for(int i=0; i< _height-_nbPiv; i++)
        {
            for(int j=0; j<_nbPiv; j++)
            {
                _F.init(_C[i*_nbPiv+j],matrix._C[i*_nbPiv+j]);
            }
        }
        _D=FFLAS::fflas_new (_F,_height-_nbPiv,_width-_nbPiv);
        for(int i=0; i< _height-_nbPiv; i++)
        {
            for(int j=0; j<_width-_nbPiv; j++)
            {
                _F.init(_D[i*(_width-_nbPiv)+j],matrix._D[i*(_width-_nbPiv)+j]);
            }
        }
    }
    #endif //BLOCK
    
    #ifndef BLOCK
    template <class Field>
    MatrixGeneric<Field>::MatrixGeneric(MatrixGeneric && matrix): _A(0), _B(0), _C(0), _D(0), _F(matrix._F)
    {
        if(_matrix!=0)
        {
            FFLAS::fflas_delete(_matrix);
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
    #endif //BLOCK
    
    
    /* Destructor */ 
    
    #ifndef BLOCK
    template <class Field>
    MatrixGeneric<Field>::~MatrixGeneric()
    {
        if(_matrix!=0)
        {
            FFLAS::fflas_delete(_matrix);
            _matrix=0;
        }
    }
    #endif // BLOCK
    
    
    #ifdef BLOCK
    template <class Field>
    MatrixGeneric<Field>::~MatrixGeneric()
    {
        if(_A!=0)
        {
            FFLAS::fflas_delete(_A);
            _A=0;
        }
        if(_B!=0)
        {
            FFLAS::fflas_delete(_B);
            _B=0;
        }
        if(_C!=0)
        {
            FFLAS::fflas_delete(_C);
            _C=0;
        }
        if(_D!=0)
        {
            FFLAS::fflas_delete(_D);
            _D=0;
        }
    }
    #endif // BLOCK
    
    template <class Field>
    void
    MatrixGeneric<Field>::erase()
    {
        if(_startTail)
        {
            delete[] _startTail;
            _startTail=0;
        }
        if(_endCol)
        {
            delete[] _endCol;
            _endCol=0;
        }
        if(_sigma)
        {
            delete[] _sigma;
            _sigma = 0;
        }
        if(_tau)
        {
            delete[] _tau;
            _tau = 0;
        }
    }
    
    
    ///* Get / Set */
    
    //template <class Field>
    //inline Element & 
    //MatrixGeneric<Field>::operator() (int row, int col) 
    //{ 
        //assert(row < _height && col < _width); 
        //return _matrix[row][col]; 
    //} 
    
    //template <class Field>
    //inline Element 
    //MatrixGeneric<Field>::operator() (int row, int col) const 
    //{ 
        //assert(row < _height && col < _width);
        //return _matrix[row][col]; 
    //}
    
    //template <class Field>
    //inline Element 
    //MatrixGeneric<Field>::getElement(int row, int col) const
    //{
        //assert(row < _height && col < _width); 
        //return _matrix[row][col]; 
    //}
    
    //template <class Field>
    //inline void 
    //MatrixGeneric<Field>::setElement (int row, int col, Element const & element)
    //{
        //assert(row < _height && col < _width); 
        //_matrix[row][col]=element; 
    //}
    
    //template <class Field>
    //Element *
    //MatrixGeneric<Field>::getRow (int row) 
    //{ 
        //assert(row < _height);
        //return _matrix[row]; 
    //}
    
    template <class Field>
    int
    MatrixGeneric<Field>::getHeight() const
    {
        return _height;
    }
    
    template <class Field>
    int
    MatrixGeneric<Field>::getWidth() const
    {
        return _width;
    }
    
    template <class Field>
    void 
    MatrixGeneric<Field>::setNbPiv(int nbPiv)
    {
        _nbPiv=nbPiv;
    }
    
    template <class Field>
    int
    MatrixGeneric<Field>::getNbPiv() const
    {
        return _nbPiv;
    }
    
    template <class Field>
    void
    MatrixGeneric<Field>::setTau(int * tau)
    {
        _tau=tau;
    }
    
    template <class Field>
    int * 
    MatrixGeneric<Field>::getTau()
    {
        return _tau;
    }
    
    template <class Field>
    void
    MatrixGeneric<Field>::setSigma(int * sigma)
    {
        _sigma=sigma;
    }
    
    template <class Field>
    int *
    MatrixGeneric<Field>::getSigma()
    {
        return _sigma;
    }
    
    template <class Field>
    void 
    MatrixGeneric<Field>::setStartTail(int * startTail)
    {
        _startTail=startTail;
    }
    
    template <class Field>
    int * 
    MatrixGeneric<Field>::getStartTail()
    {
        return _startTail;
    }
    
    template <class Field>
    void
    MatrixGeneric<Field>::setEndCol(int * endCol)
    {
        _endCol=endCol;
    }
    
    template <class Field>
    int * 
    MatrixGeneric<Field>::getEndCol()
    {
        return _endCol;
    }
    
    template <class Field>
    void
    MatrixGeneric<Field>::setInfo(int nbPiv, int *tau, int *sigma, int * startTail, int * endCol)
    {
         _nbPiv=nbPiv;
         _tau=tau;
         _sigma=sigma;
         _startTail=startTail;
         _endCol=endCol;
    }
    
    /* Miscellaneous */
    
    template <class Field>
    void
    MatrixGeneric<Field>::printMatrix (std::ostream & stream) const
    {
        for (int i=0; i<_height; i++)
        {
            for(int j=0; j<_width; j++)
            {
                stream << " " << _matrix[i*_width+j] << " "; 
            }
            stream << endl;
        }
    }
    
    #ifndef BLOCK
    template <class Field>
    void
    MatrixGeneric<Field>::printMatrix (string const & filename) const
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
    #endif // BLOCK
    
    #ifdef BLOCK
    template <class Field>
    void
    MatrixGeneric<Field>::printMatrix (string const & filename) const
    {
        string filename2="A-"+filename;
        ofstream file1(filename2);
        int i, j;
        if (file1)
        {
            file1 << "P3" << endl << _nbPiv << " " << _nbPiv << endl << 1 << endl;
            for (i = 0; i < _nbPiv; i++)
            {
                for (j = 0; j < _nbPiv; j++)
                {
                    if (!_F.isZero(_A[i*_nbPiv+j]))
                    {
                        file1 << " 0 0 0 ";
                    }
                    else
                    {
                        file1 << " 1 1 1 ";
                    }
                }
                file1 << endl;
            }
            file1.close();
        }
        
        filename2="B-"+filename;
        ofstream file2(filename2);
        if (file2)
        {
            file2 << "P3" << endl << _width-_nbPiv << " " << _nbPiv << endl << 1 << endl;
            for (i = 0; i < _nbPiv; i++)
            {
                for (j = 0; j < _width-_nbPiv; j++)
                {
                    if (!_F.isZero(_B[i*(_width-_nbPiv)+j]))
                    {
                        file2 << " 0 0 0 ";
                    }
                    else
                    {
                        file2 << " 1 1 1 ";
                    }
                }
                file2 << endl;
            }
            file2.close();
        }
        
        filename2="C-"+filename;
        ofstream file3(filename2);
        if (file3)
        {
            file3 << "P3" << endl << _nbPiv << " " << _height-_nbPiv << endl << 1 << endl;
            for (i = 0; i < _height-_nbPiv; i++)
            {
                for (j = 0; j < _nbPiv; j++)
                {
                    if (!_F.isZero(_C[i*_nbPiv+j]))
                    {
                        file3 << " 0 0 0 ";
                    }
                    else
                    {
                        file3 << " 1 1 1 ";
                    }
                }
                file3 << endl;
            }
            file3.close();
        }
        
        filename2="D-"+filename;
        ofstream file4(filename2);
        if (file4)
        {
            file4 << "P3" << endl << _width-_nbPiv << " " << _height-_nbPiv << endl << 1 << endl;
            for (i = 0; i < _height-_nbPiv; i++)
            {
                for (j = 0; j < _width-_nbPiv; j++)
                {
                    if (!_F.isZero(_D[i*(_width-_nbPiv)+j]))
                    {
                        file4 << " 0 0 0 ";
                    }
                    else
                    {
                        file4 << " 1 1 1 ";
                    }
                }
                file4 << endl;
            }
            file4.close();
        }
    }
    #endif // BLOCK
    
    #ifndef BLOCK
    template <class Field>
    bool
    MatrixGeneric<Field>::isZero(int row, int col) const
    {
        return _F.isZero(_matrix[row*_width+col]); 
    }
    #endif // BLOCK
    
    //#ifndef  BLOCK
    //template <class Field>
    //int
    //MatrixGeneric<Field>::echelonize ()
    //{
        //chrono::steady_clock::time_point start=chrono::steady_clock::now();
        //typedef chrono::duration<int,milli> millisecs_t;
        //int rank;
        //size_t *P = new size_t[_height]();
        //size_t *Q = new size_t[_width]();
        //rank = (int)FFPACK::ReducedRowEchelonForm (_F, _height, _width, _matrix, _width, P, Q, false, FFPACK::FfpackTileRecursive);
        //cout << "Rank with echelon form: " << rank << endl;
        ////rank = (int)FFPACK::ReducedRowEchelonForm (_F, _height, _width, _matrix, _width, P, Q, false, FFPACK::FfpackSlabRecursive);
        //FFPACK::getReducedEchelonForm (_F, FFLAS::FflasUpper, _height , _width, rank, Q, _matrix, _width,  FFPACK::FfpackTileRecursive);
        //cout << "Echelonization time: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms" << endl << endl;
        //delete[] P;
        //delete[] Q;
        //_height=rank;
        //return rank;
    //}
    //#endif // BLOCK
    
    #ifndef  BLOCK
    template <class Field>
    int
    MatrixGeneric<Field>::echelonize ()
    {
        chrono::steady_clock::time_point start=chrono::steady_clock::now();
        typedef chrono::duration<int,milli> millisecs_t;
        typename Field::Element one, minusOne;
        size_t *P = new size_t[_height-_nbPiv]();
        size_t *Q = new size_t[_width-_nbPiv]();
        int rank;
        
        typename Field::Element * A=_matrix;
        typename Field::Element * B=_matrix+_nbPiv;
        typename Field::Element * C=_matrix+_nbPiv*_width;
        typename Field::Element * D=_matrix+_nbPiv*_width+_nbPiv;
        
        _F.init(one,1);
        _F.init(minusOne,-1);
        /* B = A^(-1) * B */
        chrono::steady_clock::time_point startc=chrono::steady_clock::now();
        FFLAS::ftrsm (_F, FFLAS::FflasLeft, FFLAS::FflasUpper, FFLAS::FflasNoTrans, FFLAS::FflasUnit, _nbPiv, _width-_nbPiv, one, A, _width, B, _width);
        FFLAS::fidentity (_F, _nbPiv, _nbPiv, A, _width);
        cout << "Time ftrsm: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-startc).count() << " ms" << endl;
        
        /* D = D - C * B */
        startc=chrono::steady_clock::now();
        FFLAS::fgemm(_F, FFLAS::FflasNoTrans, FFLAS::FflasNoTrans, (_height-_nbPiv), (_width-_nbPiv), _nbPiv, minusOne, C, _width, B, _width, one, D, _width);
        FFLAS::fzero(_F, (_height-_nbPiv), _nbPiv, C, _width);
        cout << "Time fgemm: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-startc).count() << " ms" << endl;
        
        /* D = Gauss(D) */
        startc=chrono::steady_clock::now();
        /* PLUQ(D) */
        rank = (int)FFPACK::PLUQ (_F, FFLAS::FflasUnit, (_height-_nbPiv), (_width-_nbPiv), D, _width, P, Q);
        /* D2 = D1^(-1) * D2 */
        FFLAS::ftrsm (_F, FFLAS::FflasLeft, FFLAS::FflasUpper, FFLAS::FflasNoTrans, FFLAS::FflasUnit, rank, (_width-_nbPiv)-rank, _F.one, D, _width, D+rank, _width);
        //rank = (int)FFPACK::ReducedRowEchelonForm (_F, (_height-_nbPiv), (_width-_nbPiv), _D, (_width-_nbPiv), P, Q, false, FFPACK::FfpackTileRecursive);
        /* Suppress zero rows */
        FFLAS::fzero(_F, (_height-_nbPiv)-rank, (_width-_nbPiv), D+rank*_width, _width);
        /* Suppress L */
        FFLAS::fidentity (_F, rank, rank, D, _width);
        /* B = B * Q^T */
        FFPACK::applyP(_F, FFLAS::FflasRight, FFLAS::FflasTrans, (_width-_nbPiv), 0, (_width-_nbPiv), B, _width, Q);
        
        cout << "Time bottom right slice: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-startc).count() << " ms" << endl;
        startc=chrono::steady_clock::now();
        /* B2 = B2 - B1 * D2 */
        FFLAS::fgemm(_F, FFLAS::FflasNoTrans, FFLAS::FflasNoTrans, _nbPiv, (_width-_nbPiv)-rank, rank, minusOne, B , _width, D+rank, _width, one, B+rank, _width);
        /* B1 = 0 */
        FFLAS::fzero(_F, _nbPiv, rank, B, _width);
        cout << "Time top right slice: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-startc).count() << " ms" << endl;
        
        
        cout << "Echelonization time: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms" << endl << endl;
        delete[] P;
        delete[] Q;
        _height=rank+_nbPiv;
        return _height;
    }
    #endif // BLOCK
    
    
    
    #ifdef BLOCK
    template <class Field>
    int
    MatrixGeneric<Field>::echelonize ()
    {
        chrono::steady_clock::time_point start=chrono::steady_clock::now();
        typedef chrono::duration<int,milli> millisecs_t;
        typename Field::Element one, minusOne;
        size_t *P = new size_t[_height-_nbPiv]();
        size_t *Q = new size_t[_width-_nbPiv]();
        int rank;
        _F.init(one,1);
        _F.init(minusOne,-1);
        /* B = A^(-1) * B */
        clock_t startc=clock();
        FFLAS::ftrsm (_F, FFLAS::FflasLeft, FFLAS::FflasUpper, FFLAS::FflasNoTrans, FFLAS::FflasUnit, _nbPiv, _width-_nbPiv, one, _A, _nbPiv, _B, _width-_nbPiv);
        FFLAS::fidentity (_F, _nbPiv, _nbPiv, _A, _nbPiv);
        cout << "Time ftrsm: " << (clock() - startc)*1000/CLOCKS_PER_SEC << endl;
        
        /* D = D - C * B */
        startc=clock();
        FFLAS::fgemm(_F, FFLAS::FflasNoTrans, FFLAS::FflasNoTrans, (_height-_nbPiv), (_width-_nbPiv), _nbPiv, minusOne, _C, _nbPiv, _B, _width-_nbPiv, one, _D, _width-_nbPiv);
        FFLAS::fzero(_F, (_height-_nbPiv), _nbPiv, _C, _nbPiv);
        cout << "Time fgemm: " << (clock() - startc)*1000/CLOCKS_PER_SEC << endl;
        
        // DEBUG write D into a file
        ofstream spluq("Cyclic8-D.debug");
        if(spluq)
        {
            spluq << _height-_nbPiv << endl << _width-_nbPiv << endl;
            for (int i=0; i< _height-_nbPiv; i++)
            {
                for(int j=0; j<_width-_nbPiv; j++)
                {
                    spluq << " " << _D[i*(_width-_nbPiv)+j] << " "; 
                }
                spluq << endl;
            }
        }
        else
        {
            cout << "Error printing _D " << endl;
        }
        
        /* D = Gauss(D) */
        startc=clock();
        /* PLUQ(D) */
        rank = (int)FFPACK::PLUQ (_F, FFLAS::FflasUnit, (_height-_nbPiv), (_width-_nbPiv), _D, (_width-_nbPiv), P, Q);
        /* D2 = D1^(-1) * D2 */
        FFLAS::ftrsm (_F, FFLAS::FflasLeft, FFLAS::FflasUpper, FFLAS::FflasNoTrans, FFLAS::FflasUnit, rank, (_width-_nbPiv)-rank, _F.one, _D, (_width-_nbPiv), _D+rank, (_width-_nbPiv));
        //rank = (int)FFPACK::ReducedRowEchelonForm (_F, (_height-_nbPiv), (_width-_nbPiv), _D, (_width-_nbPiv), P, Q, false, FFPACK::FfpackTileRecursive);
        /* Suppress zero rows */
        FFLAS::fzero(_F, (_height-_nbPiv)-rank, (_width-_nbPiv), _D+rank*(_width-_nbPiv), (_width-_nbPiv));
        /* Suppress L */
        FFLAS::fidentity (_F, rank, rank, _D, (_width-_nbPiv));
        /* B = B * Q^T */
        FFPACK::applyP(_F, FFLAS::FflasRight, FFLAS::FflasTrans, (_width-_nbPiv), 0, (_width-_nbPiv), _B, (_width-_nbPiv), Q);
        
        cout << "Time bottom right slice: " << (clock() - startc)*1000/CLOCKS_PER_SEC << endl;
        startc=clock();
        /* B2 = B2 - B1 * D2 */
        FFLAS::fgemm(_F, FFLAS::FflasNoTrans, FFLAS::FflasNoTrans, _nbPiv, (_width-_nbPiv)-rank, rank, minusOne, _B , _width-_nbPiv, _D+rank, _width-_nbPiv, one, _B+rank, _width-_nbPiv);
        /* B1 = 0 */
        FFLAS::fzero(_F, _nbPiv, rank, _B, (_width-_nbPiv));
        cout << "Time top right slice: " << (clock() - startc)*1000/CLOCKS_PER_SEC << endl;
        
        
        cout << "Echelonization time: " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms" << endl << endl;
        delete[] P;
        delete[] Q;
        _height=rank+_nbPiv;
        return _height;
    }
    #endif //BLOCK
    
    ///* Operator overload */
    
    //template <class Field>
    //MatrixGeneric<Field> &
    //MatrixGeneric<Field>::operator=(MatrixGeneric<Field> const & matrix)
    //{
        //_height(matrix._height);
        //_width(matrix._width);
        //int j;
        //_matrix=new Element*[_height];
        //for(int i=0; i< _height; i++)
        //{
            //_matrix[i]=new Element[_width];
            //for(j=0; j<_width; j++)
            //{
                //_matrix[i][j]=matrix._matrix[i][j];
            //}
        //}
        //_nbPiv=matrix._nbPiv;
        //_tau=matrix._tau;
        //_sigma=matrix._sigma;
        //_startTail=matrix._startTail; 
        //_endCol=matrix._endCol;
        //return * this;
    //}
    
    //template <class Field>
    //MatrixGeneric<Field> &
    //MatrixGeneric<Field>::operator=(MatrixGeneric<Field> && matrix)
    //{
        //if(this != &matrix)
        //{
            //for(int i=0; i< _height; i++)
            //{
                //delete[] _matrix[i];
                //_matrix[i]=0;
            //} 
            //delete[] _matrix;
            
            //_matrix=move(matrix._matrix);
            //matrix._matrix=0;
            //_height=matrix._height;
            //matrix._height=0;
            //_width=matrix._width;
            //matrix._width=0;
            //_nbPiv=matrix._nbPiv;
            //matrix._nbPiv=0;
            //_tau=matrix._tau;
            //matrix._tau=0;
            //_sigma=matrix._sigma;
            //matrix._sigma=0;
            //_startTail=matrix._startTail; 
            //matrix._startTail=0;
            //_endCol=matrix._endCol;
            //matrix._endCol=0;
        //}
        //return * this;
    //}
    
    template <class Field>
    ostream & operator<<(ostream & stream, MatrixGeneric<Field> const & matrix)
    {
        matrix.printMatrix(stream);
        return stream;
    }

}

#endif // F4_MATRIX_GENERIC_INL
