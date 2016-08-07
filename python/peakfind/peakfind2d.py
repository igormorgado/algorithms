#!/usr/bin/env python


def ispeak2d(m,i,j):
    nrows=len(m)
    ncols=len(m[0])

    up=m[i-1][j]
    do=m[i+1][j]
    le=m[i][j-1]
    ri=m[i][j+1]
    ce=m[i][j]

    print up,do,le,ri,ce
    print nrows,ncols


def peakfind1d(a):
    # This "fix" the indexing and array sizes
    # And do some cleanup in code
    n=len(a)
    n2=int((n-1)/2)

    # If array size is 1, n2+1 will fail, therefore we need
    # this test  
    if n==1:
        return a[0]

    if a[n2] < a[n2-1]:
        peak=peakfind1d(a[:n2])
    elif a[n2] < a[n2+1]:
        peak=peakfind1d(a[n2+1:])
    else:
        peak=a[n2]

    return peak

if __name__ == "__main__":
    m = [
            [ 0,0,0,1,1,1,1,0,0,0 ],
            [ 1,1,1,1,1,1,1,1,1,1 ],
            [ 1,1,1,2,2,2,2,1,1,1 ],
            [ 1,1,1,2,3,3,2,1,1,1 ],
            [ 1,1,1,2,3,4,2,1,1,1 ],
            [ 1,1,1,2,3,3,2,1,1,1 ],
            [ 1,1,1,2,2,2,2,1,1,1 ],
            [ 1,1,1,1,1,1,1,1,1,1 ],
            [ 0,0,0,1,1,1,1,0,0,0 ],
            [ 0,0,0,0,0,0,0,0,0,0 ]
        ]
