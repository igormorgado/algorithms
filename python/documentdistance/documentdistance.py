#!/usr/bin/env python


def documentList(d):
    # Do not use regex for "readibility"
    # Neither list comprehensions ;-)
    #v=''.join([ c for c in d.lower() if c in 'abcdefghijklmnopqrstuvwxyz ']).split()

    v=""
    for c in d.lower():
        if c in 'abcdefghijklmnopqrstuvwxyz ':
            v=v+c

    return v.split()

def documentDistance(d1,d2):
    return



if __name__ == "__main__":
    d1="All work and no play makes jack a dull boy"
    d2="To be and not to be is that a question?"

    print documentVector(d1)
    print documentVector(d2)

