# NCKU system software 2017 spring, phone book

## Introduction
* Understand the impact of cache miss
* Get familiar with the performance analysis tool
* Realize the software optimizations


## Original structure

The original structure of the phone book data. We want to improve the data saving and the data searching.

## Small structure

Reduce the data structure from 136 Kb to 24 Kb. It boosts the speed of the data appending to the linked list.
The cache-misses reduce about 65%.

### Original structure

        size of entry : 136 bytes
        The exception last name: zyxel
        The searched last name: zyxel
        execution time of list_append() : 0.004994 sec
        execution time of list_find_name() : 0.001086 sec

         Performance counter stats for './phonebook_orig':

                    99,898      cache-misses                                                

               0.009956199 seconds time elapsed

### Reduce the data structure.
        size of entry : 24 bytes
        The exception last name: zyxel
        The searched last name: zyxel
        execution time of list_append() : 0.003323 sec
        execution time of list_find_name() : 0.000189 sec

         Performance counter stats for './phonebook_small_struct':

                    21,341      cache-misses                                                

               0.005194459 seconds time elapsed


## Binary search tree.

At the first, we use binary search tree in the top-down approach.

But the performance of data appending increasing significantly.

The original phone book file: word.txt have 349900 lines.

If we reduce the lines from 344900 lines to 34490 lines (10% data throughout of the original file).

It still needs to take about 11.632539 sec to append all of the data. It is totally not an effective method.

We can use analysis tool, perf, to check which part of the program drag the performance.

```bash
./phonebook_bst & sudo perf top -p $!
```

It shows that the program spends most of the resource to run the function: bst_insert_last_name().


## Linked list to binary search tree

We deduce that the reason for appending time will increase significantly is the binary search tree is not a balanced tree.

We have to improve the binary search tree to a balanced binary search tree.

The simple method is to use the sorted linked list, we convert it to the binary search tree, and set the middle node as the root.

Although the time for data storing is increasing, the time for search keyword significantly decreasing.




## Licensing
`phonebook` is freely redistributable under the two-clause BSD License.
Use of this source code is governed by a BSD-style license that can be found in the `LICENSE` file.


## References:
- [B01: phonebook](https://hackmd.io/s/rJYD4UPKe)
- [0140454/phonebook](https://github.com/0140454/phonebook)
- [f5120125/phonebook](https://github.com/f5120125/phonebook)
- [Perf Tutorial](https://perf.wiki.kernel.org/index.php/Tutorial)
- [Sorted Linked List to Balanced BST](http://www.geeksforgeeks.org/sorted-linked-list-to-balanced-bst/)
