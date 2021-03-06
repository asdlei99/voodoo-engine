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
// along with Voodoo Engine.  If not, see <https://www.gnu.org/licenses/>.

#ifndef VOODOO_CAMERA_H_
#define VOODOO_CAMERA_H_

#include "component.h"

namespace voodoo {
class Camera : public Component {
 public:
  Camera();

  float4x4 GetViewMatrix();
  float4x4 GetProjectionMatrix();

 private:
  float fov_, aspect_ratio_, z_near_, z_far_;
};
}  // namespace voodoo

#endif