# **Testing Plan for Takaraima**

This plan is based on the actual content of the automated tests in the code.

---

### **1. Player Effects & Gameplay Objects**

#### **Test 1: Med Kit**

**Objective:** Verify that the med kit restores the player’s health.

* **Precondition:** Player’s health is below maximum.
* **Test Steps:**

  1. Player collides with the med kit.
  2. Check that health increases by 35 but does not exceed 100.
* **Expected Outcome:** Health is restored correctly, up to 100.

---

#### **Test 2: Invincibility Sphere**

**Objective:** Verify that the invincibility sphere activates the effect.

* **Precondition:** Player does not have invincibility.
* **Test Steps:**

  1. Player collects the sphere.
  2. Check that `isInvincible = true`.
  3. Check that `invincibilityTime = 5.0f`.
* **Expected Outcome:** Player becomes invincible for 5 seconds.

---

#### **Test 3: Speed Berry Effect Duration**

**Objective:** Verify that the speed boost effect decreases over time.

* **Precondition:** Player is under the effect of speed boost (`isSpeedBoosted = true`).
* **Test Steps:**

  1. Set `speedBoostTime = 2.0f`.
  2. Call `player.update(1.0f)`.
  3. Check that `speedBoostTime` decreased to 1.0f.
* **Expected Outcome:** Speed boost timer decreases correctly.

---

#### **Test 4: Invincibility Duration**

**Objective:** Verify that the invincibility effect decreases over time.

* **Precondition:** Player is under the effect of invincibility.
* **Test Steps:**

  1. Set `invincibilityTime = 2.0f`.
  2. Call `player.update(1.0f)`.
  3. Check that `invincibilityTime` decreased to 1.0f.
* **Expected Outcome:** Invincibility timer decreases correctly.

---

#### **Test 5: Coin Collection**

**Objective:** Verify that collecting a coin increases the player’s coin counter.

* **Precondition:** Player has a coin counter.
* **Test Steps:**

  1. Player collides with a coin.
  2. Check that the number of coins increased by 1.
* **Expected Outcome:** Coin counter increases.

---

#### **Test 6: Moving Platform Update**

**Objective:** Verify that the moving platform updates without errors.

* **Precondition:** Platform is created.
* **Test Steps:**

  1. Call `platform.update(1.0f)`.
* **Expected Outcome:** No errors occur.

---

### **2. Enemies**

#### **Test 7: Walking Enemy Death**

**Objective:** Verify that the walking enemy dies at 0 HP.

* **Precondition:** Enemy has 10 HP.
* **Test Steps:**

  1. Apply damage = 10.
  2. Check that `isAlive = false`.
* **Expected Outcome:** Enemy dies at 0 HP.

---

#### **Test 8: Flying Enemy Death**

**Objective:** Verify that the flying enemy dies at 0 HP.

* **Precondition:** Enemy has 10 HP.
* **Test Steps:**

  1. Apply damage = 10.
  2. Check that `isAlive = false`.
* **Expected Outcome:** Enemy dies at 0 HP.

---

#### **Test 9: Jumping Enemy Death**

**Objective:** Verify that the jumping enemy dies at 0 HP.

* **Precondition:** Enemy has 10 HP.
* **Test Steps:**

  1. Apply damage = 10.
  2. Check that `isAlive = false`.
* **Expected Outcome:** Enemy dies at 0 HP.

---

#### **Test 10: Armored Walking Enemy Health**

**Objective:** Verify that the armored walking enemy has more health than the regular one.

* **Precondition:** Two enemies are created — regular and armored.
* **Test Steps:**

  1. Compare their `health`.
* **Expected Outcome:** Armored enemy has higher health.

---

#### **Test 11: Armored Flying Enemy Health**

**Objective:** Verify that the armored flying enemy has more health than the regular one.

* **Precondition:** Two enemies are created — regular and armored.
* **Test Steps:**

  1. Compare their `health`.
* **Expected Outcome:** Armored enemy has higher health.

---

#### **Test 12: Armored Jumping Enemy Health**

**Objective:** Verify that the armored jumping enemy has more health than the regular one.

* **Precondition:** Two enemies are created — regular and armored.
* **Test Steps:**

  1. Compare their `health`.
* **Expected Outcome:** Armored enemy has higher health.

---

### **3. Weapons**

#### **Test 13: Shotgun Fires Two Bullets**

**Objective:** Verify that the shotgun fires two bullets.

* **Precondition:** Player uses a shotgun.
* **Test Steps:**

  1. Shoot.
  2. Check that the number of bullets = 2.
* **Expected Outcome:** Shotgun fires 2 bullets.

---

#### **Test 14: Minigun Fires Multiple Bullets**

**Objective:** Verify that the minigun fires multiple bullets.

* **Precondition:** Player uses a minigun.
* **Test Steps:**

  1. Shoot.
  2. Check that the number of bullets > 1.
* **Expected Outcome:** Minigun fires in bursts.

---

#### **Test 15: Rifle Fires One Bullet**

**Objective:** Verify that the rifle fires one bullet.

* **Precondition:** Player uses a rifle.
* **Test Steps:**

  1. Shoot.
  2. Check that the number of bullets = 1.
* **Expected Outcome:** Rifle fires 1 bullet.

---

#### **Test 16: Pistol Fires One Bullet**

**Objective:** Verify that the pistol fires one bullet.

* **Precondition:** Player uses a pistol.
* **Test Steps:**

  1. Shoot.
  2. Check that the number of bullets = 1.
* **Expected Outcome:** Pistol fires 1 bullet.
