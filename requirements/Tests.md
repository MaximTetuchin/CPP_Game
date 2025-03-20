### **Testing Plan for Takaraima**

The testing plan will follow the structure of the system’s entities and classes, ensuring that each component behaves correctly according to its functionality. Below are specific test scenarios for the key objects in the game.

---

### **1. Entity Class**

#### **Test 1: Invincibility Ball (Entity)**

**Objective:** Verify that the invincibility ball works as expected when collected by the player.

- **Precondition:** The player is near an invincibility ball.
- **Test Steps:**
    1. The player collects the invincibility ball.
    2. Check if the invincibility status is applied to the player.
    3. Verify that the player is invincible for **5 seconds**.
    4. Ensure the invincibility ball disappears after being collected.
- **Expected Outcome:** Player becomes invincible for 5 seconds; invincibility ball disappears.

#### **Test 2: Med Kit (Entity)**

**Objective:** Verify that the med kit restores 35 hp of the player's health when collected.

- **Precondition:** The player has less than full health.
- **Test Steps:**
    1. The player collects the med kit.
    2. Check if the player's health increases by 35.
    3. Ensure the med kit disappears after being collected.
- **Expected Outcome:** Player's health increases by 35; med kit disappears.

#### **Test 3: Speed Berry (Entity)**

**Objective:** Verify that the speed berry works correctly when collected by the player.

- **Precondition:** The player is not under the effect of a speed berry.
- **Test Steps:**
    1. The player collects the speed berry.
    2. Check if the player's speed increases by **25%**.
    3. Ensure that the speed boost lasts for **10 seconds**.
    4. Ensure the speed berry disappears after being collected.
- **Expected Outcome:** Player's speed increases by 25% for 10 seconds; speed berry disappears.

#### **Test 4: Moving Platform**

**Objective:** Verify the movement and stop behavior of the moving platform.

- **Precondition:** The platform is moving between two fixed points.
- **Test Steps:**
    1. The player stands on the moving platform.
    2. Verify that the platform moves smoothly between its fixed points.
    3. Verify that the platform reverses direction after the stop.
- **Expected Outcome:** Platform moves between two points; player moves with the platform.

#### **Test 5: Coin**

**Objective:** Verify that the coin behaves as expected when collected.

- **Precondition:** The player is near a coin.
- **Test Steps:**
    1. The player collects the coin.
    2. Check if the coin disappears.
    3. Verify that the coin count in the top-left corner of the screen increases by **+1**.
- **Expected Outcome:** Coin disappears, and coin count increases by 1.

---

### **2. Enemy Class**

#### **Test 6: Walking Enemy**

**Objective:** Verify that the walking enemy moves and behaves as expected.

- **Precondition:** A common foe is present in the level.
- **Test Steps:**
    1. Observe the common foe’s movement (left-right until hitting a wall).
    2. Ensure the enemy reverses direction after hitting a wall.
    3. Check that the enemy disappears when its health reaches 0.
- **Expected Outcome:** Enemy moves left-right, reverses direction at walls, and disappears upon death.

#### **Test 7: Flying Enemy**

**Objective:** Verify that the flying enemy moves and behaves as expected.

- **Precondition:** A flying foe is present in the level.
- **Test Steps:**
    1. Observe the flying foe’s movement within its designated area.
    2. Ensure the enemy disappears when its health reaches 0.
- **Expected Outcome:** Flying foe moves within its space and disappears upon death.

#### **Test 8: Jumping Enemy**

**Objective:** Verify that the jumping enemy moves and behaves as expected.

- **Precondition:** A jumping foe is present in the level.
- **Test Steps:**
    1. Observe the jumping enemy’s movement on the platform.
    2. Ensure the enemy randomly jumps at intervals.
    3. Ensure the enemy disappears when its health reaches 0.
- **Expected Outcome:** Jumping foe moves and randomly jumps, disappearing upon death.

#### **Test 9: Armored Walking Enemy**

**Objective:** Test if the armored common foe behaves correctly with additional health.

- **Precondition:** An armored common foe is present in the level.
- **Test Steps:**
    1. Observe the armored common foe’s movement (left-right until hitting a wall).
    2. Ensure the enemy’s health is greater than the normal enemy’s health.
    3. Ensure the enemy disappears when its health reaches 0.
- **Expected Outcome:** Armored common foe moves and has increased health compared to the normal foe, disappearing upon death.

#### **Test 10: Armored Flying Enemy**

**Objective:** Test if the armored flying foe behaves correctly with additional health.

- **Precondition:** An armored flying foe is present in the level.
- **Test Steps:**
    1. Observe the armored flying foe’s movement within its designated area.
    2. Ensure the enemy’s health is greater than the normal flying foe’s health.
    3. Ensure the enemy disappears when its health reaches 0.
- **Expected Outcome:** Armored flying foe moves within its space and has increased health compared to the normal flying foe, disappearing upon death.

#### **Test 11: Armored Jumping Enemy**

**Objective:** Test if the armored jumping foe behaves correctly with additional health.

- **Precondition:** An armored jumping foe is present in the level.
- **Test Steps:**
    1. Observe the armored jumping foe’s movement on the platform.
    2. Ensure the enemy’s health is greater than the normal jumping foe’s health.
    3. Ensure the enemy disappears when its health reaches 0.
- **Expected Outcome:** Armored jumping foe moves, jumps randomly, and has increased health compared to the normal jumping foe, disappearing upon death.

---

### **3. Weapon Class**

#### **Test 12: Shotgun**

**Objective:** Verify that the shotgun functions correctly.

- **Precondition:** The player selects the shotgun.
- **Test Steps:**
    1. The player fires the weapon.
    2. Verify that two bullets are fired at once.
    3. Check that the bullet damage is appropriate for this weapon type.
- **Expected Outcome:** Two bullets are fired at once, and the bullets deal the correct damage.

#### **Test 13: Minigun**

**Objective:** Verify that the minigun functions correctly.

- **Precondition:** The player selects the minigun.
- **Test Steps:**
    1. The player fires the minigun.
    2. Verify that the weapon has a high fire rate and low damage.
    3. Check that the bullets are fired at a rapid rate.
- **Expected Outcome:** Minigun fires rapidly with low damage.

#### **Test 14: Rifle**

**Objective:** Verify that the rifle functions correctly.

- **Precondition:** The player selects the rifle.
- **Test Steps:**
    1. The player fires the rifle.
    2. Verify that the rifle has a moderate fire rate and damage.
    3. Check that the bullet damage is appropriate for this weapon.
- **Expected Outcome:** Rifle fires at a moderate rate and deals medium damage.

#### **Test 15: Pistol**

**Objective:** Verify that the pistol functions correctly.

- **Precondition:** The player selects the pistol.
- **Test Steps:**
    1. The player fires the pistol.
    2. Verify that the pistol has a low fire rate and moderate damage.
    3. Check that the bullet damage is appropriate for this weapon.
- **Expected Outcome:** Pistol fires slowly with medium damage.

---

This testing plan covers the functionality of key entities, enemies, and weapons, ensuring that all game elements perform as expected under various scenarios.