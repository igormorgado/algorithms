#!/usr/bin/env python

def peakfind1d(a):
    # This "fix" the indexing and array sizes
    # And do some cleanup in code
    n=len(a)
    n2=int((n-1)/2)

    # If array size is 1 or 2 look neighbors fail
    # therefore we need this test  
    if n==1:
        return a[0]
    elif n==2:
        if a[0] < a[1]:
            return a[1]
        else:
            return a[0]

    # Class given algorithm is incorrect
    if a[n2] < a[n2-1]:
        a=peakfind1d(a[:n2+1])
    elif a[n2] < a[n2+1]:
        a=peakfind1d(a[n2+1:])
    else:
        a=a[n2]

    return a

if __name__ == "__main__":
    arr1=[1,2,3,4,5,6]
    arr2=[6,5,4,3,2,1]
    arr3=[0,1,4,3,2,1,0]
    arr4=[0,1,2,3,4,1,0]
    arr5=[0,1,2,3,2,1]
    arr6=[0,1,2,3,2,1,0]
    arr7=[1,1,1,1,1,1,1]
    arr8=[1,1,1,1,1,2,1]

    print arr1, peakfind1d(arr1)
    print arr2, peakfind1d(arr2)
    print arr3, peakfind1d(arr3)
    print arr4, peakfind1d(arr4)
    print arr5, peakfind1d(arr5)
    print arr6, peakfind1d(arr6)
    print arr7, peakfind1d(arr7)
    print arr8, peakfind1d(arr8)
