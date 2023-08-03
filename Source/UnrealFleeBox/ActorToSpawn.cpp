// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorToSpawn.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AActorToSpawn::AActorToSpawn()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    //Creating our Default Components
    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));

    //Attaching the Components and setting physics
    SphereComp->SetupAttachment(RootComponent);
    SphereComp->SetSimulatePhysics(true);
    SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    StaticMeshComp->AttachToComponent(SphereComp,FAttachmentTransformRules::KeepRelativeTransform);

    //Setting the Sphere radius to be of a smaller size in line with the Static Mesh.
    SphereComp->SetSphereRadius(96.0f);

    //Setting the Static Mesh Scale and Location to fit the radius of the Sphere.
    StaticMeshComp->SetRelativeLocation(FVector(0.0, 0.0, -12.0f));
    StaticMeshComp->SetRelativeScale3D(FVector(1, 1, 1));

    //Using Constructor Helpers to set our Static Mesh Comp with a Sphere Shape.
    static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
    StaticMeshComp->SetStaticMesh(SphereMeshAsset.Object);
    
    // Use a sphere as a simple collision representation
    SphereComp->SetNotifyRigidBodyCollision(true);
    SphereComp->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
    SphereComp->OnComponentHit.AddDynamic(this, &AActorToSpawn::OnCompHit);

    // Set as root component
    RootComponent = SphereComp;
}

// Called when the game starts or when spawned
void AActorToSpawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AActorToSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AActorToSpawn::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Destroy ball if collides with Ledge or character
    if (OtherActor->GetName().Contains("Ledge") || OtherComp->GetName() == "CollisionCylinder") {
        this->Destroy();
    }
    
    // Change to Game Over screen
    if (OtherComp->GetName() == "CollisionCylinder") {
        UGameplayStatics::OpenLevel(GetWorld(), "gameover");
    }
}

