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
    for(int i = 0; i < 3; i++)
    {
       print(iarr[i]);
       print(farr[i]);
    }
    print(iarr[3]);
    pi(iarr[2]);
    return 0;
}