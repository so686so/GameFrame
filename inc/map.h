#ifndef _MAP_H_
#define _MAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>

#include "type.h"
#include "basic.h"

#define DEFAULT_MAP_WIDTH   21
#define DEFAULT_MAP_HEIGHT  21

#define TITLE_HEIGHT        1
#define TAIL_HEIGHT         1

int  getMapWidth( void );
int  getMapHeight( void );
int  getMapArea( void );

BOOL CreateMap( void );
BOOL CreateMapCustomSize( int nWidth, int nHeight );
void DestroyMap( void );

void SetBorderOpt( BOOL bOn );
void SetTitleOpt( BOOL bOn );
void SetTailOpt( BOOL bOn );
BOOL isUseBorder( void );

void ResetMap( void );
void DrawMapBorder( void );
void InitMap( void );

TILE SetMap( COORD coord, TILE newValue );
BOOL SetMap_Row( int nRow, TILE newValue );
BOOL SetMap_Col( int nCol, TILE newValue );

void ShowMap( void );
void ShowMapDot( COORD coord, TILE newValue );

TILE **getMapAddr( void );

void setTitleString( char* string, int nIdx );
void setTailString( char* string, int nIdx );
void setTitleClean( void );
void setTailClean( void );

void ShowPopupMap( void );

#endif