'''
Given a non-negative integer x, compute and return the square root of x.

Since the return type is an integer, the decimal digits are truncated, and only the integer part of the result is
returned.

Note: You are not allowed to use any built-in exponent function or operator, such as pow(x, 0.5) or x ** 0.5.

Example 1:
Input: x = 4
Output: 2

Example 2:
Input: x = 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since the decimal part is truncated, 2 is returned.


Constraints:
0 <= x <= 2^31 - 1
'''


class Solution:
    def mySqrt(self, x: int) -> int:
        eps = 0.1
        current_eps = 10
        guess = 1
        guess_n1 = 1

        while current_eps > eps:
            guess = guess_n1
            guess_n1 = 0.5 * (guess + (x / guess))
            current_eps = abs(guess_n1 - guess)

        return int(guess_n1)



if __name__ == '__main__':
    slt = Solution()
    print(slt.mySqrt(4))
    print(slt.mySqrt(8))
    print(slt.mySqrt(2))
    # print(slt.mySqrt())
