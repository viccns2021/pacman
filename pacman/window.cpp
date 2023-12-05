#include "window.hpp"

#include <chrono>
#include <random>
#include <unordered_map>

// Explicit specialization of std::hash for Vertex

template <> struct std::hash<Vertex> {
  size_t operator()(Vertex const &vertex) const noexcept {
    auto const h1{std::hash<glm::vec3>()(vertex.position)};
    return h1;
  }
};


void Window::onEvent(SDL_Event const &event) {
 if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_UP )
      m_dollySpeed = 1.0f;
    if (event.key.keysym.sym == SDLK_DOWN )
      m_dollySpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_LEFT )
      m_panSpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_RIGHT )
      m_panSpeed = 1.0f;
    if (event.key.keysym.sym == SDLK_q)
      m_truckSpeed = -1.0f;
    if (event.key.keysym.sym == SDLK_e)
      m_truckSpeed = 1.0f;
  }
  if (event.type == SDL_KEYUP) {
    if ((event.key.keysym.sym == SDLK_UP ) &&
        m_dollySpeed > 0)
      m_dollySpeed = 0.0f;
    if ((event.key.keysym.sym == SDLK_DOWN ) &&
        m_dollySpeed < 0)
      m_dollySpeed = 0.0f;
    if ((event.key.keysym.sym == SDLK_LEFT ) &&
        m_panSpeed < 0)
      m_panSpeed = 0.0f;
    if ((event.key.keysym.sym == SDLK_RIGHT ) &&
        m_panSpeed > 0)
      m_panSpeed = 0.0f;
    if (event.key.keysym.sym == SDLK_q && m_truckSpeed < 0)
      m_truckSpeed = 0.0f;
    if (event.key.keysym.sym == SDLK_e && m_truckSpeed > 0)
      m_truckSpeed = 0.0f;
  }

    if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_d)
      speed_x = 1.0f;
    if (event.key.keysym.sym == SDLK_a)
      speed_x = -1.0f;
    if (event.key.keysym.sym == SDLK_s)
      speed_z = 1.0f;
    if (event.key.keysym.sym == SDLK_w)
      speed_z  = -1.0f;
  }

  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE && !isJumping) {
        isJumping = true;
    }

  if (event.type == SDL_KEYUP) {
    if ((event.key.keysym.sym == SDLK_d) &&
        speed_x > 0 )
        speed_x = 0.0f;
    if ((event.key.keysym.sym == SDLK_a) &&
        speed_x < 0)
      speed_x = 0.0f;
    if ((event.key.keysym.sym == SDLK_s) &&
        speed_z > 0)
      speed_z = 0.0f;
    if ((event.key.keysym.sym == SDLK_w) && 
      speed_z < 0)
      speed_z = 0.0f;
}
}

void Window::onCreate() {

  auto const &assetsPath{abcg::Application::getAssetsPath()};

  abcg::glClearColor(0, 0, 0, 1);

  // Enable depth buffering
  abcg::glEnable(GL_DEPTH_TEST);

  // Create program
  m_program = abcg::createOpenGLProgram({{.source = assetsPath + "lookat.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "lookat.frag",
                                  .stage = abcg::ShaderStage::Fragment}});

  m_ground.create(m_program);

  m_pacman.loadObj(assetsPath + "pacman.obj");
  m_pacman.setupVAO(m_program);

  m_cube.loadObj(assetsPath + "cube.obj");
  m_cube.setupVAO(m_program);

  // Get location of uniform variables

  m_viewMatrixLocation = abcg::glGetUniformLocation(m_program, "viewMatrix");
  m_projMatrixLocation = abcg::glGetUniformLocation(m_program, "projMatrix");
  m_modelMatrixLocation = abcg::glGetUniformLocation(m_program, "modelMatrix");
  m_colorLocation = abcg::glGetUniformLocation(m_program, "color");
  
  // Generate VBO
  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER,
                     sizeof(m_vertices.at(0)) * m_vertices.size(),
                     m_vertices.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Generate EBO
  abcg::glGenBuffers(1, &m_EBO);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  abcg::glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(m_indices.at(0)) * m_indices.size(),
                     m_indices.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Create VAO
  abcg::glGenVertexArrays(1, &m_VAO);

  // Bind vertex attributes to current VAO
  abcg::glBindVertexArray(m_VAO);

  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  auto const positionAttribute{
      abcg::glGetAttribLocation(m_program, "inPosition")};
  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE,
                              sizeof(Vertex), nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

  // End of binding to current VAO
  abcg::glBindVertexArray(0);
}

void Window::onPaint() {

  // Clear color buffer and depth buffer
  abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

  abcg::glUseProgram(m_program);

  // Set uniform variables for viewMatrix and projMatrix
  // These matrices are used for every scene object
  abcg::glUniformMatrix4fv(m_viewMatrixLocation, 1, GL_FALSE,
                           &m_camera.getViewMatrix()[0][0]);
  abcg::glUniformMatrix4fv(m_projMatrixLocation, 1, GL_FALSE,
                           &m_camera.getProjMatrix()[0][0]);

  abcg::glBindVertexArray(m_VAO);


  glm::mat4 modelMatrix{1.0f};
  modelMatrix = glm::translate(modelMatrix, glm::vec3(position_x, position_y, position_z));
  modelMatrix = glm::rotate(modelMatrix, glm::radians(rotate), glm::vec3(0, 1, 0));
  modelMatrix = glm::scale(modelMatrix, glm::vec3(0.002f));
  abcg::glUniform4f(m_colorLocation, 1.0f, 1.0f, 0.0f, 1.0f);
  abcg::glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);
  m_pacman.render();

  abcg::glBindVertexArray(0);
  
  glm::mat4 modelMatrix2{1.0f};
  modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(1.0f, 0.0f, 0.0f));
  modelMatrix2 = glm::rotate(modelMatrix2, glm::radians(0.0f), glm::vec3(0, 1, 0));
  modelMatrix2 = glm::scale(modelMatrix2, glm::vec3(0.2));
  abcg::glUniform4f(m_colorLocation, 1.0f, 1.0f, 0.0f, 1.0f);
  abcg::glUniformMatrix4fv(m_modelMatrixLocation, 1, GL_FALSE, &modelMatrix2[0][0]);
  m_cube.render();


  // Draw ground

  m_ground.paint();

  abcg::glUseProgram(0);
}

void Window::onPaintUI() { abcg::OpenGLWindow::onPaintUI(); }

void Window::onResize(glm::ivec2 const &size) {
  m_viewportSize = size;
  m_camera.computeProjectionMatrix(size);
}

void Window::onDestroy() {
  m_ground.destroy();

  abcg::glDeleteProgram(m_program);
  abcg::glDeleteBuffers(1, &m_EBO);
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}


void Window::onUpdate() {


auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};

if (isJumping) {
        jumpTime += deltaTime;
    }

    // Atualize a posição vertical usando uma função quadrática para criar o movimento de pulo
    position_y = jumpHeight * (jumpSpeed * jumpTime - 0.5f * gravity * jumpTime * jumpTime);

    // Se o objeto atingiu o solo, pare o pulo
    if (position_y <= 0.0f) {
        position_y = 0.0f;
        jumpTime = 0.0f;
        isJumping = false;
    }

    // Atualize as outras posições (horizontal e profundidade) de acordo com as entradas do teclado
    if (speed_x != 0) {
        position_x += (speed_x * deltaTime);

        if (speed_x > 0) {
        rotate = -90.0f;

    }
    else{
      rotate = 90.0f;
    }

    } else {
        position_x = position_x;
        rotate = rotate;
    }

    if (speed_y != 0) {
        position_y += (speed_y * deltaTime);
        
        
    } else {
        position_y = position_y;
    }

    if (speed_z != 0) {
        position_z += (speed_z * deltaTime);
        if (speed_z > 0) {
        rotate = 180.0f;

    }
    else{
      rotate = 0.0f;
    }
    } else {
        position_z = position_z;
        rotate = rotate;
    }
  
  // Update LookAt camera
  m_camera.dolly(m_dollySpeed * deltaTime);
  m_camera.truck(m_truckSpeed * deltaTime);
  m_camera.pan(m_panSpeed * deltaTime);

}