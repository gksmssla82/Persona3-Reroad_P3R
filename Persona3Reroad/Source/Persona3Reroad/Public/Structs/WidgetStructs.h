// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PaperSprite.h"
#include "Components/Image.h"
#include "WidgetStructs.generated.h"


//FSprite2D
USTRUCT(BlueprintType)
struct FSprite2D
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Sprites")
	TObjectPtr<UPaperSprite> FrontSprite;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	TObjectPtr<UPaperSprite> BackSprite;
};


//FUImage2D
USTRUCT(BlueprintType)
struct FUImage2D
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FUImage2D")
	TObjectPtr<UImage> FrontImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FUImage2D")
	TObjectPtr<UImage> BackImage;

	FUImage2D()
		: FrontImage(nullptr)
		  , BackImage(nullptr)
	{
	}

	FUImage2D(const TObjectPtr<UImage>& InFrontImage, const TObjectPtr<UImage>& InBackImage)
		: FrontImage(InFrontImage)
		  , BackImage(InBackImage)
	{
	}

	void SetMemberFromSprite2D(const FSprite2D* Sprite2D) const
	{
		if (UPaperSprite* MakeFrontSprite = Sprite2D->FrontSprite)
		{
			FrontImage->SetBrushResourceObject(MakeFrontSprite);
		}
		if (UPaperSprite* MakeBackSprite = Sprite2D->BackSprite)
		{
			BackImage->SetBrushResourceObject(MakeBackSprite);
		}
	}
};

//FUImage3D
USTRUCT(BlueprintType)
struct FUImage3D
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FUImage3D")
	TObjectPtr<UImage> FrontImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FUImage3D")
	TObjectPtr<UImage> LeftImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FUImage3D")
	TObjectPtr<UImage> RightImage;

	FUImage3D()
		: FrontImage(nullptr)
		  , LeftImage(nullptr)
		  , RightImage(nullptr)
	{
	}

	FUImage3D(const TObjectPtr<UImage>& InFrontImage,
	          const TObjectPtr<UImage>& InLeftImage,
	          const TObjectPtr<UImage>& InRightImage)
		: FrontImage(InFrontImage)
		  , LeftImage(InLeftImage)
		  , RightImage(InRightImage)
	{
	}
};
