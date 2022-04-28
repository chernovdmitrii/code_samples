'''
Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest
leaf node.



Example 1:
Input: root = [3,9,20,null,null,15,7]
Output: 3

Example 2:
Input: root = [1,null,2]
Output: 2

Constraints:
The number of nodes in the tree is in the range [0, 10^4].
-100 <= Node.val <= 100
'''

from typing import Optional
from binarytree import build2
from collections import deque


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0

        return 1 + max(self.maxDepth(root.right), self.maxDepth(root.left))

    def maxDepth_bfs(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0

        level = 0
        queue = deque([root])
        while queue:

            for i in range(len(queue)):
                node = queue.popleft()
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            level += 1

        return level

    def maxDepth_interative(self, root: Optional[TreeNode]) -> int:
        stack = [[root, 1]]
        result = 0
        while stack:
            node, depth = stack.pop()

            if node:
                result = max(result, depth)
                stack.append([node.right, depth + 1])
                stack.append([node.left, depth + 1])

        return result




if __name__ == '__main__':
    slt = Solution()
    tree1 = build2([3, 9, 20, None, None, 15, 7])
    tree2 = build2([1, None, 2])

    print(slt.maxDepth(tree1))
    print(slt.maxDepth(tree2))
    print(slt.maxDepth_bfs(tree1))
    print(slt.maxDepth_bfs(tree2))
    print(slt.maxDepth_interative(tree1))
    print(slt.maxDepth_interative(tree2))
