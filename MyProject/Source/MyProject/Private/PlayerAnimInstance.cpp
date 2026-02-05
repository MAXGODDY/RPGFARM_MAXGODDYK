#include "PlayerAnimInstance.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
    MyCharacter = TryGetPawnOwner();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (MyCharacter != nullptr) // проверка на nullptr
    {
        Speed = MyCharacter->GetVelocity().Size();
    }
    else
    {
        Speed = 0.f;
    }
}
