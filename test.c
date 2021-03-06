int fib(int n)
{
    if (n > 1)
        return fib(n - 1) + fib(n - 2);
    else
        return 1;
}

float pi(int n)
{
    float sum = 0;
    float sig = 1.0;
    for (int i = 1; i <=n; i += 2)
    {
        sum += sig/i;   
        sig = 0-sig;
    }  
    return sum;
}

int main()
{
    int iarr[] = {1, 3, 5, 7};
    float farr[] = {1.1, 2.2, 3.3};
    for (int i = 0; i < 3; ++i)
    {
        print(iarr[i]);
        print(farr[i]);
    }
    print(iarr[3]);
    print(fib(iarr[1]));
    print(pi(255)*4);
    return 0;
}