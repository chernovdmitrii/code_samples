'''
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.


Example 1:

Input: s = "()"
Output: true
Example 2:

Input: s = "()[]{}"
Output: true
Example 3:

Input: s = "(]"
Output: false
'''


class Solution:
    def isValid(self, s: str) -> bool:
        brackets_pairs = {')': '(',
                          ']': '[',
                          '}': '{'}
        opening = {'(', '[', '{'}
        closing = {')', ']', '}'}

        stack = []
        for char in s:
            if char in opening:
                stack.append(char)
            if char in closing:
                if not stack:
                    return False
                elif stack.pop() != brackets_pairs[char]:
                    return False

        if not stack:
            return True
        else:
            return False


if __name__ == '__main__':
    slt = Solution()
    print(slt.isValid('()'))
    print(slt.isValid('()[]{}'))
    print(slt.isValid('{[]}'))
    print(slt.isValid('([)]'))
