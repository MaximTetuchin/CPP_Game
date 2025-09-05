# Testing Report for Takaraima

**Test Environment:** Local machine, Google Test framework  

---

## Summary

A total of **25 tests** were executed, covering player effects, gameplay objects, enemies, and weapons.  
All **25/25 tests passed successfully (100%)**. No errors, crashes, or unexpected behaviors were observed during the test execution.  

---

## Test Results

### 1. Player Effects & Gameplay Objects
- Med Kit restores health correctly (does not exceed 100). ✅  
- Invincibility Sphere activates correctly with duration = 5.0s. ✅  
- Speed Berry effect duration decreases over time. ✅  
- Invincibility duration decreases over time. ✅  
- Coin collection increases player’s coin counter by 1. ✅  
- Moving platform updates without errors. ✅  

### 2. Enemies
- Walking enemy dies at 0 HP. ✅  
- Flying enemy dies at 0 HP. ✅  
- Jumping enemy dies at 0 HP. ✅  
- Armored walking enemy has more health than regular. ✅  
- Armored flying enemy has more health than regular. ✅  
- Armored jumping enemy has more health than regular. ✅  

### 3. Weapons
- Shotgun fires 2 bullets. ✅  
- Minigun fires multiple bullets (>1). ✅  
- Rifle fires 1 bullet. ✅  
- Pistol fires 1 bullet. ✅  

---

## Overall Result

✅ **All 25 tests passed successfully.**  
The tested components (player mechanics, gameplay objects, enemies, and weapons) are functioning according to specifications.  
