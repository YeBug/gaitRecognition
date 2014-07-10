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

/**
 * @author Auteur1 <mail@ecole.ensicaen.fr> 
 * @author Auteur2 <mail@ecole.ensicaen.fr> 
 * @version     0.0.1 - Sep 20, 2010
 * 
 * @todo the list of improvements suggested for the file.
 * @bug the list of known bugs.
 */

#ifndef __MATRIX_H
#define __MATRIX_H


/**
 * @file matrix.h
 *  
 * Description of the program objectives.
 * All necessary references.
 */

class MatrixException : public std::exception {
    private:
        std::string _msg;
    public:
        MatrixException( int type ) {

            std::cout<<"+++MatrixException("<<type<<")"<<std::endl;

            _msg = "Matrix Exception Happend";

            if( type == 1 ) {
                _msg += " : NulDet";
            }

            if( type == 2 ) {
                _msg += " : NonSquareInverse";
            }

            if( type == 3 ) {
                _msg += " : OutOfBound";
            }

            if( type == 4 ) {
                _msg += " : UnmatchingSize";
            }
        };

        virtual ~MatrixException() throw() {
            std::cout<<"---MatrixException()"<<std::endl;
        };

        virtual const char * what() const throw() {
            return _msg.c_str();
        };

};


class Matrix {

    private :

        int     _row;
        int     _column;
        double* _matrix;

    public :

        /**
          * @brief Default constructor of a Matrix
          * @version 1.0.0
          */
        Matrix();

        /**
          * @brief Constructor of a Matrix
          * @param row number of line in the matrix
          * @param col number of column in the matrix
          * @version 1.0.0
          */
        Matrix(int row, int col);

        /**
          * @brief Constructor of a Matrix
          * @param m matrix you want to copy
          * @version 1.0.0
          */
        Matrix(const Matrix& m);

        /**
          * @brief destructor of the matrixs.
          * @version 1.0.0
          */
        ~Matrix();

        /**
          * @brief Overload of operator=
          * @param m matrix you want to equalize
          * @version 1.0.0
          * @return return the matrix equalized
          */
        Matrix& operator=(const Matrix& m);

        /**
          * @brief Overload of operator+
          * @param m matrix you add
          * @version 1.0.0
          * @return return the sum
          */
        Matrix& operator+(const Matrix& m) throw (MatrixException);

        /**
          * @brief Overload of operator+=
          * @param m matrix you add
          * @version 1.0.0
          * @return return the sum
          */
        Matrix& operator+=(const Matrix& m) throw (MatrixException);

        /**
          * @brief Overload of operator-
          * @param m matrix you sub
          * @version 1.0.0
          * @return return the substraction
          */
        Matrix& operator-(const Matrix& m) throw (MatrixException);

        /**
          * @brief Overload of operator-=
          * @param m matrix you sub
          * @version 1.0.0
          * @return return the substraction
          */
        Matrix& operator-=(const Matrix& m) throw (MatrixException);

        /**
          * @brief Overload of operator*
          * @param m matrix you mul
          * @version 1.0.0
          * @return return he multiplication
          */
        Matrix& operator*(const Matrix& m) throw (MatrixException);

        /**
          * @brief Overload of operator*=
          * @param m matrix you mul
          * @version 1.0.0
          * @return return the multiplication
          */
        Matrix& operator*=(const Matrix& m) throw (MatrixException);

        /**
         * @brief Function to overload the Matrix displaying
         * @param out output stream
         * @version 1.0.0
         * @return void
         */
        void display( std::ostream & out) const;

        /**
         * @brief Overload the operator*= with a scalar number
         * @param k scalar you mul
         * @version 1.0.0
         * @return return the multiplication
         */
        Matrix& operator*=( double k );

        /**
         * @brief Overload the operator[]
         * @param index index of the row you want to go
         * @version 1.0.0
         * @return return a double arr containing the row
         */
        double* operator[]( int index ) throw(MatrixException);

        /**
         * @brief get a row
         * @param index index of the row you want to go
         * @version 1.0.0
         * @return return a double arr containing the row
         */
        double* getRowNumber( int index ) const throw(MatrixException);
        double* getRowNumber( int index ) throw(MatrixException);

        /**
         * @brief transpose a matrix
         * @version 1.0.0
         * @return return the T(M)
         */
        Matrix transpose();

        /**
          * @brief calculate a matrix det.
          * @version 1.0.0
          * @return return teh value of the determinant
          */
        double determinant();

        /**
          * @brief return the sub matrix deleteing colum j and row i
          * @param i row to del
          * @param j column to del
          * @version 1.0.0
          * @return return a submatrix
          */
        Matrix subMatrix(int i, int j);
        
        /**
          * @brief return the cofactor of colum j and row i
          * @param i row to del
          * @param j column to del
          * @version 1.0.0
          * @return return the cofactor
          */
        double cofactor(int i, int j);

        /**
          * @brief calculate the comatrix using cofactors
          * @version 1.0.0
          * @return return the comatrix
          */
        Matrix comatrix();

        /**
          * @brief calculate the inverse matrix using cofactors
          * @version 1.0.0
          * @return return the inverse
          */
        Matrix inverse() throw (MatrixException);

        friend Matrix& operator*( const Matrix & m, double k );
        friend Matrix& operator*( double k, const Matrix & m );
        friend std::ostream & operator<<( std::ostream & out, const Matrix & m );
        friend std::istream & operator>>( std::istream & in, const Matrix & m );

};

/**
 * @brief Overload the operator* with a scalar number
 * @param m matrix you mul
 * @param k scalar you mul
 * @version 1.0.0
 * @return return the multiplication
 */
Matrix& operator*( const Matrix & m, double k );

/**
 * @brief Overload the operator* with a scalar number
 * @param k scalar you mul
 * @param m matrix you mul
 * @version 1.0.0
 * @return return the multiplication
 */
Matrix& operator*( double k, const Matrix & m );

/**
 * @brief Overload the << operator to display a Matrix
 * @param out output stream
 * @param r rational you want ot display
 * @version 1.0.0
 * @return return the stream
 */
std::ostream & operator<<( std::ostream & out, const Matrix & m );

/**
 * @brief Overload the >> operator to rec a Matrix
 * @param in input stream
 * @param m matrix you want to rec
 * @version 1.0.0
 * @return return the stream
 */
std::istream & operator>>( std::istream & in, const Matrix & m );

#endif
