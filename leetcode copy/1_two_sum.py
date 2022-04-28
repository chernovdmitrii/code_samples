'''
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]
'''
from typing import List
import unittest

class Tests(unittest.TestCase):
    def check(self, result, expected):
        self.assertEqual(result, expected)

class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:

        seen = {}
        for i, value in enumerate(nums):
            remaining = target - value

            if remaining in seen:
                return [i, seen[remaining]]

            seen[value] = i

if __name__ == '__main__':
    slt = Solution()
    test = Tests()

    nums_ = [2, 7, 11, 15]
    target_ = 9
    test.check(slt.twoSum(nums_, target_), [1,0])

