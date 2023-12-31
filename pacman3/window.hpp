#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"

#include "camera.hpp"
#include "ground.hpp"
#include "pacman.hpp"
#include "cube.hpp"
#include "model.hpp"
#include <chrono>




class Window : public abcg::OpenGLWindow {
protected:
  void onEvent(SDL_Event const &event) override;
  void onCreate() override;
  void onPaint() override;
  void onPaintUI() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;
  void onUpdate() override;
  void loadModelFromFile(std::string_view path);

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
  float speed_x{};
  float speed_y{};
  float speed_z{};
  float position_x=0.0f;
  float position_y=0.0f;
  float position_z=0.0f;
  float rotate=0.0f;
  float cubePosition_z = 0;
  float cubePosition_y = 0;
  float cubePosition_x = 1;
  float cubeHeight = .12;

  float jumpHeight = .50f;   // Altura máxima do pulo
  float jumpSpeed = 5.0f;    // Velocidade inicial do pulo
  float gravity = 9.8f;      // Aceleração devida à gravidade
  float jumpTime = 0.0f;     // Tempo decorrido desde o início do pulo
  bool isJumping = false;    // Flag indicando se o objeto está pulando


  Ground m_ground;
  Pacman m_pacman;
  Cube m_cube;
  Model m_model;

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;

};

#endif