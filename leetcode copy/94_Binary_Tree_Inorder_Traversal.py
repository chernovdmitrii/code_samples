'''
Given the root of a binary tree, return the inorder traversal of its nodes' values.

Example 1:
Input: root = [1,null,2,3]
Output: [1,3,2]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]


Constraints:
The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100

Follow up: Recursive solution is trivial, could you do it iteratively?
'''

from typing import Optional, List
from collections import deque
from binarytree import build2, Node

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        result: List[int] = []

        def inorder(root: Optional[TreeNode]) -> None:
            if not root:
                return
            inorder(root.left)
            result.append(root.val)
            inorder(root.right)

        inorder(root)
        return result

    def inorderTraversal2(self, root: Optional[TreeNode]) -> List[int]:
        result: List[int] = []
        stack = []
        current = root

        while current or stack:
            while current:
                stack.append(current)
                current = current.left
            current = stack.pop()
            result.append(current.val)
            current = current.right

        return result



if __name__ == '__main__':
    slt = Solution()
    # nodes = [1, None, 2, 3]
    nodes = [1, 2, 3, 4, 5, 6, 7]

    binary_tree_1 = build2(nodes)
    print(binary_tree_1)
    print(slt.inorderTraversal2(binary_tree_1))

