'''
Given an integer x, return true if x is palindrome integer.

An integer is a palindrome when it reads the same backward as forward.

For example, 121 is a palindrome while 123 is not.


Example 1:

Input: x = 121
Output: true
Explanation: 121 reads as 121 from left to right and from right to left.
Example 2:

Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
Example 3:

Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
'''


class Solution:
    # non constant space
    def isPalindrome(self, x: int) -> bool:

        x = [i for i in str(x)]
        start = 0
        end = len(x) - 1
        while end > start:
            if x[start] == x[end]:
                start += 1
                end -= 1
            else:
                return False
        return True

    # constant space
    def isPalindrome_solved(self, x: int) -> bool:
        if x < 0 and (x % 10 == 0 and x != 0):
            return False

        revertedNumber = 0
        while x > revertedNumber:
            revertedNumber = revertedNumber * 10 + x % 10
            x //= 10

        return x == revertedNumber or x == revertedNumber // 10

if __name__ == '__main__':
    slt = Solution()
    print(slt.isPalindrome(-121))
    print(slt.isPalindrome_solved(121))
