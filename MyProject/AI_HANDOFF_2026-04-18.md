# AI Handoff — 2026-04-18

Этот файл нужен как полная передача контекста для следующего чата/модели.
Главная цель: новая модель должна открыть этот файл и сразу продолжить работу без повторного исследования проекта.

## 1. Что хочет пользователь

Пользователь хочет:

- перенести в свой проект полезную locomotion / motion-matching / traversal-логику из Unreal Game Animation Sample;
- использовать в финале только своего персонажа как основной визуал;
- не тащить в финальный рабочий путь лишние sample-манекены и sandbox UI как обязательную зависимость;
- сохранить возможность потом встроить импортированные анимации и sample-логику в основной проект;
- оставить Echo / Twinblast как будущие скины для магазина.

Важно:

- пользователь очень чувствителен к "лишнему мусору" и не хочет тащить в проект ненужных sample-персонажей как видимых игровых героев;
- текущая интеграция строится как гибрид: sample locomotion base + свой визуальный персонаж + свой gameplay.

## 2. Текущее рабочее окружение

- Проект: [MyProject.uproject](C:/RPGFARM_MAXGODDYK/MyProject/MyProject.uproject)
- Корень проекта: `C:\RPGFARM_MAXGODDYK\MyProject`
- Unreal Editor запускается локально на Windows
- Пользователь сам открывает/компилирует blueprint'ы в редакторе

## 3. Что уже изменено в коде / конфиге

### Изменённые важные файлы

- [MyProject.Build.cs](C:/RPGFARM_MAXGODDYK/MyProject/Source/MyProject/MyProject.Build.cs)
- [MyProject.uproject](C:/RPGFARM_MAXGODDYK/MyProject/MyProject.uproject)
- [DefaultGameplayTags.ini](C:/RPGFARM_MAXGODDYK/MyProject/Config/DefaultGameplayTags.ini)
- [README.md](C:/RPGFARM_MAXGODDYK/MyProject/README.md)

### Смысл этих правок

- добавлены нужные module-зависимости для sample locomotion stack;
- включен `BlendStack` в `.uproject`;
- добавлены gameplay tags, которые нужны sample-контенту;
- native сборка `MyProjectEditor` уже проходила успешно.

## 4. Какие C++ bridge-классы уже существуют

Эти классы были добавлены/использованы для гибридного пути:

- [GameplayCharacterBase.h](C:/RPGFARM_MAXGODDYK/MyProject/Source/MyProject/Public/GameplayCharacterBase.h)
- [ThifCatcherSandboxBase.h](C:/RPGFARM_MAXGODDYK/MyProject/Source/MyProject/Public/ThifCatcherSandboxBase.h)
- [ThifCatcher.h](C:/RPGFARM_MAXGODDYK/MyProject/Source/MyProject/Public/ThifCatcher.h)
- [ThifCatcher.cpp](C:/RPGFARM_MAXGODDYK/MyProject/Source/MyProject/Private/ThifCatcher.cpp)

### Что это значит

- старая игровая логика добычи / удара / gameplay остаётся в native пути;
- `BP_MyThifCatcher_Sandbox` позже был перепривязан на `ThifCatcherSandboxBase`;
- атака киркой уже раньше была заведена через native gameplay path.

## 5. Какие ассеты уже импортированы и важны

### Основная sample locomotion / hybrid база

- [BP_MyThifCatcher_Sandbox.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/Blueprints/BP_MyThifCatcher_Sandbox.uasset)
- [AC_TraversalLogic.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/Blueprints/AC_TraversalLogic.uasset)
- [AC_VisualOverrideManager.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/Blueprints/AC_VisualOverrideManager.uasset)
- [BFL_HelpfulFunctions.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/Blueprints/Data/BFL_HelpfulFunctions.uasset)
- [SandboxCharacter_CMC_ABP.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/Blueprints/SandboxCharacter_CMC_ABP.uasset)
- [BP_OurCharacter.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/Blueprints/RetargetedCharacters/BP_OurCharacter.uasset)
- [IK_Ch44_Retarget.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/MainPlayer/IK_Ch44_Retarget.uasset)
- [RTG_UEFN_to_Ch44.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/MainPlayer/RTG_UEFN_to_Ch44.uasset)
- [UEFN_Mannequin](C:/RPGFARM_MAXGODDYK/MyProject/Content/Characters/UEFN_Mannequin)

### Скины на будущее

- [Echo](C:/RPGFARM_MAXGODDYK/MyProject/Content/Characters/Echo)
- [Paragon](C:/RPGFARM_MAXGODDYK/MyProject/Content/Characters/Paragon)
- [BP_Echo.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/Blueprints/RetargetedCharacters/BP_Echo.uasset)
- [BP_Twinblast.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/Blueprints/RetargetedCharacters/BP_Twinblast.uasset)

## 6. Текущее состояние конкретных blueprint'ов

### 6.1. BFL_HelpfulFunctions

Файл:

- [BFL_HelpfulFunctions.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/Blueprints/Data/BFL_HelpfulFunctions.uasset)

Текущее состояние:

- **Уже компилируется успешно**

Что было сделано:

- все debug draw функции были вычищены до пустых функций с одной фиолетовой нодой;
- обычные helper-функции были сохранены.

### Debug-функции, которые уже очищены

- `DrawDebugArrowWithCircle`
- `DrawDebugAngleThresholds`
- `DebugDraw_MultiLineGraph`
- `DebugDraw_BoolStates`
- `DebugDraw_StringArray`
- `DebugDraw_ObjectNameArray`

### Функции, которые трогать больше не нужно

- `AddToStringHistoryArray`
- `GetObjectNames`
- `GetPawnClassWithCVAR`
- `GetVisualOverrideWithCVAR`

### Вывод

`BFL_HelpfulFunctions` больше не является блокером.

---

### 6.2. AC_TraversalLogic

Файл:

- [AC_TraversalLogic.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/Blueprints/AC_TraversalLogic.uasset)

Текущее состояние:

- **Компилируется успешно**

Раньше ломался на старых нодах `Bad cast node` / `GetLedgeTransforms`, но этот этап уже пройден.

---

### 6.3. AC_VisualOverrideManager

Файл:

- [AC_VisualOverrideManager.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/Blueprints/AC_VisualOverrideManager.uasset)

Текущее состояние:

- **Компилируется успешно**

Тоже больше не является блокером.

---

### 6.4. BP_MyThifCatcher_Sandbox

Файл:

- [BP_MyThifCatcher_Sandbox.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/Blueprints/BP_MyThifCatcher_Sandbox.uasset)

Текущее состояние:

- blueprint был **reparent** на `ThifCatcherSandboxBase`;
- в `Components` у `VisualOverride` уже выставлен:
  - `Child Actor Class = BP_OurCharacter`

Назначение этого BP:

- взять sample locomotion / motion matching базу;
- показывать **своего** персонажа через `BP_OurCharacter`;
- использовать bridge/native gameplay пользователя.

На данный момент этот BP ещё не финально проверен в игре, потому что остаётся последний блокер ниже.

---

### 6.5. SandboxCharacter_CMC_ABP

Файл:

- [SandboxCharacter_CMC_ABP.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/Blueprints/SandboxCharacter_CMC_ABP.uasset)

Это **главный оставшийся блокер**.

#### Что уже ясно

Передвижение ломает не motion matching сам по себе, а старый **debug-хвост**.

Важные warning'и, которые **не являются ошибками**:

- `Steering - Node is experimental`
- `Foot Placement - Node is experimental`
- `Offset Root Bone - Node is experimental`

Их не нужно чинить.

#### Что видно по последним скринам

После того как `BFL_HelpfulFunctions` стал зелёным, `SandboxCharacter_CMC_ABP` всё ещё падает на одном оставшемся stale debug path, связанном с:

- `Draw Debug String`
- `Make Visual Logger Debug Drawer`
- `None`
- `Count`
- старые пины:
  - `Drawer`
  - `String`
  - `Location`
  - `Rotation`
  - `Line Style Thickness`
  - `Line Style Color`
  - `Depth Test`
  - `Settings Height`

То есть:

- locomotion graph сам по себе, скорее всего, живой;
- motion matching / pose history / offset root bone / foot placement — не основной источник ошибки;
- остался старый debug блок внутри `SandboxCharacter_CMC_ABP`.

#### Что дополнительно подтверждено по `Saved/Logs`

Локальный лог:

- [MyProject.log](C:/RPGFARM_MAXGODDYK/MyProject/Saved/Logs/MyProject.log)

Подтверждает более точную картину внутри `Debug_ExperimentalStateMachine`:

- есть ровно **6** ошибок `Could not find a function named "AddToFloatHistoryArray"` в одном compile-проходе;
- рядом идут битые пины `InOutValues`, `NewValue`, `MaxHistoryNum`, что очень похоже на debug/history helper-ноды;
- есть `FStructProperty::Serialize` ошибки по:
  - `CallFunc_MakeVisualLoggerDebugDrawer_ReturnValue`
  - `K2Node_MakeStruct_DrawDebugStringSettings`
  - `K2Node_MakeStruct_DrawDebugLineStyle`

Практический вывод:

- искать нужно не только `Draw Debug String`, но и связанные с ним debug/history ноды;
- с высокой вероятностью там висит один debug draw остров + шесть вызовов `AddToFloatHistoryArray`, завязанных на history-переменные вроде `PawnSpeedHistory`, `MoveData_Speed_History`, `Phase_History`, `Contact_L_History`, `Contact_R_History`, `Enable_Warping_History`.

#### Что именно было видно в редакторе

Слева в `My Blueprint` пользователь уже показывал разделы:

- `SM Transition Debug Events`
- `Debug_ExperimentalStateMachine`
- истории:
  - `TransitionHistory`
  - `PawnSpeedHistory`
  - `MoveData_Speed_History`
  - `Phase_History`
  - `Contact_L_History`
  - `Contact_R_History`
  - `Enable_Warping_History`

Вероятнее всего, stale debug draw сидит именно в:

- `Debug_ExperimentalStateMachine`
- или в связанных transition debug event branches

#### Главное для следующей модели

Нужно не "чинить locomotion", а **вырезать остаток debug draw ветки** в `SandboxCharacter_CMC_ABP`.

## 7. Что уже сделано пользователем в редакторе

Пользователь вручную:

- перепривязал `BP_MyThifCatcher_Sandbox` на `ThifCatcherSandboxBase`;
- поставил `VisualOverride -> BP_OurCharacter`;
- вручную чистил debug-функции в `BFL_HelpfulFunctions`;
- добился успешной компиляции `BFL_HelpfulFunctions`;
- уже проверял и компилировал `AC_TraversalLogic`.

## 8. Что следующей модели делать дальше

### Шаг 1. Дочистить `SandboxCharacter_CMC_ABP`

Открыть:

- [SandboxCharacter_CMC_ABP.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/Blueprints/SandboxCharacter_CMC_ABP.uasset)

Потом:

1. Найти и удалить остаточный debug блок.
2. Смотреть в:
   - `Debug_ExperimentalStateMachine`
   - `SM Transition Debug Events`
3. Удалять только:
   - `Draw Debug String`
   - `Make Visual Logger Debug Drawer`
   - `Make Struct`-ноды для `DrawDebugStringSettings` / `DrawDebugLineStyle`
   - вызовы `AddToFloatHistoryArray`, если они висят в debug/history ветке
   - связанные только с ними helper-ноды
4. Не трогать:
   - Motion Matching
   - Blend Stack
   - Pose History
   - Offset Root Bone
   - Foot Placement
   - locomotion pose flow

### Шаг 2. После очистки

1. `File -> Refresh All Nodes`
2. `Compile`
3. Если зелёный — `Save`

### Шаг 3. Потом

1. Открыть [BP_MyThifCatcher_Sandbox.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/Blueprints/BP_MyThifCatcher_Sandbox.uasset)
2. `Compile`
3. `Save`

### Шаг 4. После этого

Открыть:

- [Showcase.umap](C:/RPGFARM_MAXGODDYK/MyProject/Content/Namaqualand/Levels/Showcase.umap)

Проверить:

- спавнится ли hybrid pawn;
- работает ли sample locomotion;
- виден ли именно `BP_OurCharacter`;
- жива ли gameplay-логика пользователя.

## 9. Что точно НЕ нужно делать дальше

- не возвращать `GM_Sandbox` как финальный рабочий путь;
- не строить финальную игру вокруг sample UI;
- не тащить лишних sample персонажей как основного героя;
- не удалять working helper-функции из `BFL_HelpfulFunctions`;
- не трогать warning'и `Steering / Foot Placement / Offset Root Bone` как будто это compile error.

## 10. Самое важное кратко

На момент передачи:

- `BFL_HelpfulFunctions` — **зелёный**
- `AC_TraversalLogic` — **зелёный**
- `AC_VisualOverrideManager` — **зелёный**
- `BP_MyThifCatcher_Sandbox` — уже **reparented** и уже указывает `VisualOverride -> BP_OurCharacter`
- **единственный реальный оставшийся блокер**: `SandboxCharacter_CMC_ABP`

То есть следующая модель должна начинать именно с:

- [SandboxCharacter_CMC_ABP.uasset](C:/RPGFARM_MAXGODDYK/MyProject/Content/Blueprints/SandboxCharacter_CMC_ABP.uasset)

и искать в нём последний stale debug draw branch.
