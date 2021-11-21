#include "Point.h"
#include "fonctions.h"
#include "Random.h"
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <numeric>  // std::reduce


all_points_t initialize_random_points(int number_of_points)
{
    auto rand_gen = elie::Random();
    std::vector<Point> vecPoint;

    for (int i = 0; i < number_of_points; ++i)
    {
        vecPoint.push_back(Point{ rand_gen(0.0, 99.0), rand_gen(0.0, 99.0) });
    }

    return vecPoint;
}


void print_vector_of_points(std::vector<Point> const& vector_of_points)
{
    std::string str_vec_of_points = "";
    std::string point_x;
    std::string point_y;
    for (std::size_t i = 0; i < vector_of_points.size(); ++i)
    {
        point_x = std::to_string(vector_of_points[i].mX);
        point_y = std::to_string(vector_of_points[i].mY);

        str_vec_of_points += "{" + point_x + "," + point_y + "}, ";
    }

    std::cout << str_vec_of_points << std::endl;
}


void print_vector_of_vectors_of_points(all_clusters_t const& vector_of_vectors_of_points)
{
    std::cout << "\nVector of Vectors(Clusters) of Points:" << std::endl;
    for (std::size_t z = 0; z < vector_of_vectors_of_points.size(); ++z)
    {
        std::cout << "Cluster of Points " << z +1 << ": " << std::endl;
        print_vector_of_points(vector_of_vectors_of_points[z]);
    }
}


all_centroids_t select_random_cluster_centroids(int K, all_points_t const& vector_of_points)
{
    // args: - number of primary points (K)
    //       - vector_of_points
    // returns: a vector comprising of the randomly selected primary points

    std::vector<Point> vecCentroids;
    vecCentroids.reserve(K);

    std::sample(
        vector_of_points.begin(),
        vector_of_points.end(),
        std::back_inserter(vecCentroids),
        K,
        std::mt19937{ std::random_device{}() }
        );

    return vecCentroids;
}


double distance_between_two_points(Point first_Point, Point second_Point)
{
    double x1 = first_Point.mX;
    double x2 = second_Point.mX;
    double y1 = first_Point.mY;
    double y2 = second_Point.mY;

    return std::sqrt(std::pow(x2 - x1, 2) +
                    std::pow(y2 - y1, 2) * 1.0);
}


all_clusters_t assign_every_point_to_closest_cluster_centroid(all_points_t const& vector_of_points, all_centroids_t const& vector_of_centroids)
{
    std::vector<std::vector<Point>> vector_of_clusters_of_points(vector_of_centroids.size() );

    std::size_t const size_vector_of_points = vector_of_points.size();
    std::size_t const size_vector_of_centroids = vector_of_centroids.size();

    double stored_distance_variable;

    std::vector<double> temp_distance_vector;
    temp_distance_vector.reserve(size_vector_of_centroids);

    for (std::size_t i = 0; i < size_vector_of_points; ++i)
    {
        for (std::size_t j = 0; j < size_vector_of_centroids; ++j)
        {
            stored_distance_variable = distance_between_two_points(vector_of_points[i], vector_of_centroids[j]);
            temp_distance_vector.push_back(stored_distance_variable);
        }

        auto min_element_index = static_cast<std::size_t>(
            std::distance(std::begin(temp_distance_vector),
                          std::min_element(std::begin(temp_distance_vector), std::end(temp_distance_vector))
            ));

        vector_of_clusters_of_points[min_element_index].push_back(vector_of_points[i]);

        temp_distance_vector.clear();
    }

    return vector_of_clusters_of_points;
}


Point calculate_average_of_points_in_cluster(cluster_t const& vector_of_points_in_cluster)
{
    return std::reduce(
        vector_of_points_in_cluster.begin(), 
        vector_of_points_in_cluster.end() ) 
        / vector_of_points_in_cluster.size();
}


all_clusters_t Kmeans_cluster_point_assignation_loop(all_points_t const& vector_of_points, all_centroids_t vector_of_centroids)
{
    std::vector<std::vector<Point>> vector_of_clusters_of_points;

    for (std::vector<std::vector<Point>> vector_copy_to_compare;
        vector_copy_to_compare != vector_of_clusters_of_points or vector_copy_to_compare.empty();
        vector_of_clusters_of_points = assign_every_point_to_closest_cluster_centroid(vector_of_points, vector_of_centroids))
    {
        /*std::cout << "==================" << std::endl;
        std::cout << "\nVector of Vectors(Clusters) of Points:" << std::endl;
        for (std::size_t z = 0; z < vector_of_clusters_of_points.size(); ++z)
        {
            std::cout << "Cluster of Points " << z << ": " << std::endl;
            print_vector_of_points(vector_of_clusters_of_points[z]);
        }*/

        /*std::cout << "\nVector of Centroids (Before change):";
        print_vector_of_points(vector_of_centroids);*/
        for (std::size_t i = 0; i < vector_of_clusters_of_points.size(); ++i)
        {
            Point average_of_points = calculate_average_of_points_in_cluster(vector_of_clusters_of_points[i]);
            /*std::cout << "\nAverage of Points in cluster " << i << ": { " << average_of_points.mX
                << ", " << average_of_points.mY << "}" << std::endl;*/
            vector_of_centroids[i] = average_of_points;
        }
        /*std::cout << "\nVector of Centroids (After change):";
        print_vector_of_points(vector_of_centroids);*/

        vector_copy_to_compare = vector_of_clusters_of_points;
    }

    return vector_of_clusters_of_points;
}


all_clusters_t Kmeans_Clustering(int number_of_points, int number_of_groups)
{
    std::vector<Point> vector_of_points = initialize_random_points(number_of_points);

    std::vector<Point> vector_of_centroids = select_random_cluster_centroids(number_of_groups, vector_of_points);

    /*std::cout << "\nVector of Points:";
    print_vector_of_points(vector_of_points);
    std::cout << "\nVector of Centroids:";
    print_vector_of_points(vector_of_centroids);*/

    std::vector<std::vector<Point>> vector_of_clusters_of_points = Kmeans_cluster_point_assignation_loop(vector_of_points, vector_of_centroids);

    return vector_of_clusters_of_points;
}

