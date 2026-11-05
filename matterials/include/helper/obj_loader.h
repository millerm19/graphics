
#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

#include "objects/triangle.h"

inline void load_obj(
    const std::string& filename,
    hittable_list& world,
    shared_ptr<material> mat,
    const point3& position = point3(0, 0, 0),
    double scale = 1.0
) {
    std::ifstream file(filename);

    if (!file) {
        throw std::runtime_error("Could not open OBJ file: " + filename);
    }

    std::vector<point3> vertices;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string type;
        stream >> type;

        if (type == "v") {
            double x, y, z;

            if (stream >> x >> y >> z) {
                // Scale and translate the vertex.
                point3 vertex(
                    x * scale + position.x(),
                    y * scale + position.y(),
                    z * scale + position.z()
                );

                vertices.push_back(vertex);
            }
        }
        else if (type == "f") {
            std::vector<int> indices;
            std::string token;

            while (stream >> token) {
                size_t slash = token.find('/');
                std::string vertex_index = token.substr(0, slash);

                int index = std::stoi(vertex_index);

                // OBJ indices start at 1.
                if (index > 0) {
                    index -= 1;
                }
                else {
                    index = static_cast<int>(vertices.size()) + index;
                }

                if (index < 0 ||
                    index >= static_cast<int>(vertices.size())) {
                    throw std::runtime_error("Invalid OBJ vertex index");
                }

                indices.push_back(index);
            }

            // Convert each polygon into triangles.
            for (size_t i = 1; i + 1 < indices.size(); ++i) {
                world.add(std::make_shared<triangle>(
                    vertices[indices[0]],
                    vertices[indices[i]],
                    vertices[indices[i + 1]],
                    mat
                ));
            }
        }
    }
}

#endif
