/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gwin/gwin_widget.h
 * @brief   GWIN Widgets header file.
 *
 * @defgroup Widget Widget
 * @ingroup Widgets
 *
 * @brief		The basic widget implementation (base class).
 *
 * @details		A widget is a Window that supports interacting with the user
 * 				via an input device such as a mouse or toggle buttons. It is the
 * 				base class for widgets such as buttons and sliders.
 *
 * @pre		GFX_USE_GWIN and GWIN_NEED_WIDGET must be set to GFXON in your gfxconf.h
 * @{
 */

#ifndef _GWIDGET_H
#define _GWIDGET_H

/* This file is included within "src/gwin/gwin.h" */

// Forward definition
struct GWidgetObject;

/**
 * @brief	The GColorSet structure
 * @{
 */
typedef struct GColorSet {
	gColor			text;				/**< The text color */
	gColor			edge;				/**< The edge color */
	gColor			fill;				/**< The fill color */
	gColor			progress;			/**< The color of progress bars */
} GColorSet;
/** @} */

/**
 * @brief		The GWidgetStyle structure
 * @details		A GWidgetStyle is a set of colors that together form a "style".
 * 				These colors should not be confused with the GWindow foreground
 * 				and background colors which are used for drawing operations.
 * @{
 */
typedef struct GWidgetStyle {
	gColor			background;			/**< The window background color */
	gColor			focus;				/**< The color when a widget is focused */
	GColorSet		enabled;			/**< The colors when enabled */
	GColorSet		disabled;			/**< The colors when disabled */
	GColorSet		pressed;			/**< The colors when pressed */
} GWidgetStyle;
/** @} */

/**
 * @brief	We define a couple of GWidgetStyle's that you can use in your
 * 			application. The Black style is the default style if you don't
 * 			specify one.
 * @note	BlackWidgetStyle means that it is designed for a Black background.
 * 			Similarly WhiteWidgetStyle is designed for a White background.
 * @{
 */
extern const GWidgetStyle BlackWidgetStyle;
extern const GWidgetStyle WhiteWidgetStyle;
/** @} */

/**
 * @brief	Defines a custom drawing function for a widget
 */
typedef void (*CustomWidgetDrawFunction)(struct GWidgetObject *gw, void *param);

/**
 * @brief	Defines a the type of a tag on a widget
 */
typedef gU16	WidgetTag;

/**
 * @brief	The structure to initialise a widget.
 *
 * @note	Some widgets may have extra parameters.
 * @note	If you create this structure on the stack, you should always memset
 * 			it to all zero's first in case a future version of the software
 * 			add's extra fields. Alternatively you can use @p gwinWidgetClearInit()
 * 			to clear it.
 * @note	The text element must be static string (not stack allocated). If you want to use
 * 			a dynamic string (eg a stack allocated string) use NULL for this member and then call
 * 			@p gwinSetText() with useAlloc set to gTrue.
 *
 * @{
 */
typedef struct GWidgetInit {
	GWindowInit					g;						/**< The GWIN initializer */
	const char *				text;					/**< The initial text */
	CustomWidgetDrawFunction	customDraw;				/**< A custom draw function - use NULL for the standard */
	void *						customParam;			/**< A parameter for the custom draw function (default = NULL) */
	const GWidgetStyle *		customStyle;			/**< A custom style to use - use NULL for the default style */
	#if GWIN_WIDGET_TAGS || defined(__DOXYGEN__)
		WidgetTag				tag;					/**< The tag to associate with the widget */
	#endif
} GWidgetInit;
/** @} */

/**
 * @brief	The GWIN Widget structure
 * @note	A widget is a GWIN window that accepts user input.
 * 			It also has a number of other properties such as its ability
 * 			to redraw itself (a widget maintains drawing state).
 * @note	Do not access the members directly. Treat it as a black-box and use the method functions.
 *
 * @{
 */
typedef struct GWidgetObject {
	GWindowObject				g;					/**< This is still a GWIN */
	const char *				text;				/**< The widget text */
	CustomWidgetDrawFunction	fnDraw;				/**< The current draw function */
	void *						fnParam;			/**< A parameter for the current draw function */
	const GWidgetStyle *		pstyle;				/**< The current widget style colors */
	#if GWIN_WIDGET_TAGS || defined(__DOXYGEN__)
		WidgetTag				tag;				/**< The widget tag */
	#endif
} GWidgetObject;
/** @} */

/**
 * A comment/rant on the above structure:
 * We would really like the GWindowObject member to be anonymous. While this is
 * allowed under the C11, C99, GNU and various other standards which have been
 * around forever - compiler support often requires special flags e.g
 * gcc requires the -fms-extensions flag (no wonder the language and compilers have
 * not really progressed in 30 years). As portability is a key requirement
 * we unfortunately won't use this useful feature in case we get a compiler that
 * won't support it even with special flags.
 */

/**
 * @brief	A Generic GWIN Event
 * @note	All gwin windows when sending events will either use this structure or a
 * 			structure that is 100% compatible except that it may also have extra fields.
 * @note	There are currently no GEventGWin listening flags - use 0 as the flags to @p gwinAttachListener()
 *
 * @{
 */
typedef struct GEventGWin {
	GEventType		type;						/**< The type of this event */
	GHandle			gwin;						/**< The gwin window handle */
	#if GWIN_NEED_WIDGET && GWIN_WIDGET_TAGS
		WidgetTag	tag;						/**< The tag (if applicable) */
	#endif
} GEventGWin;
/** @} */

/**
 * @brief	The list of predefined GWIN events.
 * @note	The definition of an event type does not mean it is always sent. For example,
 * 			close events are sent by Frame windows but by little else. They are normally
 * 			only sent if there is a specific reason that the event should be sent.
 * @{
 */
#define GEVENT_GWIN_OPEN		(GEVENT_GWIN_FIRST+0x00)
#define GEVENT_GWIN_CLOSE		(GEVENT_GWIN_FIRST+0x01)
#define GEVENT_GWIN_RESIZE		(GEVENT_GWIN_FIRST+0x02)
#define GEVENT_GWIN_CTRL_FIRST	(GEVENT_GWIN_FIRST+0x40)
/** @} */

/**
 * @brief	Clear a GWidgetInit structure to all zero's
 * @note	This function is provided just to prevent problems
 * 			on operating systems where using memset() causes issues
 * 			in the users application.
 *
 * @param[in] pwi	The GWidgetInit structure to clear
 *
 * @api
 */
void gwinWidgetClearInit(GWidgetInit *pwi);

/**
 * @brief   Set the default style for widgets created hereafter.
 *
 * @param[in] pstyle	The default style. Passing NULL uses the system compiled style.
 * @param[in] updateAll	If gTrue then all existing widgets that are using the current default style
 * 						will be updated to use this new style. Widgets that have custom styles different
 * 						from the default style will not be updated.
 *
 * @note	The style must be allocated statically (not on the stack) as only the pointer is stored.
 *
 * @api
 */
void gwinSetDefaultStyle(const GWidgetStyle *pstyle, gBool updateAll);

/**
 * @brief   Get the current default style.
 *
 * @return	The current default style.
 *
 * @api
 */
const GWidgetStyle *gwinGetDefaultStyle(void);

/**
 * @brief   Set the text of a widget.
 *
 * @param[in] gh		The widget handle
 * @param[in] text		The text to set. This must be a constant string unless useAlloc is set.
 * @param[in] useAlloc	If gTrue the string specified will be copied into dynamically allocated memory.
 *
 * @note				The widget is automatically redrawn
 * @note				Non-widgets will ignore this call.
 *
 * @api
 */
void gwinSetText(GHandle gh, const char *text, gBool useAlloc);

/**
 * @brief   Get the text of a widget.
 * @return	The widget text or NULL if it isn't a widget
 *
 * @param[in] gh		The widget handle
 *
 * @api
 */
const char *gwinGetText(GHandle gh);

#if (GFX_USE_GFILE && GFILE_NEED_PRINTG && GFILE_NEED_STRINGS) || defined(__DOXYGEN__)
	/**
	 * @brief   Set the text of a widget using a printf style format.
	 * @pre		GFX_USE_GFILE, GFILE_NEED_PRINTG and GFILE_NEED_STRINGS must all be GFXON
	 *
	 * @param[in] gh		The widget handle
	 * @param[in] fmt		The format string using a printf/g syntax. See @p vsnprintg()
	 * @param[in] ...		The printg paramters.
	 *
	 * @note				The widget is automatically redrawn
	 * @note				Non-widgets will ignore this call.
	 * @note				The memory for the text is always allocated by this function.
	 *
	 * @api
	 */
	void gwinPrintg(GHandle gh, const char * fmt,...);
#endif

/**
 * @brief	Check whether a handles is a widget handle or not
 *
 * @param[in] gh		The handle to check.
 *
 * @return	gTrue if the passed handle is a widget handle. gFalse otherwise.
 *
 * @api
 */
gBool gwinIsWidget(GHandle gh);

#if GWIN_WIDGET_TAGS || defined(__DOXYGEN__)
	/**
	 * @brief   Set the tag of a widget.
	 *
	 * @param[in] gh		The widget handle
	 * @param[in] tag		The tag to set.
	 *
	 * @note				Non-widgets will ignore this call.
	 *
	 * @pre					Requires GWIN_WIDGET_TAGS to be GFXON
	 *
	 * @api
	 */
	void gwinSetTag(GHandle gh, WidgetTag tag);

	/**
	 * @brief   Get the tag of a widget.
	 * @return	The widget tag value (or 0 if it is not a widget)
	 *
	 * @param[in] gh		The widget handle
	 *
	 * @pre					Requires GWIN_WIDGET_TAGS to be GFXON
	 *
	 * @api
	 */
	WidgetTag gwinGetTag(GHandle gh);
#endif

/**
 * @brief   Set the style of a widget.
 *
 * @param[in] gh		The widget handle
 * @param[in] pstyle	The style to set. This must be a static structure (not allocated on a transient stack).
 * 						Use NULL to reset to the default style.
 *
 * @note				The widget is automatically redrawn
 * @note				Non-widgets will ignore this call.
 *
 * @api
 */
void gwinSetStyle(GHandle gh, const GWidgetStyle *pstyle);

/**
 * @brief   Get the style of a widget.
 * @return	The widget style or NULL if it isn't a widget
 *
 * @param[in] gh		The widget handle
 *
 * @api
 */
const GWidgetStyle *gwinGetStyle(GHandle gh);

/**
 * @brief   Set the routine to perform a custom widget drawing.
 *
 * @param[in] gh		The widget handle
 * @param[in] fn		The function to use to draw the widget
 * @param[in] param		A parameter to pass to the widget drawing function
 *
 * @note				The widget is not automatically redrawn. Call @p gwinDraw() to redraw the widget.
 * @note				Non-widgets will ignore this call.
 *
 * @api
 */
void gwinSetCustomDraw(GHandle gh, CustomWidgetDrawFunction fn, void *param);

/**
 * @brief	Attach a Listener to listen for widget events
 * @return	gTrue on success
 *
 * @param[in] pl		The listener
 *
 * @api
 */
gBool gwinAttachListener(GListener *pl);

#if (GFX_USE_GINPUT && GINPUT_NEED_MOUSE) || defined(__DOXYGEN__)
	gBool DEPRECATED("This call can now be removed. Attaching the mouse to GWIN is now automatic.") gwinAttachMouse(gU16 instance);
#endif

#if (GFX_USE_GINPUT && GINPUT_NEED_TOGGLE) || defined(__DOXYGEN__)
	/**
	 * @brief	Attach a toggle to a widget
	 * @return	gTrue on success
	 *
	 * @param[in] gh		The widget handle
	 * @param[in] role		The function the toggle will perform for the widget
	 * @param[in] instance	The toggle instance
	 *
	 * @note		See the documentation on the specific widget to see the possible
	 * 				values for the role parameter. If it is out of range, this function
	 * 				will return gFalse
	 *
	 * @api
	 */
	gBool gwinAttachToggle(GHandle gh, gU16 role, gU16 instance);
	/**
	 * @brief	Detach a toggle from a widget
	 * @return	gTrue on success
	 *
	 * @param[in] gh		The widget handle
	 * @param[in] role		The function the toggle will perform for the widget
	 *
	 * @note		See the documentation on the specific widget to see the possible
	 * 				values for the role parameter. If it is out of range, this function
	 * 				will return gFalse
	 *
	 * @api
	 */
	gBool gwinDetachToggle(GHandle gh, gU16 role);
#endif

#if (GFX_USE_GINPUT && GINPUT_NEED_DIAL) || defined(__DOXYGEN__)
	/**
	 * @brief	Attach a toggle to a widget
	 * @return	gTrue on success
	 *
	 * @param[in] gh		The widget handle
	 * @param[in] role		The function the dial will perform for the widget
	 * @param[in] instance	The dial instance
	 *
	 * @note		See the documentation on the specific widget to see the possible
	 * 				values for the role parameter. If it is out of range, this function
	 * 				will return gFalse
	 *
	 * @api
	 */
	gBool gwinAttachDial(GHandle gh, gU16 role, gU16 instance);
#endif

#if (GFX_USE_GINPUT && GINPUT_NEED_KEYBOARD) || GWIN_NEED_KEYBOARD || defined(__DOXYGEN__)
	/**
	 * @brief	Set the keyboard focus to a specific window
	 * @return	Returns gTrue if the focus could be set to that window
	 *
	 * @param[in] gh	The window
	 *
	 * @note	Passing NULL will remove the focus from any window.
	 * @note	Only visible enabled widgets are capable of getting the focus.
	 *
	 * @api
	 */
	gBool gwinSetFocus(GHandle gh);

	/**
	 * @brief	Get the widget that is currently in focus
	 *
	 * @details	The widget that is currently in focus is the widget that
	 *			receives mouse and keyboard events.
	 *
	 * @return	The handle of the widget that is currently in focus. May be NULL.
	 *
	 * @api
	 */
	GHandle gwinGetFocus(void);
#else
	#define gwinGetFocus()		(0)
	#define gwinSetFocus(gh)	(gFalse)
#endif

/* Include extra widget types */
#if GWIN_NEED_BUTTON || defined(__DOXYGEN__)
	#include "gwin_button.h"
#endif

#if GWIN_NEED_SLIDER || defined(__DOXYGEN__)
	#include "gwin_slider.h"
#endif

#if GWIN_NEED_CHECKBOX || defined(__DOXYGEN__)
	#include "gwin_checkbox.h"
#endif

#if GWIN_NEED_RADIO || defined(__DOXYGEN__)
	#include "gwin_radio.h"
#endif

#if GWIN_NEED_LABEL || defined(__DOXYGEN__)
	#include "gwin_label.h"
#endif

#if GWIN_NEED_LIST || defined(__DOXYGEN__)
	#include "gwin_list.h"
#endif

#if GWIN_NEED_PROGRESSBAR || defined(__DOXYGEN__)
	#include "gwin_progressbar.h"
#endif

#if GWIN_NEED_KEYBOARD || defined(__DOXYGEN__)
	#include "gwin_keyboard.h"
#endif

#if GWIN_NEED_TEXTEDIT || defined(__DOXYGEN__)
	#include "gwin_textedit.h"
#endif

#endif /* _GWIDGET_H */
/** @} */
