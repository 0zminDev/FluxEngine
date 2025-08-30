# FluxEngine Logger API - Game Developer Guide

## Quick Start

The FluxEngine Logger provides an easy-to-use logging system for your game development needs. Simply include the engine and start logging!

```cpp
#include <FluxEngine.h>

int main() {
    Flux::Core::Engine engine;
    engine.init();
    
    auto* logger = engine.getLogger();
    logger->Info("Game started successfully!");
    
    return 0;
}
```

## Basic Logging

### Getting the Logger

```cpp
// Initialize the engine first
Flux::Core::Engine engine;
engine.init();

// Get the logger instance
auto* logger = engine.getLogger();
```

### Log Levels

The logger provides 6 different log levels, from most detailed to most critical:

```cpp
logger->Trace("Detailed debugging info");     // Very detailed execution flow
logger->Debug("Development debugging");       // Debug information
logger->Info("General information");          // Normal operation info
logger->Warn("Something might be wrong");     // Warning conditions
logger->Error("Something went wrong");        // Error conditions
logger->Fatal("Critical system failure");    // Fatal errors
```

### When to Use Each Level

| Level | When to Use | Example |
|-------|-------------|---------|
| **Trace** | Very detailed execution flow | "Player position updated to (10, 20, 30)" |
| **Debug** | Development debugging | "Loading texture: player_sprite.png" |
| **Info** | General game information | "Level loaded: Forest_Level_01" |
| **Warn** | Potential issues | "Low memory warning: 85% used" |
| **Error** | Something went wrong | "Failed to load audio file: missing.wav" |
| **Fatal** | Critical failures | "Graphics driver not found" |

## Common Game Development Use Cases

### Loading Game Assets

```cpp
void GameAssetManager::loadLevel(const std::string& levelName) {
    auto* logger = engine.getLogger();
    
    logger->Info("Starting to load level: " + levelName);
    
    if (!fileExists(levelName + ".json")) {
        logger->Error("Level file not found: " + levelName + ".json");
        return;
    }
    
    logger->Debug("Loading textures for level: " + levelName);
    loadTextures(levelName);
    
    logger->Debug("Loading audio for level: " + levelName);
    loadAudio(levelName);
    
    logger->Info("Level loaded successfully: " + levelName);
}
```

### Game State Management

```cpp
void GameStateManager::changeState(GameState newState) {
    auto* logger = engine.getLogger();
    
    logger->Info("Changing game state from " + 
                getCurrentStateName() + " to " + getStateName(newState));
    
    // Cleanup current state
    if (currentState) {
        logger->Debug("Cleaning up current state");
        currentState->cleanup();
    }
    
    // Initialize new state
    logger->Debug("Initializing new state");
    currentState = createState(newState);
    
    if (!currentState->initialize()) {
        logger->Error("Failed to initialize new game state");
        return;
    }
    
    logger->Info("Game state changed successfully");
}
```

### Player Actions and Events

```cpp
class Player {
    auto* logger = engine.getLogger();
    
public:
    void takeDamage(int damage) {
        logger->Debug("Player taking " + std::to_string(damage) + " damage");
        
        health -= damage;
        
        if (health <= 0) {
            logger->Info("Player health reached zero - triggering death");
            triggerDeath();
        } else if (health < 20) {
            logger->Warn("Player health critical: " + std::to_string(health));
        }
    }
    
    void levelUp() {
        level++;
        logger->Info("Player leveled up! New level: " + std::to_string(level));
    }
};
```

### Performance Monitoring

```cpp
class GameLoop {
    auto* logger = engine.getLogger();
    
public:
    void update(float deltaTime) {
        // Monitor frame time
        if (deltaTime > 0.033f) { // More than 30 FPS
            logger->Warn("Frame time high: " + std::to_string(deltaTime) + "s");
        }
        
        // Monitor memory usage
        size_t memoryUsed = getMemoryUsage();
        if (memoryUsed > MAX_MEMORY * 0.9f) {
            logger->Error("Memory usage critical: " + 
                         std::to_string(memoryUsed / 1024 / 1024) + " MB");
        }
    }
};
```

## Advanced Usage

### Conditional Logging

Use conditional logging to avoid performance impact in release builds:

```cpp
#ifdef DEBUG_BUILD
    logger->Debug("Detailed debug information that's expensive to compute");
#endif

// Or check build configuration at runtime
if (engine.isDebugMode()) {
    logger->Trace("Very detailed trace information");
}
```

### Logging Game Events

```cpp
class GameEventLogger {
    auto* logger = engine.getLogger();
    
public:
    void onPlayerDeath(Player* player) {
        logger->Info("Player died at position: " + 
                    player->getPosition().toString());
    }
    
    void onEnemySpawn(Enemy* enemy) {
        logger->Debug("Enemy spawned: " + enemy->getType() + 
                     " at " + enemy->getPosition().toString());
    }
    
    void onItemPickup(Item* item, Player* player) {
        logger->Info("Player picked up: " + item->getName());
    }
};
```

### Error Handling with Logging

```cpp
bool GameRenderer::initializeGraphics() {
    auto* logger = engine.getLogger();
    
    logger->Info("Initializing graphics system");
    
    if (!createWindow()) {
        logger->Fatal("Failed to create game window");
        return false;
    }
    
    if (!initializeVulkan()) {
        logger->Fatal("Failed to initialize Vulkan");
        return false;
    }
    
    if (!loadShaders()) {
        logger->Error("Failed to load some shaders - using fallbacks");
        loadFallbackShaders();
    }
    
    logger->Info("Graphics system initialized successfully");
    return true;
}
```

## Best Practices for Game Development

### 1. Use Appropriate Log Levels

```cpp
// ✅ GOOD - Appropriate levels
logger->Info("Game started");                    // Important game event
logger->Debug("Loading texture: sword.png");    // Development info
logger->Error("Failed to connect to server");   // Actual error

// ❌ BAD - Wrong levels
logger->Fatal("Player moved");                   // Not a fatal event
logger->Error("Loading complete");               // Not an error
```

### 2. Include Useful Context

```cpp
// ✅ GOOD - Includes context
logger->Error("Failed to load texture 'player_sword.png' from assets/textures/");
logger->Info("Player 'John' leveled up from 5 to 6");

// ❌ BAD - Lacks context
logger->Error("Failed to load");
logger->Info("Level up");
```

### 3. Don't Log in Hot Paths

```cpp
// ✅ GOOD - Conditional logging in update loop
void update(float deltaTime) {
    // Only log occasionally or when something changes
    static int frameCount = 0;
    if (++frameCount % 60 == 0) {  // Log once per second at 60 FPS
        logger->Debug("FPS: " + std::to_string(1.0f / deltaTime));
    }
}

// ❌ BAD - Logging every frame
void update(float deltaTime) {
    logger->Trace("Update called with deltaTime: " + std::to_string(deltaTime));
}
```

### 4. Use Structured Information

```cpp
// ✅ GOOD - Structured logging
logger->Info("Combat event - Attacker: Orc, Defender: Player, Damage: 25, Result: Hit");

// ❌ BAD - Unstructured
logger->Info("Orc hit player for 25 damage");
```

## Common Patterns

### Initialization Logging

```cpp
class GameSystem {
public:
    bool initialize() {
        auto* logger = engine.getLogger();
        
        logger->Info("Initializing " + getSystemName());
        
        // Log each initialization step
        logger->Debug("Loading configuration");
        if (!loadConfig()) {
            logger->Error("Failed to load configuration");
            return false;
        }
        
        logger->Debug("Allocating resources");
        if (!allocateResources()) {
            logger->Error("Failed to allocate resources");
            return false;
        }
        
        logger->Info(getSystemName() + " initialized successfully");
        return true;
    }
};
```

### Error Recovery Logging

```cpp
bool NetworkManager::reconnect() {
    auto* logger = engine.getLogger();
    
    logger->Warn("Connection lost - attempting to reconnect");
    
    for (int attempt = 1; attempt <= MAX_RETRIES; ++attempt) {
        logger->Debug("Reconnection attempt " + std::to_string(attempt));
        
        if (connect()) {
            logger->Info("Reconnected successfully after " + 
                        std::to_string(attempt) + " attempts");
            return true;
        }
        
        logger->Warn("Reconnection attempt " + std::to_string(attempt) + " failed");
        std::this_thread::sleep_for(std::chrono::seconds(attempt));
    }
    
    logger->Error("Failed to reconnect after " + std::to_string(MAX_RETRIES) + " attempts");
    return false;
}
```

## Performance Tips

### 1. Avoid Expensive String Operations

```cpp
// ✅ GOOD - Simple messages
logger->Info("Player died");

// ⚠️ CAREFUL - Expensive string building
logger->Debug("Player at (" + std::to_string(x) + ", " + std::to_string(y) + ")");

// ✅ BETTER - Use formatting sparingly
logger->Debug(formatString("Player at (%.2f, %.2f)", x, y));
```

### 2. Use Debug-Only Logging

```cpp
#ifdef DEBUG_BUILD
    logger->Debug("Expensive debug computation: " + computeExpensiveDebugInfo());
#endif
```

### 3. Consider Log Level Filtering

The logger automatically filters out lower-priority messages in release builds, so you don't need to worry about Trace and Debug messages affecting performance in shipped games.

## Integration with Game Architecture

### Component-Based Systems

```cpp
class HealthComponent {
    auto* logger = engine.getLogger();
    
public:
    void takeDamage(int amount) {
        logger->Debug("Health component taking " + std::to_string(amount) + " damage");
        health -= amount;
        
        if (health <= 0) {
            logger->Info("Entity health depleted - triggering death");
            triggerDeath();
        }
    }
};
```

### Game State Systems

```cpp
class GameStateSystem {
    auto* logger = engine.getLogger();
    
public:
    void transition(GameState from, GameState to) {
        logger->Info("State transition: " + stateToString(from) + " -> " + stateToString(to));
        
        // Implementation...
    }
};
```

The FluxEngine Logger is designed to be simple to use while providing powerful debugging and monitoring capabilities for your game development workflow. Start with basic Info and Error logging, then add Debug and Trace messages as needed during development.
