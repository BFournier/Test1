// Définition de nouveaux types primitifs.

#pragma once

typedef enum
{
	VECTOR_PRIMITIVE_NONE,
	VECTOR_PRIMITIVE_PIXEL,
	VECTOR_PRIMITIVE_POINT,
	VECTOR_PRIMITIVE_LINE,
	VECTOR_PRIMITIVE_RECTANGLE,
	VECTOR_PRIMITIVE_ELLIPSE,
	TYPE_3DMODEL1,
	TYPE_3DMODEL2,
}   EnumObject;

// stucture de primitive vectorielle générique
typedef struct
{
	EnumObject	type;             		// 1 * 4 = 4  octets
	float				position1[2];	// 2 * 4 = 8  octets
	float				position2[2];	// 2 * 4 = 8  octets
	float				strokeWidth;	// 1 * 4 = 4  octets
	unsigned char		strokeColor[4];	// 4 * 1 = 4  octets
	unsigned char		fillColor[4];   // 4 * 1 = 4  octets
	bool				isFilled;
	int					state;			// 1 * 4 = 4  octets
	float				position[3];	// 3 * 4 = 12 octets
	float				rotation[3];	// 3 * 4 = 12 octets
	float				dimension[3];	// 3 * 4 = 12 octets
}   StructObjectLocator;                //       = 72 octets


