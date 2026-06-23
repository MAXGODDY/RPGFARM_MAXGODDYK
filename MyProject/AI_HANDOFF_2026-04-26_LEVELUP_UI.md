## AI Handoff - 2026-04-26

### Current branch / git context
- Active working branch: `99%`
- Earlier in this line of work there is already a pushed branch/PR flow from `99%` toward `et5-7`.
- The last confirmed gameplay/UI/pickaxe polish commit from earlier work was:
  - `16d52cb` `Polish hybrid character combat UI and pickaxe setup`

### What is already working
- Hybrid sandbox character setup is working again.
- Attack, ore damage, trader, pause/settings menus, stamina HUD, progression basics, and pickaxe attack animation were previously restored and made playable.
- Pickaxe/attack setup was stabilized so the character no longer flies upward during the attack once the blueprint/input duplication was removed.
- The attack animation asset being used is:
  - `C:\RPGFARM_MAXGODDYK\MyProject\Content\MainPlayer\Animations\AM_Pickaxe_Attack.uasset`
- The montage is:
  - `C:\RPGFARM_MAXGODDYK\MyProject\Content\MainPlayer\Animations\AM_Pickaxe_Attack_Montage.uasset`

### Important UI/asset context
- The user now wants a level-up popup/menu to appear when the player levels up.
- The user provided a UI pack image:
  - `C:\Users\lukgu\Downloads\Copilot_20260426_203553.png`
- That image has already been imported into the project and is visible as:
  - `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\Copilot_20260426_203553.uasset`
- The project currently draws most menus through custom Canvas HUD code, not through UMG widgets.
- The primary HUD/menu code is here:
  - `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Private\UI\PlayerGameHUD.cpp`
  - `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Public\UI\PlayerGameHUD.h`

### Exact place where level-up work was started
- I already added header declarations/state for a level-up popup in:
  - `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Public\UI\PlayerGameHUD.h`
- Added declarations/state:
  - `UpdateLevelUpPopupState()`
  - `DrawLevelUpPopup(float ViewportWidth, float ViewportHeight) const`
  - `LastObservedPlayerLevel`
  - `LevelPopupDisplayedLevel`
  - `LevelPopupDisplayedPoints`
  - `LevelPopupStartTime`
  - `LevelPopupDuration`

### Important: what is NOT finished yet
- The popup logic is NOT implemented yet in:
  - `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Private\UI\PlayerGameHUD.cpp`
- In other words:
  - header state exists
  - actual popup drawing/update flow still needs to be implemented in `.cpp`

### Existing progression/level source of truth
- Player level / XP / upgrade points logic already exists in:
  - `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Private\GameplayCharacterBase.cpp`
- Relevant method:
  - `AddExperience(int32 ExperienceAmount)`
- Existing getters already available:
  - `GetPlayerLevel()`
  - `GetCurrentExperienceAmount()`
  - `GetExperienceToNextLevelAmount()`
  - `GetAvailableUpgradePoints()`

### Intended implementation plan for the next chat
1. Implement `APlayerGameHUD::UpdateLevelUpPopupState()` in:
   - `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Private\UI\PlayerGameHUD.cpp`
2. Implement `APlayerGameHUD::DrawLevelUpPopup(...)` in the same file.
3. Call `UpdateLevelUpPopupState()` early inside `DrawHUD()`.
4. Call `DrawLevelUpPopup(...)` during normal gameplay HUD rendering when there is no large blocking modal open.
5. Reuse existing helper drawing functions already in `PlayerGameHUD.cpp`:
   - `DrawPanel(...)`
   - `DrawTextLine(...)`
   - `DrawWrappedTextBlock(...)`
   - `LocalizeText(...)`
6. First pass can be a simple animated popup using the current Canvas HUD style.
7. After that, optionally skin the popup with the imported UI pack asset.

### Recommended popup behavior
- Trigger only when observed player level increases.
- Do NOT show on first HUD initialization when the level is merely read for the first time.
- Suggested text:
  - RU title: `УРОВЕНЬ ПОВЫШЕН`
  - RU subtitle: `Достигнут уровень X`
  - RU hint: `Очки улучшений: Y`
  - RU footer: `[P] Открыть прокачку`
- Suggested duration:
  - about `3.5 - 4.0` seconds
- Suggested motion:
  - small fade in/out
  - slight upward drift or center pulse

### Current user intent / style preference
- The user likes strong stylization and explicitly wants the UI to feel more like:
  - Fortnite as a structure/template
  - steampunk in materials/details
- For THIS next step, however, the immediate task is functional:
  - when level increases, show a visible level-up menu/popup

### If the next chat wants to continue from the current editor state
- Open:
  - `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Public\UI\PlayerGameHUD.h`
  - `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Private\UI\PlayerGameHUD.cpp`
  - `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Private\GameplayCharacterBase.cpp`
- Search for:
  - `LevelPopup`
  - `DrawHUD`
  - `DrawLevelPanel`
  - `AddExperience`

### Notes for the next assistant
- Do not rip out the current attack/pickaxe logic; that part was painful and is finally stable.
- Do not assume UMG is already used for these menus; most of this HUD is Canvas-based.
- The safest next change is to finish the level-up popup in `PlayerGameHUD.cpp` first, then let the user test it before attempting a bigger UI migration.
