#include <iostream>
#include "ReceiptBag.h"

using namespace std;

int main()
{
    // Demo: create a receipt bag and insert several items.
    ReceiptBag<string> bag;

    int receipt1 = bag.insert("Driver");
    int receipt2 = bag.insert("Putter");
    int receipt3 = bag.insert("Wedge");

    // Show the unique receipt numbers assigned to each inserted item.
    cout << "Receipt for Driver: " << receipt1 << endl;
    cout << "Receipt for Putter: " << receipt2 << endl;
    cout << "Receipt for Wedge: " << receipt3 << endl;

    // Check the bag size before removing anything.
    cout << "Bag size: " << bag.size() << endl;

    // Remove an item using one of the receipts and display it.
    string& removed = bag.remove(receipt2);

    cout << "Removed item: " << removed << endl;
    cout << "Bag size after removal: " << bag.size() << endl;

    // Attempt to remove an invalid receipt to demonstrate error handling.
    try
    {
        bag.remove(99);
    }
    catch (const runtime_error& error)
    {
        cout << error.what() << endl;
    }

    return 0;
}