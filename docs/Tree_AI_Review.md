
# Module 5 - Tree AI Code Review

## AI Prompt

Review this C++17 binary search Tree implementation for memory safety,
parent-pointer correctness, copy and move behavior, compatibility with
immutable insertion, performance, and missing tests. Recommend improvements.

## AI Response

The Tree implementation uses shared_ptr for child nodes and weak_ptr
for parent nodes. This prevents circular ownership and allows memory
to be released when the tree is destroyed.

The implementation uses deep copying when creating new trees. This
helps keep parent pointers correct because the same node cannot have
different parents in separate trees.

One disadvantage is that insert() copies the entire tree. This is
less efficient than the original implementation, which shared
unchanged subtrees.

Additional tests are recommended for copy assignment, move operations,
subtree extraction, and inserting duplicate values.

Recursive copying and counting could also cause stack overflow if
the tree becomes extremely deep.

## Improvements Implemented

Added tests to verify parent pointers after copying, moving,
extracting subtrees, and inserting duplicate values.

Created the validParents() function to verify that each node
references its correct parent.

Used weak_ptr for parent references to avoid ownership cycles.

## Testing Results

The original 27 instructor tests passed.

Added tests for parent pointers, level-order traversal, and pruning.

All 35 tests passed successfully.

## Remaining Limitations

Insertion requires copying the entire tree, which reduces performance
for large trees.

The prune() function returns a reference as required by the assignment.
The caller must delete the returned Tree to prevent a memory leak.
