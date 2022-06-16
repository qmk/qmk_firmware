/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file	src/gwin/gwin_textedit.h
 * @brief	GWIN textedit widget header file
 *
 * @defgroup TextEdit TextEdit
 * @ingroup Widgets
 *
 * @brief		Widget that accepts text input.
 *
 * @note		Due to the modularity of the @p GINPUT module, the text input can either come from a real physical
 *				keyboard or from a vritual on-screen keyboard such as the @p KeyboardWidget.
 *
 * @pre			GFX_USE_GDISP must be set to GFXON in your gfxconf.h
 * @pre			GFX_USE_GWIN must be set to GFXON in your gfxconf.h
 * @pre			GDISP_NEED_TEXT must be set to GFXON in your gfxconf.h
 * @pre			GWIN_NEED_TEXTEDIT must be set to GFXON in your gfxconf.h
 * @pre			The fonts you want to use must be enabled in your gfxconf.h
 *
 * @{
 */

#ifndef _GWIN_TEXTEDIT_H
#define _GWIN_TEXTEDIT_H

// This file is included within "src/gwin/gwin_widget.h"

// A TextEdit widget
typedef struct GTexteditObject {
	GWidgetObject	w;

	char*			textBuffer;
	gMemSize		maxSize;
	gU16		cursorPos;
} GTexteditObject;

/**
 * @brief				Create a TextEdit widget
 * @details				A TextEdit widget is a rectangular box which allows the user to input data through a keyboard.
 *						The keyboard can either be a physical one or a virtual on-screen keyboard as the keyboard driver
 *						is abstracted through the GINPUT module.
 *
 * @param[in] g			The GDisplay on which the textedit should be displayed
 * @param[in] wt		The TextEdit structure to initialise. If this is NULL, the structure is dynamically allocated.
 * @param[in] pInit		The initialisation parameters to use.
 * @param[in] maxSize	The maximum number of characters the TextEdit widget can hold. (0 means unlimited).
 *
 * @return				NULL if there is no resultant drawing area, otherwise the widget handle.
 *
 * @note				If the initial text set is larger than maxSize then the text is truncated at maxSize characters.
 * @api
 */
GHandle gwinGTexteditCreate(GDisplay* g, GTexteditObject* wt, GWidgetInit* pInit, gMemSize maxSize);
#define gwinTexteditCreate(wt, pInit, maxSize)			gwinGTexteditCreate(GDISP, wt, pInit, maxSize)

/**
 * @brief				Send a special key to the textedit such as GKEY_LEFT, GKEY_RIGHT, GKEY_HOME, GKEY_END
 *
 * @param[in] gh		The window handle (must be a textedit window)
 * @param[in] key		The special key to send.
 * @pre					Requires GINPUT_NEED_KEYBOARD or GWIN_NEED_KEYBOARD to be on
 * @api
 */
void gwinTextEditSendSpecialKey(GHandle gh, gU8 key);

/**
 * @brief				Send a normal utf8 character to the textedit
 *
 * @param[in] gh		The window handle (must be a textedit window)
 * @param[in] pkey		The pointer to the utf8 character to send.
 * @param[in] len		The length of the utf8 character in bytes.
 * @note				This must ONLY be called with a single utf8 character at a time. Don't attempt to
 *						send a string of characters in the one call.
 * @note				Characters are interpreted as if they came directly from a keyboard ie a backspace
 *						character will perform the backspace operation, a tab will send the focus to the next
 *						control etc.
 * @pre					Requires GINPUT_NEED_KEYBOARD or GWIN_NEED_KEYBOARD to be on
 * @api
 */
void gwinTextEditSendKey(GHandle gh, char *pkey, unsigned len);

/**
 * @defgroup Renderings_Textedit Renderings
 *
 * @brief				Built-in rendering functions for the textedit widget.
 *
 * @details				These function may be passed to @p gwinSetCustomDraw() to get different textedit drawing styles.
 *
 * @note				In your custom textedit drawing function you may optionally call these
 * 						standard functions and then draw your extra details on top.
 * @note				These custom drawing routines don't have to worry about setting clipping as the framework
 * 						sets clipping to the object window prior to calling these routines.
 *
 * @{
 */

/**
 * @brief				The default rendering function for the textedit widget.
 *
 * @param[in] gw		The widget object (must be a button textedit).
 * @param[in] param		A parameter passed in from the user. Ignored by this function.
 *
 * @api
 */
void gwinTexteditDefaultDraw(GWidgetObject* gw, void* param);

/** @} */

#endif // _GWIN_TEXTEDIT_H
/** @} */
