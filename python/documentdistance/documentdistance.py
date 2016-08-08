#!/usr/bin/env python


def documentList(d):
    """Returns a sentence as a list of words with only
    alphabetic characters"""

    # Do not use regex for "readibility"
    # Neither list comprehensions ;-)
    # v=''.join([ c for c in d.lower() if c in 'abcdefghijklmnopqrstuvwxyz
    # ']).split()

    v=""
    for c in d.lower():
        if c in 'abcdefghijklmnopqrstuvwxyz ':
            v = v + c

    return v.split()


def documentVector(d):
    """Returns a list of words as a word vector, where each
    word is associated with a integer value"""

    v={}
    for w in d:
        if w in v.keys():
            v[w]+=1
        else:
            v[w]=1

    return v


def documentDotProduct(d1, d2):
    """For each word in both sets, returns the dot product
    between the dictionary values"""
    
    # Pick the smaller vector
    if len(d1) <= len(d2):
        d=d1
    else:
        d=d2

    # Now do the dot product
    p=0
    for w in d:
        try:
            p+=d1[w]*d2[w]
        except KeyError:
            pass

    return p


def documentNorm(d1):
    """Return a norm of a document"""

    return documentDotProduct(d1,d1)**.5


def documentAngle(d1,d2):
    """ Returns the angle <d1,d2>/|d1|+|d2| """

    return documentDotProduct(d1,d2)/(documentNorm(d1)+documentNorm(d2))


if __name__ == "__main__":
    d1 = "I'm a sentence sentence"
    d2 = "I'm a sentence, but longer sentence"

    # Step 1: Split into words
    l1 = documentList(d1)
    l2 = documentList(d2)

    # Step 2: Compute word frequencies
    v1 = documentVector(l1)
    v2 = documentVector(l2)

    # Step 3: Compute the dot product
    p = documentAngle(v1,v2)
