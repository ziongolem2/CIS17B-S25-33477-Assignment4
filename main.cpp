// Saul Resendiz
// Lesson 4 Assignment

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

class StoredItem {
private:
    std::string id;
    std::string description;
    std::string location;

public: // Creating a constructor for our stored item, declaring 3 parameters
    StoredItem(string userid, string desc, string location)
        : id(userid), description(desc), location(location) {
    }
    // GETTERS:
    string getId() const { return id; }
    string getDescription() const { return description; }
    string getLocation() const { return location; }
};

class StorageManager {
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

    // Function for finding and returning an item by ID 
    std::shared_ptr<StoredItem> findById(const std::string& id) const 
    {
        auto foundID = itemById.find(id);
        if (foundID == itemById.end())
        {
            throw ItemNotFoundException("Item with ID '" + id + "' not found.");
        }
        return 
    }
