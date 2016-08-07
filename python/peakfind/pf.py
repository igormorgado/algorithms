#!/usr/bin/env python

import numpy as np


nums = np.array((1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1))


def naiveglobalpeak(a):
    peak = np.zeros_like(nums)

    if nums[0] >= nums[1]:
        peak[0] = True

    if nums[-1] >= nums[-2]:
        peak[-1] = True

    for i in range(1, len(nums) - 1):
        if nums[i] >= nums[i + 1] and nums[i] >= nums[i - 1]:
            peak[i] = True
        else:
            peak[i] = False

    return peak


def naivelocalpeak(a):
    peak = np.zeros_like(nums)
    if nums[0] >= nums[1]:
        peak[0] = True

    if nums[-1] >= nums[-2]:
        peak[-1] = True

    for i in range(1, len(nums) - 1):
        if nums[i] >= nums[i + 1] and nums[i] >= nums[i - 1]:
            peak[i] = True
        else:
            peak[i] = False

    return peak


def divconq(a):

    n = len(a)

    if a[n / 2] < a[n / 2 - 1]:
        divconq(a[0:n / 2])
    elif a[n / 2] < a[n / 2 + 1]:
        divconq(a[n / 2:n])
    else:
        print("{} is the peak".format(a[n / 2]))


print(nums)

peak = naivelocalpeak(nums)
print(peak)

divconq(nums)
