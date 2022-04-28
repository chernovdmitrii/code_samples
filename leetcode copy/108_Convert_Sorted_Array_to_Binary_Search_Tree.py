'''
Given an integer array nums where the elements are sorted in ascending order, convert it to a height-balanced binary
search tree.

A height-balanced binary tree is a binary tree in which the depth of the two subtrees of every node never differs by
more than one.

Example 1:
Input: nums = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]
Explanation: [0,-10,5,null,-3,null,9] is also accepted:

Example 2:
Input: nums = [1,3]
Output: [3,1]
Explanation: [1,null,3] and [3,1] are both height-balanced BSTs.

Constraints:
1 <= nums.length <= 10^4
-10^4 <= nums[i] <= 10^4
nums is sorted in a strictly increasing order.
'''
from typing import List, Optional
from binarytree import build2

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def sortedArrayToBST(self, nums: List[int]) -> Optional[TreeNode]:

        def helper(left: int, right: int) -> Optional[TreeNode]:
            if left > right:
                return None

            mid = (left + right) // 2
            root = TreeNode(nums[mid])
            root.left = helper(left, mid - 1 )
            root.right = helper(mid + 1, right)
            return root

        return helper(0, len(nums) - 1)







if __name__ == '__main__':
    slt = Solution()
    # tree1 = build2([])
    tree1 = slt.sortedArrayToBST([-10,-3,0,5,9])
    print(tree1)