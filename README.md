# SkipList
<!-- Implementation of generic SkipList data structure in c++ -->
<p>
Skiplist is a data structure used to store sorted list of items, very much like Binary Search Tree.
</p>
<p>
Sorted associative containers like set and map which are implemented using height balanced binary search tree can be implemented using SkipList to achieve better performance in certain cases.
</p>

<br/>

> ### Rationale:
>> - The main advantage of using Skiplists over Balanced trees is that it is better suited for concurrent access.
>> - The algorithms for insertion and deletion in skip lists are much simpler and faster than the equivalent algorithms for balanced trees.
>> - Balanced tree algorithms rearrange the tree as operations are performed in order to maintain certain balance conditions and assure good performance but this is not required in case of SkipList.