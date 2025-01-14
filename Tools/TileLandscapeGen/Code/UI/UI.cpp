
#include "StandardDef.h"
#include "Interface.h"

#include "UISlider.h"
#include "UICheckbox.h"
#include "UIScrollablePage.h"
#include "UI.h"

#include "../Platform/Platform.h"

int		mwUIPressX = 0;
int		mwUIPressY = 0;
int		mwUIHoverX = 0;
int		mwUIHoverY = 0;

int			mnUIButtonIDPressed = NOTFOUND;
uint32		mulUIButtonIDPressedParam = 0;

UIButtonHandler			mafnUIButtonHandlers[UIBUTTONID_MAX] = 
{
	NULL,
}; 


BOOL		UIIsMouseHover( int X, int Y, int W, int H )
{
	if ( ( mwUIHoverX >= X ) &&
		 ( mwUIHoverX <= X + W ) &&
		 ( mwUIHoverY >= Y ) &&
		 ( mwUIHoverY <= Y + H ) )
	{
		return( TRUE );
	}
	return( FALSE );
}

BOOL		UIIsPressed( int X, int Y, int W, int H )
{
	if ( ( mwUIPressX >= X ) &&
		 ( mwUIPressX <= X + W ) &&
		 ( mwUIPressY >= Y ) &&
		 ( mwUIPressY <= Y + H ) )
	{
		return( TRUE );
	}
	return( FALSE );
}

void		UIRegisterButtonPressHandler( int nButtonID, UIButtonHandler fnButtonHandler )
{
	if ( ( nButtonID >= 0 ) &&
		 ( nButtonID < UIBUTTONID_MAX ) )
	{
		mafnUIButtonHandlers[ nButtonID ] = fnButtonHandler;
	}

}


void		UIButtonDraw( int nButtonID, int nX, int nY, int nWidth, int nHeight, const char* szText, int nMode, uint32 ulParam )
{
int		nTextSize;
int		nTextOffsetY;
uint32	ulButtonMainCol = 0xB0707070;
uint32	ulTextCol = 0xD0F0F0F0;
BOOL	bEnabled = TRUE;

	nTextSize = 14;
	nTextOffsetY = (nHeight - nTextSize) / 2;

	switch( nMode )
	{
	case 1:
		ulButtonMainCol = 0x60606060;
		ulTextCol = 0x60F0F0F0;
		bEnabled = FALSE;
		break;
	case 2:
		ulButtonMainCol = 0xB0901008;
		ulTextCol = 0xE0F0E080;
		break;
	case 0:
	default:
		break;
	}

	InterfaceRect( 0, nX, nY, nWidth, nHeight, ulButtonMainCol );

	if ( bEnabled )
	{
		InterfaceRect( 0, nX, nY, nWidth, 1, 0x60D0D0D0 );
		InterfaceRect( 0, nX, nY, 1, nHeight, 0x60D0D0D0 );
		InterfaceRect( 0, nX, nY + nHeight, nWidth, 1, 0x60202020 );
		InterfaceRect( 0, nX + nWidth, nY, 1, nHeight, 0x60202020 );
	}

	InterfaceSetFontFlags( FONT_FLAG_DROP_SHADOW );
	InterfaceTextCentre( 1, nX + (nWidth/2), nY + nTextOffsetY, szText, ulTextCol, 0 ); 
	InterfaceSetFontFlags( 0 );

	if ( UIIsPressed( nX, nY, nWidth, nHeight ) )
	{
		mnUIButtonIDPressed = nButtonID;
		mulUIButtonIDPressedParam = ulParam;
	}

	if ( UIIsMouseHover( nX, nY, nWidth, nHeight ) )
	{
		PlatformSetMouseOverCursor( TRUE );
	}
	
}

BOOL		UIButtonRegion( int nButtonID, int nX, int nY, int nWidth, int nHeight, uint32 ulParam )
{
	if ( UIIsMouseHover( nX, nY, nWidth, nHeight ) )
	{
		PlatformSetMouseOverCursor( TRUE );
	}

	if ( UIIsPressed( nX, nY, nWidth, nHeight ) )
	{
		mnUIButtonIDPressed = nButtonID;
		mulUIButtonIDPressedParam = ulParam;
		return( TRUE );
	}
	return( FALSE );
}




void		UIUpdate( float fDelta )
{
	mnUIButtonIDPressed = NOTFOUND;
	UIScrollablePageUpdate( fDelta );
	PlatformGetCurrentHoverPosition( &mwUIHoverX, &mwUIHoverY );
}


BOOL		UIOnPress( int X, int Y )
{
	if ( UISliderOnPress( X, Y ) == FALSE )
	{
		mwUIPressX = X;
		mwUIPressY = Y;
	}
	
	UIScrollablePageOnPress( X, Y );

	return( FALSE );
}

BOOL		UIOnRelease( int X, int Y )
{
BOOL	bRet = FALSE;

	if ( UIScrollablePageOnRelease( X, Y ) == 0 )
	{
		if ( ( UISliderOnRelease( X, Y, TRUE ) == FALSE ) &&
			 ( UICheckboxOnRelease( X, Y ) == FALSE ) )
		{
			if ( mnUIButtonIDPressed != NOTFOUND )
			{
				if ( mafnUIButtonHandlers[ mnUIButtonIDPressed ] != NULL )
				{
					mafnUIButtonHandlers[mnUIButtonIDPressed]( mnUIButtonIDPressed, mulUIButtonIDPressedParam );
				}

				 mnUIButtonIDPressed = NOTFOUND;
				 bRet = TRUE;
			}
		}
		else
		{
			bRet = TRUE;
		}
	}
	else
	{
		UISliderOnRelease( X, Y, FALSE );
		bRet = TRUE;
	}

	mwUIPressX = 0;
	mwUIPressY = 0;

	return( bRet );
}
