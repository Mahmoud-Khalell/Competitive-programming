
# Suffix Array Explanation

A **suffix array** is a powerful data structure that provides a systematic way to store and access all the suffixes of a string in sorted order. This is extremely useful in various string processing algorithms, including substring search, pattern matching, and more. Below, I will explain the suffix array, its construction, and its applications.

## What is a Suffix Array?

A suffix array for a string `S` of length `n` is an array of integers that represents the starting positions of the suffixes of `S` in lexicographical order.

For example, consider the string `S = "banana"`. The suffixes of `S` are:

1. `banana`
2. `anana`
3. `nana`
4. `ana`
5. `na`
6. `a`

When sorted in lexicographical order, the suffix array would be `[5, 3, 1, 0, 4, 2]`.

## Suffix Array Construction Algorithm

The following code constructs the suffix array for a given string `Text`. The suffix array is a sorted array of all suffixes of `Text`, represented by their starting positions. The construction uses sorting and ranking to achieve this.

### Key Concepts

1. **Rank Array**: An array that holds the rank (lexicographical order) of suffixes starting at each position.
2. **Temporary Rank Array**: A temporary array used during the ranking update process.
3. **Suffix Array**: The main array that holds the starting positions of the suffixes in sorted order.
4. **Comparison Function**: A custom comparator to sort the suffixes based on their current ranks and additional comparison for the next segment of the suffix.

### Code Explanation

```cpp
#include<bits/stdc++.h>
using namespace std;
#define all(d) d.begin(), d.end()

vector<int> Rank;      // Rank array
vector<int> TempRank;  // Temporary rank array
vector<int> Suffixes;  // Suffix array
int Length;            // Length of the text

// Custom comparator struct
struct comp {
    int h;
    comp(int H) { h = H; }

    bool operator()(int a, int b) {
        if (Rank[a] != Rank[b])
            return Rank[a] < Rank[b];
        int r1 = (a + h < Length) ? Rank[a + h] : -1;
        int r2 = (b + h < Length) ? Rank[b + h] : -1;
        return r1 < r2;
    }
};

// Function to build the suffix array
void BuildSuffixArray(string &Text) {
    Length = Text.size();
    Rank = TempRank = Suffixes = vector<int>(Length);

    for (int i = 0; i < Length; i++) {
        Suffixes[i] = i;
        Rank[i] = Text[i];
    }

    sort(all(Suffixes), comp(0));  // Initial sort based on first character

    for (int i = 1; i < Length; i <<= 1) {
        sort(all(Suffixes), comp(i));  // Sort based on first 2^i characters

        for (int e = 1; e < Length; e++)
            TempRank[e] = TempRank[e - 1] + comp(i)(Suffixes[e - 1], Suffixes[e]);

        for (int e = 0; e < Length; e++)
            Rank[Suffixes[e]] = TempRank[e];
    }
}

int32_t main() {
    string s = "abracadabra";
    cout << "Suffix array for Text \"" << s << "\": ";
    BuildSuffixArray(s);
    for (auto item : Suffixes)
        cout << item << ' ';
}
```

### Steps in the Algorithm

1. **Initialization**:
    - The `Rank`, `TempRank`, and `Suffixes` arrays are initialized to the size of the text.
    - Each suffix starting index is stored in the `Suffixes` array.
    - The initial rank for each character is assigned based on its ASCII value.

2. **Sorting**:
    - The suffixes are initially sorted based on the first character.
    - For each iteration, the suffixes are sorted based on the first `2^i` characters using the custom comparator `comp`.
    - The `comp` comparator compares the ranks of the suffixes and uses an additional comparison for the next segment of length `h`.

3. **Ranking Update**:
    - After sorting, the `TempRank` array is updated to reflect the new ranks of the suffixes.
    - The `Rank` array is updated using the values from `TempRank`.

4. **Result**:
    - The final suffix array contains the starting positions of the sorted suffixes.

### Example: "abracadabra"

Let's see how the algorithm works for the string `"abracadabra"`:

- **Initial Suffixes**:
    1. `abracadabra`
    2. `bracadabra`
    3. `racadabra`
    4. `acadabra`
    5. `cadabra`
    6. `adabra`
    7. `dabra`
    8. `abra`
    9. `bra`
    10. `ra`
    11. `a`

- **Sorted Suffixes**:
    1. `a`
    2. `abra`
    3. `abracadabra`
    4. `acadabra`
    5. `adabra`
    6. `bra`
    7. `bracadabra`
    8. `cadabra`
    9. `dabra`
    10. `ra`
    11. `racadabra`

- **Suffix Array**: `[10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2]`

This suffix array represents the starting positions of the suffixes in sorted order.

