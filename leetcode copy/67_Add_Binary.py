'''
Given two binary strings a and b, return their sum as a binary string.

Example 1:
Input: a = "11", b = "1"
Output: "100"

Example 2:
Input: a = "1010", b = "1011"
Output: "10101"

Constraints:

1 <= a.length, b.length <= 10^4
a and b consist only of '0' or '1' characters.
Each string does not contain leading zeros except for the zero itself.
'''


class Solution:
    def addBinary_inefficient(self, a: str, b: str) -> str:

        a = [int(item) for item in a]
        b = [int(item) for item in b]

        if len(a) < len(b):
            a, b = b, a

        i: int = len(b) - 1
        j: int = len(a) - 1
        carry: int = 0
        while i >= 0:
            if a[i] + b[i] + carry == 2:
                carry = 1
                a[j] = 0
            elif a[i] + b[i] + carry > 2:
                carry = 1
                a[j] = 1
            else:
                a[j] += b[i] + carry
                carry = 0

            i -= 1
            j -= 1

        while j >= 0:
            if a[j] + carry >= 2:
                a[j] = 0
                j -= 1

        if carry != 0:
            a.insert(0, carry)

        return ''.join([str(item) for item in a])

    def addBinary(self, a: str, b: str) -> str:
        result: str = ''
        carry: int = 0

        a, b = a[::-1], b[::-1]

        for i in range(max(len(a), len(b))):
            digitA = int(a[i]) if i < len(a) else 0
            digitB = int(b[i]) if i < len(b) else 0

            total = digitA + digitB + carry
            char = str(total % 2)
            result = char + result
            carry = total // 2

        if carry:
            result = '1' + result

        return result


if __name__ == '__main__':
    slt = Solution()
    print(slt.addBinary('11', '11'))
    print(slt.addBinary('11111', '1'))
    print(slt.addBinary('1010', '1011'))
