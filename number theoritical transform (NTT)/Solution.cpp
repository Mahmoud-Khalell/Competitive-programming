#include<bits/stdc++.h>
using namespace std;
#define el "\n"
#define vc vector
#define st string
#define un unsigned
#define ll long long
#define mod(n) ((n%mod)+mod)%mod
#define all(d) d.begin(), d.end()
#define rt(x) return void(cout<<x)
#define sums(n) (((un ll)n*(n+1))/2)
#define findd(s,v) (s.find(v)!=s.end())
#define mem(a,v) memset(a, v, sizeof(a))
#define u64 __int128
#define pl pair<ll,ll>
#define sum1 prefix[idx][i]
#define sp " "
#define vl vc<ll>
#define u64 __int128
u64 mod ;
u64 root ;
u64 root_1;
u64 root_pw = 1 << 23;
u64 mod1 = 30399297484750849;
u64 root1= 29554659083839571;
u64 root1_inv = 3349232486765879;
u64 mod2=31525197391593473;
u64 root2=13470042694718571;
u64 root2_inv=5382157027391508;
u64 fast(u64 base, u64 power,u64 mod)
{
    u64 res=1;
    while(power)
    {
        if(power&1)
            res=res*base%mod;
        base=base*base%mod;
        power>>=1;
    }
    return res;

}

void fft(vector<u64> & a, bool invert)
{
    u64 n = a.size();

    for (u64 i = 1, j = 0; i < n; i++)
    {
        u64 bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (u64 len = 2; len <= n; len <<= 1)
    {
        u64 wlen = invert ? root_1 : root;
        for (u64 i = len; i < root_pw; i <<= 1)
            wlen =  wlen * wlen % mod;

        for (u64 i = 0; i < n; i += len)
        {
            u64 w = 1;
            for (u64 j = 0; j < len / 2; j++)
            {
                u64 u = a[i+j], v =  a[i+j+len/2] * w % mod;
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w =  w * wlen % mod;
            }
        }
    }

    if (invert)
    {
        u64 n_1 = fast(n,mod-2,mod);
        for (u64 & x : a)
            x =  x * n_1 % mod;
    }
}

vector<u64> multiply(vector<u64>  a, vector<u64>  b)
{
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    a.resize(n);
    b.resize(n);

    fft(a, false);
    fft(b, false);
    for (int i = 0; i < n; i++)
        a[i] =a[i]*b[i]%mod;
    fft(a, true);

    return a;
}
u64 FinalMod(u64 a,u64 b,u64 mod)
{
    /* T=a%root1 =x*root1+a
       T=b%root2 =y*root2+b
       x*root1+a ==y*root2+b
       x root1-y*root2 =b-a;
       x= (b-a) * 1297649945016098
       then T = (b-a)*1297649945016098 +a

    */

    a%=mod;
    b%=mod;
    ll x=1297649945016098%mod;
    ll x0=x*(b-a);
    ll n=root1%mod;
    x0=(x0%mod+mod)%mod;
    return (x0*n+a)%mod;
}
vc<u64> FinalMultiply(vc<u64>&a,vc<u64>&b)
{
    mod=mod1;
    root=root1;
    root_1=root1_inv;
    vc<u64>w=multiply(a,b);

    mod=mod2;
    root=root2;
    root_1=root2_inv;
    vc<u64>w2=multiply(a,b);

    for(int i=0;i<w.size();i++)
        w[i]=FinalMod(w[i],w2[i],1e9+7);

    return w;
}
int main()
{


    vc<u64> w={1,2,3},ee={2,3,3};
    w=FinalMultiply(w,ee);
    for(ll i:w)
        cout<<i<<sp;

}
