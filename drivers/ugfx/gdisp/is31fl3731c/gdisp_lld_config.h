/*
Copyright 2016 Fred Sundvik <fsundvik@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _GDISP_LLD_CONFIG_H
#define _GDISP_LLD_CONFIG_H

#if GFX_USE_GDISP

/*===========================================================================*/
/* Driver hardware support.                                                  */
/*===========================================================================*/

#    define GDISP_HARDWARE_FLUSH GFXON  // This controller requires flushing
#    define GDISP_HARDWARE_DRAWPIXEL GFXON
#    define GDISP_HARDWARE_PIXELREAD GFXON
#    define GDISP_HARDWARE_CONTROL GFXON

#    define GDISP_LLD_PIXELFORMAT GDISP_PIXELFORMAT_GRAY256

#endif /* GFX_USE_GDISP */

#endif /* _GDISP_LLD_CONFIG_H */
