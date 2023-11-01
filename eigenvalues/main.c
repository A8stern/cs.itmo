#include "return_codes.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t col;
    size_t row;
    double **elements;
} Matrix;

void destroy_matrix(Matrix *matrix) {
    for (size_t i = 0; i < matrix->row; i++) {
        free(matrix->elements[i]);
    }
    free(matrix->elements);
    free(matrix);
}

Matrix *create_matrix(size_t row, size_t col) {
    Matrix *A = (Matrix *) malloc(sizeof(Matrix));
    if (A == NULL) {
        return NULL;
    }
    A->row = row;
    A->col = col;
    A->elements = (double **) malloc(row * sizeof(double *));
    if (A->elements == NULL) {
        free(A);
        return NULL;
    }
    for (size_t i = 0; i < row; i++) {
        A->elements[i] = (double *) malloc(col * sizeof(double));
        if (A->elements[i] == NULL) {
            destroy_matrix(A);
            return NULL;
        }
    }
    return A;
}

void copy_matrix(Matrix *A, Matrix *res) {
    for (int h = 0; h < A->row; h++) {
        for (int h1 = 0; h1 < A->col; h1++) {
            res->elements[h][h1] = A->elements[h][h1];
        }
    }
}

void matrix_multiply(Matrix *A, Matrix *B, Matrix *C) {
    Matrix *temp = create_matrix(A->row, A->col);
    for (int i = 0; i < A->row; i++) {
        for (int j = 0; j < A->row; j++) {
            temp->elements[i][j] = 0;
            for (int k = 0; k < A->row; k++) {
                temp->elements[i][j] += A->elements[i][k] * B->elements[k][j];
            }
        }
    }
    copy_matrix(temp, C);
    destroy_matrix(temp);
}

double find_norm(Matrix *A) {
    double res = 0;

    for (int i = 0; i < A->row; i++) {
        for (int j = 0; j < A->col; j++) {
            res += pow(A->elements[i][j], 2);
        }
    }
    return sqrt(res);
}

Matrix *tri_matrix(size_t N) {
    Matrix *res = create_matrix(N, N);
    if (res == NULL) {
        return NULL;
    }
    for (int i = 0; i < N; i++) {
        res->elements[i][i] = 1.;
    }
    return res;
}

int house(Matrix *a) {
    double norm, n;

    Matrix *r = create_matrix(a->row, a->col);
    if (r == NULL){
        return ERROR_OUT_OF_MEMORY;
    }
    Matrix *P = create_matrix(a->row, a->col);
    if (P == NULL){
        destroy_matrix(r);
        return ERROR_OUT_OF_MEMORY;
    }
    Matrix *q = tri_matrix(a->col);
    if (q == NULL){
        destroy_matrix(r);
        destroy_matrix(P);
        return ERROR_OUT_OF_MEMORY;
    }
    Matrix *E = tri_matrix(a->col);
    if (E == NULL){
        destroy_matrix(r);
        destroy_matrix(P);
        destroy_matrix(q);
        return ERROR_OUT_OF_MEMORY;
    }

    Matrix *v = create_matrix(a->row, a->col);
    if (v == NULL){
        destroy_matrix(r);
        destroy_matrix(P);
        destroy_matrix(E);
        destroy_matrix(q);
        return ERROR_OUT_OF_MEMORY;
    }
    Matrix *u = create_matrix(a->row, a->col);
    if (u == NULL){
        destroy_matrix(r);
        destroy_matrix(P);
        destroy_matrix(E);
        destroy_matrix(q);
        destroy_matrix(v);
        return ERROR_OUT_OF_MEMORY;
    }

    copy_matrix(a, r);

    for (size_t i = 0; i < a->col; i++) {

        for (size_t j = 0; j < a->row; j++) {
            v->elements[0][j] = 0;
            u->elements[0][j] = 0;
        }

        for (size_t j = i; j < a->row; j++) {
            u->elements[0][j] = r->elements[j][i];
        }

        norm = find_norm(u);

        if (u->elements[0][i] >= 0) {
            norm = -norm;
        }

        for (size_t j = i; j < a->row; j++) {
            if (j == i) {
                v->elements[0][j] = u->elements[0][j] + norm;
            } else {
                v->elements[0][j] = u->elements[0][j];
            }
        }

        n = find_norm(v);

        if (n < 0.00000001)
            continue;

        for (size_t j = i; j < a->row; j++) {
            v->elements[0][j] /= n;
        }

        for (size_t k = 0; k < a->row; k++) {
            for (size_t j = 0; j < a->row; j++) {
                P->elements[k][j] = E->elements[k][j] - v->elements[0][k] * v->elements[0][j] * 2;
            }
        }

        matrix_multiply(P, r, r);
        matrix_multiply(q, P, q);
    }
    matrix_multiply(r, q, a);
    return 0;
}

double calc(double a, double b, double c, double d) {
    return sqrt(-(4 * (b * c) + (a - d) * (a - d))) / 2;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Expected 2 arguments but found %i\n", argc - 1);
        return ERROR_PARAMETER_INVALID;
    }

    FILE *f;
    f = fopen(argv[1], "r");

    if (f == NULL) {
        fprintf(stderr, "File %s not found\n", argv[1]);
        return ERROR_CANNOT_OPEN_FILE;
    }

    int n;
    fscanf(f, "%i", &n);
    Matrix *matrix = create_matrix(n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(f, "%lg", &matrix->elements[i][j]) != 1) {
                fclose(f);
                destroy_matrix(matrix);
                return ERROR_DATA_INVALID;
            }
        }
    }
    fclose(f);
    int check;

    for (int k = 0; k < 75 * n + 100; k++) {
        check = house(matrix);
        if (check == ERROR_OUT_OF_MEMORY){
            fprintf(stderr, "Out of memory");
            destroy_matrix(matrix);
            return ERROR_OUT_OF_MEMORY;
        }
    }
    f = fopen(argv[2], "w");
    if (f == NULL) {
        fprintf(stderr, "File %s not found\n", argv[2]);
        destroy_matrix(matrix);
        return ERROR_CANNOT_OPEN_FILE;
    }
    for (int i = 0; i < n; i++) {
        if (i != n - 1) {
            if (matrix->elements[i + 1][i] < 0.00001 && matrix->elements[i + 1][i] > -0.00001) {
                fprintf(f, "%g\n", matrix->elements[i][i]);
            } else {
                double d = calc(matrix->elements[i][i], matrix->elements[i + 1][i], matrix->elements[i][i + 1],
                                matrix->elements[i + 1][i + 1]);
                fprintf(f, "%g +%g", (matrix->elements[i][i] + matrix->elements[i + 1][i + 1]) / 2, d);
                fprintf(f, "i\n");
                fprintf(f, "%g -%g", (matrix->elements[i][i] + matrix->elements[i + 1][i + 1]) / 2, d);
                fprintf(f, "i");
                i++;
                if (i < n - 1)
                    fprintf(f, "\n");
            }
        } else
            fprintf(f, "%lf", matrix->elements[i][i]);
    }

    fclose(f);
    destroy_matrix(matrix);

    return SUCCESS;
}