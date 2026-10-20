
#ifndef TREE_ALGORITHMS_H
#define TREE_ALGORITHMS_H

#include "Tree.h"
#include <queue>

// Part 4: Visit nodes one level at a time.
template <typename T, typename Visitor>
void levelOrder(const Tree<T>& tree, Visitor visit)
{
    if (tree.isEmpty())
        return;

    std::queue<Tree<T>> nodes;
    nodes.push(tree);

    while (!nodes.empty())
    {
        Tree<T> current = std::move(nodes.front());
        nodes.pop();

        visit(current.root());

        Tree<T> left = current.left();
        Tree<T> right = current.right();

        if (!left.isEmpty())
            nodes.push(std::move(left));

        if (!right.isEmpty())
            nodes.push(std::move(right));
    }
}

// Part 5: Recursively remove the ORIGINAL leaf nodes.
template <typename T>
Tree<T> pruneCopy(const Tree<T>& tree)
{
    if (tree.isEmpty())
        return Tree<T>();

    Tree<T> left = tree.left();
    Tree<T> right = tree.right();

    // This node was a leaf in the original tree.
    if (left.isEmpty() && right.isEmpty())
        return Tree<T>();

    return Tree<T>(
        pruneCopy(left),
        tree.root(),
        pruneCopy(right)
    );
}

// Assignment-required reference return.
// Caller owns the returned Tree and must delete it.
template <typename T>
Tree<T>& prune(Tree<T>& tree)
{
    return *(new Tree<T>(pruneCopy(tree)));
}

#endif
