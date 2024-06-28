
# Role Hashing

Role Hashing is an efficient technique used to compute hashes of strings using a polynomial rolling hash method. This technique is particularly useful in string matching algorithms, substring searches, and detecting string equivalences efficiently.

## Table of Contents
1. [Introduction](#introduction)
2. [Implementation](#implementation)
3. [Functions](#functions)
4. [Usage](#usage)
5. [Conclusion](#conclusion)

## Introduction
In computer science, hashing is a technique used to uniquely identify objects, such as strings, using a hash function. A rolling hash is a special type of hash function that maintains the hash value of a sliding window over a sequence of data. This repository provides an implementation of Role Hashing using polynomial rolling hashes.

## Implementation
The implementation involves several key components:
- **Initialization**: Precomputing the powers of a base number `p` and their modular inverses.
- **Hash Calculation**: Computing hash values for strings and substrings.
- **Concatenation**: Combining hash values of multiple strings.

### Initialization
We precompute the powers of a prime number `p` and their modular inverses to optimize hash calculations. This is done using the `Init` function.

### Hash Calculation
The hash of a string is computed using a polynomial hash function. For a given string `s`, the hash is calculated as:

\[ \text{hash}(s) = \sum_{i=0}^{n-1} s[i] \cdot p^i \mod M \]

where \( p \) is a prime number and \( M \) is a large prime modulus.

### Concatenation
Hashes of concatenated strings can be efficiently computed by adjusting the second hash based on the length of the first string.

## Functions
Here are the primary functions provided in the Role Hashing implementation:

### Initialization Function
Initializes the precomputed arrays for powers of `p` and their inverses.
```cpp
#include<bits/stdc++.h>
using namespace std;

#define vc vector
#define ll long long
#define mod(n) ((n%mod)+mod)%mod
#define all(d) d.begin(), d.end()
#define sums(n) (((un ll)n*(n+1))/2)
#define mem(a,v) memset(a, v, sizeof(a))
#define u64 __int128

const ll Max=300002, p=1e6+7, p_inv=697740115819189258, M=999999999999999989;
u64 powers[Max], inv[Max];
vc<ll> Hashs[Max], lens;

void Init()
{
    powers[0] = inv[0] = 1;
    for(int i = 1; i < Max; i++)
    {
        powers[i] = p * powers[i-1] % M;
        inv[i] = p_inv * inv[i-1] % M;
    }
}
```

### RoleHashing Class
A class that handles the hashing operations for strings.

#### Constructor
Initializes the hash array for a given string.
```cpp
class RoleHashing {
    vc<ll> H;
    int length;

public:
    RoleHashing(string s)
    {
        H = vc<ll>(s.size());
        H[0] = s[0];
        length = s.size();
        for(int i = 1; i < length; i++)
        {
            u64 e = s[i];
            e *= powers[i];
            e += H[i-1];
            e %= M;
            H[i] = e;
        }
    }
```

#### GetSubstr
Computes the hash of a substring from index `l` to `r`.
```cpp
    ll GetSubstr(int l, int r)
    {
        u64 e = H[r];
        if(l)
            e -= H[l-1];
        e *= inv[l];
        e = (e % M + M) % M;
        return e;
    }
```

#### GetHash
Computes the hash of an entire string.
```cpp
    static ll GetHash(string s)
    {
        u64 e = 0, r;
        for(int i = 0; i < s.size(); i++)
        {
            r = powers[i] * s[i];
            e = (e + r) % M;
        }
        return e;
    }
```

#### Concat
Concatenates two hashes, adjusting the second hash based on the length of the first string.
```cpp
    static ll Concat(u64 h1, u64 h2, int l1)
    {
        h2 *= powers[l1];
        h2 += h1;
        h2 %= M;
        return h2;
    }
};
```

## Usage
Here is an example of how to use the Role Hashing implementation:

```cpp
#include "RoleHashing.h"

int32_t main()
{
    Init(); // Precompute powers and inverses of p.

    RoleHashing hasher("example");
    ll hashValue = hasher.GetHash("example");
    ll subHash = hasher.GetSubstr(0, 2);

    cout << "Hash of 'example': " << hashValue << endl;
    cout << "Hash of substring 'exa': " << subHash << endl;

    return 0;
}
```

## Conclusion
Role Hashing is a powerful technique for efficiently computing and managing string hashes. This implementation provides a robust foundation for integrating polynomial rolling hashes into various applications.

Feel free to explore the code and adapt it to your specific needs.
