'''
Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and
return its sum.

A subarray is a contiguous part of an array.

Example 1:
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.

Example 2:
Input: nums = [1]
Output: 1

Example 3:
Input: nums = [5,4,-1,7,8]
Output: 23


Constraints:
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
'''
from typing import List


class Solution:
    def maxSubArray_cubed_complexity(self, nums: List[int]) -> int:
        current_sum: int = 0
        peak_sum: int = nums[0]

        for i in range(len(nums)):
            for j in range(i, len(nums)):
                current_sum = sum(item for item in nums[i:j + 1])
                if current_sum > peak_sum:
                    peak_sum = current_sum
            current_sum = 0

        return peak_sum

    def maxSubArray_squared_complexity(self, nums: List[int]) -> int:
        current_sum: int = 0
        peak_sum: int = nums[0]

        for i in range(len(nums)):
            for j in range(i, len(nums)):
                current_sum += nums[j]
                if current_sum > peak_sum:
                    peak_sum = current_sum
            current_sum = 0

        return peak_sum

    def maxSubArray(self, nums: List[int]) -> int:
        current_sum: int = 0
        peak_sum: int = nums[0]

        for num in nums:
            if current_sum < 0:
                current_sum = 0

            current_sum += num
            peak_sum = max(current_sum, peak_sum)

        return peak_sum


if __name__ == '__main__':
    slt = Solution()
    print(slt.maxSubArray([-2, 1, -3, 4, -1, 2, 1, -5, 4]))  #6 [4,-1,2,1]
    print(slt.maxSubArray([1])) #1
    print(slt.maxSubArray([5, 4, -1, 7, 8])) #23 [5,4,-1,7,8]
    print(slt.maxSubArray([-1]))
    print(slt.maxSubArray([-2,1]))
    print(slt.maxSubArray([8,-19,5,-4,20]))
    print(slt.maxSubArray([-8, -19, -4]))

