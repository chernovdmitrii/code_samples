'''
Given a binary tree, determine if it is height-balanced.
For this problem, a height-balanced binary tree is defined as:
a binary tree in which the left and right subtrees of every node differ in height by no more than 1.

Example 1:
Input: root = [3,9,20,null,null,15,7]
Output: true

Example 2:
Input: root = [1,2,2,3,3,null,null,4,4]
Output: false

Example 3:
Input: root = []
Output: true

Constraints:
The number of nodes in the tree is in the range [0, 5000].
-10^4 <= Node.val <= 10^4
'''
from typing import Optional
from binarytree import build2


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def isBalanced(self, root: Optional[TreeNode]) -> bool:
        def helper(root: Optional[TreeNode]) -> (bool, int):
            if not root:
                return True, 0

            left = helper(root.left)
            right = helper(root.right)
            is_balanced = abs(left[1] - right[1]) <= 1 and (left[0] and right[0])

            return is_balanced, 1 + max(left[1], right[1])

        return helper(root)[0]

if __name__ == '__main__':
    slt = Solution()

    tree1 = build2([3, 9, 20, None, None, 15, 7])
    tree2 = build2([1, 2, -2, 3, 3, None, None, 4, 4])
    tree3 = build2([1, 2, 3, 4, 5, None, 6, 7, None, None, None, None, 8])

    # print(tree3)

    print(slt.isBalanced(tree1))
    print(slt.isBalanced(tree2))
    print(slt.isBalanced(tree3))
