WEEK 1:
- Initialized the project

WEEK 2:
- Vectors
   - Added a base class for a vectors of variable dimensions
   - Added subclasses for vectors of 2, 3 and 4 dimensions
   - Implemented operations for vectors:
      - adition and sutraction of vectors
      - multiplication and division by scalar
      - dot product
      - cross product for 3D vectors
      - magnitude
      - normalization
      - assignment operators
      - relational operators
   - Added constants for the vector classes
   - Added tests for the vector classes
- Matrices
   - Added a base class for square matrices of variable sizes
   - Added subclasses for 2×2, 3×3 and 4×4 matrices
   - Implemented operations for matrices:
      - adition and subtraction of matrices
      - multiplication by scalar, vector and matrix
      - division by scalar
      - transpose
      - inverse
      - assignment operators
      - relational operators
   - Added constants for the matrix classes
   - !! Need to add more tests for the matrix classes !!

WEEK 3:
- Code Cleanup
   - Divided the math library into multiple classes
   - Pushed non-template class implementation into cpp files
- Axis Angle
   - Added the conversion into an equivalent quatertion
   - Added a rotation of 3D vector operation
   - !! Need to add more tests for the AxisAngle class !!
- Quaternion
   - Quaternion inherit from the class for 4D vectors
   - Aditional implemented operations for quaternions:
      - multiplication by another quaternion
      - conjugate
      - inverse
      - logarithm
      - exponential
      - rotation of 3D vector
      - lerp and slerp
   - Creation of equivalent axis angle and rotation matrix
   - !! Need to add more tests for the quaternion class !!
- !! Matrix classes still require additional testing !!

WEEK 4 + 5:
- Further divided the math library into multiple files for each class
- Camera class
   - Projection matrix:
      - perspective + orthographic
   - View Matrix
- Camera Buffer
   - Single container for both perspective and view matrix
   - Sends data to the shader program
   - Keeps buffer updated
- Scene Camera
   - Rotation around point (left mouse button)
   - Zoom (mouse wheel)
   - Translation of camera (right mouse button)
   - Added Axis lines

WEEK 6:
- Mesh class
   - Stores all the information about the mesh
      - vertex positions
      - vertex normals
      - vertex texture coordinates
      - indices to build the mesh
   - Model transformations
      - scale
      - translation
      - rotation
   - Generation of mesh needs to be implemented
- Model buffer class
   - Stores and sends information to the shader program
   - Same data as Mesh class + texture
   - Allows rendering of model

WEEK 7:
- Light class
   - Stores all the information about a single light
      - light position (point light) or direction from which it shines (directional light)
      - attenuation
      - light colors (ambient, diffuse, specular)
- Light buffer class
   - Stores and sends information to the shader program
   - Manages lights that illuminate the scene
   - Lighting calculated in the shader calculating Phong illumination model
- Phong illumination shader
   - Illuminates all models in the scene
   - Model material to control its color and surface properties
   - Multiple lights used for illumination

MILESTONE:
- Finished mesh generation
   - Paddle
      - variable width, height, angle and the number of parts
   - Ball
      - variable number of parts
- Polar coordinates class
   - Conversion between 2d vector
   - Nomalization of angle

WEEK 9 + 10:
- Added PhysicsObject class to handle the physics simulation
   - bounce method to change the direction of the object base on collided surfaces normal
   - Bounce factor to change the objects force with each bounce
   - Move to change the object's position based on its direction and change in time
- Added SceneObject class to handle the updates with each frame
   - update to update the object with each frame
   - late_update method to update the object after the update was called on all scene objects
   - physics_update method to handle the object's physics simulation
   - start to initialize the object on the first frame
   - Added subclasses to handle each object type in the scene
      - SceneModelObject to handle models without physics
      - ScenePhysicsObject to handle models with physics
      - SceneCameraObject to handle the camera
      - SceneLightObject to handle the light
   - Each of these subclasses will handle the communication with the buffers and keep them updated

FINAL:
- Added collision detection
   - Only collision between circle collider and paddle collider
      - Ball collider collides with paddle colliders
      - Ball bounces on collision
      - Paddle collider is unaffected by collision
   - Added game scene objects
      - Ball moves through the scene and bounces from bricks, Game Over if it exits the playing area
      - Bricks stacked on top of each other, Victory if no bricks remain
      - Paddles that the player coltrols to stop the ball leaving the playing area
- Added scene states:
   - Running, Paused, Victory, Game Over
   - Added GUI rendering for pause, victory and game over states
   - Added time factor to slow game speed
- Added advanced graphics:
   - Added UVs for paddles and balls
   - Added a transparent area around the ball if occluded
   - Normal mapping for better lighting
   - Shadow mapping from a single light source
   - Skybox