#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <time.h>

double drawvariable(double interval[], long int drawarray[],int lendraw, long int expnum);
double evaluation(char arr[],int len,void *intervals,int sizeint,void *drawarray,char variables[],long int expnum);
char * postfix_conversion(char arr[],int len);
void pop_element(char st[], char fin[]);
void push_element(char arr[], char pushed);
int has_higher_precedence(char st,char x);
int is_oporfun(char x);
int get_value(char x);
int is_right_associative(char x);
int whatary(char x);
double binaryeval(char op, double x, double y);
void doublepusher(double x[],double num,int len);
double doublepoper(double x[],int len);
double unaryeval(char op, double x);


int main()
{
    char formula[200],variables[30];
    char *postfix;
    int intervalnum,lenformula,lenpostfix,i,variablenum=0,j,k;
    long int expnum,n,*tempresults,**drawarray;
    char letterarr[29]="\0";
    double max=-DBL_MAX,min=DBL_MAX, return_result;
    double *lowlimits,* upplimits,*outputintervals,*expresults,**probabilities,**intervals;
    fgets(formula,200,stdin);
    lenformula=strlen(formula);
    formula[lenformula-1]=0;
    for (i = 0; i < lenformula; ++i) {
        if(formula[i]>= 'A' && formula[i]<= 'Z') {
            if(letterarr[formula[i]-'A']==1)
                continue;
            else{
                letterarr[formula[i]-'A']=1;
                variablenum++;
            }
        }
    }
    scanf("%d %ld",&intervalnum,&expnum);
    lowlimits=malloc(variablenum*sizeof(double));
    upplimits=malloc(variablenum*sizeof(double));
    probabilities=malloc(variablenum*sizeof(double*));
    for ( i = 0; i < variablenum; ++i)
        probabilities[i]=malloc((intervalnum+2)*sizeof(double));
    for (i = 0; i < variablenum; ++i) {
        scanf(" %c",&variables[i]);
        scanf(" %lf %lf", &lowlimits[i], &upplimits[i]);
        for (j = 0; j < intervalnum;++j) {
            scanf(" %lf", &probabilities[i][j]);
        }
    }
    drawarray=malloc(variablenum*sizeof(long int*));
    for ( i = 0; i < variablenum; ++i)
        drawarray[i]=malloc((intervalnum)*sizeof(long int));
    for (i = 0; i < variablenum; ++i) {
        for (j = 0; j < intervalnum; ++j) {
            drawarray[i][j]=(long int)(expnum*probabilities[i][j]);
        }
    }
    intervals=malloc(variablenum*sizeof(double*));
    for ( i = 0; i < variablenum; ++i)
        intervals[i]=malloc((intervalnum+1)*sizeof(double));
    for (i = 0,j = 0; i < variablenum; ++i) {
        intervals[i][j]=lowlimits[i];
    }

    for (i = 0; i < variablenum; ++i) {
        for (j = 1,k = 0; j < intervalnum+1; ++j,++k) {
            intervals[i][j]=intervals[i][k]+((upplimits[i]-lowlimits[i])/intervalnum);
        }
    }

    postfix=postfix_conversion(formula,lenformula);
    lenpostfix=strlen(postfix);
    for (n = 0; n < expnum; ++n) {
        if(max<(return_result = evaluation(postfix,lenpostfix,intervals,intervalnum+1,drawarray,variables,expnum)))
        {
            max=return_result;
            continue;
        }
        else if(min>return_result)
        {
            min=return_result;
            continue;
        }
        else
            continue;
    }
    outputintervals=malloc((intervalnum+1)*sizeof(double));
    outputintervals[0]=min;
    for (i = 1, j = 0; i < intervalnum+1;++j, ++i)
        outputintervals[i]=outputintervals[j]+((max-min)/intervalnum);

    tempresults=malloc(intervalnum*sizeof(long int));
    for (i = 0; i < intervalnum+1; ++i) {
        tempresults[i]=0;
    }
    for (n = 0; n < expnum; ++n) {
        for (j = 0; j < intervalnum+1; ++j) {
            if(evaluation(postfix,lenpostfix,intervals,intervalnum+1,drawarray,variables,expnum)<outputintervals[j])
            {
                tempresults[j]+=1;
                break;
            }
            else
                continue;
        }
    }
    expresults=malloc(intervalnum*sizeof(double));
    for (i = 0; i < intervalnum+1; ++i) {
        expresults[i]=(double)tempresults[i]/expnum;
    }
    printf("%f %f ",min,max);
    for (i = 0; i < intervalnum; ++i) {
        printf("%f ",expresults[i]);
    }
    free(outputintervals);
    free(expresults);
    free(upplimits);
    free(lowlimits);
    free(postfix);
    free(tempresults);
    free(intervals);
    free(drawarray);
    free(probabilities);
    return 0;
}

double drawvariable(double interval[], long int drawarray[],int lendraw, long int expnum)
{
    int index=0,i;
    long int randihtimal,sum=drawarray[0];
    double upper,lower,result=0.0;
    randihtimal=rand()%(expnum);
    for (i = 0; i < lendraw; ++i)
    {
        if(randihtimal<=sum)
        {
            index=i;
            upper = interval[index];
            lower = interval[index-1];
            result= (upper - lower) * ((double)rand()/(double)RAND_MAX) + lower;
            break;
        }
        else
        {
            index += 1;
            sum+=drawarray[i+1];
            continue;
        }
    }
    return result;
}

double evaluation(char arr[],int len,void *intervals,int sizeint,void *drawarray,char variables[],long int expnum)
{
    int i, j,indexnumbers=0,lenvar=strlen(variables);
    double **intervalss, *ptr1;
    long int **drawarrayy, *ptr2;
    double numbers[200] = {0}, num1, num2,*temp;
    temp=malloc(lenvar*sizeof(double));
    for (i = 0; i < lenvar; ++i)
        temp[i]=0;
    intervalss = malloc(sizeint * sizeof(double *));
    drawarrayy = malloc((sizeint-1) * sizeof(long int *));
    ptr1 = intervals;
    ptr2 = drawarray;
    for (i = 0; i < sizeint; ++i)
        intervalss[i] = ptr1 + i * sizeint;
    for (i = 0; i < sizeint-1; ++i)
        drawarrayy[i] = ptr2 + i * (sizeint-1);
    for (i = 0; i <= len-1; ++i) {
        if(((arr[i] >= '0' && arr[i] <= '9')&&(arr[i-1] >= '0' && arr[i-1] <= '9')) || arr[i]=='.' || arr[i-1]=='.')
            continue;
        else if(is_oporfun(arr[i]))
        {
            if(whatary(arr[i]))
            {
                num2=doublepoper(numbers,indexnumbers);
                indexnumbers--;
                num1=doublepoper(numbers,indexnumbers);
                indexnumbers--;
                doublepusher(numbers,binaryeval(arr[i],num1,num2),indexnumbers);
                indexnumbers++;
            }
            else
            {
                num1=doublepoper(numbers,indexnumbers);
                indexnumbers--;
                doublepusher(numbers,unaryeval(arr[i],num1),indexnumbers);
                indexnumbers++;
            }
        }
        else if(arr[i]==' ')
            continue;
        else {
            if((arr[i] >= '0' && arr[i] <= '9')){
                doublepusher(numbers, atof(&arr[i]),indexnumbers);
                indexnumbers++;
            }
            else
            {
                for (j = 0; j < 30; ++j) {
                    if(arr[i]==variables[j]) {
                        if (temp[j]!=0)
                        {
                            doublepusher(numbers,temp[j],indexnumbers);
                            indexnumbers++;
                        }
                        else{
                            temp[j]=drawvariable(intervalss[j], drawarrayy[j], sizeint-1,expnum);
                            doublepusher(numbers,temp[j],indexnumbers);
                            indexnumbers++;
                        }
                    }
                }
            }
        }
    }
    free(intervalss);
    free(drawarrayy);
    free(temp);
    return numbers[0];
}

char * postfix_conversion(char arr[],int len)
{
    char *final=calloc(200,1);
    char stack[200]="";
    int i,lenstack,lenfinal,k,stackindex=0,j,u=0,l,lenf;
    for (i = 0; i <= len-1; ++i) {
        if( u!=0 && !((arr[i] >= '0' && arr[i] <= '9') || arr[i]=='.')) {
            final[strlen(final)] = ' ';
            u=0;
        }
        if(arr[i]==' ' || arr[i]=='i' || arr[i]=='n' || arr[i]=='q' || arr[i]=='r' || arr[i]=='t' || arr[i]=='o')
            continue;
        else if(arr[i]=='s')
        {
            if(arr[i+1]=='i')
                arr[i]='m';
            else if(arr[i+1]=='q')
                arr[i]='p';
            else
                continue;
        }
        if(arr[i]=='.')
            push_element(final, arr[i]);
        else if(is_oporfun(arr[i]))
        {
            if(stackindex==0) {
                stack[stackindex] = arr[i];
                ++stackindex;
            }
            else {
                if(arr[i]=='(') {
                    push_element(stack, arr[i]);
                    ++stackindex;
                }
                else if(arr[i]==')')
                {
                    for (j = stackindex-1; j > -1; --j) {
                        if(stack[j]=='(') {
                            stack[j] = 0;
                            --stackindex;
                            break;
                        }
                        else {
                            pop_element(stack, final);
                            --stackindex;
                        }
                    }
                }
                else if(has_higher_precedence(stack[stackindex - 1], arr[i])) {
                    for (l = stackindex; l >=0; --l) {
                        if(l-1<0)
                        {
                            push_element(stack, arr[i]);
                            ++stackindex;
                            break;
                        }
                        else if (has_higher_precedence(stack[l-1], arr[i])) {
                            pop_element(stack, final);
                            stack[l-1]=0;
                            --stackindex;
                        }
                        else {
                            push_element(stack, arr[i]);
                            ++stackindex;
                            break;
                        }
                    }
                }
                else {
                    push_element(stack, arr[i]);
                    ++stackindex;
                }
            }
        }
        else
        {
            if(arr[i+1]=='.' || final[strlen(final)-1]=='.' || ((arr[i] >= '0' && arr[i] <= '9')&&(arr[i+1] >= '0' && arr[i+1] <= '9')) || ((arr[i] >= '0' && arr[i] <= '9')&&(arr[i-1] >= '0' && arr[i-1] <= '9')))
            {
                ++u;
                push_element(final,arr[i]);
            }
            else {
                push_element(final, arr[i]);
                lenf=strlen(final);
                final[lenf]=' ';
            }
        }
    }
    lenstack=strlen(stack);
    lenfinal=strlen(final);
    if(final[lenfinal-1] >= '0' && final[lenfinal-1] <= '9')
        final[lenfinal]=' ';
    lenfinal=strlen(final);
    for (i = lenstack,k=0; i > 0; ++k,--i) {
        final[lenfinal+k]=stack[i-1];
    }
    return final;
}

void doublepusher(double x[],double num ,int len)
{
    x[len]=num;
    return;
}

double doublepoper(double x[],int len)
{
    double temp;
    if(len==0) {
        temp = x[len];
        x[len] = 0;
    }
    else
    {
        temp=x[len-1];
        x[len-1]=0;
    }
    return temp;
}

double binaryeval(char op, double x, double y)
{
    double result=0.0;
    switch (op)
    {
        case '+':
            result=x+y;
            break;
        case '*':
            result=x*y;
            break;
        case '/':
            result=x/y;
            break;
        case '-':
            result=x-y;
            break;
        case '^':
            result=pow(x,y);
            break;
        default:
            break;
    }
    return result;
}

double unaryeval(char op, double x)
{
    double result=0.0;
    switch (op)
    {
        case '~':
            result=-x;
            break;
        case 'l':
            result=log(x);
            break;
        case 'c':
            result=cos(x);
            break;
        case 'm':
            result=sin(x);
            break;
        case 'p':
            result=sqrt(x);
            break;
        default:
            break;
    }
    return result;
}

int is_oporfun(char x)
{
    if(x=='/' || x=='*' || x=='+' || x=='-' || x=='^' || x=='~' || x=='l' || x=='c' || x=='m' || x=='(' || x==')' || x=='p')
        return 1;
    else
        return 0;
}

int whatary(char x)
{
    if(x=='/' || x=='*' || x=='+' || x=='-' || x=='^')
        return 1;
    else
        return 0;
}

void pop_element(char st[], char fin[])
{
    int lenst=strlen(st),lenfin=strlen(fin);
    if(lenfin==200)
        return;
    else {
        fin[lenfin] = st[lenst - 1];
        st[lenst - 1] = 0;
    }
}

void push_element(char arr1[], char pushed)
{
    int len1=strlen(arr1);
    if(len1==0) {
        arr1[0] = pushed;
        return;
    }
    else if(len1==200)
        return;
    else
        arr1[len1]=pushed;
}

int get_value(char x)
{
    int valuex=0;
    switch (x)
    {
        case 'm':
            valuex=4;
            break;
        case 'c':
            valuex=4;
            break;
        case 'p':
            valuex=4;
            break;
        case 'l':
            valuex=4;
            break;
        case '~':
            valuex=4;
            break;
        case '^':
            valuex=3;
            break;
        case '*':
            valuex=2;
            break;
        case '/':
            valuex=2;
            break;
        case '+':
            valuex=1;
            break;
        case '-':
            valuex=1;
            break;
        case '(':
            valuex=0;
        default:
            break;
    }
    return valuex;
}

int has_higher_precedence(char op1,char op2)
{
    int value1=get_value(op1),value2=get_value(op2);
    if(value1==value2)
    {
        if(is_right_associative(op1))
            return 0;
        else
            return 1;
    }
    else
        return value1 > value2 ? 1:0;
}

int is_right_associative(char x)
{
    return x=='^' ? 1:0;
}






