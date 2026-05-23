//
// Created by desktop on 26. 4. 26..
//
#include "../include/data/Material.h"
#include <istream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <unordered_map>

using namespace std;

bool Material::loadMtl(const string &filename) {
    unordered_map<string, uint16_t> pathMap;
    for (size_t i=0; i< texturePaths.size(); i++) {
        pathMap[texturePaths[i]] = static_cast<uint16_t>(i);
    }

    ifstream in;
    in.open(filename, ifstream::in);
    if (in.fail()) {
        cerr << "Mising file -> " << filename << endl;
        return false;
    }
    string line;
    string trash;
    string currName;
    material currMtl;
    bool first = true;
    while (getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;

        istringstream iss(line.c_str());
        if (line.compare(0, 7, "newmtl ") == 0) {
            if (!first) {
                mtls[currName] = currMtl;
            }else first = false;
            currMtl = material();
            iss >> trash >> currName;
            currMtl.materialId = static_cast<uint16_t>(mtls.size());
            currMtl.textureId = numeric_limits<uint16_t>::max();
        }else if (line.compare(0, 3, "Ns") == 0) {
            iss >> trash >> currMtl.shininess;
        }else if (line.compare(0, 3, "Ka") == 0) {
            iss >> trash >> currMtl.ambient.x >> currMtl.ambient.y >> currMtl.ambient.z;
        }else if (line.compare(0, 3, "Kd") == 0) {
            iss >> trash >> currMtl.diffuse.x >> currMtl.diffuse.y >> currMtl.diffuse.z;
        }else if (line.compare(0, 3, "Ks") == 0) {
            iss >> trash >> currMtl.specular.x >> currMtl.specular.y >> currMtl.specular.z;
        }else if (line.compare(0, 3, "Ke") == 0) {
            iss >> trash >> currMtl.emission.x >> currMtl.emission.y >> currMtl.emission.z;
        }else if (line.compare(0, 3, "Ni") == 0) {
            iss >> trash >> currMtl.opticalDensity;
        }else if (line.compare(0, 2, "d") == 0) {
            iss >> trash >> currMtl.dissolve;
        }else if (line.compare(0, 6, "illum") == 0) {
            iss >> trash >> currMtl.illumination;
        }else if (line.compare(0, 7, "map_Kd") == 0) {
            string texturePath;
            iss >> trash >> texturePath;

            if (const auto it = pathMap.find(texturePath); it != pathMap.end()) {
                currMtl.textureId = it->second;
            }else {
                const auto id = static_cast<uint16_t>(texturePaths.size());
                texturePaths.push_back(texturePath);
                pathMap[texturePath] = id;
                currMtl.textureId = id;
            }
        }
    }
    if (currName.empty()) return false;
    mtls[currName] = currMtl;
    return true;
}