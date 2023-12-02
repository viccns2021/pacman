#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"

#include "camera.hpp"
#include "ground.hpp"

struct Vertex {
  glm::vec3 position;

  friend bool operator==(Vertex const &, Vertex const &) = default;
};

class Window : public abcg::OpenGLWindow {
protected:
  void onEvent(SDL_Event const &event) override;
  void onCreate() override;
  void onPaint() override;
  void onPaintUI() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;
  void onUpdate() override;

private:
  glm::ivec2 m_viewportSize{};

  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};
  GLuint m_program{};

  GLint m_viewMatrixLocation{};
  GLint m_projMatrixLocation{};
  GLint m_modelMatrixLocation{};
  GLint m_colorLocation{};

  Camera m_camera;

  float m_dollySpeed{};
  float m_truckSpeed{};
  float m_panSpeed{};
  float radians{};
  float speed_x{};
  float speed_y{};
  float speed_z{};
  float position_x=0;
  float position_y=0;
  float position_z=0;
  float rotate=0;

  float jumpHeight = 0.8f;   // Altura máxima do pulo
  float jumpSpeed = 5.0f;    // Velocidade inicial do pulo
  float gravity = 9.8f;      // Aceleração devida à gravidade

  float jumpTime = 0.0f;     // Tempo decorrido desde o início do pulo
  bool isJumping = false;    // Flag indicando se o objeto está pulando


  Ground m_ground;

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;

  void loadModelFromFile(std::string_view path);
};

#endif