'''
You are given the heads of two sorted linked lists list1 and list2.

Merge the two lists in a one sorted list. The list should be made by splicing together the nodes of the first two lists.

Return the head of the merged linked list.

Example 1:
Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]

Example 2:
Input: list1 = [], list2 = []
Output: []

Example 3:
Input: list1 = [], list2 = [0]
Output: [0]
'''

# Definition for singly-linked list.

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
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        if not list1: return list2
        if not list2: return list1

        current = dummy = ListNode()

        while list1 and list2:
            if list1.val > list2.val:
                current.next = list2
                list2 = list2.next
            else:
                current.next = list1
                list1 = list1.next

            current = current.next


        # Adding remaining of a list, in case lists have different sizes
        if list1: current.next = list1
        if list2: current.next = list2

        # by default the first node is "0"
        return dummy.next

if __name__ == '__main__':
    slt = Solution()

    list1 = array_to_list([1, 2, 4])
    list2 = array_to_list([1, 3, 4])
    node = slt.mergeTwoLists(list1, list2)
    linked_list = LinkedList()
    linked_list.head = node
    print(linked_list)
