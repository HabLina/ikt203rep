## Time complexity analysis

#### Results:
1) String: "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
   Pattern: "LMNO"
   ![img_2.png](images/img_2.png)
2) String: "This is a test to test the KMP matching algorithm. We are gonna conduct a time complexity analysis on it."
   Pattern: "a time"
   ![img_3.png](images/img_3.png)
3) String: "hey how is it going"
   Pattern: "how is"
   ![img_.png](images/img_.png)
4) String: "(assignment text) - see test_cases.txt"
   Pattern: "KMP"!
   ![img_4.png](images/img_4.png)
5) String: "(Numbers of π - see test_cases.txt)"
   Pattern: "34"
   ![img_5.png](images/img_5.png)
6) String: "ABBABAB"
   Pattern: "aba"
   ![img_6.png](images/img_6.png)
7) String: "@!*%*@&*%"
   Pattern: "*%"
   ![img_7.png](images/img_7.png)
8) String: "Lina er drit fet"
   Pattern: " "
   ![img_8.png](images/img_8.png)
9) String: "ABCDEFGH"
   Pattern: "XYZ"
   ![img_9.png](images/img_9.png)
10) String: "Hello, World!"
    Pattern: ""
    ![img.png](images/img_10.png)
11) String: "AbCdEfG"
    Pattern: "bCd"
    ![img.png](images/img_11.png)

### Analysis

The KMP algorithm is design for efficient string pattern matching. The prefix table
is constructed by iterating through the pattern string once which takes O(M) time.
The KMPSearch function performs a linear scan of the text, comparing each character
to the pattern. Worst case it iterates through the entire text once, in each iteration
it either increments text index (i) or decrements pattern index (j) based of prefix table.
The worst-case occurs when there is no matches, and it increments until reaching the end of the text.
This means that the time complexity of O(N), where N is the length of the text.

The most time-consuming operation is the linear scan for the text. The time complexity
is achieved because the prefix table construction (O(M)) and the text scanning (O(N))
performs independently. It achieves this efficiency when constructing a prefix table that allows
it to skip unnecessary comparisons during the search phase.

#### Worst-case time complexity (Big-O Notation)
1) Prefix table construction: the time complexity of the prefix table is O(M),
   where M is the length of the pattern.
2) Search Algorithm: the outer loop, iterates through the text, runs N times,
   where N is the length of the text. The inner loop, iterates through the pattern,
   which runs at most M times for each outer loop iteration. The worst-case
   complexity of the search phase is O(N).
3) The worst-case complexity KMP algorithm is O(N + M).
###### The time complexity of the algorithm: O(N + M)

#### Test cases
1) String length (N) = 26
   Pattern length (M) = 4
   Time complexity: O(N + M) = O(26 + 4) = O(30)
2) String length (N) = 89
   Pattern length (M) = 6
   Time complexity: O(N + M) = O(89 + 6) = O(95)
3) String length (N) = 19
   Pattern length (M) = 8
   Time complexity: O(N + M) = O(19 + 8) = O(27)
4) String length (N) = 1060
   Pattern length (M) = 3
   Time complexity: O(N + M) = O(1060 + 3) = O(1063)
5) String length (N) = 751
   Pattern length (M) = 3
   Time complexity: O(N + M) = O(751 + 3) = O(754)
6) String length (N) = 7
   Pattern length (M) = 3
   Time complexity: O(N + M) = O(7 + 3) = O(10)
7) String length (N) = 9
   Pattern length (M) = 2
   Time complexity: O(N + M) = O(9 + 2) = O(11)
8) String length (N) = 17
   Pattern length (M) = 1
   Time complexity: O(N + M) = O(17 + 1) = O(18)
9) String length (N) = 8
   Pattern length (M) = 3
   Time complexity: O(N + M) = O(8 + 3) = O(11)
10) String length (N) = 13
    Pattern length (M) = 0 (empty pattern)
    Time complexity: O(N + M) = O(13 + 0) = O(13)
11) String length (N) = 7
    Pattern length (M) = 3
    Time complexity: O(N + M) = O(7 + 3) = O(10)

This is a Big-O Notation, O(N), where it represents a linear time complexity
as the algorithm's execution time grows linearly with the combined length of the
text and pattern.


### Comparing with different algorithms

##### Brute Force Algorithm
This algorithm has a time complexity of O(N*M) in the worst case,
as it compares each character in the string_text with each character in the pattern.
KMP would then be more efficient, especially for large texts and patterns.

##### Boyer-Moore Algorithm
Boyer-Moore has an average-case time complexity for searching which is O(N/M),
but it can be faster than KMP in practice. In the worst case,
Boyer-Moore can have a time complexity of O(N*M). It often performs better than
KMP due to its skip and jump heuristics.
This algorithm can sometimes outperform KMP for certain types of data.