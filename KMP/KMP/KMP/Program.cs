namespace KMP
{
    internal class Program
    {
        static List<int> KMP(string text, string pattern)
        {
            var result = new List<int>();
            var prefix = new int[pattern.Length];
            for (int i = 1,j; i < pattern.Length; i++)
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

            for (int i = 0,j=0; i < text.Length; i++)
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
