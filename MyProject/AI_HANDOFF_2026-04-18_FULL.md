# AI Handoff — 2026-04-18

## Главное

Пользователь **не просит сейчас продолжать кодинг**, а хочет **передать следующему чату всю информацию**, чтобы тот сразу продолжил работу с текущего места.

Текущая цель проекта:

- взять основу передвижения / traversal / motion-matching из `GameAnimationSample`
- встроить это в **реальный проект**
- использовать **своего персонажа / свою игровую логику**
- не оставлять чужих sample-персонажей как итоговый игровой путь
- отдельно оставить импортированные скины `Echo` и `Twinblast` для будущего магазина

## Корневой путь проекта

- `C:\RPGFARM_MAXGODDYK\MyProject`

## Что уже сделано

### 1. C++ и конфиги

Ранее были добавлены / изменены:

- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Public\GameplayCharacterBase.h`
- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Public\ThifCatcherSandboxBase.h`
- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Public\ThifCatcher.h`
- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\Private\ThifCatcher.cpp`
- `C:\RPGFARM_MAXGODDYK\MyProject\Source\MyProject\MyProject.Build.cs`
- `C:\RPGFARM_MAXGODDYK\MyProject\MyProject.uproject`
- `C:\RPGFARM_MAXGODDYK\MyProject\Config\DefaultGameplayTags.ini`
- `C:\RPGFARM_MAXGODDYK\MyProject\README.md`

Замечания:

- В `MyProject.Build.cs` уже были добавлены missing module-зависимости для sample-системы.
- В `.uproject` уже включались нужные плагины, включая `BlendStack`.
- Ранее уже была успешная сборка `MyProjectEditor`.
- В `ThifCatcher.cpp` уже была интегрирована логика удара киркой через montage.

### 2. Импортированные ассеты / системы

Ключевые sample-ассеты, уже лежащие в проекте:

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\BP_MyThifCatcher_Sandbox.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\AC_TraversalLogic.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\AC_VisualOverrideManager.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\Data\BFL_HelpfulFunctions.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\SandboxCharacter_CMC_ABP.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\RetargetedCharacters\BP_OurCharacter.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Characters\UEFN_Mannequin\...`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\MainPlayer\IK_Ch44_Retarget.uasset`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\MainPlayer\RTG_UEFN_to_Ch44.uasset`

Импортированные скины для будущего магазина:

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Characters\Echo`
- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Characters\Paragon`
- связанные BP-обёртки под `RetargetedCharacters` ранее тоже импортировались

### 3. Уже сделанные редакторные шаги

#### `BP_MyThifCatcher_Sandbox`

Путь:

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\BP_MyThifCatcher_Sandbox.uasset`

Состояние:

- blueprint **already reparented** на `ThifCatcherSandboxBase`
- `VisualOverride` component уже настроен на:
  - `Child Actor Class = BP_OurCharacter`

Это важное текущее состояние, его не нужно повторять.

#### `AC_TraversalLogic`

Путь:

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\AC_TraversalLogic.uasset`

Состояние:

- ранее уже был успешный compile
- по последним скринам он **компилируется**

#### `AC_VisualOverrideManager`

Путь:

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\AC_VisualOverrideManager.uasset`

Состояние:

- ранее уже был успешный compile
- по последним скринам он **компилируется**

#### `BFL_HelpfulFunctions`

Путь:

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\Data\BFL_HelpfulFunctions.uasset`

Текущее состояние:

- **уже успешно скомпилирован**
- пользователь вручную вычистил устаревшие debug-функции

Что уже оставлено пустышками:

- `DrawDebugArrowWithCircle`
- `DrawDebugAngleThresholds`
- `DebugDraw_MultiLineGraph`
- `DebugDraw_BoolStates`
- `DebugDraw_StringArray`
- `DebugDraw_ObjectNameArray`

Что было оставлено рабочим и не трогалось:

- `AddToStringHistoryArray`
- `GetObjectNames`
- `GetPawnClassWithCVAR`
- `GetVisualOverrideWithCVAR`

Последний скрин подтверждает:

- `Compile of BFL_HelpfulFunctions successful`

### 4. Что уже НЕ является блокером

Следующее уже **не блокирует**:

- `BFL_HelpfulFunctions`
- `AC_TraversalLogic`
- `AC_VisualOverrideManager`
- reparent / VisualOverride в `BP_MyThifCatcher_Sandbox`

## Главный текущий блокер

### `SandboxCharacter_CMC_ABP`

Путь:

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\SandboxCharacter_CMC_ABP.uasset`

Именно он сейчас продолжает падать на compile.

## Что именно ломается в `SandboxCharacter_CMC_ABP`

По последним скринам compile errors такие:

- `No structure in SubCategoryObject in pin Settings`
- `No structure in SubCategoryObject in pin Line_Style`
- `Output pin type 'Vector' is not compatible with input type of 'Vector' on 'vector + vector'`
- `In use pin Drawer no longer exists on node Draw_Debug_String`
- `In use pin String no longer exists on node Draw_Debug_String`
- `In use pin Location no longer exists on node Draw_Debug_String`
- `In use pin Rotation no longer exists on node Draw_Debug_String`
- `Input pin Line Style Thickness specifying non-default value no longer exists on node Draw_Debug_String`
- `Input pin Line Style Color specifying non-default value no longer exists on node Draw_Debug_String`
- `Input pin Depth Test specifying non-default value no longer exists on node Draw_Debug_String`
- `Input pin Settings Height specifying non-default value no longer exists on node Draw_Debug_String`
- `Could not find a function named 'None' in 'SandboxCharacter_CMC_ABP' on Draw_Debug_String`
- `Could not find a function named 'Count' in 'SandboxCharacter_CMC_ABP' on Draw_Debug_String`
- `Node Draw_Debug_String won't be pruned as isolated one`

Итоговая строка ошибки:

- `Compile of SandboxCharacter_CMC_ABP failed. 9 Fatal Issue(s) 6 Warning(s)`

Дополнительно локальный лог:

- [MyProject.log](C:/RPGFARM_MAXGODDYK/MyProject/Saved/Logs/MyProject.log)

подтверждает, что в том же проблемном участке есть ещё и такие ошибки:

- `Could not find a function named "AddToFloatHistoryArray"` — **6 раз в одном compile-проходе**
- broken pins на `AddToFloatHistoryArray`:
  - `<Unnamed>`
  - `InOutValues`
  - `NewValue`
  - `MaxHistoryNum`
- `FStructProperty::Serialize Loading` с unknown structure для:
  - `Debug_ExperimentalStateMachine:CallFunc_MakeVisualLoggerDebugDrawer_ReturnValue`
  - `Debug_ExperimentalStateMachine:K2Node_MakeStruct_DrawDebugStringSettings`
  - `Debug_ExperimentalStateMachine:K2Node_MakeStruct_DrawDebugLineStyle`

### Что НЕ является ошибкой

Эти строки не нужно чинить:

- `Steering - Node is experimental`
- `Foot Placement - Node is experimental`
- `Offset Root Bone - Node is experimental`

Это только warnings, не блокеры.

## Что уже пробовали внутри `SandboxCharacter_CMC_ABP`

Пользователь открывал:

- `AnimGraph`
- `State Machine (Experimental) / Debug`
- `Debug_ExperimentalStateMachine`

В `My Blueprint` видно:

- `SM Transition Debug Events`
- `Debug_ExperimentalStateMachine`
- bool `DebugExperimentalStateMachine`
- debug/history variables:
  - `TransitionHistory`
  - `PawnSpeedHistory`
  - `MoveData_Speed_History`
  - `Phase_History`
  - `Contact_L_History`
  - `Contact_R_History`
  - `Enable_Warping_History`

Также пользователь пробовал искать:

- `Draw Debug String`

Но явный узел через поиск быстро не нашёлся.

## Самая вероятная причина

В `SandboxCharacter_CMC_ABP` всё ещё висит **одна или несколько старых debug-веток**, которые ссылаются на obsolete `Draw_Debug_String`-узлы и старые пины.

Важно:

- это, скорее всего, **не ломает locomotion логику**
- ломается именно старый debug layer

Уточнение по логам:

- это не одинокий узел, а, скорее всего, один общий debug/history остров внутри `Debug_ExperimentalStateMachine`;
- внутри него висит один `MakeVisualLoggerDebugDrawer`, два битых make-struct debug-типа и **6** stale-вызовов `AddToFloatHistoryArray`.

## Что следующему чату нужно делать

### Основная задача

Дочинить compile у:

- `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\SandboxCharacter_CMC_ABP.uasset`

через удаление / нейтрализацию **только debug-веток**, не ломая основную locomotion pipeline.

### Что нельзя трогать

Не удалять:

- Motion Matching node
- Blend Stack
- Pose History
- Offset Root Bone
- Foot Placement
- Main locomotion chain
- Traversal animation logic
- Additive Lean / Aim Offset / Root Offset / locomotion state machine

### Что безопасно удалять

Можно удалять, если это purely debug:

- `Draw_Debug_String`
- `Make Visual Logger Debug Drawer`
- `K2Node_MakeStruct_DrawDebugStringSettings`
- `K2Node_MakeStruct_DrawDebugLineStyle`
- `AddToFloatHistoryArray` в debug-контексте
- debug-only string/append/count/none branches
- любые isolated debug helper ветки, не влияющие на pose output

### Скорее всего надо искать в

- `EventGraph`
- `Debug_ExperimentalStateMachine`
- `SM Transition Debug Events`
- любые collapsed debug-only секции вокруг history variables

## Где продолжать тест после фикса

После того как `SandboxCharacter_CMC_ABP` станет зелёным:

1. открыть:
   - `C:\RPGFARM_MAXGODDYK\MyProject\Content\Blueprints\BP_MyThifCatcher_Sandbox.uasset`
2. `Compile`
3. `Save`
4. открыть:
   - `C:\RPGFARM_MAXGODDYK\MyProject\Content\Namaqualand\Levels\Showcase.umap`
5. `Play`

Потом проверить:

- спавнится ли новый pawn
- работает ли sample movement logic
- виден ли `BP_OurCharacter`
- работает ли inherited gameplay / ore / LMB attack

## Пользовательское намерение

Очень важно:

- пользователь **не хочет, чтобы новый чат начинал всё сначала**
- пользователь **не просит сейчас писать новый код с нуля**
- он хочет, чтобы следующий чат **прямо продолжил от текущего состояния**

## Краткий итог

Текущее состояние проекта:

- `BFL_HelpfulFunctions` — зелёный
- `AC_TraversalLogic` — зелёный
- `AC_VisualOverrideManager` — зелёный
- `BP_MyThifCatcher_Sandbox` — reparent сделан, `VisualOverride = BP_OurCharacter`
- главный оставшийся блокер — `SandboxCharacter_CMC_ABP`

Следующему чату надо:

1. открыть `SandboxCharacter_CMC_ABP`
2. найти / удалить последний stale debug `Draw_Debug_String`-хвост
3. добиться успешного compile
4. затем собрать `BP_MyThifCatcher_Sandbox`
5. проверить `Showcase`
