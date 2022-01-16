#include "Fire.hpp"

static RGBA g_firePallete[] = {{7,7,7,255},
              {31,7,7,255}, {47,15,7,255},
              {71,15,7,255}, {87,23,7,255},
              {103,31,7,255}, {119,31,7,255},
              {143,39,7,255}, {159,47,7,255},
              {175,63,7,255}, {191,71,7,255},
              {199,71,7,255}, {223,79,7,255},
              {223,87,7,255}, {223,87,7,255},
              {215,95,7,255}, {215,95,7,255},
              {215,103,15,255}, {207,111,15,255},
              {207,119,15,255}, {207,127,15,255},
              {207,135,23,255},{199,135,23,255},
              {199,143,23,255},{199,151,31,255},
              {191,159,31,255},{191,159,31,255},
              {191,167,39,255},{191,167,39,255},
              {191,175,47,255},{183,175,47,255},
              {183,183,47,255},{183,183,55,255},
              {207,207,111,255},{223,223,159,255},
              {239,239,199,255},{255,255,255,255}
};


Fire::Fire(unsigned int width, unsigned int height) {
  m_width = width;
  m_height = height;
  m_firePixels = new int[width*height];
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++){
      if (row==height-1) {
        m_firePixels[row*width + col] = 36;
      }
      else {
        m_firePixels[row*width + col] = 0;
      }
    }
  }
}

Fire::~Fire() {
  delete[] m_firePixels;
}

void Fire::SpreadFire(int from) {
  int rand = std::rand() % 4;
  int to = from - m_width - rand + 1;
  // Chose to divide by three to make the fire
  //taller without effecting to variable
  m_firePixels[to] = m_firePixels[from] - rand/3;
}

sf::Uint8* Fire::SpreadFireWave(){
  sf::Uint8* pixels = new sf::Uint8[m_height*m_width*4];

  for (int row = 0; row < m_height; row++){
    for (int col = 0; col < m_width; col++) {
      int index = m_firePixels[row * m_width + col];
      pixels[((m_width * row) + col) * 4]
        = g_firePallete[index].r;
      pixels[((m_width * row) + col) * 4 + 1]
        = g_firePallete[index].g;
      pixels[((m_width * row) + col) * 4 + 2]
        = g_firePallete[index].b;
      pixels[((m_width * row) + col) * 4 + 3]
        = g_firePallete[index].a;
    }
  }
  return pixels;
}

void Fire::DoFire() {
  for(int col = 0; col < m_width; col++) {
        for (int row = 1; row < m_height; row++) {
            SpreadFire(row * m_width + col);
        }
    }
}

void Fire::Render(sf::RenderWindow& window) {
  DoFire();
  sf::Texture texture;
  texture.create(m_width, m_height);
  texture.update(SpreadFireWave());
  sf::Sprite sprite(texture);
  window.draw(sprite);
}

//g++ -std=c++17 -g main.cpp Fire.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system
