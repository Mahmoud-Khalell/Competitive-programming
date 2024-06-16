
# Knuth-Morris-Pratt (KMP) Algorithm

<p style="font-size:18px;">
The Knuth-Morris-Pratt (KMP) algorithm is a string searching algorithm that searches for occurrences of a "pattern" within a "text" by employing the observation that when a mismatch occurs, the pattern itself embodies sufficient information to determine where the next match could begin, thus bypassing re-examination of previously matched characters.
</p>

## How It Works

<p style="font-size:18px;">
The KMP algorithm works in two main phases:
</p>

1. **Preprocessing the Pattern:**
    <p style="font-size:18px;">
    - **Prefix Function (LPS Array):** We preprocess the pattern to create an array of the longest proper prefix which is also a suffix (LPS array). This array is used to skip characters while matching.
    </p>

2. **Searching the Text:**
    <p style="font-size:18px;">
    - We use the LPS array to find the pattern in the text efficiently by skipping characters in the text and pattern when a mismatch occurs.
    </p>

## Code Explanation

<p style="font-size:18px;">
Here's a brief explanation of the code:
</p>

### KMP Algorithm Implementation

```csharp
namespace KMP
{
    internal class Program
    {
        static List<int> KMP(string text, string pattern)
        {
            var result = new List<int>();
            var prefix = new int[pattern.Length];
            for (int i = 1, j; i < pattern.Length; i++)
            {
                j = prefix[i - 1];
                while (j > 0 && pattern[i] != pattern[j])
                {
                    j = prefix[j - 1];
                }
                if (pattern[i] == pattern[j])
                {
                    j++;
                }
                prefix[i] = j;
            }

            for (int i = 0, j = 0; i < text.Length; i++)
            {
                while (j > 0 && text[i] != pattern[j])
                {
                    j = prefix[j - 1];
                }
                if (text[i] == pattern[j])
                {
                    j++;
                }
                if (j == pattern.Length)
                {
                    result.Add(i - j + 1);
                    j = prefix[j - 1];
                }
            }
            return result;
        }

        static void Main(string[] args)
        {
            var text = "abxabcabcaby";
            var pattern = "ab";
            var result = KMP(text, pattern);
            foreach (var item in result)
            {
                Console.WriteLine(item);
            }
        }
    }
}
```

### Usage

1. **Compute LPS Array:**
    ```csharp
    var prefix = new int[pattern.Length];
    for (int i = 1, j; i < pattern.Length; i++)
    {
        j = prefix[i - 1];
        while (j > 0 && pattern[i] != pattern[j])
        {
            j = prefix[j - 1];
        }
        if (pattern[i] == pattern[j])
        {
            j++;
        }
        prefix[i] = j;
    }
    ```

2. **Search Text:**
    ```csharp
    for (int i = 0, j = 0; i < text.Length; i++)
    {
        while (j > 0 && text[i] != pattern[j])
        {
            j = prefix[j - 1];
        }
        if (text[i] == pattern[j])
        {
            j++;
        }
        if (j == pattern.Length)
        {
            result.Add(i - j + 1);
            j = prefix[j - 1];
        }
    }
    ```

3. **Output Results:**
    ```csharp
    var text = "abxabcabcaby";
    var pattern = "ab";
    var result = KMP(text, pattern);
    foreach (var item in result)
    {
        Console.WriteLine(item);
    }
    ```

## Conclusion

<p style="font-size:18px;">
The KMP algorithm is efficient for string searching, with a time complexity of O(n) for searching, where n is the length of the text. The preprocessing phase (LPS array computation) also runs in O(m) time, where m is the length of the pattern. This implementation in C# demonstrates the core concepts of pattern preprocessing and efficient searching using the KMP algorithm.
</p>

