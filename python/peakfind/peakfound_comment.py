#!/usr/bin/env python

def center(a):
    return int((len(a)-1)/2)

def peakfinding1d(a):
    # This "fix" the indexing and array sizes
    # And do some cleanup in code
    n=len(a)
    n2=center(a)

    # If array size is 1, n2+1 will fail, therefore we need
    # this test  
    if n==1:
        print "!!!PEAK FOUND!!! {}".format(a[0])
        return a[0]

    if a[n2] < a[n2-1]:
        print "ARRAY IN  : {}".format(a)
        print "a[n2] = {}  < {} = a[n2-1]".format(a[n2],a[n2-1])
        peak=peakfinding1d(a[:n2])
        return peak
        print "ARRAY PICK: {}".format(a[:n2])
    elif a[n2] < a[n2+1]:
        print "ARRAY IN  : {}".format(a)
        print "a[n2] = {}  < {} = a[n2+1]".format(a[n2],a[n2+1])
        peak=peakfinding1d(a[n2+1:])
        return peak
        print "ARRAY PICK: {}".format(a[n2+1:])
    else:
        print "!!!PEAK FOUND!!! {}".format(a[n2])
        return a[n2]

if __name__ == "__main__":
    arr1=[1,2,3,4,5,6]
    arr2=[6,5,4,3,2,1]
    arr3=[0,1,4,3,2,1,0]
    arr4=[0,1,2,3,4,1,0]
    arr5=[0,1,2,3,2,1]
