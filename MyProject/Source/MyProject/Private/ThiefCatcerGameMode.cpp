#include "ThiefCatcerGameMode.h"
#include "UObject/ConstructorHelpers.h"

AThiefCatcerGameMode::AThiefCatcerGameMode() : Super()
{
    // вызов FClassFinder
    ConstructorHelpers::FClassFinder<APawn> MainCharacterThiefCatcher(TEXT("/Game/Blueprints/Bp_MyThifCatcher"));

    // Проверка на успешную загрузку
    if (MainCharacterThiefCatcher.Succeeded())
    {
        DefaultPawnClass = MainCharacterThiefCatcher.Class;
    }
}
