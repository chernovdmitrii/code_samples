'''
Given an integer numRows, return the first numRows of Pascal's triangle.
In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:



Example 1:
Input: numRows = 5
Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]

Example 2:
Input: numRows = 1
Output: [[1]]


Constraints:
1 <= numRows <= 30
'''
from typing import List


class Solution:
    def generate(self, numRows: int) -> List[List[int]]:
        result = []
        if numRows >= 1:
            result.append([1])
        if numRows >= 2:
            result.append([1, 1])

        for i in range(3, numRows + 1):
            new_row = []
            for j in range(i):
                if j == 0 or j == i - 1:
                    new_row.append(1)
                    continue
                new_row.append(result[i - 2][j - 1] + result[i - 2][j])

            result.append(new_row)

        return result

    def generate2(self, numRows: int) -> List[List[int]]:
        result = [[1]]

        for i in range(numRows - 1):
            temp = [0] + result[-1] + [0]
            new_row = []
            for j in range(len(result[-1]) + 1):
                new_row.append(temp[j] + temp[j + 1])

            result.append(new_row)

        return result


if __name__ == '__main__':
    slt = Solution()

    for i in range(3, 10):
        print(slt.generate2(i))
