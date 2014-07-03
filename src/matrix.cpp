/* -*- c-basic-offset: 3 -*-
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */

/*
 * @author Reynald Pereira <reynald.pereira@ecole.ensicaen.fr>
 * @author Tristan Freulon <tristan.fleulon@ecole.ensicaen.fr>
 * @version     0.0.1 - Wed Sep 25 2013
 *
 * @todo the list of improvements suggested for the file.
 * @bug the list of known bugs.
 */

/*
 * @file matrix.cpp
 *
 * Description of the program objectives.
 * All necessary references.
 */

#include <iostream>
#include "matrix.h"

using namespace std;

/**
  * @brief Default constructor of a Matrix
  * @version 1.0.0
  */
Matrix::Matrix() : _row(0),_column(0),_matrix(0) {
    //cout<<"+++Matrix()"<<endl;
}


/**
  * @brief destructor of the matrixs.
  * @version 1.0.0
  */
Matrix::~Matrix() {

    //cout<<"---~Matrix()"<<endl;

    delete[] _matrix;
}

/**
  * @brief Constructor of a Matrix
  * @param row number of line in the matrix
  * @param col number of column in the matrix
  * @version 1.0.0
  */
Matrix::Matrix(int row, int col) : _row(row),_column(col) {

    //cout<<"+++Matrix("<<_row<<","<<_column<<")"<<endl;
    _matrix = new double [row*col];
}

/**
  * @brief Constructor of a Matrix
  * @param m matrix you want to copy
  * @version 1.0.0
  */
Matrix::Matrix(const Matrix& m) : _row(m._row),_column(m._column) {

    int max = _row*_column;

    _matrix = new double [max];

    for(int i=0;i<max;i++) {
        _matrix[i] = m._matrix[i];
    }

   // cout<<"rrrMatrix("<<_row<<","<<_column<<")"<<endl;
}

/**
  * @brief Overload of operator=
  * @param m matrix you want to equalize
  * @version 1.0.0
  * @return return the matrix equalized
  */
Matrix& Matrix::operator=(const Matrix& m) {

    int max;

    _row    = m._row;
    _column = m._column;
    max     = _row*_column;

    delete[] _matrix;

    _matrix = new double [max];

    for(int i=0;i<max;i++) {
        _matrix[i] = m._matrix[i];
    }

    return *this;
}

/**
 * @brief Overload the operator+
 * @param m matrix you add
 * @version 1.0.0
 * @return return the sum
 */
Matrix& Matrix::operator+( const Matrix & m ) throw (MatrixException) {

    if ( m._row != _row || m._column != _column ) {

        throw MatrixException(4);
    }

    *this += m;

    return *this;
}

/**
 * @brief Overload the operator+=
 * @param m matrix you add
 * @version 1.0.0
 * @return return the sum
 */
Matrix& Matrix::operator+=( const Matrix & m ) throw (MatrixException) {

    if ( m._row != _row || m._column != _column ) {

        throw MatrixException(4);
    }

    int max = _row*_column;

    for(int i=0;i<max;i++) {
        _matrix[i] += m._matrix[i];
    }

    return *this;
}

/**
 * @brief Overload the operator-
 * @param m matrix you sub
 * @version 1.0.0
 * @return return the substraction
 */
Matrix& Matrix::operator-( const Matrix & m ) throw (MatrixException) {
    if ( m._row != _row || m._column != _column ) {

        throw MatrixException(4);
    }

    *this -= m;

    return *this;
}

/**
 * @brief Overload the operator-=
 * @param m matrix you sub
 * @version 1.0.0
 * @return return the substraction
 */
Matrix& Matrix::operator-=( const Matrix & m ) throw (MatrixException) {

    if ( m._row != _row || m._column != _column ) {

        throw MatrixException(4);
    }

    int max = _row*_column;

    for(int i=0;i<max;i++) {
        _matrix[i] -= m._matrix[i];
    }

    return *this;
}

/**
 * @brief Overload the operator* with 2 matrix
 * @param m matrix you mul
 * @version 1.0.0
 * @return return the multiplication
 * @bug unable to understand why the algorithme is wrong
 */
Matrix& Matrix::operator*( const Matrix & m ) throw (MatrixException) {
    if ( m._column != _row || m._row != _column ) {

        throw MatrixException(4);
    }

    Matrix ret(_row,_column);
    int max  = _row*_column;
    double s = 0;

    for(int i=0;i<max;i++) {
        for(int j=0+i%_column;j<_column+i%_column;j++) {

            s += _matrix[j]*m._matrix[i+j%_column];
        }

        ret._matrix[i] = s;
        s          = 0;
    }

    return *(new Matrix(ret));
}

/**
 * @brief Overload the operator*= with 2 matrix
 * @param m matrix you mul
 * @version 1.0.0
 * @return return the multiplication
 */
Matrix& Matrix::operator*=( const Matrix & m ) throw (MatrixException) {
    if (  m._column != _row || m._row != _column ) {

        throw MatrixException(4);
    }

    return (*this)*m;
}

/**
 * @brief Overload the operator* with a scalar number
 * @param k scalar you mul
 * @param m matrix you mul
 * @version 1.0.0
 * @return return the multiplication
 */
Matrix& operator*( double k, const Matrix & m ) {
    Matrix m2(m);

    m2 *= k;

    return *(new Matrix(m2));
}

/**
 * @brief Overload the operator* with a scalar number
 * @param m matrix you mul
 * @param k scalar you mul
 * @version 1.0.0
 * @return return the multiplication
 */
Matrix& operator*( const Matrix & m, double k ) {

    return operator*(k,m);
}

/**
 * @brief Overload the operator*= with a scalar number
 * @param k scalar you mul
 * @version 1.0.0
 * @return return the multiplication
 */
Matrix& Matrix::operator*=( double k ) {
    int max = _row*_column;

    for(int i=0;i<max;i++) {
        _matrix[i] *= k;
    }

    return *this;
}

/**
 * @brief Function to overload the Matrix displaying
 * @param out output stream
 * @version 1.0.0
 * @return void
 */
void Matrix::display( std::ostream & out) const {
    int max = _row*_column;

    for(int i=0;i<max;i++) {

        if( i%_column == 0 && i != 0 ) {
            out<<"\n";
        }

        out<<_matrix[i]<<" ";
    }
}

/**
 * @brief Overload the << operator to display a Matrix
 * @param out output stream
 * @param m matrix you want to display
 * @version 1.0.0
 * @return return the stream
 */
ostream & operator<<( ostream & out, const Matrix & m ) {
    m.display(out);
    return out;
}

/**
 * @brief Overload the >> operator to rec a Matrix
 * @param in input stream
 * @param m matrix you want to rec
 * @version 1.0.0
 * @return return the stream
 */
istream & operator>>( istream & in, const Matrix & m ) {

    int max = m._row*m._column;

    for(int i=0;i<max;i++) {
        in>>m._matrix[i];
    }

    return in;
}

/**
 * @brief Overload the operator[]
 * @param index index of the row you want to go
 * @version 1.0.0
 * @return return a double arr containing the row
 */
double* Matrix::operator[]( int index ) throw(MatrixException) {

    if ( index > _row ) {

        throw MatrixException(3);
    }

    return(_matrix+index*_column);

}

/**
 * @brief get a row
 * @param index index of the row you want to go
 * @version 1.0.0
 * @return return a double arr containing the row
 */
double* Matrix::getRowNumber( int index ) throw(MatrixException) {

    if ( index > _row ) {

        throw MatrixException(3);
    }

    return(_matrix+index*_column);

}

/**
 * @brief transpose a matrix
 * @version 1.0.0
 * @return return the T(M)
 */
Matrix Matrix::transpose() {

    Matrix ret(_column,_row);

    for(int i=0;i<_row;i++) {

        for(int j=0;j<_column;j++) {
            ret.getRowNumber(j)[i] = this->getRowNumber(i)[j];
        }
    }

    return ret;
}


/**
  * @brief calculate a matrix det.
  * @version 1.0.0
  * @return return teh value of the determinant
  */
double Matrix::determinant() {

    double ret = 0;

    if( _row == 2 ) {
        return _matrix[0]*_matrix[3] - _matrix[1]*_matrix[2];
    }

    for(int j=0;j<_row;j++) {
        if( (0+j)%2 == 1) {
            ret -= subMatrix(0,j).determinant()*getRowNumber(0)[j];
        }
        else {
            ret += subMatrix(0,j).determinant()*getRowNumber(0)[j];
        }
    }

    return ret;
}

/**
  * @brief return the sub matrix deleteing colum j and row i
  * @param i row to del
  * @param j column to del
  * @version 1.0.0
  * @return return a submatrix
  */
Matrix Matrix::subMatrix(int i, int j) {

    Matrix ret(_row-1,_column-1);
    int col = 0;
    int row = 0;

    for(int k=0;k<ret._row;k++) {
        if(k == i) {
            row++;
        }
        for(int l=0;l<ret._column;l++) {
            if(l == j) {
                col++;
            }
            ret._matrix[k*ret._column+l] = _matrix[row*_column+col];
            col++;
        }
        row++;
        col = 0;
    }

    return ret;
}

/**
  * @brief return the cofactor of colum j and row i
  * @param i row to del
  * @param j column to del
  * @version 1.0.0
  * @return return the cofactor
  */
double Matrix::cofactor(int i, int j) {
    double ret = 0;

    if ( _row == 2 ) {

        if( (i+j)%2 == 1) {
            return -_matrix[2*j+i];
        }
        return _matrix[2*j+i];
    }

    if( (i+j)%2 == 1) {
        ret -= subMatrix(i,j).determinant();
    }
    else {
        ret += subMatrix(i,j).determinant();
    }

    return ret;
}

/**
 * @brief calculate the comatrix using cofactors
 * @version 1.0.0
 * @return return the comatrix
 */
Matrix Matrix::comatrix() {

    Matrix ret(_row,_column);

    for(int k=0;k<ret._row;k++) {
        for(int l=0;l<ret._column;l++) {
            ret._matrix[k*ret._column+l] = cofactor(k,l);
        }
    }

    return ret;
}

/**
 * @brief calculate the inverse matrix using cofactors
 * @version 1.0.0
 * @return return the inverse
 */
Matrix Matrix::inverse() throw(MatrixException){

    if ( determinant() ==  0 ) {
        throw MatrixException(1);
    }
    if ( _column != _row ) {
        throw MatrixException(2);
    }

    return (1/determinant())*comatrix().transpose();

}
