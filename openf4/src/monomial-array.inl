/* 
 * Copyright (C) 2015 Antoine Joux, Vanessa Vitse and Titouan Coladon
 * 
 * This file is part of openf4.
 * 
 * openf4 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * openf4 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with openf4.  If not, see <http://www.gnu.org/licenses/>.
 */

  /**
  * \file monomial-array.inl
  * \brief Definition of MonomialArray methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef OPENF4_MONOMIAL_ARRAY_INL
#define OPENF4_MONOMIAL_ARRAY_INL

using namespace std;

namespace F4
{
    /* Global variables */
    
    extern int VERBOSE;
    
    extern int NB_THREAD;
    
    
    /* Constructors */
    
    MonomialArray::MonomialArray(int nbVariable, int capacity):_tabulatedProduct(0), _nbVariable(nbVariable), _size(0), _varlistIndex(0), _numMaxRow(0), _numMaxColumn(0)
    {
        /* Initialise Monomial */
        Monomial::initMonomial(nbVariable, 0);
        
        /* Initialise _monomialArray */
        _monomialArray.resize(capacity);
    }
             
    MonomialArray::MonomialArray(int nbVariable, int capacity, int degree):_tabulatedProduct(0), _nbVariable(nbVariable), _size(0), _varlistIndex(0), _numMaxRow(0), _numMaxColumn(0)
    {
        /* Initialise Monomial */
        Monomial::initMonomial(nbVariable, degree);
        
        /* Fill NB_MONOMIAL up to degree "degree" */
        Monomial::setNbMonomial(degree);
        
        /* Initialise _monomialArray */
        _monomialArray.resize(capacity);
        
        /* Fill _monomialArray up to degree "degree" */
        setMonomialArray();
    }
    
    /* Destructor */
    
    MonomialArray::~MonomialArray()
    {
        /* Free the varlists */
        for(int i=0; i<_varlistIndex; i++)
        {
            delete[] _varlistArray[i];
            _varlistArray[i]=0;
        }
        
        /* Free _tabulatedProduct */
        freeTabulatedProduct();
        
        /* Free Monomial */
        Monomial::freeMonomial();
    }
    
    
    /* Miscellaneous */
    
    void MonomialArray::setMonomialArray()
    {
        size_t size=Monomial::getNbMonomial();
        if(size>_size)
        {
            if (VERBOSE>1)
            {
                cout << "MonomialArray: " << (size - _size) << " new monomials, " << ((double)(size - _size) * (sizeof(Monomial) + _nbVariable*sizeof(uint8_t)))/1000000 << " Mo reserved for _monomialArray, varlistIndex = " << _varlistIndex << endl;
            }
            _monomialArray.resize(size);
            _varlistArray[_varlistIndex]=new uint8_t[(size - _size)*_nbVariable];
            assert(_varlistArray[_varlistIndex] != 0);
            uint8_t * ptr = _varlistArray[_varlistIndex];
            for(size_t i=_size; i<size; i++)
            {
                _monomialArray[i].setVarlist(ptr);
                ptr+=_nbVariable;
                _monomialArray[i].intToMonomial(i);
            }
            _varlistIndex++;
            _size=size;
            
            /* Fill _tabulatedProduct */
            setTabulatedProduct(Monomial::getMaxDegree()-1);
        }
    }

    void MonomialArray::setTabulatedProduct(int degree)
    {
        double size=0;
        
        if(_tabulatedProduct==0)
        {
            /* Number of monomial of degree 1 */
            _numMaxRow = Monomial::getNbMonomial(1, _nbVariable + 1); 
            _tabulatedProduct = new vector<int>[_numMaxRow];
            assert(_tabulatedProduct!=0);
        }
        /* Number of monomial of degree deg */
        int numMaxColumn = Monomial::getNbMonomial(degree, _nbVariable + 1);
        
        if(numMaxColumn>_numMaxColumn)
        {
        
            /* Time */
            chrono::steady_clock::time_point start;
            typedef chrono::duration<int,milli> millisecs_t;
            
            if (VERBOSE > 1)
            {
                start = chrono::steady_clock::now();
                if (VERBOSE > 2)
                {
                    cout << "Monomial::setTabulatedProduct: _numMaxRow: " << _numMaxRow << endl;
                    cout << "Monomial::setTabulatedProduct: _numMaxColumn: " << _numMaxColumn << endl;
                    cout << "Monomial::setTabulatedProduct: numMaxColumn (new): " << numMaxColumn << endl;
                }
            }
            
            size += (_numMaxRow * (numMaxColumn-_numMaxColumn) * sizeof (int));
            
            const uint8_t * varlist1;
            const uint8_t * varlist2;
            uint8_t varlist[_nbVariable];
            short deg=0;
            
            #ifdef USE_OPENMP
            omp_set_num_threads(NB_THREAD);
            #pragma omp parallel for private(varlist, varlist1, varlist2, deg)
            #endif // USE_OPENMP
            for (int numMon1 = 0; numMon1 < _numMaxRow; numMon1++)
            {
                varlist1=_monomialArray[numMon1].getVarlist();
                _tabulatedProduct[numMon1].reserve(numMaxColumn);
                for (int numMon2 = _numMaxColumn; numMon2 < numMaxColumn; numMon2++)
                {
                    varlist2=_monomialArray[numMon2].getVarlist();
                    deg=0;
                    for(int i=0; i<_nbVariable; i++)
                    {
                        varlist[i]=varlist1[i]+varlist2[i];
                        deg+=varlist[i];
                    }
                    _tabulatedProduct[numMon1].push_back(Monomial::varlistToInt(varlist,deg));
                }
            }
            if (VERBOSE > 1)
            {
                cout << "Monomial: products computed up to deg " << 1 << " x " << degree << " in " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms" << endl; 
                cout << "Monomial: " << size/1000000 << "Mo allocated for _tabulatedProduct " << endl;
            }
            _numMaxColumn=numMaxColumn;
        }
    }
    
    void 
    MonomialArray::freeTabulatedProduct()
    {
        if(_tabulatedProduct)
        {
            delete[] _tabulatedProduct;
            _tabulatedProduct=0;
        }
    }
    
    int 
    MonomialArray::multNumMonomial(int numMon1, int numMon2)
    {
        if (numMon1 > numMon2)
        {
            swap(numMon1,numMon2);
        }
        
        if (numMon1 < _numMaxRow && numMon2 < _numMaxColumn)
        {
            return _tabulatedProduct[numMon1][numMon2];
        }
        else
        {
            if( VERBOSE > 3)
            {
                cout << "MonomialArray::MultNumMonomial: cannot use _tabulatedProduct, deg " << _monomialArray[numMon1].getDegree() << " * " << _monomialArray[numMon2].getDegree()  << endl;
            }
            if(numMon1 > (int)_size || numMon2 > (int)_size)
            {
                Monomial::increaseNbMonomial(max(numMon1, numMon2));
                setMonomialArray();
            }
            int res = multiplyMonomial(_monomialArray[numMon1], _monomialArray[numMon2]);
            /* Increase _monomialArray for next time */
            setMonomialArray();
            return res;
        }
    }

    
    uint8_t
    MonomialArray::getNumVarlist(int numMon, int index)
    {
        if(index>(int)_size)
        {
            Monomial::increaseNbMonomial(index);
            setMonomialArray();
        }
        return _monomialArray[numMon].getVarlist(index);
    }
    
    
    /* Access */
    
    Monomial const & 
    MonomialArray::getNumMonomial(int index)
    {
        if(index>(int)_size)
        {
            Monomial::increaseNbMonomial(index);
            setMonomialArray();
        }
        return _monomialArray[index];
    }
    
    Monomial const & 
    MonomialArray::operator[](int index)
    {
        if(index>(int)_size)
        {
            Monomial::increaseNbMonomial(index);
            setMonomialArray();
        }
        return _monomialArray[index];
    }
}

#endif // OPENF4_MONOMIAL_ARRAY_INL
