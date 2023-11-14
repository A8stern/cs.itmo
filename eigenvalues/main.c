#define _CRT_SECURE_NO_WARNINGS
#include "return_codes.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t col;
    size_t row;
    double *elements;
} Matrix;

double getItem(Matrix* pSrc, size_t x, size_t y) 
{
    if (!pSrc) return 0;
    size_t offset = y * pSrc->col + x;
    return pSrc->elements[offset];
}

void setItem(Matrix* pSrc, size_t x, size_t y, double value) 
{
    if (!pSrc) return;
    size_t offset = y * pSrc->col + x;
    pSrc->elements[offset] = value;
}

void destroy_matrix(Matrix *matrix) 
{
    if (!matrix) return;
    if (matrix -> elements) free(matrix->elements);
    free(matrix);
}

Matrix *create_matrix(size_t row, size_t col) 
{
    Matrix *A = (Matrix *) malloc(sizeof(Matrix));
    if (!A) return NULL;
    A->row = row;
    A->col = col;
    A->elements = (double *) malloc(row * col * sizeof(double));
    if (!A->elements) {
        free(A); return NULL;
    }
    memset(A->elements, 0, row * col * sizeof(double));
    return A;
}

void copy_matrix(Matrix *pSrc, Matrix *pDst) 
{
    if (!pSrc || !pDst) return;
    double* matrixElemsSrc = (double*)pSrc->elements;
    double* matrixElemsDst = (double*)pDst->elements;
    if (!matrixElemsSrc || !matrixElemsDst) return;
    for (int h = 0; h < pSrc->row; h++) 
    {
        for (int h1 = 0; h1 < pSrc->col; h1++) 
        {
            *matrixElemsDst++ = *matrixElemsSrc++;
        }
    }
}

void show_matrix(Matrix* pSrc) 
{
    if (!pSrc) return;
    double* matrixElems = (double*)pSrc->elements;
    for (size_t i = 0; i < pSrc->row; i++) 
    {
        for (size_t j = 0; j < pSrc->col; j++) 
        {
            fprintf(stdout, "%g ", *matrixElems++);
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}

void matrix_multiply(Matrix *A, Matrix *B, Matrix *C) 
{ 
    if (!A || !B || !C) return;
    Matrix *temp = create_matrix(A->row, A->col);
    if (!temp) return;
    for (int i = 0; i < A->row; i++)
        for (int j = 0; j < A->col; j++) 
        {
            setItem(temp, i, j, 0);
            for (int k = 0; k < B->row; k++) 
            {
                double value = getItem(temp, i, j) + getItem(A, i, k) * getItem(B, k, j);
                setItem(temp, i, j, value);
            }
        }
    copy_matrix(temp, C); 
    destroy_matrix(temp); 
}

double find_norm(Matrix *A) 
{
    if (!A) return -1;
    double res = 0;

    for (int i = 0; i < A->row; i++) 
        for (int j = 0; j < A->col; j++) 
            res += getItem(A, i, j) * getItem(A, i, j);

        
    return sqrt(res);
}

Matrix *tri_matrix(size_t N) 
{
    Matrix *res = create_matrix(N, N);
    if (!res) return NULL;
    double* matrixElems = (double*)res->elements;
    for (int i = 0; i < N; i++) 
    {
        *matrixElems = 1.;
        matrixElems += N + 1;
    }
    return res;
}

int house(Matrix *a) 
{
    if (!a) return ERROR_DATA_INVALID;
    double norm, n; Matrix* r = NULL, * P = NULL, * q = NULL, * E = NULL, * v = NULL, * u = NULL;

    if (!(r = create_matrix(a->row, a->col))) return ERROR_OUT_OF_MEMORY;
    if (!(P = create_matrix(a->row, a->col))) 
    {
        destroy_matrix(r); return ERROR_OUT_OF_MEMORY;
    }
    if (!(q = tri_matrix(a->col))) 
    {
        destroy_matrix(r); destroy_matrix(P); return ERROR_OUT_OF_MEMORY;
    }
    if (!(E = tri_matrix(a->col))) 
    {
        destroy_matrix(r); destroy_matrix(P); destroy_matrix(q); return ERROR_OUT_OF_MEMORY;
    }
    if (!(v = create_matrix(a->row, a->col))) 
    {
        destroy_matrix(r); destroy_matrix(P); destroy_matrix(E); destroy_matrix(q); return ERROR_OUT_OF_MEMORY;
    }
    if (!(u = create_matrix(a->row, a->col))) 
    {
        destroy_matrix(r); destroy_matrix(P); destroy_matrix(E); destroy_matrix(q); destroy_matrix(v); return ERROR_OUT_OF_MEMORY;
    }
    copy_matrix(a, r);
    for (size_t i = 0; i < a->col; i++) 
    {
        for (size_t j = 0; j < a->row; j++) 
        {
            setItem(v, 0, j, 0); setItem(u, 0, j, 0);
        }
        for (size_t j = i; j < a->row; j++) 
        {
            setItem(u, 0, j, getItem(r, j, i));
        }
        norm = find_norm(u);
        if (getItem(u, 0, i) >= 0) 
        {
            norm = -norm;
        }
        for (size_t j = i; j < a->row; j++) 
        {
            if (j == i) {
                setItem(v, 0, j, getItem(u, 0, j) + norm);
            } else {
                setItem(v, 0, j, getItem(u, 0, j));
            }
        }
        n = find_norm(v);
        if (n < 0.00000001) continue;

        for (size_t j = i; j < a->row; j++) 
        {
            setItem(v, 0, j, getItem(v, 0, j) / n);
        }
        for (size_t k = 0; k < a->row; k++) 
        {
            for (size_t j = 0; j < a->row; j++) 
            {
                double value = getItem(E, k, j) - getItem(v, 0, k) * getItem(v, 0, j) * 2;
                setItem(P, k, j, value);
            }
        }
        matrix_multiply(P, r, r);
        matrix_multiply(q, P, q);
    }
    matrix_multiply(r, q, a);
    destroy_matrix(r); destroy_matrix(P); destroy_matrix(E); destroy_matrix(q); destroy_matrix(v); destroy_matrix(u);
    return 0;
}

double calc(double a, double b, double c, double d) 
{
    return sqrt(-(4 * (b * c) + (a - d) * (a - d))) / 2;
}

Matrix* initMatrix(FILE* f, int* errorCode)
{
    if (!errorCode) return NULL;
    if (!f) {
        *errorCode = ERROR_PARAMETER_INVALID;
        return NULL;
    }
    *errorCode = SUCCESS;
    int n;
    fscanf(f, "%i", &n);
    Matrix* matrix = create_matrix(n, n);
    if (!matrix)
    {
        fclose(f);
        *errorCode = ERROR_OUT_OF_MEMORY;
        return NULL;
    }
    double* matrixElems = (double*)matrix->elements;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fscanf(f, "%lg", matrixElems++) != 1)
            {
                fclose(f);
                destroy_matrix(matrix);
                *errorCode = ERROR_DATA_INVALID;
                return NULL;
            }
        }
    }
    fclose(f);
    int check;

    for (int k = 0; k < 75 * n + 100; k++)
    {
        check = house(matrix);
        if (check == ERROR_OUT_OF_MEMORY)
        {
            fprintf(stderr, "Out of memory");
            destroy_matrix(matrix);
            *errorCode = ERROR_OUT_OF_MEMORY;
            return NULL;
        }
    }
    return matrix;
}

int printEigenvalues(FILE* f, Matrix* matrix) 
{
    if (!f || !matrix) return ERROR_DATA_INVALID;
    
    for (size_t i = 0; i < matrix -> row; i++)
    {
        if (i != matrix->row - 1)
        {
            if (getItem(matrix, i + 1, i) < 0.00001 && getItem(matrix, i + 1, i) > -0.00001)
            {
                fprintf(f, "%g\n", getItem(matrix, i, i));
            }
            else
            {
                double d = calc(getItem(matrix, i, i), getItem(matrix, i + 1, i), getItem(matrix, i, i + 1),
                    getItem(matrix, i + 1, i + 1));
                fprintf(f, "%g +%g", (getItem(matrix, i, i) + getItem(matrix, i + 1, i + 1)) / 2, d);
                fprintf(f, "i\n");
                fprintf(f, "%g -%g", (getItem(matrix, i, i) + getItem(matrix, i + 1, i + 1)) / 2, d);
                fprintf(f, "i");
                i++;
                if (i < matrix->row - 1)
                    fprintf(f, "\n");
            }
        }
        else
            fprintf(f, "%lf", getItem(matrix, i, i));
    }

    fclose(f);
    destroy_matrix(matrix);
    return SUCCESS;
}

int main(int argc, char *argv[]) 
{
    if (argc != 3)
    {
        fprintf(stderr, "Expected 2 arguments but found %i\n", argc - 1);
        return ERROR_PARAMETER_INVALID;
    }
    FILE* f;
    f = fopen(argv[1], "r");

    if (f == NULL)
    {
        fprintf(stderr, "File %s not found\n", argv[1]);
        return ERROR_CANNOT_OPEN_FILE;
    }

    int errorCode = ERROR_PARAMETER_INVALID;
    Matrix* matrix = initMatrix(f, &errorCode);
    if (!matrix) return errorCode;
    
    f = fopen(argv[2], "w");
    if (f == NULL) 
    {
        fprintf(stderr, "File %s not found\n", argv[2]);
        destroy_matrix(matrix);
        return ERROR_CANNOT_OPEN_FILE;
    }
    
    return printEigenvalues(f, matrix);
} 