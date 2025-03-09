### 1. **Functional Requirements**

#### 1.1 **Character Control**

- The player can move **left and right**.
- The player can **jump** (only if on a surface).
- The player can **use weapons** (shoot).
- The player can **pick up items** (coins, bonuses).

#### 1.2 **Coins**

- Coins are scattered across the level.
- When the player **or a bullet** comes in contact with a coin, the **coin disappears**.
- The number of collected coins is displayed **in the top left corner of the screen**.

#### 1.3 **Chests**

- Chests are placed in specific locations on the level.
- The player can **open a chest** by dealing damage with a weapon.
- After opening, with a **1/3 chance**, one of the following bonuses is dropped:
    1. **Health Pack** (+1/3 HP).
    2. **Invincibility Orb** (grants invincibility for **10 seconds**).
    3. **Speed Berry** (increases speed by **35%** for **10 seconds**).
- After opening, the chest **disappears**.

#### 1.4 **Weapons**

- There are **four types of weapons** in the game:
    1. **Minigun** – high fire rate, **low damage**.
    2. **Assault Rifle** – medium fire rate, **medium damage**.
    3. **Double-barrel Rifle** – low fire rate, **high damage**.
    4. **Pistol** - low fire rate, **low damage**.
- The player can **carry only one weapon** at a time.
- Bullet damage depends on the weapon type.

#### 1.5 **Moving Platforms**

- There are **horizontal** and **vertical** platforms in the game.
- They move **between fixed points**.
- At the extreme points, they **stop for 1.5 seconds**, then continue moving in the opposite direction.
- The player can **stand on a platform** and move with it.

#### 1.6 **Enemies**

##### 1.6.1 **Normal Enemy**

- Moves **left-right** until it hits a wall, then turns around.

##### 1.6.2 **Jumping Enemy**

- Moves along a surface and **periodically jumps** at random intervals.

##### 1.6.3 **Flying Enemy**

- Similar to the normal enemy, but **flies** within a limited space.

##### 1.6.4 **Armored Jumping Enemy**

- Moves along a surface and **periodically jumps** at random intervals.

##### 1.6.5 **Armored Normal Enemy**

- The normal enemy but with **increased health**.

##### 1.6.6 **Armored Flying Enemy**

- The flying enemy but with **increased health**.

---

### 2. **Non-functional Requirements**

- **Frame Rate (FPS):** at least **60 frames per second**.
- **Graphics:** Support for screen resolutions **800x600 and above**.

---

### 3. **Use Case Scenarios**

#### **Use Case 1: Coin Collection**

**Precondition:** Coins are present in the level.

1. The player controls the character.
2. The character touches a coin.
3. The coin disappears.
4. The coin counter in the top left corner increases by **+1**.

#### **Use Case 2: Opening a Chest**

**Precondition:** A chest is present in the level.

1. The player approaches the chest.
2. The player deals damage to the chest with a weapon.
3. The chest disappears.
4. With a 1/3 chance, one of the bonuses (health pack, invincibility orb, or speed berry) is dropped.
5. The bonus is added to the player's inventory.

#### **Use Case 3: Combat with Enemies**

**Precondition:** The enemy is within the player’s line of sight.

1. The player selects a weapon.
2. The player shoots.
3. The bullet hits the enemy.
4. The enemy receives damage.
5. If the enemy’s health reaches **0 HP**, it disappears.

#### **Use Case 4: Using Moving Platforms**

**Precondition:** The platform is moving between two points.

1. The player jumps onto the platform.
2. The platform moves with the player.
3. At the extreme point, the platform stops for **1.5 seconds**.
4. The platform continues moving in the opposite direction.

---

This translation and breakdown of functional and non-functional requirements along with use case scenarios provide a clear and structured framework for the game development process.