#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <Eigen/Core>

class WavefrontObject {
public:
  WavefrontObject() {
  }

  ~WavefrontObject() {
  }

  void clear() {
    m_vertexs.clear();
    m_normals.clear();
    m_colors.clear();
    m_faces.clear();
  }

  int load_from_file(const char* file_path) {
    clear();

    std::ifstream fin(file_path);
    if(fin.fail()) {
      printf("open file %s error\n", file_path);
      return -1;
    }

    std::string line;
    while(!fin.eof()) {
      std::getline(fin, line);
      std::istringstream iss(line.c_str());

      char trash;
      if(!line.compare(0, 2, "v ")) {
        iss >> trash;
        Eigen::Vector3f v;
        Eigen::Vector3f c;
        iss >> v(0) >> v(1) >> v(2) >> c(0) >> c(1) >> c(2);
        m_vertexs.emplace_back(v);
        m_colors.emplace_back(c);
      } else if(!line.compare(0, 3, "vn ")) {
        iss >> trash >> trash;
        Eigen::Vector3f n;
        iss >> n(0) >> n(1)>> n(2);
        m_normals.emplace_back(n);
      } else if(!line.compare(0, 2, "f ")) {
        iss >> trash;
        Eigen::Vector3i f;
        iss >> f(0) >> f(1) >> f(2);
        f = f -  Eigen::Vector3i(1, 1, 1);
        m_faces.emplace_back(f);
      }
    }
    fin.close();
    
    return 0;
  }

  int save_to_file(const char* file_path) {
    FILE* fp = fopen(file_path, "w");
    if(!fp) {
      printf("open file %s error\n", file_path);
      return -1;
    }

    for(int n = 0; n < m_vertexs.size(); ++n) {
      fprintf(fp, "v %f %f %f\n", m_vertexs[n][0], m_vertexs[n][1], m_vertexs[n][2]);
      fprintf(fp, "vn %f %f %f\n", m_normals[n][0], m_normals[n][1], m_normals[n][2]);
    }
    for(int n = 0; n < m_faces.size(); ++n) {
      fprintf(fp, "f %d %d %d\n", m_faces[n][0] + 1, m_faces[n][1] + 1, m_faces[n][2] + 1);
    }

    fclose(fp);

    return 0;
  }

  int vertex_nums() const {
    return m_vertexs.size();
  }

  int normal_nums() const {
    return m_normals.size();
  }

  int face_nums() const {
    return m_faces.size();
  }

  std::vector<Eigen::Vector3f> m_vertexs;
  std::vector<Eigen::Vector3f> m_normals;
  std::vector<Eigen::Vector3f> m_colors;
  std::vector<Eigen::Vector3i> m_faces;
};
