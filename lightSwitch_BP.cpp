// Fill out your copyright notice in the Description page of Project Settings.


#include "lightSwitch_BP.h"

#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AlightSwitch_BP::AlightSwitch_BP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DesiredIntensity = 5000.0f;

	PointLight1 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
	PointLight1->Intensity = DesiredIntensity;
	PointLight1->SetVisibility(true);
	RootComponent = PointLight1;

	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"));
	Sphere1-> InitSphereRadius(250.0f);
	Sphere1->SetupAttachment(RootComponent);
	Sphere1->SetHiddenInGame(false);


	Sphere1-> OnComponentBeginOverlap.AddDynamic(this, &AlightSwitch_BP::OnOverlapBegin);
	Sphere1-> OnComponentEndOverlap.AddDynamic(this, &AlightSwitch_BP::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AlightSwitch_BP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AlightSwitch_BP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//Turn light on when overlapped
void AlightSwitch_BP::OnOverlapBegin_Implementation(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && (OtherActor!= this) && OtherComp)
	{
		ToggleLight();
	}
}
//Turn light off when not overlapped
void AlightSwitch_BP::OnOverlapEnd_Implementation(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
					   class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}

void AlightSwitch_BP::ToggleLight()
{
	PointLight1->ToggleVisibility();
}