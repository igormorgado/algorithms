#!/usr/bin/env python

#  This heap was written for didatics, not for performance
#  Min heap operations not implemented. Leave as exercise to the reader. ;-)

# Set operations
# Swap not described on lecture but makes things more readable
def swap(S,i,j):
    """Swap the contents of the key "i" with the key "j"."""
    __TEMP__=S[i]
    S[i]=S[j]
    S[j]=__TEMP__

    #Uncoment here to see the swaps ;-)
    #print S

    return S

def insert(S, x):
    """Insert element "x" in set "S"."""
    S += [ x ]
    return S

def increase_key(S,x,k):
    """Increase the val of x-th key to the new value k.""" 
    S[x] += k
    return S


# Heap Operations
# differs slightly from lecture because python is 0-indexed.
def heap_size(S):
    """Return the length of heap."""
    return len(S)

def root(S):
    return S[0]

def left(S, i):
    """"Returns the left children element of key i."""
    j=2*i+1
    if j < heap_size(S):
        return S[j]
    else:
        return None

def right(S, i):
    """"Returns the right children element of key i."""
    j=2*i+2
    if j < heap_size(S):
        return S[j]
    else:
        return None

def children(S, i):
    """Return the values children of the i-th key."""
    return left(S,i),right(S,i)

def parent(S, i):
    """Returns the parent of key i."""
    return S[int((i-1)/2)]


def is_min_heap(S,i):
    """Definition: the key of a node is <= than the keys of it's children"""
    return False

# Here I have renamed to maxh to not conflit with python max method
# I could avoid it using classes, but, simplicity is on mind here.
def maxh(S): 
    """Return element of "S" with the largest key."""
    if is_max_heap(S,0):
        return S[0]
    else:
        # Max to non max_heaps
        __MAX__=None
        for x in S:
            if x > __MAX__:
                __MAX__= x
        return __MAX__

def extract_max(S):
    """Return element of "S" with the largest key.
    And remove it from S"""
    if is_max_heap(S,0):
        ROOT=root(S)
        swap(S,0,heap_size(S)-1)
        del S[-1]
        if not is_max_heap(S,0):
            max_heapify(S,0)
        return ROOT
    else:
        # Max to non max_heaps
        __MAXKEY__=None
        __MAX__=None
        key=0
        for x in S:
            if x > __MAX__:
                __MAX__= x
                __MAXKEY__= key

            key+=1
        del S[key]
        return __MAX__


# Does not exists originaly, but makes code clear
def is_leaf(S,i):
    """Returns if the element is a leaf or not"""
    if i+1 > heap_size(S)/2:
        return True
    else:
        return False

def is_max_heap(S,i):
    """Definition: the key of a node is >= than the keys of it's children"""

    if i > heap_size(S)-1:
        return False

    if is_leaf(S,i):
        return True

    if S[i] >= left(S,i) and S[i] >= right(S,i):
        return True
    else:
        return False

def max_heapify(S,i):
    """Corrects a single violation of the heap property
    in a sub-tree root.
    We assume blindly that left and right are max heaps."""
    if not is_leaf(S,i) and not is_max_heap(S,i):
        # Find the biggest child.
        l,r = children(S,i)
        if l >= r:
            j=2*i+1
        else:
            j=2*i+2

        swap(S,i,j)

        max_heapify(S,j)

    return S

def build_max_heap(S):
    """Produces an max heap from an unordered array."""
    for i in range((heap_size(S)/2)-1,-1,-1):
        max_heapify(S,i)

    return S

def heap_sort(S):
    """Returns a sorted heap"""
    build_max_heap(S)
    N=[]
    for i in range(heap_size(S)):
        insert(N,extract_max(S))

    return N

if __name__ == "__main__":
    heap = [ 16, 14, 10, 8, 7, 9, 3, 2, 4, 1 ]
    heap2 = [ 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 ]

    print heap2 == heap
    build_max_heap(heap2)
    print heap2 == heap

    # Just to keep the bad heap to tests
    heap2 = [ 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 ]

