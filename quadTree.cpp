#include <iostream>
#include <cmath>
#include "area.cpp"
#include "node.cpp"
#include "body.cpp"

class quadTree
{
private:
    Area area;
    Node* root;
    int max_depth = 128;
    const int offset = 5;
    
public:
    quadTree(Area a, int depth = 128) : area(a), max_depth(depth){
        root = new Node(area.min_x, area.min_y, area.max_x, area.max_y);
    }

    bool check_in_range(const Nbody& body){
        return(area.min_x < body.x && body.x < area.max_x && area.min_y < body.y && body.y < area.max_y);
    }
    
    int get_quadrant(const Nbody& body, const Area& area){
        double mid_x = (area.min_x + area.max_x) / 2;
        double mid_y = (area.min_y + area.max_y) / 2;
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
        int quadrant = get_quadrant(*body, Area(node->min_x, node->min_y, node->max_x, node->max_y));

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

