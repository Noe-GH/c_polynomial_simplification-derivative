#include <stdio.h>
#include <stdlib.h>

struct polynomial
{
    int base;
    int exponent;
    struct polynomial * ptrNext;
};

typedef struct polynomial Polynomial;
typedef Polynomial* ptrPolynomial;

void main_menu();
void push(ptrPolynomial *ptrListTop, int b, int e);
void pop(ptrPolynomial *ptrListTop);
void sort(ptrPolynomial ptrListTop);
void print_poly(ptrPolynomial ptrListTop);
void get_derivative(ptrPolynomial ptrListTop);

int main(int argc, char **argv)
{
    ptrPolynomial ptrTop=NULL;
    int Option;
    int b, e;
    printf("This code simplifies a polynomial and gets its derivative.\n\n");
    
    main_menu();
    scanf("%i", &Option);
    printf("\n");
    while(Option != 6)
    {
        switch(Option)
        {
            case 1:
                printf("Type the base of the polynomial:\n");
                scanf("%i", &b);
                printf("Type the exponent of the polynomial\n");
                scanf("%i", &e);
                push(&ptrTop, b, e);
                printf("\n");
                print_poly(ptrTop);
                main_menu();
                break;
            
            case 2:
                if(ptrTop!=NULL)
                {
                    pop(&ptrTop);
                    printf("The top element has been deleted.\n");
                    printf("/n");
                    print_poly(ptrTop);
                }
                else
                {
                    printf("\nThe list is empty.\n\n");
                }
                printf("\n");
                main_menu();
                break;

            case 3:
                if (ptrTop!=NULL)
                {
                    sort(ptrTop);
                    print_poly(ptrTop);
                }
                else
                {
                    printf("\nThe list is empty.\n\n");
                }
                printf("\n");
                main_menu();
                break;

            case 4:
                if (ptrTop!=NULL)
                {
                    print_poly(ptrTop);
                }
                else
                {
                    printf("\nThe list is empty.\n\n");
                }
                printf("\n");
                main_menu();
                break;
            
            case 5:
                if (ptrTop!=NULL)
                {
                    get_derivative(ptrTop);
                }
                else
                {
                    printf("\nThe list is empty.\n\n");
                }
                printf("\n");
                main_menu();
                break;
            
            case 6:
                break;
                
            default:
                printf("\nUnavailable option\n");
                printf("\n");
                main_menu();
                break;
        }
        scanf("%i", &Option);
        printf("\n");
    }
    printf("Program closed.\n");
    printf("\n");
    
	return 0;
}

void main_menu()
{
    printf("Type an option of the menu:\n\n");
    printf("1. Type a term for the polynomial\n");
    printf("2. Delete the top term of the polynomial\n");
    printf("3. Reduce and order the polynomial\n");
    printf("4. Print the polynomial\n");
    printf("5. Get the derivative of the polynomial\n");
    printf("6. Close program\n");
    printf("\n");
}

void push(ptrPolynomial *ptrListTop, int b, int e)
{
    ptrPolynomial ptrNew;
    ptrNew = (ptrPolynomial)malloc(sizeof(Polynomial));
    
    if(ptrNew != NULL)
    {
        ptrNew -> base = b;
        ptrNew -> exponent = e;
        ptrNew -> ptrNext = *ptrListTop;
        *ptrListTop = ptrNew;
    }
    else
    {
        printf("It was not possible to assign memory space.");
    }
}

void pop(ptrPolynomial *ptrListTop)
{
    ptrPolynomial ptrTemp;
    ptrTemp = *ptrListTop;
    *ptrListTop = (*ptrListTop)->ptrNext;
    free(ptrTemp);
}

void sort(ptrPolynomial ptrListTop)
{
    ptrPolynomial ptrPivot;
    ptrPolynomial ptrPrev;
    ptrPolynomial ptrComp;
    ptrPolynomial ptrTemp;
    int b;
    int e;
    
    // Reducing algorithm
    ptrPivot = ptrListTop;
    while(ptrPivot != NULL)
    {
        ptrPrev = ptrPivot;
        ptrComp = ptrPivot->ptrNext;
        
        while(ptrComp!=NULL)
        {
            if((ptrPivot->exponent)==(ptrComp->exponent))
            {
                (ptrPivot->base)=(ptrPivot->base)+(ptrComp->base);
                ptrTemp=ptrComp;
                ptrComp=ptrComp->ptrNext;
                ptrPrev->ptrNext=ptrComp;
                free(ptrTemp);
            }
            else
            {
                ptrPrev=ptrPrev->ptrNext;
                ptrComp=ptrComp->ptrNext;
            }
        }
        ptrPivot=ptrPivot->ptrNext;
    }

    // Sorting algorithm
    ptrPivot=ptrListTop;
    while(ptrPivot!=NULL)
    {
        ptrComp=ptrPivot->ptrNext;
        while(ptrComp!=NULL)
        {
            if( (ptrPivot->exponent) < (ptrComp->exponent) )
            {
                b=ptrPivot->base;
                e=ptrPivot->exponent;
                ptrPivot->base=ptrComp->base;
                ptrPivot->exponent=ptrComp->exponent;
                ptrComp->base=b;
                ptrComp->exponent=e;
            }
            ptrComp=ptrComp->ptrNext;
        }
        ptrPivot=ptrPivot->ptrNext;
    }
}

void print_poly(ptrPolynomial ptrListTop)
{
    ptrPolynomial ptrTemp;
    ptrTemp = ptrListTop;
    printf("The polynomial is:\n");
    while(ptrTemp!=NULL)
    {
        if(ptrTemp->base>=0)
        {
            printf(" +");
        }
        printf("%ix^%i", ptrTemp->base, ptrTemp->exponent);
        ptrTemp=ptrTemp->ptrNext;
    }
    printf("\n\n");
    
}

void get_derivative(ptrPolynomial ptrListTop)
{
    ptrPolynomial ptrTemp;
    ptrTemp = ptrListTop;
    printf("The derivative of the polynomial is:\n");
    while(ptrTemp!=NULL)
    {
        if(((ptrTemp->base)*(ptrTemp->exponent))>=0)
        {
            printf(" + ");
        }
        printf("%ix^%i", (ptrTemp->base)*(ptrTemp->exponent), ptrTemp->exponent-1);
        ptrTemp=ptrTemp->ptrNext;
    }
    printf("\n\n");
}

