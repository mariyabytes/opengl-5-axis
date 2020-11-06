#include <vector>
#include "headers/generater_functions.h"
#include "headers/vertex.h"
#include <cmath>
template<typename T>
std::vector<T> linspace(T a, T b, size_t N) {
    T h = (b - a) / static_cast<T>(N - 1);
    std::vector<T> xs(N);
    typename std::vector<T>::iterator x;
    T val;
    for (x = xs.begin(), val = a; x != xs.end(); ++x, val += h) // NOLINT(cert-flp30-c)
        *x = val;
    return xs;
}

int binomialCoefficient(int n, int k) {
    // Base Cases
    if (k == 0 || k == n)
        return 1;

    // Recur
    return binomialCoefficient(n - 1, k - 1) +
           binomialCoefficient(n - 1, k);
}

std::vector<Vertex> generateTriangles() {
    int divisions = 151;
    double u_min = 0.0, u_max = 1.0, v_min = 0.0, v_max = 1.0;

    int N = 4, M = 4;

    int control_points[16][3] = {
            {-75, -75, 15},
            {-75, -25, 0},
            {-75, 25,  25},
            {-75, 75,  20},
            {-25, -75, 15},
            {-25, -25, 20},
            {-25, 25,  25},
            {-25, 75,  30},
            {25,  -75, 35},
            {25,  -25, 40},
            {25,  25,  30},
            {25,  75,  35},
            {75,  -75, 25},
            {75,  -25, 35},
            {75,  25,  35},
            {75,  75,  20},
    };

    std::vector<double> u1 = linspace(u_min, u_max, divisions);
    std::vector<double> v1 = linspace(v_min, v_max, divisions);

    glm::vec3 finalControlPointList[N][M];

    int temp = 0;

    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < M; j++) {

            finalControlPointList[i][j] = glm::vec3(control_points[temp][0], control_points[temp][1],
                                                    control_points[temp][2]);
            temp++;
        }
    }

    double u, v, b1;
    glm::vec3 triangle_array[divisions][divisions];
    glm::vec3 temp_vector;

    for (size_t i1 = 0; i1 < divisions; i1++) {
        u = u1[i1];
        for (size_t j1 = 0; j1 < divisions; j1++) {
            v = v1[j1];
            temp_vector = glm::vec3(0.f);
            for (size_t i = 0; i < N; i++) {
                for (size_t j = 0; j < M; j++) {
                    b1 = binomialCoefficient(N - 1, i) * pow(u, i) * pow((1 - u), (N - 1 - i)) *
                         binomialCoefficient(M - 1, j) *
                         pow(v, j) * pow((1 - v), (M - 1 - j));
                    temp_vector += (float) b1 * finalControlPointList[i][j];
                }
            }

            triangle_array[i1][j1] = temp_vector;
        }
    }

    std::vector<Vertex> vertexArray;
    Vertex tempVertex{};
    tempVertex.color = glm::vec3(1.f);
    tempVertex.normal = glm::vec3(1.f);
    tempVertex.texcoord = glm::vec2(0.f, 1.f);

    for (size_t i = 0; i < divisions - 1; i++) {
        for (size_t j = 0; j < divisions - 1; j++) {
            tempVertex.position = triangle_array[j][i];
            vertexArray.push_back(tempVertex);
            tempVertex.position = triangle_array[j + 1][i];
            vertexArray.push_back(tempVertex);
            tempVertex.position = triangle_array[j + 1][i + 1];
            vertexArray.push_back(tempVertex);

            tempVertex.position = triangle_array[j][i];
            vertexArray.push_back(tempVertex);
            tempVertex.position = triangle_array[j + 1][i + 1];
            vertexArray.push_back(tempVertex);
            tempVertex.position = triangle_array[j][i + 1];
            vertexArray.push_back(tempVertex);
        }
    }

    return vertexArray;
}

std::vector<Vertex> generateTorus() {
    float radius_inner = 6.0f;
    float radius_outer = 6.7f;
    int theta_min = 0;
    int theta_max = -180;

    glm::vec3 wt = glm::vec3(0.f, 0.f, 1.f);
    glm::vec3 ut = glm::vec3(1.f, 0.f, 0.f);
    glm::vec3 vt = glm::vec3(0.f, -1.f, 0.f);
    glm::vec3 tc1 = glm::vec3(0.f, 0.f, 0.f);

    glm::vec3 ccc;

    int div_t = 51, div_p = 91;

    std::vector<double> theta_a = linspace((theta_min * M_PI) / 180, (theta_max * M_PI) / 180, div_t);

    double tempTheta;
    double tempPhi;

    std::vector<double> phi_i;

    glm::vec3 triangleVerticesArray[div_t][div_p];

    for (size_t i = 0; i < div_t; i++) {
        tempTheta = theta_a[i];
        phi_i = linspace((double) 0, 2 * M_PI, div_p);

        for (size_t j = 0; j < div_p; j++) {
            tempPhi = phi_i[j];
            ccc = ut * (float) ((radius_outer + radius_inner * cos(tempTheta)) * cos(tempPhi)) +
                  vt * (float) ((radius_outer + radius_inner * cos(tempTheta)) * sin(tempPhi)) +
                  wt * (float) (radius_inner * sin(tempTheta)) + tc1;

            triangleVerticesArray[i][j] = ccc;
        }
    }

    std::vector<Vertex> vertexArray;
    Vertex tempVertex{};
    tempVertex.color = glm::vec3(1.f, 0.f, 0.f);
    tempVertex.normal = glm::vec3(1.f);
    tempVertex.texcoord = glm::vec2(0.f, 1.f);

    for (size_t i = 0; i < div_p - 1; i++) {
        for (size_t j = 0; j < div_t - 1; j++) {
            tempVertex.position = triangleVerticesArray[j][i];
            vertexArray.push_back(tempVertex);
            tempVertex.position = triangleVerticesArray[j + 1][i];
            vertexArray.push_back(tempVertex);
            tempVertex.position = triangleVerticesArray[j + 1][i + 1];
            vertexArray.push_back(tempVertex);

            tempVertex.position = triangleVerticesArray[j][i];
            vertexArray.push_back(tempVertex);
            tempVertex.position = triangleVerticesArray[j + 1][i + 1];
            vertexArray.push_back(tempVertex);
            tempVertex.position = triangleVerticesArray[j][i + 1];
            vertexArray.push_back(tempVertex);
        }
    }

    return vertexArray;
}

// Equation

// (x - 52.5)*150/375,
