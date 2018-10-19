// This file is part of Voodoo Engine.
//
// Voodoo Engine is free software : you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Voodoo Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Foobar.  If not, see <https://www.gnu.org/licenses/>.

#ifndef VOODOO_GRAPHICS_API_H_
#define VOODOO_GRAPHICS_API_H_

#include "window.h"

namespace voodoo {
class Renderer;
class Camera;

class GraphicsAPI {
 public:
  virtual bool Init(std::shared_ptr<Window> window) = 0;
  virtual bool Render(std::shared_ptr<Renderer> renderer,
                      std::shared_ptr<Camera> camera) = 0;
};
}  // namespace voodoo

#endif