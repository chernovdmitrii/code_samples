'''
Write a function to find the longest common prefix string amongst an array of strings.
If there is no common prefix, return an empty string "".

Example 1:
Input: strs = ["flower","flow","flight"]
Output: "fl"

Example 2:
Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.


Constraints:
1 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] consists of only lower-case English letters.

https://www.geeksforgeeks.org/longest-common-prefix-using-sorting/
'''
from typing import List


class Solution:
    def longestCommonPrefix_mine(self, strs: List[str]) -> str:
        word = min(strs)
        prefix = ''
        for i, char in enumerate(word):
            length = 0
            for word in strs:
                if len(word) != 0:
                    if word[i] == char:
                        length += 1
                    else:
                        break
            if length != len(strs):
                break
            else:
                prefix += char

        return prefix


if __name__ == '__main__':
    slt = Solution()
    print(slt.longestCommonPrefix_mine(["flower", "flow", "flight"]))
    print(slt.longestCommonPrefix_mine(["dog", "racecar", "car"]))
    print(slt.longestCommonPrefix_mine([""]))
    print(slt.longestCommonPrefix_mine(["", "b"]))
    print(slt.longestCommonPrefix_mine(["ab", "a"]))
