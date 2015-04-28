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
  * \file monomial-array.inl
  * \brief Definition of MonomialArray methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef F4_MONOMIAL_ARRAY_INL
#define F4_MONOMIAL_ARRAY_INL

using namespace std;

namespace F4
{
    /* Global variables */
    
    extern int VERBOSE;
    
    extern int NB_THREAD;
    
    
    /* Constructors */
    
    MonomialArray::MonomialArray(int nbVariable, int capacity):_tabulatedProduct(0), _nbVariable(nbVariable), _size(0), _capacity(capacity), _varlistIndex(0), _numMaxRow(0), _numMaxColumn(0)
    {
        /* Initialise Monomial */
        Monomial::initMonomial(nbVariable, 0);
        
        /* Initialise _monomialArray */
        _monomialArray = new Monomial[_capacity];
    }
             
    MonomialArray::MonomialArray(int nbVariable, int capacity, int degree):_tabulatedProduct(0), _nbVariable(nbVariable), _size(0), _capacity(capacity), _varlistIndex(0), _numMaxRow(0), _numMaxColumn(0)
    {
        /* Initialise Monomial */
        Monomial::initMonomial(nbVariable, degree);
        
        /* Fill NB_MONOMIAL up to degree "degree" */
        Monomial::setNbMonomial(degree);
        
        /* Initialise _monomialArray */
        _monomialArray = new Monomial[_capacity];
        
        /* Fill _monomialArray up to degree "degree" */
        setMonomialArray();
    }
             
    MonomialArray::MonomialArray(int nbVariable, int capacity, int degree, int deg1, int deg2):_nbVariable(nbVariable), _size(0), _capacity(capacity), _varlistIndex(0), _numMaxRow(0), _numMaxColumn(0)
    {
        /* Initialise Monomial */
        Monomial::initMonomial(nbVariable, degree);
        
        /* Fill NB_MONOMIAL up to degree "degree" */
         Monomial::setNbMonomial(degree);
        
        /* Initialise _monomialArray */
        _monomialArray = new Monomial[_capacity];
        
        /* Fill _monomialArray up to degree "degree" */
        setMonomialArray();
        
        /* Fill _tabulatedProduct */
        setTabulatedProduct(deg1, deg2);
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
        
        /* Free the array */
        delete[] _monomialArray;
        _monomialArray=0;
        
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
            assert(size<_capacity);
            if (VERBOSE>1)
            {
                cout << "MonomialArray: " << (size - _size) << " new monomials, " << ((double)(size - _size) * (sizeof(Monomial) + _nbVariable*sizeof(uint8_t)))/1000000 << " Mo reserved for _monomialArray, varlistIndex = " << _varlistIndex << endl;
            }
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
        }
    }
    
    void MonomialArray::setTabulatedProduct(int deg1, int deg2)
    {
        /* If _monomialArray does not contain monomials of degree deg1+deg2 we increase it. */
        Monomial::setNbMonomial(deg1+deg2);
        setMonomialArray();
        
        double size=0;
        int i;
        _numMaxRow = Monomial::getNbMonomial(deg1, _nbVariable + 1);
        _numMaxColumn = Monomial::getNbMonomial(deg2, _nbVariable + 1);
        
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
            }
        }
        
        _tabulatedProduct = new int*[_numMaxRow];
        assert(_tabulatedProduct!=0);
        size += (_numMaxRow * _numMaxColumn * sizeof (int));
        
        const uint8_t * varlist1;
        const uint8_t * varlist2;
        uint8_t varlist[_nbVariable];
        short deg=0;
        
        omp_set_num_threads(NB_THREAD);
        #pragma omp parallel for private(varlist, varlist1, varlist2, i, deg)
        for (int numMon1 = 0; numMon1 < _numMaxRow; numMon1++)
        {
            varlist1=_monomialArray[numMon1].getVarlist();
            _tabulatedProduct[numMon1]=new int[_numMaxColumn];
            for (int numMon2 = 0; numMon2 < _numMaxColumn; numMon2++)
            {
                varlist2=_monomialArray[numMon2].getVarlist();
                deg=0;
                for(i=0; i<_nbVariable; i++)
                {
                    varlist[i]=varlist1[i]+varlist2[i];
                    deg+=varlist[i];
                }
                _tabulatedProduct[numMon1][numMon2] = Monomial::varlistToInt(varlist,deg);
            }
        }
        if (VERBOSE > 1)
        {
            cout << "Monomial: products computed up to deg " << deg1 <<" x " << deg2 << " in " << chrono::duration_cast<millisecs_t>(chrono::steady_clock::now()-start).count() << " ms" << endl; 
            cout << "Monomial: " << size/1000000 << "Mo allocated for _tabulatedProduct " << endl;
        }
    }
        
    void 
    MonomialArray::freeTabulatedProduct()
    {
        if(_tabulatedProduct)
        {
            for (int numMon = 0; numMon < _numMaxRow; numMon++)
            {
                delete[] _tabulatedProduct[numMon];
                _tabulatedProduct[numMon]=0;
            }
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
            
            return multiplyMonomial(_monomialArray[numMon1], _monomialArray[numMon2]);
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

#endif // F4_MONOMIAL_ARRAY_INL
