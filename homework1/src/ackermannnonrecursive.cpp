int A(int m,int n)
{
    int s[100000];
    int top=0;

   
    s[top]=m;

    while (top>=0)
    {
        
        m=s[top];
        top--;

        if (m==0)
        {
            n=n+1;
        }
        else if (n==0)
        {
            n=1;
            top++;
            s[top]=m-1;
        }
        else
        {
            n=n-1;

            top++;
            s[top]=m-1;

            top++;
            s[top]=m;
        }
    }

    return n;
}

int main()
{
    int m,n;

    cout<<"請輸入 m 和 n：";
    cin >>m>>n;

    cout<<A(m,n)<<endl;

    return 0;
}
