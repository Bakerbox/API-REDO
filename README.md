# API-REDO

# Modern C++ Code Refactoring Presentation


## Slide 2: Issue - Incorrect RAII Implementation
- **Problem**: Resources not properly managed with RAII principles
- **Better Approach**: Implement proper constructors, destructors, and move operations
- **Code Example**:
```cpp
// Before
explicit TextureResource(const std::string& path) noexcept {
    texture = LoadTexture(path.c_str());
}

// After
explicit TextureResource(const std::string& path) {
    texture = LoadTexture(path.c_str());
    if (texture.id == 0) {
        throw std::runtime_error("Failed to load texture: " + path);
    }
}
```
- **Citation**: "Classes that have pointer members should define appropriate special member functions (copy/move constructors and copy/move assignment operators)" - C++ Core Guidelines R.21

## Slide 3: Issue - Two-Phase Initialization
- **Problem**: Objects initialized in constructor and then in separate function calls
- **Better Approach**: Complete initialization in constructor using member initializer lists
- **Code Example**:
```cpp
// Before
Game::Game(State state) : background(600)
{
    Reset();
    player = Player();
    gameState = state;
}

// After
Game::Game(State initialState)
    : gameState(initialState),
      score(0),
      // ... other initializations
      player(std::make_unique<Player>()),
      background(std::make_unique<Background>(600))
{
    // Initialize game state
    Reset();
}
```
- **Citation**: "Avoid 'naked' new and delete" - C++ Core Guidelines R.11, "Use constructor/destructor pairs to represent resource acquisition and release" - C++ Core Guidelines R.1

## Slide 4: Issue - Improper Exception Handling
- **Problem**: Functions marked noexcept that can throw, no exception handling
- **Better Approach**: Proper exception specification and handling
- **Code Example**:
```cpp
// Before
void InsertNewHighScore(std::string name) noexcept;
Texture2D GetPlayerTextureAtIndex(int index) noexcept { return *shipTextures.at(index)->get(); }

// After
void InsertNewHighScore(const std::string& name);
const Texture2D& GetPlayerTexture(size_t index) const {
    if (index >= shipTextures.size()) {
        throw std::out_of_range("Ship texture index out of range");
    }
    return shipTextures[index]->get();
}
```
- **Citation**: "Mark functions that won't throw as noexcept" - C++ Core Guidelines F.6, "Use exceptions for error handling only" - C++ Core Guidelines E.2

## Slide 5: Issue - Poor Type System Usage
- **Problem**: Using enum for entity types instead of C++ type system
- **Better Approach**: Leverage polymorphism and the visitor pattern
- **Code Example**:
```cpp
// Before
enum struct EntityType { PLAYER, ENEMY, PLAYER_PROJECTILE, ENEMY_PROJECTILE };
if (projectile.GetType() == EntityType::PLAYER_PROJECTILE) {
    HandlePlayerProjectileCollisions(projectile);
}

// After
// Type-safe visitor pattern for collision detection
virtual bool CollideWith(const Entity& other) const = 0;
virtual bool CollideWith(const Player& player) const = 0;
virtual bool CollideWith(const Alien& alien) const = 0;
virtual bool CollideWith(const Projectile& projectile) const = 0;
virtual bool CollideWith(const Wall& wall) const = 0;
```
- **Citation**: "Use class hierarchies to represent concepts with inherent hierarchical structure" - C++ Core Guidelines H.2, "Use virtual functions to represent customization points" - C++ Core Guidelines C.120

## Slide 6: Issue - Char Arrays vs std::string
- **Problem**: Using char arrays instead of std::string
- **Better Approach**: Use std::string for text handling
- **Code Example**:
```cpp
// Before
char name[9 + 1] = "\0";  
int letterCount = 0;

// After
std::string playerName;
int letterCount = 0;
```
- **Citation**: "Prefer standard library string to C-style strings" - C++ Core Guidelines SL.str.1, "Use std::string to own character sequences" - C++ Core Guidelines R.2

## Slide 7: Issue - Vector Growth and Memory Management
- **Problem**: Not reserving space for vectors, repeated push_back
- **Better Approach**: Reserve space and use emplace_back
- **Code Example**:
```cpp
// Before
for (int i = 0; i < wallCount; ++i) {
    Wall newWall({ wall_Spacing * (i + 1), wall_Y });
    Walls.push_back(newWall);
}

// After
walls.reserve(wallCount);
for (int i = 0; i < wallCount; ++i) {
    walls.emplace_back(Vector2{wallSpacing * (i + 1), wallY});
}
```
- **Citation**: "Reserve space for STL containers if the number of elements is known" - C++ Core Guidelines Perf.5, "For simple parameters, pass by value" - C++ Core Guidelines F.16

## Slide 8: Issue - Random Number Generation
- **Problem**: Using C-style rand() without seeding
- **Better Approach**: Modern C++ random number generation with proper seeding
- **Code Example**:
```cpp
// Before
int const randomAlienIndex = (Aliens.size() > 1) ? rand() % Aliens.size() : 0;

// After
// Seed the random number generator with current time
unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
rng.seed(seed);
// ...
std::uniform_int_distribution<size_t> dist(0, aliens.size() - 1);
size_t randomAlienIndex = dist(rng);
```
- **Citation**: "Prefer <random> to rand()" - C++ Core Guidelines ES.46, "Avoid magic constants" - C++ Core Guidelines ES.45

## Slide 9: Issue - Macros vs constexpr
- **Problem**: Using macros instead of constexpr
- **Better Approach**: Use constexpr for compile-time constants
- **Code Example**:
```cpp
// Before
#define screenWidth  1920
#define screenHeight  1080
#define alienOffset 40

// After
constexpr int screenWidth = 1920;
constexpr int screenHeight = 1080;
constexpr float ALIEN_OFFSET = 40.0f;
```
- **Citation**: "Prefer constexpr to const for values known at compile time" - C++ Core Guidelines Con.5, "Avoid macros" - C++ Core Guidelines ES.31

## Slide 10: Issue - Inconsistent Initialization
- **Problem**: Mixing direct initialization, member initialization list, and in-constructor assignment
- **Better Approach**: Consistent use of member initialization lists
- **Code Example**:
```cpp
// Before
Player() noexcept
{
    radius = 50; 
    float const window_width = static_cast<float>(GetScreenWidth());
    position.x = window_width / 2;
    position.y = static_cast<float>(GetScreenHeight()) - 50.0f;
}

// After
Player()
    : Entity({static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) - 50.0f}, 50.0f),
      lives(3),
      speed(7.0f),
      frameTimer(0.0f),
      textureFrame(0),
      playerBaseHeight(70.0f)
{
    // All initialization done in initializer list
}
```
- **Citation**: "Use member initializers instead of assignment" - C++ Core Guidelines C.49, "Initialize members in the order of member declaration" - C++ Core Guidelines C.48

## Slide 12: Summary of Improvements

- Implemented proper RAII throughout the codebase
- Replaced EntityType enum with C++ polymorphism
- Fixed exception handling and specifications
- Replaced char arrays with std::string
- Improved vector usage with reserve and emplace_back
- Used modern C++ random number generation
- Replaced macros with constexpr
- Consistent initialization patterns
- Clear resource ownership
- Improved code readability and maintainability

