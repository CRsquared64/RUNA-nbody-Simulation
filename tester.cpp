#include <iostream>
#include <variant>
#include <array>
#include <memory>  // For std::unique_ptr

// Forward declaration of Node class
class Node;

// Blank class to represent a blank item
class Blank {
public:
    Blank() : name("Unknown") {}
    Blank(const std::string& n) : name(n) {}

    void print() const {
        std::cout << "Blank: " << name << std::endl;
    }

private:
    std::string name;
};

// NBody class representing a body in the n-body simulation
class NBody {
public:
    std::string name;

    // Default constructor
    NBody() : name("Unknown") {}

    // Parameterized constructor
    NBody(const std::string& n) : name(n) {}

    void print() const {
        std::cout << "NBody: " << name << std::endl;
    }
};

// Node class that contains an array of either NBody or Node objects
class Node {
public:
    // A variant that can hold either an NBody, Blank, or a unique_ptr to another Node
    using NodeContent = std::variant<NBody, Blank, std::unique_ptr<Node>>;

    // Array to hold exactly 4 NBody or Node objects
    std::array<NodeContent, 4> contents;

    // Constructor
    Node() {
        // Initialize the array with default-constructed Blank objects
        for (auto& item : contents) {
            item = Blank();  // All array elements are initially Blank
        }
    }

    // Function to insert either an NBody or Node at a specific index
    void insertAt(size_t index, NodeContent content) {
        if (index < contents.size()) {
            contents[index] = std::move(content);  // Use move assignment
        } else {
            std::cerr << "Error: Index out of bounds." << std::endl;
        }
    }

    // Updated print function with indentation support
    void print(int indent = 0) const {
        std::string indentation(indent, ' ');  // Indentation for nested nodes

        for (const auto& item : contents) {
            // Check if the current item is a Blank
            if (std::holds_alternative<Blank>(item)) {
                std::cout << indentation;
                std::get<Blank>(item).print();
            }
            // Check if the current item is an NBody
            else if (std::holds_alternative<NBody>(item)) {
                std::cout << indentation;
                std::get<NBody>(item).print();
            }
            // Check if the current item is another Node
            else if (std::holds_alternative<std::unique_ptr<Node>>(item)) {
                std::cout << indentation << "Node containing: " << std::endl;
                std::get<std::unique_ptr<Node>>(item)->print(indent + 2);  // Recursively print child nodes with more indentation
            }
        }
    }
};

int main() {
    // Create NBody objects
    NBody earth("Earth");
    NBody mars("Mars");

    // Create a node and a unique_ptr to a child node
    Node rootNode;
    auto childNode = std::make_unique<Node>();

    // Insert NBody into the rootNode
    rootNode.insertAt(0, earth);

    // Insert another node into the rootNode
    rootNode.insertAt(1, std::move(childNode));  // Move the unique_ptr into the variant

    // Create a new node and insert it into the childNode
    auto newChildNode = std::make_unique<Node>();
    newChildNode->insertAt(0, mars);

    // Move the new child node into the rootNode
    rootNode.contents[1] = std::move(newChildNode);  // Move the unique_ptr into the variant

    // Print the contents of rootNode
    std::cout << "Contents of rootNode:" << std::endl;
    rootNode.print();

    return 0;
}
