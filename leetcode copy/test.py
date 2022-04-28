def factorial(x: int) -> int:
    if x == 1:
        return 1
    else:
        return x * factorial(x - 1)


def Fibonacci(x: int) -> int:
    if x == 0:
        return 0
    elif x == 1 or x == 2:
        return 1
    else:
        return Fibonacci(x - 1) + Fibonacci(x - 2)


def sum(arr: list) -> int:
    if arr == []:
        return 0
    else:
        return arr[0] + sum(arr[1:])


def count(arr: list) -> int:
    if arr == []:
        return 0
    else:
        return 1 + count(arr[1:])


def max(arr: list, min: int = 0) -> int:
    if len(arr) == 2:
        return arr[0] if arr[0] > arr[1] else arr[1]
    else:
        sub_max = max(arr[1:])
        return arr[0] if arr[0] > sub_max else sub_max


def binary_search(arr, low, high, x):
    # Check base case
    if high >= low:

        mid = (high + low) // 2

        # If element is present at the middle itself
        if arr[mid] == x:
            return mid

        # If element is smaller than mid, then it can only
        # be present in left subarray
        elif arr[mid] > x:
            return binary_search(arr, low, mid - 1, x)

        # Else the element can only be present in right subarray
        else:
            return binary_search(arr, mid + 1, high, x)

    else:
        # Element is not present in the array
        return -1

def quicksort(arr: list) -> list:
    if len(arr) < 2:
        return arr
    else:
        pivot = arr[0]

        less = [item for item in arr[1:] if item <= pivot]

        greater = [item for item in arr[1:] if item >= pivot]

        return quicksort(less) + [pivot] + quicksort(greater)


if __name__ == '__main__':
    # print(factorial(100))
    # print(Fibonacci(9))
    print(sum([2, 4, 6]))
    print(count([2, 4, 6]))
    print(max([2, 4, 6, 9, 1, 0]))

    # Test array
    arr = [2, 3, 4, 10, 40]
    x = 10

    # Function call
    print(binary_search(arr, 0, len(arr) - 1, x))
    print(quicksort([10, 5, 2, 3]))
