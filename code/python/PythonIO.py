import sys
input = sys.stdin.readline

# Input
def readInt():
    return int(input())
def readIntList():
    return list(map(int,input().split()))
def readStr():
    s = input()
    return list(s[:len(s) - 1])
def readInts():
    return map(int,input().split())
