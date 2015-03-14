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
    // Global variables
    
    extern int VERBOSE;
    
    // Constructor 
    
    template <typename Element>
    Matrix<Element>::Matrix():_matrix(0), _height(0), _width(0), _nbPiv(0), _tau(0), _sigma(0), _startTail(0), _endCol(0)
    {
    }
    
    template <typename Element>
    Matrix<Element>::Matrix(unsigned int height, unsigned int width): _height(height), _width(width), _nbPiv(0), _tau(0), _sigma(0), _startTail(0), _endCol(0)
    {
        //_matrix=new Element[_height*_width]();
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
                // Get height
                pos=string1.size();
                tmp=line.substr(pos);
                _height=stoul(tmp);
                
                // Get width
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
                // Get nbPiv
                pos=string2.size();
                tmp=line.substr(pos);
                _nbPiv=stoul(tmp);
                cout << "nbPiv: " << _nbPiv << endl;
            }
            getline(file, line);
            if (line.find(string4)!=string::npos)
            {
                // skip one line
                getline(file, line);
                
                // Get sigma
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
                // skip one line
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
                // skip one line
                getline(file, line);
                
                // Get endCol
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
                // Get matrix
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
    Matrix<Element>::Matrix(Matrix && matrix): _matrix(matrix._matrix), _height(matrix._height), _width(matrix._width), _nbPiv(matrix._nbPiv), _tau(matrix._tau), _sigma(matrix._sigma), _startTail(matrix._startTail), _endCol(matrix._endCol)
    {
    }
    
    
    // Destructor 
    
    template <typename Element>
    Matrix<Element>::~Matrix()
    {
        for(int i=0; i< _height; i++)
        {
            delete[] _matrix[i];
            _matrix[i]=0;
        } 
        delete[] _matrix;
        _matrix=0;
    }
    
    
    // Get / Set
    
    template <typename Element>
    inline Element & 
    Matrix<Element>::operator() (unsigned row, unsigned col) 
    { 
        assert(row < _height && col < _width); 
        //return _matrix[_width*row + col]; 
        return _matrix[row][col]; 
    } 
    
    template <typename Element>
    inline Element 
    Matrix<Element>::operator() (unsigned row, unsigned col) const 
    { 
        assert(row < _height && col < _width);
        //return _matrix[_width*row + col]; 
        return _matrix[row][col]; 
    }
    
    template <typename Element>
    inline Element 
    Matrix<Element>::getElement(unsigned row, unsigned col) const
    {
        assert(row < _height && col < _width); 
        //return _matrix[_width*row + col]; 
        return _matrix[row][col]; 
    }
    
    template <typename Element>
    inline void 
    Matrix<Element>::setElement (unsigned row, unsigned col, Element const & element)
    {
        assert(row < _height && col < _width); 
        //_matrix[_width*row + col]=element;
        _matrix[row][col]=element; 
    }
    
    template <typename Element>
    Element *
    Matrix<Element>::getRow (unsigned row) 
    { 
        assert(row < _height);
        //return &(_matrix[_width*row]); 
        return _matrix[row]; 
    }
    
    template <typename Element>
    int
    Matrix<Element>::getHeight()
    {
        return _height;
    }
    
    template <typename Element>
    int
    Matrix<Element>::getWidth()
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
    Matrix<Element>::getNbPiv()
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
    
    // Miscellaneous
    
    template <typename Element>
    void
    Matrix<Element>::printMatrix (std::ostream & stream) const
    {
        for (int i=0; i<_height; i++)
        {
            for(int j=0; j<_width; j++)
            {
                //stream << " " << _matrix[i*_width+j] << " ";
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
            //file.close();
        }
    }
    
    template <typename Element>
    bool
    Matrix<Element>::isZero(unsigned row, unsigned col) const
    {
        //return _matrix[_width*row + col].isZero();
        return (_matrix[row][col]).isZero(); 
    }
    
    template <typename Element>
    void
    Matrix<Element>::multRow(unsigned numRow, Element element, unsigned start, unsigned end)
    {
        assert((start >= 0) && (end <= _width));
        Element * row = getRow(numRow);
        for(int i=start; i<end; ++i)
        {
            row[i]*=element;
        }
    }
    
    template <typename Element>
    void
    Matrix<Element>::addMultRow(unsigned numRow1, unsigned numRow2, Element element, unsigned start, unsigned end)
    {
        assert((start >= 0) && (end <= _width));
        Element * row1 = getRow(numRow1);
        Element * row2 = getRow(numRow2);
        for(int i=start; i<end; ++i)
        {
            row1[i]+=(element*row2[i]);
        }
    }
    
    template <typename Element>
    void
    Matrix<Element>::swapRow(unsigned numRow1, unsigned numRow2, unsigned start, unsigned end)
    {
        assert((start >= 0) && (end <= _width));
        //Element * row1 = getRow(numRow1);
        //Element * row2 = getRow(numRow2);
        //swap_ranges(row1+start, row1+end, row2+start);
        Element * tmp = _matrix[numRow1];
        _matrix[numRow1] = _matrix[numRow2];
        _matrix[numRow2] = tmp;
    }
    
    template <typename Element>
    void
    Matrix<Element>::swapCol(unsigned numCol1, unsigned numCol2, unsigned start, unsigned end)
    {
        assert((start >= 0) && (end <= _height));
        for(int i=start; i<end; i++)
        {
            //swap(_matrix[i*_width+numCol1], _matrix[i*_width+numCol2]);
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
        int i, l, l2;               //,_endCol;
        i = 0;
        l = 0;
        Element piv, inv;
        //Element *exch;
        //Element exval;
        int exc;

        if (VERBOSE > 1)
            printf ("Echelonization time: ");

    #define TRANCHE 64
        /*echelonnage de la partie gauche de la matrice */
        start = clock ();
        int ll;
        for (l = _nbPiv - 1; l >= 0; l -= TRANCHE)
        {
            //1er tranche
            if (l < TRANCHE)
            {
                //partie triangulaire
                for (ll = l; ll > 0; ll--)
                {
                    // TODO: multRow (1, _matrix[ll], _width, ll);       //normalisation de toute la ligne
                    for (l2 = 0; l2 < ll; l2++)
                    {
                        if ((!isZero(l2,ll) ))
                        {
                            // TODO: getElement(l2,ll) = modulo (getElement(l2,ll));
                            if ((!isZero(l2,ll) ))
                            {
                                addMultRow (l2, ll, -getElement(l2,ll), _startTail[ll], _width);
                                setElement(l2,ll,0);
                            }
                        }
                    }
                }
                // TODO: multRow (1, _matrix[0], _width, 0);
                
                //partie rectangulaire basse (sous  _nbPiv)
                for (l2 = _nbPiv; l2 < _endCol[l]; l2++)
                {
                    for (ll = l; ll >= 0; ll--)
                    {
                        if ((!isZero(l2,ll) ))
                        {
                            // TODO: getElement(l2,ll) = modulo (getElement(l2,ll));
                            if ((!isZero(l2,ll) ))
                            {
                                addMultRow (l2, ll, -getElement(l2,ll), _startTail[ll], _width);
                                setElement(l2,ll,0);
                            }
                        }
                    }
                }
            }
            //autres tranches
            else
            {
                //partie triangulaire de la tranche
                for (ll = l; ll > l - TRANCHE; ll--)
                {
                    // TODO multRow (1, _matrix[ll], _width, ll);       //normalisation de toute la ligne
                    for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                    {
                        if ((!isZero(l2,ll) ))
                        {
                            // TODO: getElement(l2,ll) = modulo (getElement(l2,ll));
                            if ((!isZero(l2,ll) ))
                            {
                                addMultRow (l2, ll, -getElement(l2,ll), _startTail[ll], _width);
                                setElement(l2,ll,0);
                            }
                        }
                    }
                }
                //partie rectangulaire haute
                for (l2 = 0; l2 <= l - TRANCHE; l2++)
                {
                    for (ll = l; ll > l - TRANCHE; ll--)
                    {
                        if ((!isZero(l2,ll) ))
                        {
                            // TODO: getElement(l2,ll) = modulo (getElement(l2,ll));
                            if ((!isZero(l2,ll) ))
                            {
                                addMultRow (l2, ll, -getElement(l2,ll), _startTail[ll], _width);
                                setElement(l2,ll,0);
                            }
                        }
                    }
                }
                //partie rectangulaire basse (sous  _nbPiv)
                for (l2 = _nbPiv; l2 < _endCol[l]; l2++)
                {
                    for (ll = l; ll > l - TRANCHE; ll--)
                    {
                        if ((!isZero(l2,ll) ))
                        {
                            // TODO: getElement(l2,ll) = modulo (getElement(l2,ll));
                            if ((!isZero(l2,ll) ))
                            {
                                addMultRow (l2, ll, -getElement(l2,ll), _startTail[ll], _width);
                                setElement(l2,ll,0);
                            }
                        }
                    }
                }
            }
        }
        tmp_ech_g = (((double)clock () - start) * 1000) / CLOCKS_PER_SEC;

        /* echelonnage de la partie basse (droite) de la matrice */
        start = clock ();
        ca = _nbPiv;
        l = _nbPiv;
        while (l < _height)
        {
            for (; ca < _width; ca++)
            {
                //recherche d'un pivot dans la col ca
                for (i = l; i < _height; i++)
                {
                    // TODO: _matrix[i][ca] = modulo (_matrix[i][ca]);
                    if (!isZero(i,ca) )
                        break;
                }
                if (i < _height)
                    break;          //pivot trouve dans la col ca
            }
            if (ca == _width)
            {
                //toutes les lignes sous la l-ieme sont nulles
                _height = l;        //on oublie toutes les lignes nulles
            }
            else
            {
                //echange avec la ligne de pivot
                //exch = _matrix[l];
                //_matrix[l] = _matrix[i];
                //_matrix[i] = exch;
                swapRow(l,i,0, _width);
                if (ca != l)
                {
                    //echange de colonnes
                    ll = (_endCol[l] > _endCol[ca] ? _endCol[l] : _endCol[ca]);
                    swapCol(l,ca,0, ll);
                    //for (l2 = 0; l2 < ll; l2++)
                    //{
                        //exval = _matrix(l2,l);
                        //_matrix(l2,l) = _matrix(l2,ca);
                        //_matrix(l2,ca) = exval;
                    //}
                    swapCol(l, ca, _nbPiv, _height);
                    //for (l2 = _nbPiv; l2 < _height; l2++)
                    //{
                        //exval = _matrix(l2,l);
                        //_matrix(l2,l) = _matrix(l2,ca);
                        //_matrix(l2,ca) = exval;
                    //}
                    //on retient l'echange de colonnes
                    _tau[_sigma[l]] = ca;
                    _tau[_sigma[ca]] = l;
                    exc = _sigma[l];
                    _sigma[l] = _sigma[ca];
                    _sigma[ca] = exc;
                    exc = _endCol[l];
                    _endCol[l] = _endCol[ca];
                    _endCol[ca] = exc;
                }                   //fin ech
                piv = getElement(l,l);
                inv = piv.inverse();
                multRow (l, inv, ca + 1, _width);      //normalisation de toute la ligne
                setElement(l,l,1);
                //elimination de termes de la colonne sous le pivot
                for (l2 = l + 1; l2 < _height; l2++)
                {
                    // TODO: _matrix(l2,l) = modulo (getElement(l2,l));
                    if (!isZero(l2,l) )
                    {
                        addMultRow (l2, l, -getElement(l2,l), ca, _width);
                        setElement(l2,l,0);
                    }
                }
                l++;
                ca++;
            }
        }
        tmp_ech_db = (((double)clock () - start) * 1000) / CLOCKS_PER_SEC;

        /*echelonnage de la partie haute (droite) de la matrice */
        start = clock ();

        /*Check endcol */
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
                //premiere tranche
                //triangle
                for (ll = l; ll > _nbPiv; ll--)
                {
                    // TODO: multRow (1, _matrix[ll], _width, ll);
                    for (l2 = _nbPiv; l2 < ll; l2++)
                    {
                        if ((!isZero(l2,ll) ))
                        {
                            // TODO: getElement(l2,ll) = modulo (getElement(l2,ll));
                            if ((!isZero(l2,ll) ))
                            {
                                addMultRow (l2, ll, -getElement(l2,ll), _height, _width);
                                setElement(l2,ll,0);
                            }
                        }
                    }
                }
                // TODO: multRow (1, _matrix[_nbPiv], _width, _nbPiv);
                max_endcol = _endCol[l];
                min_endcol = _endCol[_nbPiv];
                //rectangle au dessus
                for (l2 = 0; l2 < min_endcol; l2++)
                {
                    for (ll = l; ll >= _nbPiv; ll--)
                    {
                        // TODO: getElement(l2,ll) = modulo (getElement(l2,ll));
                        if ((!isZero(l2,ll) ))
                        {
                            addMultRow (l2, ll, -getElement(l2,ll), _height, _width);
                            setElement(l2,ll,0);
                        }
                    }
                }
                for (l2 = min_endcol; l2 < max_endcol; l2++)
                {
                    for (ll = l; _endCol[ll] > l2; ll--)
                    {
                        // TODO: getElement(l2,ll) = modulo (getElement(l2,ll));
                        if ((!isZero(l2,ll) ))
                        {
                            addMultRow (l2, ll, -getElement(l2,ll), _height, _width);
                            setElement(l2,ll,0);
                        }
                    }
                }
            }
            else
            {
                //triangle
                for (ll = l; ll > l - TRANCHE + 1; ll--)
                {
                    // TODO: multRow (1, _matrix[ll], _width, ll);       //normalisation de toute la ligne
                    for (l2 = l - TRANCHE + 1; l2 < ll; l2++)
                    {
                        if ((!isZero(l2,ll) ))
                        {
                            // TODO: getElement(l2,ll) = modulo (getElement(l2,ll));
                            if ((!isZero(l2,ll) ))
                            {
                                addMultRow (l2, ll, -getElement(l2,ll), _height, _width);
                                setElement(l2,ll,0);
                            }
                        }
                    }
                }
                // TODO: multRow (1, _matrix[l - TRANCHE + 1], _width, l - TRANCHE + 1);
                //rectangle au dessus
                max_endcol = _endCol[l];
                min_endcol = _endCol[l - TRANCHE + 1];
                for (l2 = 0; l2 < min_endcol; l2++)
                {
                    for (ll = l; ll > l - TRANCHE; ll--)
                    {
                        // TODO: getElement(l2,ll) = modulo (getElement(l2,ll));
                        if ((!isZero(l2,ll) ))
                        {
                            addMultRow (l2, ll, -getElement(l2,ll), _height, _width);
                            setElement(l2,ll,0);
                        }
                    }
                }
                for (l2 = min_endcol; l2 < max_endcol; l2++)
                {
                    for (ll = l; _endCol[ll] > l2; ll--)
                    {
                        // TODO: getElement(l2,ll) = modulo (getElement(l2,ll));
                        if ((!isZero(l2,ll) ))
                        {
                            addMultRow (l2, ll, -getElement(l2,ll), _height, _width);
                            setElement(l2,ll,0);
                        }
                    }
                }
                for (l2 = _nbPiv; l2 <= l - TRANCHE; l2++)
                {
                    for (ll = l; ll > l - TRANCHE; ll--)
                    {
                        if ((!isZero(l2,ll) ))
                        {
                            // TODO: getElement(l2,ll) = modulo (getElement(l2,ll));
                            if ((!isZero(l2,ll) ))
                            {
                                addMultRow (l2, ll, -getElement(l2,ll), _height, _width);
                                setElement(l2,ll,0);
                            }
                        }
                    }
                }
            }
        }
        tmp_ech_dh = (((double)clock () - start) * 1000) / CLOCKS_PER_SEC;

        // TODO: 
        //for (i = 0; i < _height; i++)
        //{
            //for (l = 0; l < _width; l++)
            //{
                //_matrix[i][l] = modulo (_matrix[i][l]);
            //}
        //}

        if (VERBOSE > 1)
        {
            printf ("%.1f + %.1f + %.1f ms = %.1f CPU\n", tmp_ech_g, tmp_ech_db, tmp_ech_dh, tmp_ech_g + tmp_ech_db + tmp_ech_dh);
        }
        return _height;
    }
    
    
    // Operator overload
    
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
        _nbPiv(matrix._nbPiv);
        _tau(matrix._tau);
        sigma(matrix._sigma);
        _startTail(matrix._startTail); 
        _endCol(matrix._endCol);
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
            _matrix(matrix._matrix);
            matrix._matrix=0;
            _height(matrix._height);
            matrix._height=0;
            _width(matrix._width);
            matrix._width=0;
            _nbPiv(matrix._nbPiv);
            matrix._nbPiv=0;
            _tau(matrix._tau);
            sigma(matrix._sigma);
            matrix._sigma=0;
            _startTail(matrix._startTail); 
            matrix._startTail=0;
            _endCol(matrix._endCol);
            matrix._endCol=0;
        }
    }
    
    template <typename Element>
    ostream & operator<<(ostream & stream, Matrix<Element> const & matrix)
    {
        matrix.printMatrix();
        return stream;
    }

}

#endif // F4_MATRIX_INL
