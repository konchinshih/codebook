/* Steps to build suffix array
 * 1. Base Case: One letter
 *    Do AnySort() -> store in buc[0]
 *    Fill SA and Rank
 *
 * 2. Repeat O(log(n)) times
 *    Fill buc[0] with last result
 *    Do RadixSort()
 *    Fill SA and Rank
 *
 *    Conditions for ending in advance:
 *        if every element is distinct (Rank[i] all diff)
 *        // just end process
 *
 * Tip: Radix Sort
 *    Repeat twice
 *        Count
 *        Reset bucket (build pos array)
 *        Fill element into new bucket
 */
