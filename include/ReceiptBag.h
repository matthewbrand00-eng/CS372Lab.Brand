#ifndef RECEIPTBAG_H
#define RECEIPTBAG_H

#include <vector>
#include <optional>
#include <stdexcept>

// Stores items and their matching receipt numbers in parallel vectors.
template <typename ItemType>
class ReceiptBag
{
private:
    std::vector<ItemType> items;          // actual items stored in the bag
    std::vector<int> receipts;            // receipt number assigned to each item
    int nextReceipt;                      // next unique receipt ID to assign
    std::optional<ItemType> removedItem;  // item removed most recently, used by remove()

public:
    // Creates an empty bag and starts receipt numbering at 1.
    ReceiptBag();

    // Inserts an item into the bag and returns a unique receipt number.
    // The returned receipt can later be used to remove the item.
    int insert(const ItemType& item);

    // Removes and returns the item associated with the given receipt.
    // Throws std::runtime_error if no item matches that receipt.
    ItemType& remove(int receipt);

    // Returns true if the bag contains no items.
    bool empty() const;

    // Returns the number of items currently in the bag.
    int size() const;
};

template <typename ItemType>
ReceiptBag<ItemType>::ReceiptBag()
{
    nextReceipt = 1;
}

template <typename ItemType>
int ReceiptBag<ItemType>::insert(const ItemType& item)
{
    // Add the new item to the bag and assign it the current receipt ID.
    items.push_back(item);
    receipts.push_back(nextReceipt);

    int receipt = nextReceipt;
    nextReceipt++;

    return receipt;
}

template <typename ItemType>
bool ReceiptBag<ItemType>::empty() const
{
    return items.empty();
}

template <typename ItemType>
int ReceiptBag<ItemType>::size() const
{
    return static_cast<int>(items.size());
}

template <typename ItemType>
ItemType& ReceiptBag<ItemType>::remove(int receipt)
{
    // Search for the receipt number. Since receipts and items are kept in parallel,
    // the matching index identifies the item to remove from both vectors.
    for (int i = 0; i < static_cast<int>(receipts.size()); i++)
    {
        if (receipts[i] == receipt)
        {
            removedItem = items[i];

            items.erase(items.begin() + i);
            receipts.erase(receipts.begin() + i);

            return removedItem.value();
        }
    }

    throw std::runtime_error("Invalid receipt");
}

#endif