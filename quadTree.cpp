#include <iostream>
#include <cmath>
#include "area.cpp"
#include "node.cpp"
#include "body.cpp"

class quadTree
{
private:
    area Area;
    Node* root;
    int max_depth = 128;
    const int offset = 5;
    
public:
    quadTree(area a, int depth = 128) : Area(a), max_depth(depth){
        root = new Node(Area.min_x, Area.min_y, Area.max_x, Area.max_y);
    }

    bool check_in_range(const Nbody& body){
        return(Area.min_x < body.x && body.x < Area.max_x && Area.min_y < body.y && body.y < Area.max_y);
    }
    
    int get_quadrant(const Nbody& body, const area& Area){
        double mid_x = (Area.min_x + Area.max_x) / 2;
        double mid_y = (Area.min_y + Area.max_y) / 2;
        if (body.x < mid_x){
            if (body.y < mid_y){
                return 2; // botom left
            }
            else{
                return 0; // top left
            }
        }
        else{
            if (body.y < mid_y){
                return 3; // bottom right
            }
            else{
                return 1; // top right
            }
        }
    }
    void insert(Nbody* body, Node* node = nullptr, int depth = 0){
        if (node == nullptr){
            node = root;
        }
        if (depth == max_depth) {
            std::cerr << "Max Depth Reached at (" << body->x << ", " << body->y << ") in node (" << node->x << ", " << node->y << ")\n";
            return;
        }
        int quadrant = get_quadrant(*body, area(node->min_x, node->min_y, node->max_x, node->max_y));

        if (node->children[quadrant] != nullptr) {
            if (Nbody* existingBody = dynamic_cast<Nbody*>(node->children[quadrant])) {
                if (body->x == existingBody->x && body->y == existingBody->y) {
                    body->x += offset; // Adjust position slightly to avoid exact overlap
                }

                // If the quadrant already contains a body, subdivide and reinsert
                std::vector<Nbody*> bodies = { existingBody, body };
                node->children[quadrant] = nullptr; // Reset to nullptr before subdivision
                subdivide(node, quadrant);

                for (Nbody* b : bodies) {
                    insert(b, dynamic_cast<Node*>(node->children[quadrant]), depth + 1);
                }
            } else {
                // If the quadrant contains a node, recursively insert into it
                insert(body, dynamic_cast<Node*>(node->children[quadrant]), depth + 1);
            }
        } else {
            // If the quadrant is empty, insert the body directly
            node->children[quadrant] = body;
        }
    }
    void subdivide(Node* node, int quadrant) {
        double mid_x = (node->min_x + node->max_x) / 2;
        double mid_y = (node->min_y + node->max_y) / 2;

        switch (quadrant) {
            case 0:
                node->children[quadrant] = new Node(node->min_x, mid_y, mid_x, node->max_y, node->depth + 1);
                break;
            case 1:
                node->children[quadrant] = new Node(mid_x, mid_y, node->max_x, node->max_y, node->depth + 1);
                break;
            case 2:
                node->children[quadrant] = new Node(node->min_x, node->min_y, mid_x, mid_y, node->depth + 1);
                break;
            case 3:
                node->children[quadrant] = new Node(mid_x, node->min_y, node->max_x, mid_y, node->depth + 1);
                break;
            default:
                break;
        }

  
};

