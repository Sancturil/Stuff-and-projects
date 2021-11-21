#include "Point.h"
#include "fonctions.h"
#include "Random.h"
#include <iostream>


int main()
{ 


    std::vector<std::vector<Point>> vector_of_clusters_of_points = Kmeans_Clustering(50, 3);
    std::cout << "==================" << std::endl;
    print_vector_of_vectors_of_points(vector_of_clusters_of_points);

}