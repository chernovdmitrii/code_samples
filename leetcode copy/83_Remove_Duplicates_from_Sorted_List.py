'''
Given the head of a sorted linked list, delete all duplicates such that each element appears only once. Return the
linked list sorted as well.

Example 1:
Input: head = [1,1,2]
Output: [1,2]

Example 2:
Input: head = [1,1,2,3,3]
Output: [1,2,3]


Constraints:
The number of nodes in the list is in the range [0, 300].
-100 <= Node.val <= 100
The list is guaranteed to be sorted in ascending order.
'''

from typing import Optional


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class LinkedList:
    def __init__(self):
        self.head = None

    # is called when you want it to be printed
    def __repr__(self):
        node = self.head
        nodes = []
        while node is not None:
            nodes.append(str(node.val))
            node = node.next
        nodes.append("None")
        return " -> ".join(nodes)


def array_to_list(arr: list) -> ListNode:
    list1 = ListNode(arr[0])
    list_copy = list1
    for item in arr[1:]:
        list1.next = ListNode(item)
        list1 = list1.next

    return list_copy


class Solution:
    def deleteDuplicates(self, head: Optional[ListNode]) -> Optional[ListNode]:

        # handling zero or one element list
        if not head or not head.next:
            return head

        current = head
        while current and current.next:

            if current.val == current.next.val:
                current.next = current.next.next
            else:
                current = current.next

        return head


if __name__ == '__main__':
    slt = Solution()

    list1 = array_to_list([1, 1, 2])
    list2 = array_to_list([1, 1, 2, 3, 3])
    list3 = array_to_list([1, 1])

    answer1 = LinkedList()
    answer1.head = slt.deleteDuplicates(list1)
    print(answer1)

    answer2 = LinkedList()
    answer2.head = slt.deleteDuplicates(list2)
    print(answer2)

    answer3 = LinkedList()
    answer3.head = slt.deleteDuplicates(list3)
    print(answer3)
