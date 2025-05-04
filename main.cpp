// Saul Resendiz
// Lesson 4 Assignment
// Test Code

using namespace std;

#include <iostream>
#include <unordered_map>
#include <map>
#include <memory>
#include <stdexcept>

// Exception when duplicate item is added
class DuplicateItemException : public std::runtime_error 
{
public:
    DuplicateItemException(const std::string& msg) : std::runtime_error(msg) {}
};

// Exception when item is not found
class ItemNotFoundException : public std::runtime_error {
public:
    ItemNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

class StoredItem 
{
private:
    std::string id;
    std::string description;
    std::string location;

public: // Creating a constructor for our stored item, declaring 3 parameters
    StoredItem(std::string id, std::string description, std::string location)
        : id(id), description(description), location(location) {}
    
    // GETTERS:
    string getId() const 
    { 
        return id; 
    }
    string getDescription() const 
    {
        return description; 
    }
    string getLocation() const 
    {
        return location; 
    }
};

class StorageManager 
{
private:    // Creating 2 seperate maps that have shared pointers pointing to a StoredItem object
    std::unordered_map<std::string, std::shared_ptr<StoredItem>> itemById;
    std::map<std::string, std::shared_ptr<StoredItem>> itemByDescription;

public:
    // Adding the item to both of the maps (unordered then ordered)
    void addItem(const std::shared_ptr<StoredItem>& item) 
    {
        if (itemById.find(item->getId()) != itemById.end())
        {
            throw DuplicateItemException("Item with ID '" + item->getId() + "' already exists!");
        }
        // If the item is not a duplicate: continue to next branch of code; add item to both maps

        itemById[item->getId()] = item; // Adding to 1st map, by ID
        itemByDescription[item->getDescription()] = item; // Adding to 2nd map, by description
    }

    // Function for finding and returning an item according to their respective ID 
    std::shared_ptr<StoredItem> findById(const std::string& id) const 
    {
        auto idIterator = itemById.find(id);    // find the location of an item by its ID
        if (idIterator == itemById.end())   // If makes it to end without finding item, throw exception
        {
            throw ItemNotFoundException("Item with ID '" + id + "' not found.");
        }
        return idIterator->second;  // returning the second value(the actual item) instead of the ID(1st value)
    }
    

    // Remove item from both maps, throwing if item not found
    void removeItem(const std::string& id) 
    {
        auto idIterator = itemById.find(id);
        if (idIterator == itemById.end())
        {
            throw ItemNotFoundException("Item with '" + id + "' not found.");
        }
        auto foundItem = idIterator->second; // foundItem obtains the second value of the map; the item Object 
        itemById.erase(idIterator);
        itemByDescription.erase(foundItem->getDescription()); // Deleting item from both maps
    }

    // Creating a function to list all items in terms of description 
    void listItemsByDescription() const 
    {
        for (const auto& items : itemByDescription) // Looping over every key and value within the map
        {
            std::shared_ptr<StoredItem> item = items.second; // Making sure to get the second value(actual item object)
            std::cout << "ITEM(S) BY DESCRIPTION: " << endl;
            std::cout << "ID# : " << item->getId()
                << ", Description: " << item->getDescription()
                << ", Location: " << item->getLocation() << std::endl;
        }
    }
};

// TESTING FUNCTIONS NOW :

void testDuplicateAddition(StorageManager& test) // Taking StoreManager object as reference 
{
    try {
        auto item = std::make_shared<StoredItem>("ITEM999", "Flashlight", "Aisle 9, Shelf 9");
        test.addItem(item); 
        test.addItem(item); // Should throw exception here since is a duplicate
    }
    catch (const DuplicateItemException& e) // Catching duplicate exception
    {
        std::cout << "Uh Oh. Caught error!" << e.what() << std::endl;
    }
}

// Testing "item does not exist" function 
void testItemNotFound(StorageManager& test) // Taking StoreManager object as reference
{
    try 
    {
        test.findById("NA");  // Seaching for item that doesn't exist
    }
    catch (const ItemNotFoundException& e) 
    {
        std::cout << "Caught error!" << e.what() << std::endl;
    }
}

// Main function
int main() // MAIN 
{
    StorageManager testManager; // Creating a manager object to test our program 

    // Creating three different items 
    auto item1 = std::make_shared<StoredItem>("ITEM1", "Backpack", "Aisle 1, Shelf 1");
    auto item2 = std::make_shared<StoredItem>("ITEM2", "Hammer", "Aisle 2, Shelf 2");
    auto item3 = std::make_shared<StoredItem>("ITEM3", "Nightlight", "Aisle 3, Shelf 3");

    // Now we add all three items to our StoreManager so we can maange the items directly
    testManager.addItem(item1);
    testManager.addItem(item2);
    testManager.addItem(item3);

    // SEARCHING ITEM BY ID WITHIN OUR STORAGE MANAGER OBJECT 
    try 
    {
        auto foundItem = testManager.findById("ITEM1");
        std::cout << "Found Item! Item: " << foundItem->getDescription() << " at " << foundItem->getLocation() << std::endl;
    }
    catch (const std::exception& e) 
    {
        std::cout << "Could not find item. " << e.what() << std::endl;
    }

    // REMOVING ITEM THAT DOES NOT EXIST IN OUR APPLICATION:
    try 
    {
        testManager.removeItem("ITEM249"); // Trying to remove item that isn't available
    }
    catch (const ItemNotFoundException& e) 
    {
        std::cout << "Item does not exist. " << e.what() << std::endl;
    }

    // Displaying items in terms of description:
    testManager.listItemsByDescription();

    // Calling test functions
    std::cout << "Testing functions:" << endl;
    cout << endl;
    testDuplicateAddition(testManager);
    testItemNotFound(testManager);

    return 0;
}
