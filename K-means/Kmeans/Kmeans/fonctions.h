#ifndef FONCTIONS_H_
#define FONCTIONS_H_

#include "Point.h"
#include <vector>


using all_points_t = std::vector<Point>;
using all_centroids_t = std::vector<Point>;
using cluster_t = std::vector<Point>;
using all_clusters_t = std::vector<cluster_t>;


all_points_t initialize_random_points(int number_of_points);

void print_vector_of_points(std::vector<Point> const& vector_of_points);
void print_vector_of_vectors_of_points(all_clusters_t const& vector_of_vectors_of_points);

all_centroids_t select_random_cluster_centroids(int K, all_points_t const& vector_of_points);

double distance_between_two_points(Point first_Point, Point second_Point);

all_clusters_t assign_every_point_to_closest_cluster_centroid(all_points_t const& vector_of_points, all_centroids_t const& vector_of_centroids);

Point calculate_average_of_points_in_cluster(cluster_t const& vector_of_points_in_cluster);

all_clusters_t Kmeans_cluster_point_assignation_loop(all_points_t const& vector_of_points, all_centroids_t vector_of_centroids);

all_clusters_t Kmeans_Clustering(int number_of_points, int number_of_groups);


#endif /* FONCTIONS_H_ */