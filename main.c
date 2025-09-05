#include <stdio.h>
#include <stdlib.h>
#define CORRECT_ARR 2
#define MIN_ARR 0
#define START_NUMBER_DIAG 0
#define START_ARR 0

typedef enum {
    CORRECT_INPUT,
    INCORRECT_INPUT,
} InputStatus;

InputStatus inputArrMatrix(int* n, int* m);
InputStatus inputMatrix(int** mat, int n, int m);
int validation(int* n, int* m);
int** allocationMemoryMatrix(int n, int m);
int* createArr(int** mat, int* arr, int n, int m);
int* allocationMemoryArr(int n, int m);
void sortMatrix(int** mat, int* arr, int n, int m);
void sortArr(int* arr, int n, int m);
void clearMemoryMatrix(int** mat, int n);
void invertDiag(int** mat, int n, int m);
void swap(int* pa, int* pb);
void outputMatrix(int** mat, int n, int m);

int main()
{
    int n, m;
    InputStatus inputStatus = inputArrMatrix(&n, &m);
    if(inputStatus == INCORRECT_INPUT) {
        printf("Incorrect input");
    }
    else {
        int** mat = allocationMemoryMatrix(n, m);
        int* arr = allocationMemoryArr(n, m);
        if(mat == NULL)
            inputStatus = INCORRECT_INPUT;
        else {
            inputStatus = inputMatrix(mat, n, m);
            arr = createArr(mat, arr, n, m);
            sortArr(arr, n, m);
            sortMatrix(mat, arr, n, m);
            invertDiag(mat, n, m);
            outputMatrix(mat, m, m);
        }
        clearMemoryMatrix(mat, n);
        free(arr);
    }
    return inputStatus;
}
InputStatus inputArrMatrix(int* n, int* m) {
    InputStatus inputStatus = CORRECT_INPUT;
    if((scanf("%d %d", n, m) != CORRECT_ARR) || validation(n, m))
        inputStatus = INCORRECT_INPUT;
    return inputStatus;
}

InputStatus inputMatrix(int** mat, int n, int m) {
    InputStatus inputStatus = CORRECT_INPUT;
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j++) {
            if( !(scanf("%d", *(mat + i) + j ))) {
                inputStatus = INCORRECT_INPUT;
                break;
            }
        }
    }
    return inputStatus;
}

int validation(int* n, int* m) {
    return ((*n <= MIN_ARR) || (*m <= MIN_ARR) || (*n != *m));
}

int* allocationMemoryArr( int n, int m) {
    return (int*)calloc(m*n, sizeof(int));
}

int* createArr(int** mat, int* arr, int n, int m) {
    int currentArr = START_ARR;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            arr[currentArr] = mat[i][j];
            currentArr++;
        }
    }
    return arr;
}

int** allocationMemoryMatrix(int n, int m) {
    int** mat =(int**)calloc(n, sizeof(int*));
    if(mat != NULL) {
        for(int i = 0; i < n; i++) {
            mat[i] = (int*)calloc(m, sizeof(int));
            if(mat[i] == NULL) {
                clearMemoryMatrix(mat, i);
                mat = NULL;
                break;
            }
        }
    }
    return mat;
}

void clearMemoryMatrix(int** mat, int n) {
    int** endArr = mat + n;
    for(int** pCurrentArr = mat; pCurrentArr < endArr; pCurrentArr++)
        free(*pCurrentArr);
    free(mat);
}

void outputMatrix(int** mat, int n, int m) {
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

void swap(int* pa, int* pb) {
    int temp = *pa;
    *pa = *pb;
    *pb =temp;
}

void sortArr(int* arr, int n, int m) {
    int sizeArr = n*m;
    for(int i = 0; i < sizeArr - 1; i++) {
        for(int j = i + 1; j < sizeArr; j++) {
            if(*(arr + i) > *(arr+ j))
                swap(arr + i, arr + j);
        }
    }
}

void sortMatrix(int** mat, int* arr, int n, int m) {
    int numberDiag = START_NUMBER_DIAG;
    int sizeArr = n*n;
    for(int currentElemArr = 0; currentElemArr < sizeArr;) {
        for(int i = 0; i < n; i ++) {
            for(int j =0; j < m; j ++) {
                if(i+j == numberDiag) {
                    mat[i][j] = arr[currentElemArr];
                    currentElemArr++;
                }
            }
        }
        numberDiag++;
    }
}

void invertDiag(int** mat, int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(((i+j) %  2 == 0) && (i <= j))
                swap(*(mat + i) + j, *(mat + j) + i);
        }
    }
}

