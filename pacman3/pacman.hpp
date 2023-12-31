#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "abcgOpenGL.hpp"

struct Vertex {
  glm::vec3 position{};
  glm::vec3 normal{};

  friend bool operator==(Vertex const &, Vertex const &) = default;
};

class Pacman {

public:

  // Funções de renderização
  void loadObj(std::string_view path, bool standardize = true);
  void render(int numTriangles = -1) const;
  void setupVAO(GLuint program);
  void destroy() const;

  [[nodiscard]] int getNumTriangles() const {
    return gsl::narrow<int>(m_indices.size()) / 3;
  }

private:

  GLuint m_VAO, m_VBO, m_EBO;
  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;
  
  void createBuffers();
  void standardize();
};

#endif