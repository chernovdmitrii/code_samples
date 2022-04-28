'''
Given a string s consisting of some words separated by some number of spaces, return the length of the last word in the
string.
A word is a maximal substring consisting of non-space characters only.

Example 1:
Input: s = "Hello World"
Output: 5
Explanation: The last word is "World" with length 5.

Example 2:
Input: s = "   fly me   to   the moon  "
Output: 4
Explanation: The last word is "moon" with length 4.

Example 3:
Input: s = "luffy is still joyboy"
Output: 6
Explanation: The last word is "joyboy" with length 6.

Constraints:
1 <= s.length <= 10^4
s consists of only English letters and spaces ' '.
There will be at least one word in s.
'''


class Solution:
    def lengthOfLastWord_mine(self, s: str) -> int:
        s = s.split(' ')
        if '' in s:
            while '' in s:
                s.remove('')


        return len(s[len(s) - 1])

    def lengthOfLastWord(self, s: str) -> int:
        length: int = 0
        i = len(s) - 1

        while s[i] == ' ':
            i -= 1

        while s[i] != ' ' and i >= 0:
           length += 1
           i -= 1

        return length


if __name__ == '__main__':
    slt = Solution()
    print(slt.lengthOfLastWord("Hello World"))
    print(slt.lengthOfLastWord("   fly me   to   the moon  "))
    print(slt.lengthOfLastWord("luffy is still joyboy"))
    print(slt.lengthOfLastWord('a'))
