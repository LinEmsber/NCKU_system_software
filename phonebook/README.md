# phone book

## Introduction

Use different kinds of data structures and algorithms to store the data and search the target data.
There are five situations, hereunder:
1. Original
2. Small structure
3. Binary search tree
4. Convert linked list to binary search tree
5. Hash table

## Purpose
* Understand the impact of cache miss
* Get familiar with the performance analysis tool
* Realize the software optimizations


## Original structure

The original structure of the phone book data. We want to improve the data storing and the data searching.

```c
/* original version */
typedef struct __PHONE_BOOK_ENTRY {
	char lastName[MAX_LAST_NAME_SIZE];
	char firstName[16];
	char email[16];
	char phone[10];
	char cell[10];
	char addr1[16];
	char addr2[16];
	char city[16];
	char state[2];
	char zip[5];
	struct __PHONE_BOOK_ENTRY * p_next;
} list_node_t;
```

## Small structure

Reduce the data structure from 136 Kb to 24 Kb. It boosts the speed of the data appending to the linked list.
The cache-misses reduce about 79% ( |639655 - 130154| / 639655 = 0.79 ), as follows:

The small structure:
```c
typedef struct small_PHONE_BOOK list_node_t;

struct small_PHONE_BOOK{
	char lastName[ MAX_LAST_NAME_SIZE];
	struct small_PHONE_BOOK * p_next;
};
```

The cache-misses of original structure:

```bash
$ sudo perf stat -e cache-misses ./phonebook_orig

size of list_node_t : 136 bytes
The exception last name: zyxel
The searched last name: zyxel
execution time of list_append() : 0.038618 sec
execution time of list_find_name() : 0.009744 sec

 Performance counter stats for './phonebook_orig':

           639,655      cache-misses                                                

       0.067041881 seconds time elapsed

```

The cache-misses of the small structure:

```bash
$ sudo perf stat -e cache-misses ./phonebook_small_struct

size of list_node_t : 24 bytes
The exception last name: zyxel
The searched last name: zyxel
execution time of list_append() : 0.032082 sec
execution time of list_find_name() : 0.002239 sec

 Performance counter stats for './phonebook_small_struct':

           130,154      cache-misses                                                

       0.043002778 seconds time elapsed

```

## Binary search tree.

At the first, we want to use a binary search tree to store all data, but the performance of data appending increasing significantly.
Although we reduce the lines from 344900 lines (the amount of the original data) to 34490 lines (only 10% data amount of the original data), it still needs to take about 6.47 sec to append all of the data. It is totally not an effective method, even the data search is quick.

```bash
size of list_node_t : 24 bytes
The exception last name: zyxel
The searched last name: zyxel
execution time of bst_insert_last_name() : 6.472056 sec
execution time of bst_search() : 0.000000 sec

 Performance counter stats for './phonebook_bst':

       6472.388468      task-clock (msec)         #    1.000 CPUs utilized          
                27      context-switches          #    0.004 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
             1,008      page-faults               #    0.156 K/sec                  
    22,686,937,142      cycles                    #    3.505 GHz                    
   <not supported>      stalled-cycles-frontend  
   <not supported>      stalled-cycles-backend   
    44,728,030,027      instructions              #    1.97  insns per cycle        
     6,741,610,246      branches                  # 1041.595 M/sec                  
       127,428,566      branch-misses             #    1.89% of all branches        

       6.474016993 seconds time elapsed
```

We can use analysis tool, perf, to check which part of the program drag the performance.

```bash
$ sudo perf record ./phonebook_bst

size of list_node_t : 24 bytes
The exception last name: zyxel
The searched last name: zyxel
execution time of bst_insert_last_name() : 7.066286 sec
execution time of bst_search() : 0.000000 sec
[ perf record: Woken up 1 times to write data ]
[ perf record: Captured and wrote 0.011 MB perf.data (52 samples) ]
```

```bash
$ sudo perf report

Samples: 61  of event 'cycles:pp', Event count (approx.): 40182885542803           
Overhead  Command        Shared Object      Symbol                                 
  49.77%  phonebook_bst  phonebook_bst      [.] bst_insert_last_name
  32.84%  phonebook_bst  libc-2.23.so       [.] __strcasecmp_avx
  15.30%  phonebook_bst  libc-2.23.so       [.] __strcasecmp_l_avx
   2.10%  phonebook_bst  phonebook_bst      [.] strcasecmp@plt
   0.00%  phonebook_bst  [kernel.kallsyms]  [k] memtype_rb_lowest_match.constprop.7
   0.00%  phonebook_bst  [kernel.kallsyms]  [k] perf_output_copy
   0.00%  perf           [kernel.kallsyms]  [k] native_write_msr_safe
   0.00%  phonebook_bst  [kernel.kallsyms]  [k] native_write_msr_safe
```

It shows that the program spends most of the resource to run the function: bst_insert_last_name(), and the secondly most effort is to conduct __strcasecmp_avx() which is for bst_insert_last_name() to chose left or right node.


## Linked list to binary search tree

We deduce that the reason for appending time will increase significantly is the binary search tree is not a balanced tree.
We have to improve the binary search tree to a balanced binary search tree.
The simple method is to use the sorted linked list, we convert it to the binary search tree, and set the middle node as the root.
Although the time for data storing is increasing, the time for search keyword significantly decreasing.

```bash
$ sudo perf stat ./phonebook_list2bst

size of list_node_t : 24 bytes
The exception last name: zyxel
The searched last name: zyxel
execution time of list_append() + list_to_bst() : 0.059928 sec
execution time of bst_search() : 0.000011 sec

 Performance counter stats for './phonebook_list2bst':

         73.728879      task-clock (msec)         #    0.904 CPUs utilized          
                24      context-switches          #    0.326 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
             8,254      page-faults               #    0.112 M/sec                  
       251,438,183      cycles                    #    3.410 GHz                    
   <not supported>      stalled-cycles-frontend  
   <not supported>      stalled-cycles-backend   
       410,079,118      instructions              #    1.63  insns per cycle        
        77,732,250      branches                  # 1054.299 M/sec                  
         1,256,527      branch-misses             #    1.62% of all branches        

       0.081589942 seconds time elapsed
```

## Hash table

We use hash table to store and search the data.

```bash
$ sudo perf stat ./phonebook_hash

size of list_node_t : 24 bytes
The exception last name: zyxel
The searched last name: zyxel
execution time of hash_table_put() : 0.093381 sec
execution time of hash_table_get() : 0.000000 sec

 Performance counter stats for './phonebook_hash':

         97.016579      task-clock (msec)         #    0.937 CPUs utilized          
                 4      context-switches          #    0.041 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
             5,531      page-faults               #    0.057 M/sec                  
       327,319,149      cycles                    #    3.374 GHz                    
   <not supported>      stalled-cycles-frontend  
   <not supported>      stalled-cycles-backend   
       326,323,990      instructions              #    1.00  insns per cycle        
        55,971,868      branches                  #  576.931 M/sec                  
         1,013,993      branch-misses             #    1.81% of all branches        

       0.103557244 seconds time elapsed
```

The usage time for storing and searching is significantly decrease. We use perf to analysis it, as follows:

```bash
$ sudo perf record ./phonebook_hash && sudo perf report

size of list_node_t : 24 bytes
The exception last name: zyxel
The searched last name: zyxel
execution time of hash_table_put() : 0.109099 sec
execution time of hash_table_get() : 0.000001 sec
[ perf record: Woken up 1 times to write data ]
[ perf record: Captured and wrote 0.011 MB perf.data (22 samples) ]

Samples: 22  of event 'cycles:pp', Event count (approx.): 21990307406506
Overhead  Command         Shared Object      Symbol                     
 100.00%  phonebook_hash  phonebook_hash     [.] hash_table_put         
   0.00%  phonebook_hash  phonebook_hash     [.] hash_table_create      
   0.00%  phonebook_hash  libc-2.23.so       [.] malloc                 
   0.00%  phonebook_hash  [kernel.kallsyms]  [k] copy_page              
   0.00%  phonebook_hash  phonebook_hash     [.] main                   
   0.00%  perf            [kernel.kallsyms]  [k] perf_event_aux.part.57
   0.00%  phonebook_hash  [kernel.kallsyms]  [k] exit_to_usermode_loop  
   0.00%  perf            [kernel.kallsyms]  [k] native_write_msr_safe  
   0.00%  phonebook_hash  [kernel.kallsyms]  [k] native_write_msr_safe  
```

## Licensing
`phonebook` is freely redistributable under the two-clause BSD License.
Use of this source code is governed by a BSD-style license that can be found in the `LICENSE` file.

## Conclusion

The following figure shows that the appending and searching data in different kinds of data structure and algorithms.

![Time usage of diffenert methods](https://github.com/LinEmsber/NCKU_system_software/blob/master/phonebook/runtime.png "Figure")


## References:
- [B01: phonebook](https://hackmd.io/s/rJYD4UPKe)
- [0140454/phonebook](https://github.com/0140454/phonebook)
- [f5120125/phonebook](https://github.com/f5120125/phonebook)
- [Perf Tutorial](https://perf.wiki.kernel.org/index.php/Tutorial)
- [Sorted Linked List to Balanced BST](http://www.geeksforgeeks.org/sorted-linked-list-to-balanced-bst/)
