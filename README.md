# SkipList
<!-- Implementation of generic SkipList data structure in c++ -->
<p>
Skiplist is a data structure used to store sorted list of items, very much like Binary Search Tree.
</p>
<p>
Sorted associative containers like set and map which are implemented using height balanced binary search tree can be implemented using SkipList to achieve better performance in certain cases.
</p>

<br/>

### Rationale
- The main advantage of using Skiplists over Balanced trees is that it is better suited for concurrent access.
- The algorithms for insertion and deletion in skip lists are much simpler and faster than the equivalent algorithms for balanced trees.
- Balanced tree algorithms rearrange the tree as operations are performed in order to maintain certain balance conditions and assure good performance but this is not required in case of SkipList.

<br>

## Implementation
[SkipList.h](SkipList.h) contains the implementation of the generic SkipList data structure. The container provides a bidirectional iterator which can be used with the functions of the STL `<algorithm>` library.

```cpp
template<
	class Key,			// SkipList::key_type/value_type
	class Compare = std::less<Key>	// SkipList::key_compare/value_compare
>class SkipList;
```

### Member types
<table>
	<tr>
		<th>member type	</th>
		<th>definition</th>
		<th>notes</th>
	</tr>
	<tr>
		<td>key_type</td>
		<td>Key</td>
		<td></td>
	</tr>
	<tr>
		<td>value_type</td>
		<td>Key</td>
		<td></td>
	</tr>
	<tr>
		<td>key_compare</td>
		<td>Compare</td>
		<td>defaults to: less&ltkey_type&gt </td>
	</tr>
	<tr>
		<td>value_compare</td>
		<td>Compare</td>
		<td>defaults to: less&ltvalue_type&gt </td>
	</tr>
	<tr>
		<td>pointer</td>
		<td>value_type*</td>
		<td></td>
	</tr>
	<tr>
		<td>const_pointer</td>
		<td>const value_type*</td>
		<td></td>
	</tr>
	<tr>
		<td>reference</td>
		<td>value_type&</td>
		<td></td>
	</tr>
	<tr>
		<td>const_reference</td>
		<td>const value_type&</td>
		<td></td>
	</tr>
	<tr>
		<td>iterator</td>
		<td>a bidirectional iterator to const value_type</td>
		<td></td>
	</tr>
	<tr>
		<td>const_iterator</td>
		<td>a bidirectional iterator to const value_type</td>
		<td></td>
	</tr>
	<tr>
		<td>size_type</td>
		<td></td>
		<td>same as size_t</td>
	</tr>
	<tr>
		<td></td>
		<td></td>
		<td></td>
	</tr>
</table>
<br>

### Member functions
<table>
	<tr>
		<td>(constructor)</td>
		<td>constructs the SkipList</td>
	</tr>
	<tr>
		<td>(destructor)</td>
		<td>destructs the SkipList</td>
	</tr>
	<tr>
		<td>operator=</td>
		<td>copy container content</td>
	</tr>
</table>

#### Capacity
<table>
	<tr>
		<td>empty</td>
		<td>checks whether the container is empty</td>
	</tr>
	<tr>
		<td>size</td>
		<td>returns the number of elements</td>
	</tr>
</table>

#### Iterators
<table>
	<tr>
		<td>begin</td>
		<td>returns an iterator to the beginning</td>
	</tr>
	<tr>
		<td>end</td>
		<td>returns an iterator to one past the end</td>
	</tr>
</table>

#### Modifiers
<table> 
	<tr>
		<td>insert</td>
		<td>inserts element</td>
	</tr>
	<tr>
		<td>insert_unique</td>
		<td>inserts element if an element with same key is not in the container</td>
	</tr>
	<tr>
		<td>remove</td>
		<td>removes the element</td>
	</tr>
	<tr>
		<td>clear</td>
		<td>clears the contents of the list</td>
	</tr>
</table>

#### Lookup
<table>
	<tr>
		<td>find</td>
		<td>Get iterator to element</td>
	</tr>
	<!-- <tr>
		<td>contains</td>
		<td>checks if the container contains element with specific key</td>
	</tr> -->
</table>
