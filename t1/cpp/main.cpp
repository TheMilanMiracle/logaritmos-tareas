#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <chrono>
#include "./mtree/mtree.h"

std::chrono::time_point<std::chrono::system_clock> start, end;


int main(){

    start = std::chrono::system_clock::now();

    // Node *o1 = newNode(NULL, 0);
    Point *o1 = newPoint(-5.0, 0.0);

    // Node *o2 = newNode(NULL, 0);
    Point *o2 = newPoint(-2.0, 0.0);

    // Node *o3 = newNode(NULL, 0);
    Point *o3 = newPoint(-8.0, 0.0);

    // Node *o4 = newNode(NULL, 0);
    Point *o4 = newPoint(-12.0, 0.0);

    std::vector<Entry*> e3_entries = {newEntry(o1, -1, NULL), newEntry(o2, -1, NULL)};
    Node *e3 = newNode(e3_entries);
    Entry *e3_entry = newEntry(newPoint(-5.0, 0.0), 3, e3);

    std::vector<Entry*> e4_entries = {newEntry(o3, -1, NULL), newEntry(o4, -1, NULL)};
    Node *e4 = newNode(e4_entries);
    Entry *e4_entry = newEntry(newPoint(-8.0, 0.0), 4, e4);

    std::vector<Entry*> e1_entries = {e3_entry, e4_entry};
    Node *e1 = newNode(e1_entries);
    Entry *e1_entry = newEntry(newPoint(-6.0, 0.0), 10, e1); 

    MTree *tree = newMTree(e1, 2);

    std::vector<Point*> puntos = searchTree(tree, newPoint(-2.0, 0.0), 20);

    std::cout << puntos.size() << std::endl;



    std::vector<Point*> points = generate_points(pow(2, 5));

    for(int i = 0; i < points.size(); i++){

        std::cout << "(" << points[i]->x << ", " << points[i]->y << ")" << std::endl;
 
    }

    // std::vector<int> test;

    // std::cout << "test.size() = " << test.size()<< std::endl;


    end = std::chrono::system_clock::now();

    std::chrono::duration<double> time = end - start;

    std::cout << "> main finished after " << time.count() << " seconds" << std::endl;

}