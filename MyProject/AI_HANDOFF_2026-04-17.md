# AI Handoff

Project: `C:\RPGFARM_MAXGODDYK\MyProject`
Date: `2026-04-17`
User language: Russian
Current goal: replace the old gameplay character flow with a sample-based movement/traversal base, but keep only the user's own visual character and gameplay logic. No extra sample characters in the final game.

## What the user wants

The user wants:

- to use the sample locomotion / traversal character as the new gameplay base
- but only with their own visual character
- and to move their own gameplay logic onto that new base
- and later use transferred skins like `Echo` / `Twinblast` in an in-game shop

The user does **not** want a sandbox-only final workflow or random sample characters showing up.

## Important maps

- Main gameplay map to test: `C:\RPGFARM_MAXGODDYK\MyProject\Content\Namaqualand\Levels\Showcase.umap`
- Do **not** test on `NewMap`

## Main C++ work already done

### New gameplay base class

Created:

- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Public\GameplayCharacterBase.h`
- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Private\GameplayCharacterBase.cpp`

`AGameplayCharacterBase : public ACharacter`

This class already contains the old gameplay logic moved out of the classic character:

- mining / ore interaction
- trader interaction
- upgrade interaction
- stamina logic
- attack / montage logic
- legacy input binding for `"Attack"`

Attack uses:

- `AttackMontage`
- defaults to `AM_Pickaxe_Attack_Montage`
- uses `PlayAnimMontage`

### New thin sample-based gameplay class

Created:

- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Public\ThifCatcherSandboxBase.h`
- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Private\ThifCatcherSandboxBase.cpp`

`AThifCatcherSandboxBase : public AGameplayCharacterBase`

This is the intended parent for the sample-based blueprint pawn.

### Existing classic character updated

Updated:

- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Public\ThifCatcher.h`
- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Private\ThifCatcher.cpp`

`AThifCatcher` now derives from `AGameplayCharacterBase`.

### Other C++ references updated to new gameplay base

Updated references to `AGameplayCharacterBase` in:

- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Public\ThiefPlayerController.h`
- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Private\ThiefPlayerController.cpp`
- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Public\UI\PlayerGameHUD.h`
- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Private\UI\PlayerGameHUD.cpp`
- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Private\Actors\TraderNPC.cpp`
- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Private\PlayerAnimInstance.cpp`

### Main game mode fallback logic

Updated:

- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Private\ThiefCatcerGameMode.cpp`

It now tries to load:

1. `/Game/Blueprints/BP_MyThifCatcher_Sandbox`
2. fallback to `/Game/Blueprints/Bp_MyThifCatcher`

## User's main existing gameplay character

Old main gameplay BP:

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\Bp_MyThifCatcher.uasset`

This is still the user's old real gameplay character.

## Sample / retarget content transferred into the project

### Sample locomotion / retarget base

Transferred:

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\SandboxCharacter_CMC.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\SandboxCharacter_CMC_ABP.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\PC_Sandbox.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\BPI_SandboxCharacter_ABP.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\BPI_SandboxCharacter_Pawn.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\AC_PreCMCTick.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\AC_TraversalLogic.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\AC_VisualOverrideManager.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Input\IMC_Sandbox.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Characters\UEFN_Mannequin`

### Retarget / user visual assets

Transferred / created:

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\MainPlayer\IK_Ch44_Retarget.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\MainPlayer\RTG_UEFN_to_Ch44.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\RetargetedCharacters\ABP_GenericRetarget.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\RetargetedCharacters\BP_OurCharacter.uasset`

`BP_OurCharacter` is the user's visual sample wrapper used earlier in the sample project.

### Store skins already transferred

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Characters\Echo`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Characters\Paragon`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\RetargetedCharacters\BP_Echo.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\RetargetedCharacters\BP_Twinblast.uasset`

User wants these skins later for shop integration.

## Config work already done

Created:

- `C:\RPGFARM_MAXGODDYK\MyProject\Config\DefaultGameplayTags.ini`

Purpose:

- restore missing sample gameplay tags, especially `Foley.Event.*` etc.

## Redirectors and duplicate cleanup already done

- User already ran `Update Redirector References` on `Content`
- User already deleted unreferenced redirectors
- duplicate bad folder `Content\Blueprints\Data\Data` was removed earlier

## Sample dependency folders recopied cleanly

With the editor closed, these sample folders/assets were recopied from the original `GameAnimationSample` project:

- `Content\Blueprints\Data`
- `Content\Blueprints\Cameras`
- `Content\Blueprints\AnimNotifies`
- `Content\Blueprints\SmartObjects`
- `Content\Levels\LevelPrototyping`
- `Content\Audio\Foley`
- plus refreshed versions of:
  - `AC_TraversalLogic`
  - `AC_VisualOverrideManager`
  - `SandboxCharacter_CMC_ABP`
  - `SandboxCharacter_CMC`
  - `AC_PreCMCTick`
  - `GM_Sandbox`

Source project used for copying:

- `C:\Users\lukgu\OneDrive\Документы\Unreal Projects\GameAnimationSample`

## Blueprint currently being used for the new base

User duplicated:

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\SandboxCharacter_CMC.uasset`

to:

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\BP_MyThifCatcher_Sandbox.uasset`

Then user already did:

- reparented `BP_MyThifCatcher_Sandbox` to `ThifCatcherSandboxBase`
- set `Mesh -> VisualOverride -> Child Actor Class = BP_OurCharacter`

This is confirmed in the editor already.

## Important current state of blueprint compilation

### Good now

`AC_VisualOverrideManager` compiled successfully in the latest user screenshot:

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\AC_VisualOverrideManager.uasset`

The screenshot showed successful compile and `Visual Override` default currently `None`.

### Still broken / suspicious

#### 1) `AC_TraversalLogic`

File:

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\AC_TraversalLogic.uasset`

Latest user screenshot showed compile errors:

- invalid target type on a cast node
- stale `As Level Block Traversable` pin on a bad cast node
- `GetLedgeTransforms` function / pins missing

This means traversal is still broken at blueprint level.

#### 2) `BFL_HelpfulFunctions`

File:

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\Data\BFL_HelpfulFunctions.uasset`

Latest user screenshot showed it is still broken in debug draw functions, especially:

- `DebugDraw_MultiLineGraph`

Observed compile errors from screenshot:

- vector pin incompatibility
- failed pin expansion on debug draw box
- missing structure on `LineStyle`
- stale `Drawer` related pins / nodes

These look like debug-only sample functions that may be safe to neutralize or no-op if needed.

#### 3) `SandboxCharacter_CMC_ABP`

File:

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\SandboxCharacter_CMC_ABP.uasset`

Latest screenshot still showed a compile error, but no exact node details were captured.

It may still depend on broken helper data / traversal pieces.

## User preference that must be respected

User explicitly said:

- do not keep extra sample characters
- only keep their own character and the logic needed
- sample characters were not meant to remain visible in final flow
- they want to move to the new base character, not keep a sandbox-only experience

So the likely final architecture should be:

1. `BP_MyThifCatcher_Sandbox` becomes the new real gameplay pawn base
2. user visual `BP_OurCharacter` or direct user mesh replaces sample visuals
3. old gameplay logic stays through `AGameplayCharacterBase`
4. sample-only extra characters / widgets / visual override menus should not be part of final shipped flow

## Most recent user-visible problem

The user reopened the editor and showed:

- `AC_VisualOverrideManager` OK
- `AC_TraversalLogic` still broken
- `BFL_HelpfulFunctions` still broken
- `SandboxCharacter_CMC_ABP` still in compile error state

The user wants work to continue from there.

## Recommended next steps for the next model

Best next path is likely:

1. Fix or neutralize `BFL_HelpfulFunctions`
   - specifically debug draw functions like `DebugDraw_MultiLineGraph`
   - these appear non-essential and may be safely no-op'd if nothing gameplay-critical uses them

2. Fix or temporarily disable traversal dependency
   - either repair `AC_TraversalLogic` stale nodes
   - or bypass traversal in `BP_MyThifCatcher_Sandbox` temporarily so movement base can compile and run

3. Recompile in this order:
   - `BFL_HelpfulFunctions`
   - `AC_TraversalLogic`
   - `SandboxCharacter_CMC_ABP`
   - `BP_MyThifCatcher_Sandbox`

4. Then test:
   - `C:\RPGFARM_MAXGODDYK\MyProject\Content\Namaqualand\Levels\Showcase.umap`

5. Once the new base pawn is stable:
   - remove dependence on sample `Visual Override` menus / DDCvars for final gameplay
   - wire the project to spawn `BP_MyThifCatcher_Sandbox` on real map startup
   - keep `BP_Echo` / `BP_Twinblast` only as future skin assets for shop

## Notes about user workflow

- User is okay doing concrete editor steps if short and direct
- User wants minimal theory
- User switches models often, so this file should be the first thing the next model reads
