'''
Given the roots of two binary trees p and q, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

Example 1:
Input: p = [1,2,3], q = [1,2,3]
Output: true

Example 2:
Input: p = [1,2], q = [1,null,2]
Output: false

Example 3:
Input: p = [1,2,1], q = [1,1,2]
Output: false


Constraints:
The number of nodes in both trees is in the range [0, 100].
-10^4 <= Node.val <= 10^4
'''
from typing import List, Optional
from binarytree import build2


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
        if not p and not q:
            return True
        # if (not p and q) or (p and not q):
        if not p or not q:
            return False
        if p.val != q.val:
            return False

        return self.isSameTree(p.left, q.left) and self.isSameTree(p.right, q.right)


if __name__ == '__main__':
    slt = Solution()
    treeA1 = treeB1 = build2([1, 2, 3])
    treeA2, treeB2 = build2([1, 2]), build2([1, None, 2])
    treeA3, treeB3 = build2([1, 2, 1]), build2([1, 1, 2])

    print(slt.isSameTree(treeA1, treeB1))
    print(slt.isSameTree(treeA2, treeB2))
    print(slt.isSameTree(treeA3, treeB3))

